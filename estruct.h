 typedef enum
    { 
        NINGUNA,
        ATAQUE,
        DEFENSA,
        CURAR,
        RANDOM
    }accion_activa_t;

    typedef struct
    {
        int vida; //Vida del personaje. Puede estar en el rango de [1300 - 1700].
        int energia; //Energia del personaje. Puede estar en el rango de [70 - 100]. 
        int ataque; //Plus de ataque del personaje. Puede en el rango [50 - 70].
        int curacion; //Capacidad de curacion del personaje. Rango: [200 - 350].
        int aumento_energia; //Aumento de energia producido en la accion de curar/defender.
        int reduc_energ_ataq; //Cantidad de energia reducida al realizar un ataque,
        //representada por un nro negativo (la cantidad a restar * -1).
        float red_danio; //Toma su valor del macro CONST_DEFENSA. 
    }personaje_t;

    typedef struct
    {
        int vida;
        int energia;
        bool defensa; //Decision de aplicar o no la reduccion de la defensa.
        bool vivo;
        personaje_t personaje;
    }jugador_t;

    typedef struct
    {
        int danio_causado;
        int energia_reducida; 
    }ataque_t;

    typedef struct
    {
        int danio_after_reduction;
        int energia_ganada;
    }defensa_t;

    typedef struct
    {
        int vida_agregada;
        int energia_agregada;
    }curar_t;

    typedef struct
    {
        ataque_t ataque_rival,
        ataque_t ataque,
        curar_t curar,
        defensa_t defensa
    }accion_jugador_t;

    typedef enum
    {   
        NINGUNO = -4,
        HUMANO,
        MAQUINA,
        AMBOS
    }jugador_muerto_t

    typedef struct
    {
        char accion_jugad[32];
        char accion_maquin[32];
        int vida_restante_jugador;
        int energia_restante_jugador;
        int vida_restante_maquina;
        int energia_restante_maquina;
        size_t turno;
    }turno_t;
