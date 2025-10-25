#ifndef COMBATE

    #define COMBATE
    #define EULER 2.7182818

    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    #include<math.h>
    #include "combate.h"

    typedef enum
    {
        CURAR = 1,
        ATAQUE,
        DEFENSA
    }accion_activa_t;
    typedef struct
    {
        char nombre[24];
        char descripcion[64];
        int max_vida;
        int max_energia;
        int plus_ataque;
        int capac_curacion;
        float reduccion_escudo;
        float reduccion_defensa;
        float penetracion_escudo;
    }personaje_t;

    typedef struct
    {
        char nombre_jugador[32];
        float vida;
        int energia;
        int puntos_escudo;
        bool escudo;
        personaje_t personaje;
    }jugador_t;

    typedef struct
    {
        float danio_causado;
        int puntos_escudo_quitados;
        int energia_reducida; 
    }ataque_t;

    typedef struct
    {
        float danio_after_reduction;
        int energia_ganada;
    }defensa_t;

    typedef struct
    {
        float vida_agregada;
        int energia_agregada;
        bool escudo;
    }curar_t;

    typedef struct
    {
        ataque_t ataque_rival,
        ataque_t ataque,
        curar_t curar,
        defensa_t defensa
    }accion_jugador_t;

    typedef struct
    {
        size_t cant_turnos;
        char accion_previa_jugad[16];
        char accion_previa_maquin[16];
        int escudo_restante_jugador;
        int escudo_restante_maquina;
        int vida_restante_jugador;
        int vida_restante_maquina;
        int energia_restante_jugador;
        int energia_restante_maquina;
    }turno_t;

    
    /**
        @brief La funcion calcula el danio de un ataque de un jugador a otro.

        @details Toma las estadisticas de los personajes de cada jugador 
        y del estado actual de cada jugador. ATENCION: No modifica las estructuras
        que contienen los datos de los jugadores. Lo que hace es guardar los datos 
        que afecta en una estructura de tipo ataque_t y la retorna.
        
        @param [in] personaje_atacado es un puntero a una estructura de tipo 
        personaje_t que tiene la informacion del personaje del jugador que es 
        atacado. Es usado para calcular el danio causado por el ataque al jugador
        atacado en base a la capacidad de reduccion que este tiene.

        @param [in] personaje_atacante es un puntero a una estructura de tipo 
        personaje_t. Muy similar al anterior parametro; esta estructura contiene
        los datos del atacante, que son usados para calcular el danio que el
        personaje del jugador atacante hara.

        @param [in] jugad_atacado es un puntero a una estructura de tipo
        jugador_t. Esta estructura contiene las estadisticas actuales del jugador
        atacado. Se usa para calcular el danio que es capaz de reducir las skills
        del personaje.

        @param [in] jugad_atacante es un puntero a una estructura de tipo 
        jugador_t. Esta estructura contiene las estadisticas actuales del jugador
        atacante. Se usa para para calcular cuanto danio es capaz de hacer el 
        personaje. 

        @pre Todas los punteros a las estructuras deben ser != NULL a memorias  
        correspondientes a su tipo.

        @return una estructura ataque_t, la cual contiene los datos que el ataque 
        modifica.

        @post La cantidad de danio causado es igual al valor de retorno.

        @invariant personaje_atacado, personaje_atacante, jugad_atacado, 
        jugad_atacante NO son modificados.
    */
    ataque_t calcular_ataque(const personaje_t *const personaje_atacado, 
    const personaje_t *const personaje_atacante, const jugador_t *const jugad_atacado, 
    const jugador_t *const jugad_atacante);

    /**
        @brief La realiza la accion de defensa de un jugador.

        @details La funcion defensa depende del ataque que es infingido
        por el jugador rival. Es por esto que recibira un parametro que representa
        el danio causado por el rival. Este sera reducido dependiendo de las 
        estadisticas del jugador y del personaje atacado.

        @param [in] personaje_en_defensa es un puntero a una estructura de tipo
        personaje_t. Esta estructura tiene los datos del personaje del jugador
        que se esta defendiendo. Es usado para calcular el danio que reduce de manera
        default mas el plus que la accion de defensa proporciona.

        @param [in] jugador_en_defensa es un puntero a una estructura de tipo
        jugador_t. Esta estructura contiene los datos del estado actual del personaje
        del jugador que esta siendo atacado.

        @param danio_causado es el danio original que causaria el rival.

        @pre Todas los punteros a las estructuras deben ser != NULL a memorias  
        correspondientes a su tipo.

        @return una estructura de tipo defensa_t con los el danio ya reducido y
        la energia ganada.
        @post Las estructuras personaje_en_defensa y jugador_en_defensa NO son
        mofidicadas.
    */
    defensa_t calcular_defensa(const personaje_t *const personaje_en_defensa, 
    jugador_t *jugador_en_defensa, const float danio_causado);

    /**
        @brief Esta funcion realiza la accion de curar de un jugador.

        @details La funcion no modifica el jugador originial. Lo que hace es 
        ingresar los datos que modifica a una estructura curar_t y la retorna.
        EL valor curacion e suna constante definida en la estructura del personaje
        que esta utilizando el jugador. Tambien se le proporciona un plus de energia
        proporcionar a su capacidad de curacion.

        @param [in] jugador es un puntero a una estructura jugador_t que contiene
        el personaje el cual esta usando. De aqui se sacara el valor de la capacidad
        de curacion del personaje.

        @pre jugador debe ser un puntero a una memoria != NULL de tipo jugador_t. 

        @return una estructura curar_t con los datos de la curacion y gana de energia
        del jugador.
    */
    curar_t curar_jugador(const jugador_t *const jugador)

    /**
        @brief La funcion modifica una estructura de tipo jugador_t con los  
        datos de la estructura accion_jugad.

        @details La estructura accion_jugad contiene una union dentro con los datos 
    */
    void modificar_jugador(jugador_t *jugador, accion_jugador_t accion_jugad);

#endif