#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include<time.h> //buscar como usar para agregar fecha al archivo.
#include "combate.h"


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
    turno_t turno_return = {0};
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
    
        turno_return.vida_restante_jugador = jugador_obtener_vida(jugador);
        turno_return.energia_restante_jugador = jugador_obtener_energia(jugador);

        turno_return.vida_restante_maquina = jugador_obtener_vida(maquina);
        turno_return.energia_restante_maquina = jugador_obtener_energia(maquina);

        turno_return.turno = turno;  
    }
    return turno_return;
}

void imprimir_turno(const turno_t *const turno_print)
{
    if(turno_print->turno != 0)
    {
        fprintf(stdout, "Turno numero %zu\n", turno_print->turno);
    }
    fprintf(stdout, "  Accion realizada por el jugador: %s\n", turno_print->accion_jugad);
    fprintf(stdout, "  Accion realizada por la maquina: %s\n", turno_print->accion_maquin);
    fprintf(stdout, "  Vida restante del jugador: %d\n", turno_print->vida_restante_jugador);
    fprintf(stdout, "  Energia restante del jugador: %d\n", turno_print->energia_restante_jugador);
    fprintf(stdout, "  Vida restante de la maquina: %d\n", turno_print->vida_restante_maquina);
    fprintf(stdout, "  Energia restante de la maquina: %d\n", turno_print->energia_restante_maquina);
}

void modificar_energia_jugador(jugador_t *jugador, int energia_modificar)
{
    const personaje_t *personaje_jugador = jugador_obtener_personaje(jugador);
    int energia_jug = jugador_obtener_energia(jugador);
    int energ_max_presonaje = personaje_jugador->energia;
    if(energia_modificar > 0)
    {
        if((energia_jug + energia_modificar) > energ_max_presonaje)
        {
            jugador_establecer_energia(jugador, energ_max_presonaje);
        }
        else
        {
            jugador_establecer_energia(jugador, (energia_jug + energia_modificar));
        }
    }
    else
    if(energia_modificar < 0)
    {
        if(energia_jug + energia_modificar <= 0)
        {
            jugador_establecer_energia(jugador, 1);
        }
        else
        {
           jugador_establecer_energia(jugador, (energia_jug + energia_modificar));
        }
    }
}

ataque_t calcular_ataque(const jugador_t *const jugad_atacado, 
const jugador_t *const jugad_atacante)
{
    ataque_t ataque_retorno;
    const personaje_t *personaje_jug_atacante = jugador_obtener_personaje(jugad_atacante);
    int ataque_jug = personaje_jug_atacante->ataque;
    int energia_jug = personaje_jug_atacante->energia;
    int const_defens = jugador_obtener_defensa(jugad_atacado);
    int red_energ_ataq = personaje_jug_atacante->reduc_energ_ataq;

    int calculo_ataque = ataque_jug + energia_jug - const_defens;

    ataque_retorno.danio_causado = calculo_ataque;
    ataque_retorno.energia_reducida = red_energ_ataq;

    return ataque_retorno;
}

defensa_t calcular_defensa(const jugador_t *const jugador_en_defensa, const int danio_causado)
{
    const personaje_t *personaje_jugador = jugador_obtener_personaje(jugador_en_defensa); 
    defensa_t defensa_retorno;
    int energia_a_sumar = personaje_jugador->aumento_energia;
    int danio_final = danio_causado * CONST_DEFENSA;

    defensa_retorno.danio_luego_reduction = danio_final;
    defensa_retorno.energia_ganada = (int)(energia_a_sumar * 1.5);

    return defensa_retorno;
}

curar_t curar_jugador(const jugador_t *const jugador)
{
    const personaje_t *personaje_jugador = jugador_obtener_personaje(jugador);
    curar_t curar_retorno;
    int cant_curacion = personaje_jugador->curacion;
    int energia_a_sumar = personaje_jugador->aumento_energia;

    curar_retorno.vida_agregada = cant_curacion;
    curar_retorno.energia_agregada = energia_a_sumar;

    return curar_retorno;
}

int randomizar_accion(const jugador_t *const jugador)
{
    const personaje_t *personaje_jugador = jugador_obtener_personaje(jugador);
    int retorno = 0;
    int vida_jugad = jugador_obtener_vida(jugador);
    int vida_max_personaj = personaje_jugador->vida;
    int capacidad_curacion = personaje_jugador->curacion;
    int energ_jug = jugador_obtener_energia(jugador);
    bool no_puede_atacar = (energ_jug < ENERGIA_BAJA); 
    bool no_puede_curar = ((capacidad_curacion + vida_jugad) > vida_max_personaj);


    if ((no_puede_atacar && no_puede_curar) == true)
    {
        retorno = DEFENSA;
    }
    else if (no_puede_atacar == true)
    {
        retorno = (rand() % 2) + DEFENSA;
    }
    else if (no_puede_curar == true)
    {
        retorno = (rand() % 2) + ATAQUE;
    }
    else
    {
        retorno = (rand() % 3) + ATAQUE;
    }
    return retorno;
}

