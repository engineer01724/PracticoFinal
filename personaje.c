#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include "personaje.h"   


struct jugador
{
    int vida;
    int energia;
    int defensa; 
    bool vivo;
    personaje_t personaje;
};

jugador_t *crear_jugador_dinamico(const personaje_t *personaje)
{
    jugador_t *jugador = NULL;
    if(personaje == NULL)
    {
        return NULL;
    } 
    jugador = (jugador_t *)malloc(sizeof(jugador_t));
    if(jugador != NULL)
    {
        jugador->vida = personaje->vida;
        jugador->energia = personaje->energia;
        jugador->defensa = personaje->defensa;
        jugador->vivo = true;
        jugador->personaje = *personaje;
    }
    
    return jugador;
}

void destruir_jugador(jugador_t **jugador)
{
    if((jugador != NULL) && (*jugador != NULL))
    {
        free(*jugador);
        *jugador = NULL;
    }
}

int jugador_obtener_vida(const jugador_t *jugador)
{
    int vida_jug = 0;
    if(jugador == NULL)
    {
        vida_jug = ERROR_LECTURA_PUNTERO;
    }
    else
    {
        vida_jug = jugador->vida;
    }
    return vida_jug;
}

int jugador_obtener_energia(const jugador_t *jugador)
{
    int energia_jug = 0;
    if(jugador == NULL)
    {
        energia_jug = ERROR_LECTURA_PUNTERO;
    }
    else
    {
        energia_jug = jugador->energia;
    }
    return energia_jug;
}

int jugador_obtener_defensa(const jugador_t *jugador)
{
    int defensa_jug = 0;
    if(jugador == NULL)
    {
        defensa_jug = ERROR_LECTURA_PUNTERO;
    }
    else
    {
        defensa_jug = jugador->defensa;
    }
    return defensa_jug;
}

bool jugador_esta_vivo(const jugador_t *jugador)
{
    bool jug_vivo = true;
    if(jugador->vivo == false)
    {
        jug_vivo = false;
    }
    return jug_vivo;
}

const personaje_t *jugador_obtener_personaje(const jugador_t *jugador)
{
    const personaje_t *referencia = NULL;
    if(jugador != NULL)
    {
        referencia = &jugador->personaje;
    }
    return referencia;
}

void jugador_establecer_vida(jugador_t *jugador, int nueva_vida)
{
    jugador->vida = nueva_vida;
}

void jugador_establecer_energia(jugador_t *jugador, int nueva_energia)
{
    jugador->energia = nueva_energia;
}

void jugador_establecer_defensa(jugador_t *jugador, int nueva_defensa)
{
    jugador->defensa = nueva_defensa;
}

void jugador_establecer_vivo(jugador_t *jugador, bool estado)
{
    jugador->vivo = estado;
}

personaje_t *crear_arreglo_personajes(const size_t tamanio)
{
    personaje_t *retorno = NULL;
    retorno = (personaje_t *)malloc(tamanio * sizeof(personaje_t));
    return retorno;
}

void destruir_memoria(void **ptr_mem)
{
    if((ptr_mem != NULL) && (*ptr_mem != NULL))
    {
        free(*ptr_mem);
        *ptr_mem = NULL;
    }  
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

personaje_t crear_personaje_random()
{
    personaje_t personaje_retorno;
    
    int vida_ran = (rand() % (VIDA_MAX - VIDA_MIN + 1)) + VIDA_MIN;
    int energia_ran = (rand() % (ENERGIA_MAX - ENERGIA_MIN + 1)) + ENERGIA_MIN;
    int ataque_ran = (rand() % (ATAQUE_MAX - ATAQUE_MIN + 1)) + ATAQUE_MIN;
    int defensa_ran = (rand() % (DEFENSA_MAX - DEFENSA_MIN + 1)) + DEFENSA_MIN;
    int curacion_ran = (rand() % (CURACION_MAX - CURACION_MIN + 1)) + CURACION_MIN;
    int aumento_energia_ran = (rand() % (AUMENTO_ENERGIA_MAX - AUMENTO_ENERGIA_MIN + 1)) + AUMENTO_ENERGIA_MIN;
    int reduc_energ_ataq_ran = (rand() % (REDUC_ENERG_ATAQ_MAX - REDUC_ENERG_ATAQ_MIN + 1)) + REDUC_ENERG_ATAQ_MIN;

    personaje_retorno.vida = vida_ran;
    personaje_retorno.energia = energia_ran;
    personaje_retorno.ataque = ataque_ran;
    personaje_retorno.defensa = defensa_ran;
    personaje_retorno.curacion = curacion_ran;
    personaje_retorno.aumento_energia = aumento_energia_ran;
    personaje_retorno.reduc_energ_ataq = reduc_energ_ataq_ran;
    personaje_retorno.red_danio = CONST_DEFENSA;

    return personaje_retorno;
}