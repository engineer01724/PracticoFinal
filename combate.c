#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "combate.h"

turno_t *crear_arreglo_turnos(const size_t tamanio)
{
    turno_t *retorno = NULL;
    retorno = (turno_t *)malloc(tamanio * sizeof(turno_t));
    return retorno;
}

turno_t *agregar_turno(turno_t *arr_turno, size_t cant_actual, size_t cant_agregar)
{
    turno_t *retorno = NULL;
    retorno = (turno_t *)realloc(arr_turno, (cant_actual + cant_agregar);
    * sizeof(turno_t));
    return retorno;
}

personaje_t *crear_arreglo_personajes(const size_t tamanio)
{
    personaje_t *retorno = NULL;
    retorno = (personaje_t *)realloc(arr_turno, (cant_actual + cant_agregar) 
    * sizeof(personaje_t));
    return retorno;
}

void destruir_memoria(void **ptr_mem)
{
    if((*ptr_mem != NULL) && (ptr_mem != NULL))
    {
        free(*ptr_mem);
        *ptr_mem = NULL;
    }  
}

void imprimir_personaje(const personaje_t *const personaje)
{
    fprintf(stdout, "Vida: %d\n", personaje->vida);
    fprintf(stdout, "Energia: %d\n", personaje->energia);
    fprintf(stdout, "Ataque: %d\n", personaje->ataque);
    fprintf(stdout, "Curacion: %d puntos de vida\n", personaje->curacion);
    fprintf(stdout, "Defensa: %.1f \n", personaje->red_danio);
}

char *accion_a_cadena(int accion_jugador)
{   
    char *accion_jug = NULL;

    switch(accion_jugador)
    {
        case ATAQUE:
            accion_jug = "ATAQUE";
            break;
        case DEFENSA: 
            accion_jug = "DEFENSA";
        case CURAR:
            accion_jug = "CURAR";
        default:
            accion_jug = "DESCONOCIDA";
    }

    return strdup(accion_jug);
}

turno_t llenar_struct_turno(const jugador_t *const jugador, 
const jugador_t *const maquina, const size_t turno, int accion_jugad, 
int accion_maquin)
{
    turno_t turno_return;
    char *descrp_accion_jug = NULL;
    char *descrp_accion_maquin = NULL;

    if(turno == 0)
    {
        descrp_accion_jug = "NINGUNA (inicio del juego)";
        descrp_accion_maquin = "NINGUNA (inicio del juego)";
    }
    else
    {
        descrp_accion_jug = accion_a_cadena(accion_jugad);
        descrp_accion_maquin = accion_a_cadena(accion_maquin);
    }

    strncpy(turno_return.accion_jugad, descrp_accion_jug, sizeof(turno_return.accion_jugad) - 1);
    turno_return.accion_jugad[sizeof(turno_return.accion_jugad) - 1] = '\0';

    strncpy(turno_return.accion_maquin, descrp_accion_maquin, sizeof(turno_return.accion_maquin) - 1);
    turno_return.accion_maquin[sizeof(turno_return.accion_maquin) - 1] = '\0';

    if(turno != 0)
    {
        destruir_memoria(&descrp_accion_jug);
        destruir_memoria(&descrp_accion_maquin);
    }
    
    turno_return.vida_restante_jugador = jugador->vida;
    turno_return.energia_restante_jugador = jugador->energia;

    turno_return.vida_restante_maquina = maquina->vida;
    turno_return.energia_restante_maquina = maquina->energia;

    turno_return.turno = turno;    

    return turno_return;
}

void imprimir_turno(const turno_t *const turno_print)
{
    fprintf(stdout, "Turno numero %zu", turno_print->turno);
    fprintf(stdout, "Accion realizada por el jugador: %s\n", turno_print->accion_jugad);
    fprintf(stdout, "Accion realizada por la maquina: %s\n", turno_print->accion_maquin);
    fprintf(stdout, "Vida restante del jugador: %d\n", turno_print->vida_restante_jugador);
    fprintf(stdout, "Energia restante del jugador: %d\n", turno_print->energia_restante_jugador);
    fprintf(stdout, "Vida restante de la maquina: %d\n", turno_print->vida_restante_maquina);
    fprintf(stdout, "Energia restante de la maquina: %d\n", turno_print->energia_restante_maquina);
}

personaje_t crear_personaje_random()
{
    personaje_t personaje_retorno;
    int vida_ran = (rand() % (1700 - 1300 + 1)) + 1300;
    int energia_ran = (rand() % (100 - 70 + 1)) + 70;
    int ataque_ran = (rand() % (70 - 50 + 1)) + 50;;
    int curacion_ran = (rand() % (350 - 200 + 1)) + 200;
    int aumento_energia_ran = (rand() % (35 - 20 + 1)) + 20;
    int reduc_energ_ataq_ran = (rand() % (15 - 7 + 1)) + 7;
    float red_danio = CONST_DEFENSA;

    personaje_retorno.vida = vida_ran;
    personaje_retorno.energia = energia_ran;
    personaje_retorno.ataque = ataque_ran;
    personaje_retorno.curacion = curacion_ran;
    personaje_retorno.aumento_energia = aumento_energia_ran;
    personaje_retorno.reduc_energ_ataq = reduc_energ_ataq_ran;
    personaje_retorno.red_danio = red_danio;

    return personaje_retorno;
}

int modificar_energia_jugador(jugador_t *jugador, int energia_modificar)
{
    int energia_jug = jugador->energia;
    if(energia_modificar > 0)
    {
        if((energia_jug + energia_modificar) > jugador->personaje.energia)
        {
            jugador->energia = jugador->personaje.energia;
        }
        else
        {
            jugador->energia = energia_jug + energia_modificar;
        }
    }
    else
    if(energia_modificar < 0)
    {
        if(energia_jug - energia_modificar <= 0)
        {
            jugador->energia = 1;
        }
        else
        {
            jugador->energia = energia_jug + energia_modificar;
        }
    }
}

ataque_t calcular_ataque(const jugador_t *const jugad_atacado, 
const jugador_t *const jugad_atacante)
{
    ataque_t ataque_retorno;
    int ataque_jug = jugad_atacante->ataque;
    int energia_jug = jugad_atacante->energia;
    int red_energ_ataq = jugad_atacante->reduc_energ_ataq;
    float red_danio_atacado = jugad_atacado->red_danio;

    int calculo_ataque = (int)roundf(EULER * ((float)ataque_jug + (float)energia_jug));

    if(jugad_atacado->defensa == true)
    {
        calculo_ataque = calculo_ataque * red_danio_atacado;
    }
    ataque_retorno = {.danio_causado = calculo_ataque, 
    .energ_reduc = red_energ_ataq};

    return ataque_retorno;
}

