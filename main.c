#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>   
#include<math.h>
#include "combate.h"
#include "personaje.h"
#include "historial.h"

int main(void)
{
    srand(time(NULL));
    bool exito_primer_turno = true;
    int jugador_muerto = NINGUNO; 
    size_t num_personaje_human = 0;
    size_t num_personaje_maquin = 0;
    size_t num_turnos = 1;
    size_t cant_personajes = 3;
    historia_turnos_t *turnos = NULL;
    personaje_t *personajes = NULL;
    personaje_t personaje_random = {0};
    jugador_t *jugador = NULL;
    jugador_t *maquina = NULL;
    turno_t turno_inicial = {0};
    

    turnos = crear_historial_turnos();
    if(turnos == NULL)
    {
        return EXIT_FAILURE;
    }

    personajes = crear_arreglo_personajes(cant_personajes);
    if(personajes == NULL)
    {
        historial_destruir(&turnos);
        return EXIT_FAILURE;
    }

    for(size_t i = 0; i < cant_personajes; i++)
    {
        personaje_random = crear_personaje_random();
        personajes[i] = personaje_random; 
    }
    fprintf(stdout, "Juego de combate, jugador vs IA\n");
    fprintf(stdout, "Se le mostraran 3 personajes. Elija el numero del personaje");
    fprintf(stdout, " que desea usar.\n");
    imprimir_separador_sig_igual();

    while((num_personaje_human <= 0) || (num_personaje_human > cant_personajes))
    {
        for(size_t i = 0; i < cant_personajes; i++)
        {
            fprintf(stdout, "\tPersonaje %zu:\n", i + 1);
            imprimir_personaje(&personajes[i]);
            fprintf(stdout, "\n");
            imprimir_separador_sig_igual();
        }

        if(scanf("%zu", &num_personaje_human) != 1)
        {
            fprintf(stdout, "Error, formato incorrecto. Solo numeros por favor.");
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
    
    jugador = crear_jugador_dinamico(&personajes[num_personaje_human - 1]);
    fprintf(stdout, "Personaje numero %zu correctamente elegido\n", num_personaje_human);
    fprintf(stdout, "IA eligiendo personaje de manera random...\n");
    fprintf(stdout, "IA ha elegido un personaje!\n");

    num_personaje_maquin = rand() % cant_personajes;
    maquina = crear_jugador_dinamico(&personajes[num_personaje_maquin]);

    fprintf(stdout, "Estadisticas del personaje elegido por la IA:\n\n");
    imprimir_personaje(&personajes[num_personaje_maquin]);

    turno_inicial = llenar_struct_turno(jugador, maquina, 0, NINGUNA, NINGUNA);
    exito_primer_turno = historial_agregar_fin(turnos, &turno_inicial);

    if(exito_primer_turno == false)
    {
        fprintf(stderr, "Error critico al agregar turno al historial. Finalizando programa");
        return EXIT_FAILURE;
    }

    for(size_t i = 0; jugador_muerto == NINGUNO; i++)
    {
        bool exito_insert_turn = true;
        static int ataques_seguidos = 0;
        int accion_jugador = 0;
        int accion_maquina = 0;
        int verif_accion_jug = accion_jugador;
        accion_jugador_t acciones_jugador = {0};
        accion_jugador_t acciones_maquina = {0};
        turno_t turno_temp = {0};
        turno_t *ptr_ultimo_turno = NULL;

        if(i == 0)
        {
           imprimir_separador_sig_igual();
           fprintf(stdout, "Inicio del juego\n");
           fprintf(stdout, "Estado inicial de los jugadores:\n\n");
           imprimir_turno(&turno_inicial);
        }
        else
        {

            ptr_ultimo_turno = historial_ultim_turno(turnos);
            imprimir_separador_sig_igual();

            fprintf(stdout, "Estadisticas luego del turno numero %zu:\n", i);
            imprimir_turno(ptr_ultimo_turno);
            fprintf(stdout, "Comienzo del turno %zu\n", i + 1);
            
            imprimir_separador_sig_igual();
        }

        mostrar_opciones_accion();
        verif_lect_correcta_accion(&accion_jugador);

        while(verif_accion_jug != accion_jugador)
        {
            verif_accion_jug = verific_valid_accion_jug(jugador, accion_jugador, ataques_seguidos);
            if(verif_accion_jug == RANGO_INVALIDO)
            {
                fprintf(stdout, "Rango de seleccion invalido. Intente nuevamente\n");
                fprintf(stdout, "Reiteracion de las opciones:\n");
                mostrar_opciones_accion();
                verif_lect_correcta_accion(&accion_jugador);
            }
            else
            if(verif_accion_jug == DEMASIADOS_ATAQUES)
            {
                fprintf(stdout, "Limite de ataques seguidos (3) alcanzado. Seleccione otra opcion\n");
                fprintf(stdout, "Reiteracion de las opcioens:");
                mostrar_opciones_accion();
                verif_lect_correcta_accion(&accion_jugador);
            }
            else
            if(verif_accion_jug == ENERGIA_INSUFIC)
            {
                fprintf(stdout, "Energia insuficiente para atacar. Seleccione otra opcion\n");
                mostrar_opciones_accion();
                verif_lect_correcta_accion(&accion_jugador);
            }
        }

        if (accion_jugador == ATAQUE)
        {
            ataques_seguidos++;
            fprintf(stdout, "(Ataque %d de 3 seguidos)\n", ataques_seguidos);
        }
        else    
        {
            ataques_seguidos = 0;
        }

        fprintf(stdout, "Accion numero %d elegida correctamente\n", accion_jugador);
        fprintf(stdout, "IA eligiendo accion random\n\n");
        
        accion_maquina = decision_accion_maquina(&jugador, &maquina, accion_jugador); 
        fprintf(stdout, "IA elige la opcion numero %d\n", accion_maquina);

        actualizar_defensa_por_accion(jugador, accion_jugador);
        actualizar_defensa_por_accion(maquina, accion_maquina);

        resolucion_acciones(jugador, maquina, accion_jugador, accion_maquina, &acciones_jugador, 
        &acciones_maquina);

        modificar_jugador(&jugador, &acciones_jugador, accion_jugador, accion_maquina);
        modificar_jugador(&maquina, &acciones_maquina, accion_maquina, accion_jugador);
        
        turno_temp = llenar_struct_turno(jugador, maquina, i + 1, accion_jugador, accion_maquina);
        exito_insert_turn = historial_agregar_fin(turnos, &turno_temp);
        if(exito_insert_turn == false)
        {
            fprintf(stderr, "Error critico al pedir memoria para el nuevo turno. Finalizado programa");
            return EXIT_FAILURE;
        }
        jugador_muerto = determ_jug_muerto(jugador, maquina);
    }

    fprintf(stdout, "\nJuego terminado!\n");
    
    historial_destruir(&turnos);
    destruir_memoria((void **)&personajes);

    return EXIT_SUCCESS;
}