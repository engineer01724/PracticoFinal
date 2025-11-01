#ifndef PERSONAJE
    #define PERSONAJE
    #define ERROR_LECTURA_PUNTERO -500
    #define CONST_DEFENSA 0.7

    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    #include<stdbool.h>
    
    typedef struct
    {
        int vida; //Vida del personaje. Puede estar en el rango de 
        int energia; //Energia del personaje. Puede estar en el rango de 
        int ataque; //Plus de ataque del personaje. Puede en el rango 
        int defensa; //Constante que se resta siempre al ataque del rival.
        int curacion; //Capacidad de curacion del personaje. Rango: 
        int aumento_energia; //Aumento de energia producido en la accion de curar.
        int reduc_energ_ataq; //Cantidad de energia reducida al realizar un ataque.
        float red_danio; //Toma su valor del macro CONST_DEFENSA. 
    }personaje_t;
    
    typedef struct jugador jugador_t;

    typedef enum 
    {
        VIDA_MIN = 200,
        VIDA_MAX = 250,

        ENERGIA_MIN = 50,
        ENERGIA_MAX = 65,

        ATAQUE_MIN = 65,
        ATAQUE_MAX = 80,

        DEFENSA_MIN = 50,
        DEFENSA_MAX = 64,

        CURACION_MIN = 55,
        CURACION_MAX = 70,

        AUMENTO_ENERGIA_MIN = 10,
        AUMENTO_ENERGIA_MAX = 15,

        REDUC_ENERG_ATAQ_MIN = -15, 
        REDUC_ENERG_ATAQ_MAX = -10

    }limites_stats_t;

    /**
        @brief CONSTUCTOR. Crea un jugador de manera dinamica (en el heap).

        @details La funcion llamadora debe liberar la memoria haciendo uso de la
        funcion destruir_jugador.

        @param [in] personaje es un puntero a una estructura personaje_t con la info 
        del personaje elegido por el jugador.

        @pre personaje tiene que ser un puntero a una estructura != NULL de tipo 
        personaje_t.

        @return un puntero opaco a la estructura jugador_t creada e inicializada. (O
        NULL si falla la inicializacion)

        @post Se creo, inicializo y retorno el puntero a la estructura opaca 
        jugador_t (O se devolvio NULL si fallo).

        @invariant personaje no cambia.
    */
    jugador_t *crear_jugador_dinamico(const personaje_t *personaje);

    /**
        @brief DESTRUCTOR. Esta funcion destruye un jugador creado de manera
        dinamica.

        @param [out] jugador es un puntero a la estructura opaca jugador_t que 
        se desea destruir.

        @pre jugador tiene que ser un puntero a una estructura opaca jugador_t
        != NULL

        @post Se libero la memoria previamente reservada y se le asigno NULL al
        puntero que apuntaba a dicha memoria.
    */
    void destruir_jugador(jugador_t **jugador);

    /**
        @brief SELECTOR. Obtiene la vida del jugador.

        @param [in] jugador es un puntero a la estructura opaca jugador_t con la
        info que desea extraerse.

        @pre jugador tiene que ser un puntero a una estructura opaca jugador_t
        != NULL.

        @return la vida del jugador.

        @post Se leyo y retorno la vida del jugador.

        @invariant jugador no es modificado.
    */
    int jugador_obtener_vida(const jugador_t *jugador);

    /**
        @brief SELECTOR. Obtiene la energia de un jugador.
        
        @param [in] jugador es un puntero a la estructura opaca jugador_t con la
        info que desea extraerse.

        @pre jugador tiene que ser un puntero a una estructura opaca jugador_t
        != NULL.
        
        @return la energia del jugador.

        @post Se leyo y retorno la energia del jugador.

        @invariant jugador no es modificado.
    */
    int jugador_obtener_energia(const jugador_t *jugador);

    /**
        @brief SELECTOR. Obtiene la defensa de un jugador.
        
        @param [in] jugador es un puntero a la estructura opaca jugador_t con la
        info que desea extraerse.

        @pre jugador tiene que ser un puntero a una estructura opaca jugador_t
        != NULL.
        
        @return la defensa del jugador.

        @post Se leyo y retorno la defensa del jugador.

        @invariant jugador no es modificado.
    */
    int jugador_obtener_defensa(const jugador_t *jugador);

    /**
        @brief CONSULTOR. Consulta si el jugador esta vivo o no.

        @param [in] jugador es un puntero a la estructura opaca jugador_t con la
        info que desea extraerse.

        @pre jugador tiene que ser un puntero a una estructura opaca jugador_t
        != NULL.
        
        @return true si el jugador esta vivo. false si no lo esta.

        @post Se retorno el valor true si el jugador esta vivo, o false si el 
        jugador no lo esta.

        @invariant jugador no es modificado.
    */
    bool jugador_esta_vivo(const jugador_t *jugador);

    /**
        @brief SELECTOR. Obtiene una referencia al personaje de un jugador.

        @param [in] jugador es un puntero a la estructura opaca jugador_t con 
        la info que desea extraerse.

        @pre jugador tiene que ser un puntero a una estructura opaca jugador_t
        != NULL.

        @return un puntero de solo lectura al personaje del jugador que fue pasado 
        por parametro.

        @invariant jugador no es modificado.
    */
    const personaje_t *jugador_obtener_personaje(const jugador_t *jugador);

    /**
        @brief MUTADOR. Esta funcion modifica la vida de jugador_t.
        
        @param [out] jugador es un puntero a la estructura opaca jugador_t de 
        la cual se quiere modificar la vida.

        @param nueva_vida es la nueva vida que tendra el jugador.

        @pre jugador tiene que ser un puntero a una estructura opaca 
        jugador_t != NULL.

        @post Se cambio la vida del jugador por el valor de nueva_vida
    */
    void jugador_establecer_vida(jugador_t *jugador, int nueva_vida);

    /**
        @brief MUTADOR. La funcion modifica la energia de un jugador_t

        @param [out] jugador es un puntero a la estructura opaca jugador_t de 
        la cual se quiere modificar la energia.

        @param nueva_energia es la nueva energia que tendra el jugador.

        @pre jugador tiene que ser un puntero a una estructura opaca 
        jugador_t != NULL.

        @post Se cambio la energia del jugador por el valor de nueva_energia
    */
    void jugador_establecer_energia(jugador_t *jugador, int nueva_energia);

    /**
        @brief MUTADOR. Esta funcion modifica la defensa de un jugador_t.

        @param [out] jugador es un puntero a la estructura opaca jugador_t de 
        la cual se quiere modificar la defensa.

        @param nueva_defensa es la nueva defensa que tendra el jugador.

        @pre jugador tiene que ser un puntero a una estructura opaca 
        jugador_t != NULL.

        @post Se cambio la defensa del jugador por el valor de nueva_defensa.
    */    
    void jugador_establecer_defensa(jugador_t *jugador, int nueva_defensa);

    /**
        @brief MUTADOR. La funcion modifica si el jugador esta vivo o no.

        @param [out] jugador es un puntero a la estructura opaca jugador_t de 
        la cual se quiere modificar si el jugador esta vivo o no.

        @param estado es el estado el cual se quiere establecer al jugador. true
        para vivo, false para muerto.

        @pre jugador tiene que ser un puntero a una estructura opaca 
        jugador_t != NULL.

        @post Se cambio el estado de vivo del jugador.
    */
    void jugador_establecer_vivo(jugador_t *jugador, bool estado);

    /**
        @brief. CONTRUSCTOREsta funcion crea un arreglo dinamico de elementos de tipo 
        personaje_t de capacidad tamanio.
        
        @details La funcion llamadora es encargada de liberar el recurso creado 
        haciendo uso de la funcion 'destruir_memoria'.

        @param tamanio es el tamanio del cual se quiere crear el arreglo.

        @pre tamanio deb ser > 0.

        @return un puntero a la memoria del heap donde se aloja el recuros recien
        creado.

        @post Se creo y retorno el recurso de tamanio tamanio.
    */
    personaje_t *crear_arreglo_personajes(const size_t tamanio);

    /**
        @brief Esta funcion destruye memoria dinamica previamente pedida.
        
        @param [in, out] ptr_mem es un puntero al puntero que apunta a la direccion 
        dinamica que se desea liberar.

        @post Se libero la memoria dinamica y al puntero a la misma se le ha asignado 
        el valor NULL.
    */
    void destruir_memoria(void **ptr_mem);

    /**
        @brief ITERADOR. Esta funcion imprime un personaje_t.

        @param [in] personaje es un puntero a la estructura de tipo personaje_t
        que desea imprimirse.

        @pre personaje debe ser un puntero a una direccion != NULL de tipo personaje_t.

        @post Se imprimio el personaje. 

        @invariant personaje no es modificado.
    */
    void imprimir_personaje(const personaje_t *const personaje);

    /**
        @brief Crea un personaje_t con estadisticas random.

        @details Haciendo uso de la funcion rand(), crea un personaje con estadisticas dentro de 
        los sgts rangos: vida: [400 - 500]. energia: [65 - 50]. ataque: [65 - 80] defensa: [50 - 64].
        curacion: [55 - 70]. aumeto_energia: [10 - 15]. reduccion de energia: [10 - 15]. Factor de
        reduccion de la defensa: constante (0.7).
    */
    personaje_t crear_personaje_random();

#endif