#ifndef COMBATE
    #define COMBATE

    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    #include<stdbool.h>
    #include "personaje.h" 
   
    typedef struct
    {
        char accion_jugad[32];
        char accion_maquin[32];
        int vida_restante_jugador;
        int energia_restante_jugador;
        int vida_restante_maquina;
        int energia_restante_maquina;
        size_t turno;
        bool mem_ped_correct;
    }turno_t;

    typedef enum
    {
        RANGO_INVALIDO = -3,
        DEMASIADOS_ATAQUES,
        ENERGIA_INSUFIC
    }errores_accion_t;

    typedef enum
    { 
        NINGUNA,
        ATAQUE,
        DEFENSA,
        CURAR,
        RANDOM,
        INVALIDA
    }accion_activa_t;

    typedef enum
    {
        ENERGIA_BAJA = 10,
        VIDA_BAJA = 100,
    }estadisticas_bajas_t;

    typedef struct
    {
        int danio_causado;
        int energia_reducida; 
    }ataque_t;

    typedef struct
    {
        int danio_luego_reduction;
        int energia_ganada;
    }defensa_t;

    typedef struct
    {
        int vida_agregada;
        int energia_agregada;
        bool defensa;
    }curar_t;

    typedef struct
    {
        ataque_t ataque_rival;
        ataque_t ataque;
        curar_t curar;
        defensa_t defensa;
    }accion_jugador_t;

    typedef enum
    {   
        NINGUNO = -4,
        HUMANO,
        MAQUINA,
        AMBOS,
    }jugador_muerto_t;

    /**
        @brief Esta funcion toma la accion del jugador y la convierte a una cadena.

        @details Esta funcion devuelve un puntero a memoria dinamica donde se aloja
        el literal de cadena que describe la accion realizada. La funcion llamadora
        es responsable de liberar la memoria haciendo uso de la funcion :
        destruir_memoria.
        @param accion_jugador es la accion tomada por el jugador, en formato int.

        @pre accion_jugador debe corresponder a una de las acciones de la struct
        accion_activa_t.

        @return un puntero a una cadena con la accion realizada.
    */
    char *accion_a_cadena(int accion_jugador);

    /**
        @brief Esta funcion llena una estructura de tipo turno_t.

        @details La funcion toma los datos de los dos jugadores y extrae los datos 
        necesarios para almacenar la informacion de los jugadores luego de que el
        turno haya terminado.

        @param [in] jugador es un puntero a una estructura de tipo jugador_t con
        los datos del jugador humano. Estos datos seran usados para llenar los 
        campos correspondientes del turno.

        @param [in] maquina es un puntero a una estructura de tipo jugador_t con
        los datos de la maquina. Estos datos seran usados para llenar los campos 
        correspondientes del turno.

        @param turno es el numero de turno recien jugado.

        @param accion_jugad es la accion que tomo el jugador. Segun cual fue, se
        convertira a una cadena y se guardara en el campo accion_jugad.

        @param accion_jugad es la accion que tomo la maquina. Segun cual fue, se
        convertira a una cadena y se guardara en el campo accion_maquin.

        @pre turno debe ser > 0. jugador y maquina deben ser puntero a una memoria
        != NULL de tipo jugador_t.

        @return una estructura de tipo turno_t con los datos del turno recien jugado.

        @post Los datos del turno han sido guardados y devueltos al programa 
        principal.  

        @invariant tanto jugador como maquina como turno no se ven modificados.
    */
    turno_t llenar_struct_turno(const jugador_t *const jugador, 
    const jugador_t *const maquina, const size_t turno, int accion_jugad, 
    int accion_maquin);

    /**
        @brief Esta funcion imprime una estructura de tipo turno_t

        @param [in] turno es el puntero a la estructura de tipo turno_t que se desea
        imprimir.

        @pre turno debe ser un puntero a una memoria != NULL de tipo turno_t.

        @post Se imprimio el arreglo.

        @invariant turno no es modificado.
    */
    void imprimir_turno(const turno_t *const turno_print);

    /**
        @brief Reduce la energia de un jugador.

        @details Luego de cada turno, el juego reducira la energia de ambos
        jugador en una constante definida antes de comenzar el juego. Esta funcion
        hace eso. La funcion contempla el caso de que modificar energ_reduc al jugador
        supere los limites establecidos. En ese caso, setea su energia a 1 o al maximo
        posible, dependiendo de que limite se rompio.

        @param [in, out] jugador es un puntero a la esturctura jugador_t del jugador
        del cual se desea modificar la energia.
        
        @param energia_modificar es la energia que se desea modificar al usuario.
        Esta puede ser negativa (para restarle esa cantidad al jugador) o positiva
        (para sumarle esa cantidad al jugador).

        @pre energia_jugador debe ser un puntero a una memoria != NULL la estructura
        del jugador del cual se quiere modificar su energia. energia_modificar 
        debe ser != 0.

        @post Se modifico el miembro 'energia' proporcionado.

        @invariant energia_modificar no es modificado.
    */
    void modificar_energia_jugador(jugador_t *jugador, int energia_modificar);

    /**
        @brief La funcion calcula el danio de un ataque de un jugador a otro.

        @details Toma las estadisticas de los personajes de cada jugador 
        y del estado actual de cada jugador. 
        ATENCION: No modifica las estructuras que contienen los datos de los 
        jugadores. Lo que hace es guardar los datos que afecta en una estructura de 
        tipo ataque_t y la retorna.
        IMPORTANTE: Los datos del personaje utilizado por cada jugador estan dentro 
        de las estructuras jugador_t.

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

        @invariant jugad_atacado y jugad_atacante NO son modificados.
    */
    ataque_t calcular_ataque(const jugador_t *const jugad_atacado, 
    const jugador_t *const jugad_atacante);

    /**
        @brief La realiza la accion de defensa de un jugador.

        @details La funcion defensa depende del ataque que es infingido
        por el jugador rival. Es por esto que recibira un parametro que representa
        el danio causado por el rival. Este sera reducido dependiendo de las 
        estadisticas del jugador y del personaje atacado.
        IMPORTANTE: Los datos del personaje utilizado estan dentro de la estructuras 
        jugador_t, en el miembro 'personaje'

        @param [in] jugador_en_defensa es un puntero a una estructura de tipo
        jugador_t. Esta estructura contiene los datos del estado actual del personaje
        del jugador que esta siendo atacado.

        @param danio_causado es el danio original que causaria el rival.

        @pre El puntero a la estructura jugador_en_defensa debe apuntar a una 
        memoria != NULL de tipo jugador_t.

        @return una estructura de tipo defensa_t con los el danio ya reducido y
        la energia ganada.

        @post La estructura jugador_en_defensa NO es modificadas.
    */
    defensa_t calcular_defensa(const jugador_t *const jugador_en_defensa, 
    const int danio_causado);

    /**
        @brief Esta funcion realiza la accion de curar de un jugador.

        @details La funcion no modifica el jugador originial. Lo que hace es 
        ingresar los datos que modifica a una estructura curar_t y la retorna.
        EL valor curacion e suna constante definida en la estructura del personaje
        que esta utilizando el jugador. Tambien se le proporciona un plus de energia.

        @param [in] jugador es un puntero a una estructura jugador_t que contiene
        el personaje el cual esta usando. De aqui se sacara el valor de la capacidad
        de curacion del personaje.

        @pre jugador debe ser un puntero a una memoria != NULL de tipo jugador_t. 

        @return una estructura curar_t con los datos de la curacion y gana de energia
        del jugador.
    */
    curar_t curar_jugador(const jugador_t *const jugador);

    /**
        @brief Esta funcion randomiza la accion de un jugador.

        @details Puede tomar cualquiera de las 3 accione posibles (DEFENDER, ATACAR,
        CURAR). La unica restriccion es que si la vida del jugador esta llena, o la 
        capacidad de curacion del personaje del jugador es mayor a la diferencia entre
        la vida maxima y la vida actual, la accion de curacion no sera elegida.
        Para la eleccion random, se hace uso de la funcion rand().

        @param [in] jugador es un puntero a la estructura con los datos del jugador
        que quiere randomizar su accion. Se usa para restringir la curacion si se
        cumple uno de los casos detallados en la seccion 'details'.

        @pre jugador debe ser un puntero a una memoria != NULL de tipo jugador_t.
        
        @return La accion a tomar, determinada de manera random.

        @post El valor de retorno es == a la accion que se tomara, elegida de manera
        random.
        
        @invariant jugador no es modificado de ninguna manera.
    */
    int randomizar_accion(const jugador_t *const jugador);

    /**
        @brief Esta funcion elige que accion realizara la maquina.

        @details La funcion toma las estadisticas actuales del jugador humano y de
        la maquina y, en base a ellas, decide cual es la accion mas optima a tomar.
        CASOS: La vida de la maquina es muy baja -> CURAR. Energia baja -> DEFENDER.
        Vida del jugador baja -> ATACAR. Si ninguna accion es preferible -> RANDOM.
        Esta ultima accion sera gestionada por la funcion 'randomizar_accion'.
        Las otras seran gestionadas por la funcion correspondiente.

        @param [in] jug_humano es un puntero a la estructura donde se alojan los
        datos del jugador humano. Se usan para determinar la accion a tomar.

        @param [in] jug_maquina es  es un puntero a la estructura donde se alojan los
        datos del jugador de la maquina. Se usa tambien para determinar la accion 
        a tomar.

        @pre Tanto jug_humano como jug_maquina deben ser puntero a memorias != NULL
        de tipo jugador_t.

        @return La accion que la maquina seguira en el corriente turno. Los casos
        estan detallados en la seccion 'details'.
    */
    int decision_accion_maquina(const jugador_t *const jug_humano, 
    const jugador_t *const jug_maquina, int accion_jug);

    /**
        @brief La funcion modifica una estructura de tipo jugador_t con los  
        datos de la estructura accion_jugad.

        @details La estructura accion_jugad contiene una union dentro con los 
        datos que pueden afectar las estadisticas del jugador: el ataque del rival;
        el ataque del jugador; la defensa del jugador; la curacion del jugador.
        Se decidira cual de las estructuras con datos del jugador se toma en cuenta
        dependiendo de la accion tomada por el jugador (param accion). Y se tomara
        en cuenta la accion rival si ataque_rival == true.

        @param [out] jugador es un puntero a una estructura de tipo jugador_t. Esta 
        sera modificada con los datos en la estructura accion_jugad.

        @param [in] accion_jugad  es un puntero a una estructura de tipo 
        accion_jugador_t. Esta tiene 4 estructuras dentro (ir a details para mas
        detalles). Se usa para modificar los datos de jugador.

        @param accion representa la accion que realizo el jugador en el ultimo turno.
        Se usa para saber cual de las estructuras dentro de accion_jugador_t se 
        debe usar para modificar los datos del jugador.

        @param accion_rival Es la accion realizada por el rival. Se usa para determinar si
        la accion del rival modifica las estadisticas del jugador. Esto solo sucede si
        la accion del rival es == ATAQUE.

        @pre Los punteros a estructuras jugador y accion_jugad deben apuntar a
        memorias != NULL de tipo jugador_t y accion_jugador_t respectivamente.
        accion debe obtener su valor de la enum accion_activa_t.

        @post La estructura del jugador que esta siendo modificado fue modificada
        con los datos correspondientes.
    */
    void modificar_jugador(jugador_t *jugador, accion_jugador_t *accion_jugad, 
    int accion, int accion_rival);
    
    /**
        @brief La funcion determina si el juego ha finalizado.

        @details LA funcion verifica que los dos jugadores tengan vida > 0. Si uno
        de los dos no lo tiene, devuelve un valor negativo acorde al jugador que esta
        muerto.

        @param [in] jugador_hum es un puntero a la estructura jugador_t que contiene
        la informacion de estado del jugador humano.

        @param [in] jugador_hum es un puntero a la estructura jugador_t que contiene
        la informacion de estado del jugador maquina.

        @pre Ambos punteros deben apuntar a memorias != NULL de tipo jugador_t

        @return HUMANO  si el jugador humano esta muerto, MAQUINA si la maquina esta muerta,
        AMBOS si ambos estan muertos (caso que podria ocurrir si en el ultimo turno ambos atacan
        y ambos mueren).

        @post Se devuelve el valor correspondiente al jugador que esta muerto.

        @invariant ninguna de las estructuras proporcionadas son modificadas.
    */
    int determ_jug_muerto(const jugador_t *const jugador_hum, const jugador_t *const jug_maquina); 

    /**
        @brief Esta funcion se encarga de resolver las acciones de ambos jugadores en un turno.

        @details La funcion se encarga de llenar las estructuras de tipo accion_jugador_t con las acciones
        realizadas por los jugadores en el turno. Recibe punteros a las estructuras del jugador y de la 
        maquina para poder resolver las acciones realizadas correctamente. 
        Recibe punteros a dos estructuras de tipo accion_jugador_t donde llenara la estructura correspondiente
        con los datos de la accion del jugador y de la maquina.
        Se modifican estructuras declaradas fuera de la funcion ya que, al tener 4 estructuras dentro de si, 
        seria un peso alto de retorno.
        Hace uso de las funciones 

        @param [in, out] jugador es un puntero a la estructura de tipo jugador_t que contiene la informacion 
        del jugador humano pertinente para la resolucion de las acciones.

        @param [in, out] maquina es un puntero a la estructura de tipo jugador_t que contiene la informacion 
        de la  maquina pertinente para la resolucion de las acciones.

        @param accion_jugador es un entero que representa la accion tomada por el jugador en el turno.
        Este entero es uno de los que aparecen en enum accion_activa_t.

        @param accion_maquina es un entero que representa la accion tomada por la maquina en el turno.
        Este entero es uno de los que aparecen en enum accion_activa_t.

        @param [out] acciones_jugador es un puntero a la estructura que contendra la accion del jugador.
        
        @param [out] acciones_maquina es un puntero a la estructura que contendra la accion de la maquina.

        @pre acciones_jugador y acciones_maquina deben ser puntero a estructuras VACIAS (para evitar errores)
        de tipo accion_jugador_t. maquina y jugador deben ser puntero a estructuras de tipo jugador_t con todos
        los datos pertinentes (como vida, energia, personaje) inicializados.

        @post Los campos de las  estrucutras 'acciones_jugador' y 'acciones_maquina' han sido llenadas con los
        datos pertinentes.

        @invariant accion_maquina y accion_jugador no cambian.
    */
    void resolucion_acciones(const jugador_t *const jugador, const jugador_t *const maquina, 
    int accion_jugador, int accion_maquina, accion_jugador_t *acciones_jugador, 
    accion_jugador_t *acciones_maquina);

    /** 
        @brief Esta funcion actualiza la estadistica de la defensa de un jugador.

        @details La funcion actualiza el miembro defensa del jugador. Si la accion es == CURAR, 
        divide a la mitad el miembro defensa. Si la accion es != CURAR, entonces lo restaura (de ser
        necesario) a la capacidad maxima del personaje del jugador.

        @param [in, out] jugador es un puntero a una estructura de tipo jugador_t del jugador del
        cual se quiere modificar su estadistica de defensa.
        
        @param accion es la accion que realizo el jugador.
    */
    void actualizar_defensa_por_accion(jugador_t *jugador, int accion);

    /**
        @brief imprime un separador usando el caracter '='

        @details crea un separador de 35 '='. Agrega un "\n" al final.
    */
    void imprimir_separador_sig_igual();

    /**
        @brief Esta funcion comprueba que el jugador tenga suficiente energia para poder
        realizar la accion de ATAQUE.

        @param [in] jugador es un puntero a la estructura de tipo jugador_t donde se alojan los
        datos del jugador humano. Se usara para leer la energia y compararla contra el minimo requerido para
        atacar.

        @param accion_jugador es un entero, proveniente de la struct accion_activa_t, que representa la
        accion realizada por el jugador. Se usa para comprobar la energia solo si se intento atacar.

        @pre jugador debe ser un puntero a una estructura de tipo jugador_t ya inicializada con los
        datos pertinentes del jugador.

        @return INVALIDA si tiene insuficiente energia. Si tiene suficiente energia, retorna 1. (este valor
        no es importante debido a como se maneja la logica en el main).
    */
    int comprobar_energ_ataq(const jugador_t *const jugador, int accion_jugador);

    /**
        @brief Esta funcion comprobara que la desicion de accion del jugador siga las reglas estipuladas
        por ej juego.

        @
    */
    int verific_valid_accion_jug(jugador_t *jugador, const int accion_jugador, int ataques_seguidos);

    /*
        @brief
    */
    void mostrar_opciones_accion();

    void verif_lect_correcta_accion(int *accion_jugador);


    /**
        @brief Esta funcion imprime un mensaje que anuncia quien gano.

        @warning No llamar a esta funcion dentro del proceso del juego, ya que
        la funcion esta pensada para mostrar quien fue el ganador.

        @details La funcion evalua el dato almacenado en jugador_muerto y,
        en base a el, imprime un mensaje anunciando ganador/perdedor/empate.

        @param jugador_muerto es un valor que representa alguno de los estados
        listados en jugador_muerto_t (excepto NINGUNO).

        @pre jugador_muerto debe ser uno de los valores listados en jugador_muerto_t
        (no puede ser = NINGUNO).

        @post Se imprimio el mensaje que anuncia al ganador.
    */
    void imprim_ganador(int jugador_muerto);



#endif