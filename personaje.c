#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include "personaje.h"   
#include "combate.h"

typedef struct
{
    int vida;
    int energia;
    int defensa; 
    bool vivo;
    personaje_t personaje;
}jugador_t;

jugador_t *crear_jugador_dinamico(const personaje_t *personaje)
{
    jugador_t *jugador = NULL;
    if(personaje == NULL)
    {
        return NULL;
    } 
    jugador = (jugador_t *)malloc(sizeof(jugador_t));
    return jugador;
}

void destruir_jugador(jugador_t **jugador)
{
    if((jugador != NULL) || (*jugador != NULL))
    {
        free(*jugador);
        *jugador = NULL;
    }
}

int jugador_obtener_vida(const jugador_t *jugador)
{
    int vida_jug = jugador->vida;
    if(jugador == NULL)
    {
        vida_jug = ERROR_LECTURA_PUNTERO;
    }
    return vida_jug;
}

personaje_t *crear_arreglo_personajes(const size_t tamanio)
{
    personaje_t *retorno = NULL;
    retorno = (personaje_t *)malloc(tamanio * sizeof(personaje_t));
    return retorno;
}

personaje_t crear_personaje_random()
{
    personaje_t personaje_retorno;
    int vida_ran = (rand() % (500 - 400 + 1)) + 400;
    int energia_ran = (rand() % (65 - 50 + 1)) + 50;
    int ataque_ran = (rand() % (80 - 65 + 1)) + 65;
    int defensa_ran = (rand() % (64 - 50 + 1)) + 50;
    int curacion_ran = (rand() % (70 - 55 + 1)) + 55;
    int aumento_energia_ran = (rand() % (15 - 10 + 1)) + 10;
    int reduc_energ_ataq_ran = ((rand() % (15 - 10 + 1)) + 10) * (-1);
    float red_danio = CONST_DEFENSA;

    personaje_retorno.vida = vida_ran;
    personaje_retorno.energia = energia_ran;
    personaje_retorno.ataque = ataque_ran;
    personaje_retorno.defensa = defensa_ran;
    personaje_retorno.curacion = curacion_ran;
    personaje_retorno.aumento_energia = aumento_energia_ran;
    personaje_retorno.reduc_energ_ataq = reduc_energ_ataq_ran;
    personaje_retorno.red_danio = red_danio;

    return personaje_retorno;
}

void imprimir_personaje(const personaje_t *const personaje)
{
    fprintf(stdout, "  Vida: %d\n", personaje->vida);
    fprintf(stdout, "  Energia: %d\n", personaje->energia);
    fprintf(stdout, "  Ataque: %d\n", personaje->ataque);
    fprintf(stdout, "  Defensa: %d\n", personaje->defensa);
    fprintf(stdout, "  Curacion: %d puntos de vida\n", personaje->curacion);
    fprintf(stdout, "  Factor defensa: %.1f \n\n", personaje->red_danio);
}