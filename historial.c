#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include "historial.h"   

struct historial_turnos
{
    nodo_t *inicio;
    nodo_t *final;
    size_t tamanio;
};    

struct nodo
{
    turno_t turno;
    struct nodo *siguiente;
};

historial_turnos_t *crear_historial_turnos()
{
    historial_turnos_t *historial = NULL;
    historial = (historial_turnos_t *)malloc(sizeof(historial_turnos_t));
    if(historial != NULL)
    {
        historial->inicio = NULL;
        historial->final = NULL;
        historial->tamanio = 0;
    }
    return historial;
}

bool historial_agregar_fin(historial_turnos_t *historial, turno_t *turno)
{   
    if(historial == NULL)
    {
        return false;
    }

    nodo_t *nuevo = NULL;
    nuevo = (nodo_t *)malloc(sizeof(nodo_t));

    if(nuevo == NULL)
    {
        return false;
    }

    nuevo->turno = *turno;
    nuevo->siguiente = NULL;

    if(historial->inicio == NULL)
    {
        historial->inicio = nuevo;
        historial->final = nuevo;
    }
    else
    {
        historial->final->siguiente = nuevo;
        historial->final = nuevo;
    }
    historial->tamanio++;

    return true;
}

void historial_imprimir(const historial_turnos_t *historial)
{
    if(historial == NULL)
    {
        return;
    }
    nodo_t *nod_imprimir = historial->inicio;

    while(nod_imprimir != NULL)
    {
        imprimir_turno(&nod_imprimir->turno);
        nod_imprimir = nod_imprimir->siguiente;
    }
}

void historial_destruir(historial_turnos_t **historial)
{
    if((historial == NULL) && (*historial == NULL))
    {
        return;
    }
    nodo_t *actual = (*historial)->inicio;
    nodo_t *siguiente = NULL;
    while(actual != NULL)
    {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
    free(*historial);
    *historial = NULL;
}

const turno_t *historial_ultim_turno(const historial_turnos_t *historial)
{
    if((historial == NULL) || (historial->final == NULL))
    {
        return NULL;
    }

    nodo_t *nodo_fin = historial->final;
    return &nodo_fin->turno;
}   

bool historial_guardar_archivo(const historial_turnos_t *historial, const char *nombre_arch)
{
    FILE *archivo = fopen(nombre_arch, "w");
    if(archivo == NULL)
    {
        return false;
    }
    nodo_t *actual = historial->inicio;
    
    while(actual != NULL)
    {
        imprimir_separador_archivo(archivo);
        if(actual->turno.turno != 0)
        {
            fprintf(archivo, "Turno numero %zu:\n", actual->turno.turno);
        }
        fprintf(archivo, "  Accion realizada por el jugador: %s\n", actual->turno.accion_jugad);
        fprintf(archivo, "  Accion realizada por la maquina: %s\n", actual->turno.accion_maquin);
        fprintf(archivo, "  Vida restante del jugador: %d\n", actual->turno.vida_restante_jugador);
        fprintf(archivo, "  Energia restante del jugador: %d\n", actual->turno.energia_restante_jugador);
        fprintf(archivo, "  Vida restante de la maquina: %d\n", actual->turno.vida_restante_maquina);
        fprintf(archivo, "  Energia restante de la maquina: %d\n", actual->turno.energia_restante_maquina);
        imprimir_separador_archivo(archivo);
        actual = actual->siguiente;
    }

    if(fclose(archivo) != 0) 
    {
        return false;
    }
    return true;
}

void imprimir_separador_archivo(FILE *archivo)
{
    for(size_t i = 0; i < 35; i++)
    {
        fprintf(archivo, "=");
    }
    fprintf(archivo, "\n");
}