int decision_accion_maquina(const jugador_t *const jug_humano, 
const jugador_t *const jug_maquina, int accion_jug)
{
    int accion_maquina = 0;
    int energia_maquina = jugador_obtener_energia(jug_maquina);
    int vida_hum = jugador_obtener_vida(jug_humano);
    int vida_maquina = jugador_obtener_vida(jug_maquina);
    bool continuar = true;

    if((accion_jug == CURAR) && (energia_maquina > ENERGIA_BAJA))
    {
        int ran_acc_maqu = (rand() % (100 - 0 + 1)) + 0;;
        if(ran_acc_maqu < 75)
        {
            accion_maquina = ATAQUE;
            continuar = false;
        }
    }
    else
    if(accion_jug == ATAQUE)
    {
        int ran_acc_maqu = (rand() % (100 - 0 + 1)) + 0;;
        if(ran_acc_maqu < 70)
        {
            accion_maquina = DEFENSA;
            continuar = false;
        }
    }
    
    if((vida_maquina < VIDA_BAJA) && (continuar == true))
    {
        accion_maquina = CURAR;
    }
    else
    if(energia_maquina < ENERGIA_BAJA)
    {
        accion_maquina = DEFENSA;
    }
    else
    if(vida_hum < VIDA_BAJA)
    {
        if(energia_maquina > ENERGIA_BAJA)
        {
            accion_maquina = ATAQUE;
        }
        else
        {
            accion_maquina = DEFENSA;
        }
    }
    else
    {
        accion_maquina = randomizar_accion(jug_maquina);
    }
    return accion_maquina;
}

void modificar_jugador(jugador_t *jugador, accion_jugador_t *accion_jugad, 
int accion, int accion_rival)
{
    const personaje_t *personaje_jug = jugador_obtener_personaje(jugador);
    int energ_jug = jugador_obtener_energia(jugador);
    int energ_max_personaj = personaje_jug->energia;
    int vida_jug = jugador_obtener_vida(jugador);
    int vida_max_personaj = personaje_jug->vida;

    switch(accion)
    {
        case ATAQUE:
        { 
            int energ_reduc = accion_jugad->ataque.energia_reducida;
            int energ_result = energ_jug + energ_reduc;

            if(energ_result <= 0)
            {
                jugador_establecer_energia(jugador, 1);
            }
            else
            {
                jugador_establecer_energia(jugador, energ_result);
            }
            break;
        }
        case DEFENSA:
        {          
            int energia_ganada = accion_jugad->defensa.energia_ganada;

            if((energ_jug + energia_ganada) > energ_max_personaj)
            {
                jugador_establecer_energia(jugador, energ_max_personaj);
            }
            else
            {
                jugador_establecer_energia(jugador, (energ_jug + energia_ganada)); 
            }
            break; 
        }
        case CURAR:
        {
            int vida_ganada = accion_jugad->curar.vida_agregada;
            int energia_ganada = accion_jugad->curar.energia_agregada;
            if((vida_jug + vida_ganada) > vida_max_personaj)
            {
                jugador_establecer_vida(jugador, vida_max_personaj);
            }
            else
            {
                jugador_establecer_vida(jugador, (vida_jug + vida_ganada));
            }

            if((energ_jug + energia_ganada) > energ_max_personaj)
            {
                jugador_establecer_energia(jugador, energ_max_personaj);
            }
            else
            {
                jugador_establecer_energia(jugador, energ_jug + energia_ganada);
            }
            break; 
        }
    }

    if(accion_rival == ATAQUE)
    {
        int danio_rival = 0;
        int vida_resultante = 0;
        if(accion == DEFENSA)
        {
            danio_rival = accion_jugad->defensa.danio_luego_reduction;
        }
        else
        {
            danio_rival = accion_jugad->ataque_rival.danio_causado;
        }

        vida_resultante = jugador_obtener_vida(jugador) - danio_rival;  

        if(vida_resultante <= 0)
        {
            jugador_establecer_vida(jugador, 0);
            jugador_establecer_vivo(jugador, false);
        }
        else
        {
            jugador_establecer_vida(jugador, vida_resultante);
        }
    }
}

int determ_jug_muerto(const jugador_t *const jugador_hum, const jugador_t *const jug_maquina)
{
    int retorno = NINGUNO;
    bool jugador_vivo = jugador_esta_vivo(jugador_hum);
    bool maquina_viva = jugador_esta_vivo(jug_maquina);
    if(jugador_vivo == false)
    {
        retorno = HUMANO;
    }
    if(maquina_viva == false)
    {
        retorno = MAQUINA;
    }
    if((jugador_vivo == false) && (maquina_viva == false))
    {
        retorno = AMBOS;
    }
    return retorno;
}

