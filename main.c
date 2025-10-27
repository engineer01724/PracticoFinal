#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>   
#include<math.h>
#include "combate.h"

int main(void)
{
    srand(time(NULL));
    int suma_energia = 15;
    int resta_energia = 20;
    int num_personaje_human = 0;
    int num_personaje_maquin = 0;
    size_t num_turnos = 1;
    size_t cant_personajes = 3;
    bool end_of_game = false;
    turno_t *turnos = NULL;
    personaje_t *personajes = NULL;
    personaje_t personaje_random;
    jugador_t jugador;
    jugador_t maquina;

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

        if(scanf("%d", &num_personaje_human) != 1)
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
    fprintf(stdout, "Personaje correctamente elegido\n");
    fprintf(stdout, "IA eligiendo personaje de manera random...\n");

    num_personaje_maquin = rand() % cant_personajes + 1.
    maquina.personaje = personajes[num_personaje_maquin];

    fprintf(stdout, "Estadisticas del personaje elegido por la IA:\n");
    imprimir_personaje(&maquina.personaje);

    turnos[0] = llenar_struct_turno(jugador, maquina, 0, NINGUNA, NINGUNA);
    imprimir_turno(&turnos[0]);

    for(size_t i = 0; end_of_game == false; i++)
    {
        int accion_jugador = 0;
        int accion_maquina = 0;
        ataque_t ataque_jug = {0};
        ataque_t ataque_maquin = {0};
        defensa_t defensa_jug = {0};
        defensa_t defensa_maquin = {0};
        curar_t curar_jug = {0};
        curar_t curar_maquin = {0};

        if(i == 0)
        {
           fprintf(stdout, "Inicio del juego\n");
           fprintf("Estado inicial de los jugadores:\n");
           imprimir_turno(turnos[0]);
        }
        else
        {
            fprintf(stdout, "Estadisticas luego del turno numero %zu:\n", i);
            imprimir_turno(&turno[i]);
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
            bool maquina_ataque = true;
            case ATAQUE:
                ataque_jug = calcular_ataque(&maquina, &jugador);
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
                break;
            case CURAR:
                curar_jug = curar_jugador(&jugador);   
        }

        switch(accion_maquina)
        {
            case ATAQUE:
                if(maquina_ataque == true)
                {
                    ataque_maquin = calcular_ataque(&jugador, &maquina);
                }
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
            case CURAR:
                curar_maquin = curar_jugador(&maquina);    
        }

        turnos = agregar_turno(turnos, num_turnos, 1);
        if(turnos == NULL)
        {
            fprintf(stderr, "Error critico al agregar nuevo turno. Terminando programa");
            return EXIT_FAILURE;
        }
        
        energia_modificar(&jugador.energia, suma_energia);
        energia_modificar(&jugador.energia, suma_energia);
        
        turnos[num_turnos] = llenar_struct_turno();
        num_turnos++;
    }
    return EXIT_SUCCESS;
}