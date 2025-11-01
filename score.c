#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "score.h"

bool obtener_score_global(score_t *score)
{
    FILE *archivo = fopen("score.txt", "r");

    if (archivo == NULL) 
    {  
        modificar_score(score, 0, 0); 
    
        bool exito_escrit = escribir_score_global(score);
        if (exito_escrit == false)
        {
            return false; 
        }
        return true; 
    }
    
    int puntos_jug_local = 0;
    int puntos_maq_local = 0;
    
    int result_lectura = fscanf(archivo, "Score entre Jugador y Maquina: Jugador: %d, Maquina: %d.", 
    &puntos_jug_local, &puntos_maq_local);
    
    if(fclose(archivo) != 0) 
    {
        return false;
    } 

    if (result_lectura != 2)
    {
        modificar_score(score, 0, 0);
        bool exito_escrit = escribir_score_global(score);
        if (exito_escrit == false)
        {
            return false; 
        }
        return true; 
    }

    score->puntaje_humano = puntos_jug_local;
    score->puntaje_maquina = puntos_maq_local;
    
    return true;
}

bool escribir_score_global(const score_t *score)
{
    FILE *archivo = fopen("score.txt", "w");
    if(archivo == NULL)
    {
        return false;
    }

    int puntaj_hum = score->puntaje_humano;
    int puntaj_maq = score->puntaje_maquina;
    fprintf(archivo, "Score entre Jugador y Maquina: Jugador: %d, Maquina: %d.", puntaj_hum, puntaj_maq);
    
    if(fclose(archivo) != 0) 
    {
        return false;
    }
    return true;
}

void modificar_score(score_t *score, int puntaje_humano, int puntaje_maquina)
{
    score->puntaje_humano = score->puntaje_humano + puntaje_humano;
    score->puntaje_maquina = score->puntaje_maquina + puntaje_maquina;
}

void modif_score_segun_ganad(score_t *score, int perdedor)
{
    switch(perdedor)
    {
        case HUMANO:
            modificar_score(score, 0, 1);
            break;
        case MAQUINA:
            modificar_score(score, 1, 0);
            break;
        case AMBOS: 
            modificar_score(score, 1, 1);
            break;
    }
}

void escribir_lider_score(const score_t *score)
{
    int cant_vict_jug = score->puntaje_humano;
    int cant_vict_maq = score->puntaje_maquina;
    if(cant_vict_jug > cant_vict_maq)
    {
        fprintf(stdout, "El jugador va ganando por %d a %d\n", cant_vict_jug, cant_vict_maq);
    }
    else
    if(cant_vict_jug < cant_vict_maq)
    {
        fprintf(stdout, "La maquina va ganando %d a %d\n", cant_vict_maq, cant_vict_jug);
    }
    else
    {
        fprintf(stdout, "El jugador y la maquina van empatados %d a %d\n", cant_vict_jug, cant_vict_maq);
    }
}