void resolucion_acciones(const jugador_t *const jugador, const jugador_t *const maquina, 
int accion_jugador, int accion_maquina, accion_jugador_t *acciones_jugador, accion_jugador_t *acciones_maquina)
{
    bool maquina_ataque = true;
    ataque_t ataque_jug = {0};
    ataque_t ataque_maquin = {0};
    defensa_t defensa_jug = {0};
    defensa_t defensa_maquin = {0};
    curar_t curar_jug = {0};
    curar_t curar_maquin = {0};

    switch(accion_jugador)
    {
        case ATAQUE:
            ataque_jug = calcular_ataque(maquina, jugador);
            acciones_jugador->ataque = ataque_jug;
            acciones_maquina->ataque_rival = ataque_jug;
            break;
        case DEFENSA:
            if(accion_maquina == ATAQUE)
            {
                ataque_maquin = calcular_ataque(jugador, maquina);
                defensa_jug = calcular_defensa(jugador, ataque_maquin.danio_causado);
                maquina_ataque = false;
            }
            else
            {
                defensa_jug = calcular_defensa(jugador, 0);
            }
            acciones_jugador->defensa = defensa_jug;
            acciones_maquina->ataque = ataque_maquin;
            break;
        case CURAR:
            curar_jug = curar_jugador(jugador);   
            acciones_jugador->curar = curar_jug;
    }
    
    switch(accion_maquina)
    {
        case ATAQUE:
            if(maquina_ataque == true)
            {
                ataque_maquin = calcular_ataque(jugador, maquina);
            }
            acciones_maquina->ataque = ataque_maquin;
            acciones_jugador->ataque_rival = ataque_maquin;
            break;
        case DEFENSA:
            if(accion_jugador == ATAQUE)
            {
                defensa_maquin = calcular_defensa(maquina, ataque_jug.danio_causado);
            }
            else
            {
                defensa_maquin = calcular_defensa(maquina, 0);
            }
            acciones_maquina->defensa = defensa_maquin;
            break;
        case CURAR:
            curar_maquin = curar_jugador(maquina);
            acciones_maquina->curar = curar_maquin; 
            break;  
    }
}

void actualizar_defensa_por_accion(jugador_t *jugador, int accion)
{
    const personaje_t *personaje_jug = jugador_obtener_personaje(jugador);
    int defensa_personaje = personaje_jug->defensa;

    if(accion == CURAR)
    {
        jugador_establecer_defensa(jugador, (int)(defensa_personaje / 2));
    }
    else
    {
        jugador_establecer_defensa(jugador, defensa_personaje);
    }
}

int comprobar_energ_ataq(const jugador_t *const jugador, int accion_jugador)
{
    int retorno = accion_jugador;
    int energia_jug = jugador_obtener_energia(jugador);

    if(accion_jugador == ATAQUE)
    {
        if(energia_jug < ENERGIA_BAJA)
        {
            retorno = INVALIDA;
        }
    }
    return retorno;
}

int verific_valid_accion_jug(jugador_t *jugador, const int accion_jugador, int ataques_seguidos)
{
    int comprob_valid_accion = 0;
    int retorno = 0;
    if((accion_jugador >= ATAQUE) && (accion_jugador <= CURAR))
    {
        comprob_valid_accion = comprobar_energ_ataq(jugador, accion_jugador);
        if(comprob_valid_accion == INVALIDA)
        {
            retorno = ENERGIA_INSUFIC;
        }
        else
        if((comprob_valid_accion == ATAQUE) && (ataques_seguidos == 3))
        {   
            retorno = DEMASIADOS_ATAQUES;
        }
        else
        {
            retorno = accion_jugador;
        }
    }
    else
    {
        retorno = RANGO_INVALIDO;
    }
    return retorno;
}

void mostrar_opciones_accion()
{
    fprintf(stdout, "Elija su siguiente accion. Ingrese el numero correspondiente");
    fprintf(stdout, " a la accion deseada\n");
    fprintf(stdout, " 1. ATACAR\n 2. DEFENDER\n 3. CURAR\n");
}

void verif_lect_correcta_accion(int *accion_jugador)
{
    while(scanf("%d", accion_jugador) != 1)
    {
        fprintf(stdout, "Error de formato. Por favor, solo ingrese numeros.");
        fprintf(stdout, "Intente nuevamente. Reiteracion de las opciones:\n");
        mostrar_opciones_accion();
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    } 
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void imprimir_separador_sig_igual()
{
    for(size_t i = 0; i < 35; i++)
    {
        fprintf(stdout, "=");
    }
    fprintf(stdout, "\n");
}

void imprim_ganador(int jugador_muerto)
{
    switch(jugador_muerto)
    {
        case HUMANO:
            fprintf(stdout, "La maquina ha ganado. :(");
            break;
        case MAQUINA:
            fprintf(stdout, "El jugador ha ganado!");
            break;
        case AMBOS:
            fprintf(stdout, "Se ha producido un empate! (Ambos jugadores realizaron un ataque fatal en el ultimo turno de la partida)");
            break;
    }
}