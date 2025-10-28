#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
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
    retorno = (turno_t *)realloc(arr_turno, (cant_actual + cant_agregar) * sizeof(turno_t));
    return retorno;
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
            break;
        case CURAR:
            accion_jug = "CURAR";
            break;
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
    turno_return.mem_ped_correct = true;
    char *descrp_accion_jug = NULL;
    char *descrp_accion_maquin = NULL;
    bool mem_ped_correc = true;


    if(turno == 0)
    {
        descrp_accion_jug = "NINGUNA (inicio del juego)";
        descrp_accion_maquin = "NINGUNA (inicio del juego)";
    }
    else
    {
        descrp_accion_jug = accion_a_cadena(accion_jugad);
        if(descrp_accion_jug == NULL)
        {
            mem_ped_correc = false;
            turno_return.mem_ped_correct = false;
        }
        else
        {
            descrp_accion_maquin = accion_a_cadena(accion_maquin);
            if(descrp_accion_maquin == NULL)
            {
                destruir_memoria((void **)&descrp_accion_jug);
                mem_ped_correc = false;
                turno_return.mem_ped_correct = false;
            }
        }
    }
    if(mem_ped_correc == true)
    {
        strncpy(turno_return.accion_jugad, descrp_accion_jug, sizeof(turno_return.accion_jugad) - 1);
        turno_return.accion_jugad[sizeof(turno_return.accion_jugad) - 1] = '\0';

        strncpy(turno_return.accion_maquin, descrp_accion_maquin, sizeof(turno_return.accion_maquin) - 1);
        turno_return.accion_maquin[sizeof(turno_return.accion_maquin) - 1] = '\0';

        if(turno != 0)
        {
            destruir_memoria((void **)&descrp_accion_jug);
            destruir_memoria((void **)&descrp_accion_maquin);
        }
    
        turno_return.vida_restante_jugador = jugador->vida;
        turno_return.energia_restante_jugador = jugador->energia;

        turno_return.vida_restante_maquina = maquina->vida;
        turno_return.energia_restante_maquina = maquina->energia;

        turno_return.turno = turno;  
    }
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
    int vida_ran = (rand() % (1700 - 1350 + 1)) + 1350;
    int energia_ran = (rand() % (100 - 70 + 1)) + 70;
    int ataque_ran = (rand() % (70 - 50 + 1)) + 50;;
    int curacion_ran = (rand() % (500 - 350 + 1)) + 350;
    int aumento_energia_ran = (rand() % (35 - 20 + 1)) + 20;
    int reduc_energ_ataq_ran = ((rand() % (25 - 15 + 1)) + 15) * (-1);
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

void modificar_energia_jugador(jugador_t *jugador, int energia_modificar)
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
    int ataque_jug = jugad_atacante->personaje.ataque;
    int energia_jug = jugad_atacante->energia;
    int red_energ_ataq = jugad_atacante->personaje.reduc_energ_ataq;
    float red_danio_atacado = jugad_atacado->personaje.red_danio;

    int calculo_ataque = (int)round(EULER * ((float)ataque_jug + (float)energia_jug));

    if(jugad_atacado->defensa == true)
    {
        calculo_ataque = (int)round((float)calculo_ataque * (float)red_danio_atacado);
    }
    ataque_retorno.danio_causado = calculo_ataque;
    ataque_retorno.energia_reducida = red_energ_ataq;

    return ataque_retorno;
}

defensa_t calcular_defensa(jugador_t *jugador_en_defensa, const int danio_causado)
{
    defensa_t defensa_retorno;
    int energia_a_sumar = jugador_en_defensa->personaje.aumento_energia;
    int danio_final = danio_causado * 0.5;

    defensa_retorno.danio_luego_reduction = danio_final;
    defensa_retorno.energia_ganada = energia_a_sumar;

    return defensa_retorno;
}

curar_t curar_jugador(const jugador_t *const jugador)
{
    curar_t curar_retorno;
    int cant_curacion = jugador->personaje.curacion;
    int energia_a_sumar = jugador->personaje.aumento_energia;

    curar_retorno.vida_agregada = cant_curacion;
    curar_retorno.energia_agregada = energia_a_sumar;

    return curar_retorno;
}

int randomizar_accion(const jugador_t *const jugador)
{
    int vida_jugad = jugador->vida;
    int vida_max_personaj = jugador->personaje.vida;
    int capacidad_curacion = jugador->personaje.curacion;
    int decision_random = (rand() % (CURAR)) + ATAQUE;

    if((capacidad_curacion + vida_jugad) > vida_max_personaj)
    {
        decision_random = (rand() % DEFENSA) + ATAQUE;
    }

    return decision_random;
}

int decision_accion_maquina(const jugador_t *const jug_humano, 
const jugador_t *const jug_maquina)
{
    int accion_maquina = 0;
    int energia_maquina = jug_maquina->energia;
    int vida_hum = jug_humano->vida;
    int vida_maquina = jug_maquina->vida;

    if(vida_maquina < 300)
    {
        accion_maquina = CURAR;
    }
    else
    if(energia_maquina < 25)
    {
        accion_maquina = DEFENSA;
    }
    //Si la vida del jugador es baja, prioriza esto antes que todo los demas:
    if(vida_hum < 300)
    {
        accion_maquina = ATAQUE;
    }
    return accion_maquina;
}

void modificar_jugador(jugador_t *jugador, accion_jugador_t *accion_jugad, 
int accion, int accion_rival)
{
    int energ_jug = jugador->energia;
    int energ_max_personaj = jugador->personaje.energia;
    int vida_jug = jugador->vida;
    int vida_max_personaj = jugador->personaje.vida;
    int aument_energ = jugador->personaje.aumento_energia;
    int cap_curac = jugador->personaje.curacion;

    switch(accion)
    {
        case ATAQUE:
        { 
            int energ_reduc = accion_jugad->ataque.energia_reducida;
            int energ_result = energ_jug - energ_reduc;

            if(energ_result <= 0)
            {
                jugador->energia = 1;
            }
            else
            {
                jugador->energia = energ_result;
            }
            break;
        }

        case DEFENSA:
        { 
            if(accion_rival == ATAQUE)
            {
                int danio_rival = accion_jugad->ataque_rival.danio_causado;
                int vida_resultante = vida_jug - danio_rival;

                if(vida_resultante <= 0)
                {
                    jugador->vida = 0;
                    jugador->vivo = false;
                }
                else
                {
                    jugador->vida = vida_resultante;
                }
            }
            
            if((energ_jug + aument_energ) > energ_max_personaj)
            {
                jugador->energia = energ_max_personaj;
            }
            else
            {
                jugador->energia = energ_jug + aument_energ;
            }
            
            break; 
        }

        case CURAR:
        {
            if((vida_jug + cap_curac) > vida_max_personaj)
            {
                jugador->vida = vida_max_personaj;
            }
            else
            {
                jugador->vida = vida_jug + cap_curac;
            }
            
            if((energ_jug + aument_energ) > energ_max_personaj)
            {
                jugador->energia = energ_max_personaj;
            }
            else
            {
                jugador->energia = energ_jug + aument_energ;
            }
            break; 
        }
    }
}

int determ_jug_muerto(const jugador_t *const jugador_hum, const jugador_t *const jug_maquina)
{
    int retorno = NINGUNO;

    if(jugador_hum->vivo == false)
    {
        retorno = HUMANO;
    }
    if(jug_maquina->vivo == false)
    {
        retorno = MAQUINA;
    }
    if((jug_maquina->vivo == false) && (jugador_hum->vivo == false))
    {
        retorno = AMBOS;
    }
    return retorno;
}

