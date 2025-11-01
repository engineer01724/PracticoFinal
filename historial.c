#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include "historial.h"   
#include "combate.h"

typedef struct nodo
{
    turno_t turno;
    struct nodo *siguiente;
}nodo_t;

typedef struct
{
    nodo_t *inicio;
    nodo_t *final;
    size_t tamanio;
}historial_turnos_t;   



