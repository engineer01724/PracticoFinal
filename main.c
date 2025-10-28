#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>   
#include<math.h>
#include "combate.h"

int main(void)
{
    srand(time(NULL));
    int jugador_muerto = NINGUNO; 
    int suma_energia = 15;
    size_t num_personaje_human = 0;
    size_t num_personaje_maquin = 0;
    size_t num_turnos = 1;
    size_t cant_personajes = 3;
    turno_t *turnos = NULL;
    personaje_t *personajes = NULL;
    personaje_t personaje_random = {0};
    jugador_t jugador = {0};
    jugador_t maquina = {0};

    turnos = crear_arreglo_turnos(1);
    if(turnos == NULL)
    {
        return EXIT_FAILURE;
    }

    personajes = crear_arreglo_personajes(cant_personajes);
    if(personajes == NULL)
    {
        return EXIT_FAILURE;
    }

    for(size_t i = 0; i < cant_personajes; i++)
    {
        personaje_random = crear_personaje_random();
        personajes[i] = personaje_random; 
    }
     
    fprintf(stdout, "Se le mostraran 3 personajes. Elija el numero del personaje");
    fprintf(stdout, " que desea usar.\n");

    while((num_personaje_human <= 0) || (num_personaje_human > cant_personajes))
    {
        for(size_t i = 0; i < cant_personajes; i++)
        {
            fprintf(stdout, "Personaje %zu:\n", i + 1);
            imprimir_personaje(&personajes[i]);
        }

        if(scanf("%zu", &num_personaje_human) != 1)
        {
            fprintf(stderr, "Error, formato incorrecto. Solo numeros por favor.");
            fprintf(stdout, "Listado de las opciones de personajes:\n");
        }
        else
        {
            if((num_personaje_human <= 0) || (num_personaje_human > cant_personajes))
            {
                fprintf(stdout, "Opcion elegida no valida. Intente de nuevo\n");
                fprintf(stdout, "Recuerde los personajes disponibles y sus indices:\n");
            }
        }
    }
    
    jugador.personaje = personajes[num_personaje_human - 1]; 
    jugador.vida = jugador.personaje.vida;
    fprintf(stdout, "Personaje correctamente elegido\n");
    fprintf(stdout, "IA eligiendo personaje de manera random...\n");

    num_personaje_maquin = rand() % cant_personajes + 1;
    maquina.personaje = personajes[num_personaje_maquin];
    maquina.vida = maquina.personaje.vida;

    fprintf(stdout, "Estadisticas del personaje elegido por la IA:\n");
    imprimir_personaje(&maquina.personaje);

    turnos[0] = llenar_struct_turno(&jugador, &maquina, 0, NINGUNA, NINGUNA);
    imprimir_turno(&turnos[0]);

    for(size_t i = 0; jugador_muerto == NINGUNO; i++)
    {
        bool maquina_ataque = true;
        int accion_jugador = 0;
        int accion_maquina = 0;
        ataque_t ataque_jug = {0};
        ataque_t ataque_maquin = {0};
        defensa_t defensa_jug = {0};
        defensa_t defensa_maquin = {0};
        curar_t curar_jug = {0};
        curar_t curar_maquin = {0};
        accion_jugador_t acciones_jugador = {0};
        accion_jugador_t acciones_maquina = {0};

        if(i == 0)
        {
           fprintf(stdout, "Inicio del juego\n");
           fprintf(stdout, "Estado inicial de los jugadores:\n");
           imprimir_turno(&turnos[0]);
        }
        else
        {
            fprintf(stdout, "Estadisticas luego del turno numero %zu:\n", i);
            imprimir_turno(&turnos[i]);
            fprintf(stdout, "Comienzo del turno %zu\n", i + 1);
        }

        fprintf(stdout, "Elija su siguiente accion. Ingrese el numero correspondiente");
        fprintf(stdout, " a la accion deseada\n");

        while((accion_jugador < 1) || (accion_jugador > 3))
        {
            fprintf(stdout, " 1. ATACAR\n 2. DEFENDER\n 3. CURAR\n");
            if(scanf("%d", &accion_jugador) != 1)
            {
                fprintf(stderr, "Error de formato. Por favor solo ingrese numeros.");
                fprintf(stdout, "Intente nuevamente. Reiteracion de las opciones:\n");
            }
            else
            {
                if((accion_jugador < 1) || (accion_jugador > 3))
                {
                    fprintf(stdout, "Seleccion fuera de los limites. Elija de nuevo\n");
                    fprintf(stdout, "Reiteracion de las opciones:\n");
                }
            }
        }

        fprintf(stdout, "Accion elegida correctamente\n");
        fprintf(stdout, "IA eligiendo accion random\n");

        accion_maquina = decision_accion_maquina(&jugador, &maquina);
        
        switch(accion_jugador)
        {
            case ATAQUE:
                ataque_jug = calcular_ataque(&maquina, &jugador);
                acciones_jugador.ataque = ataque_jug;
                acciones_maquina.ataque_rival = ataque_jug;
                break;
            case DEFENSA:
                if(accion_maquina == ATAQUE)
                {
                    ataque_maquin = calcular_ataque(&jugador, &maquina);
                    defensa_jug = calcular_defensa(&jugador, ataque_maquin.danio_causado);
                    maquina_ataque = false;
                }
                else
                {
                    defensa_jug = calcular_defensa(&jugador, 0);
                }
                acciones_jugador.defensa = defensa_jug;
                acciones_maquina.ataque = ataque_maquin;
                break;
            case CURAR:
                curar_jug = curar_jugador(&jugador); 
                jugador.defensa = false;   
                acciones_jugador.curar = curar_jug;
        }
        if((accion_jugador != CURAR) && (jugador.defensa == false))
        {
            jugador.defensa = true;
        }
    
        switch(accion_maquina)
        {
            case ATAQUE:
                if(maquina_ataque == true)
                {
                    ataque_maquin = calcular_ataque(&jugador, &maquina);
                }
                acciones_maquina.ataque = ataque_maquin;
                acciones_jugador.ataque_rival = ataque_maquin;
                break;
            case DEFENSA:
                if(accion_jugador == ATAQUE)
                {
                    defensa_maquin = calcular_defensa(&maquina, ataque_jug.danio_causado);
                }
                else
                {
                    defensa_maquin = calcular_defensa(&maquina, 0);
                }
                acciones_maquina.defensa = defensa_maquin;
                break;
            case CURAR:
                curar_maquin = curar_jugador(&maquina);
                acciones_maquina.curar = curar_maquin;
                maquina.defensa = false;    
        }
        if((accion_maquina != CURAR) && (maquina.defensa == false))
        {
            maquina.defensa = true;
        }
        
        turnos = agregar_turno(turnos, num_turnos, 1);
        if(turnos == NULL)
        {
            fprintf(stderr, "Error critico al agregar nuevo turno. Terminando programa");
            return EXIT_FAILURE;
        }

        modificar_jugador(&jugador, &acciones_jugador, accion_jugador, accion_maquina);
        modificar_jugador(&maquina, &acciones_maquina, accion_maquina, accion_jugador);

        modificar_energia_jugador(&jugador, suma_energia);
        modificar_energia_jugador(&maquina, suma_energia);
        
        turnos[num_turnos] = llenar_struct_turno(&jugador, &maquina, i + 1, accion_jugador, accion_maquina);
        if(turnos[num_turnos].mem_ped_correct == false)
        {
            fprintf(stderr, "Error critico al pedir memoria para el nuevo turno. Finalizadon programa");
            return EXIT_FAILURE;
        }
        num_turnos++;
        jugador_muerto = determ_jug_muerto(&jugador, &maquina);
    }

    fprintf(stdout, "Juego terminado!");

    destruir_memoria((void **)&turnos);
    destruir_memoria((void **)&personajes);

    return EXIT_SUCCESS;
}