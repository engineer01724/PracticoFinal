#ifndef COMBATE
    #define COMBATE
    #define EULER 2.7182818
    #define CONST_DEFENSA 0.7
    #define CONST_ACCION_DEFENSA 0.5

    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    #include<stdbool.h>
    #include<math.h>
    #include "combate.h"

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
        int aumento_energia; //Aumento de energia producido en la accion de curar.
        int reduc_energ_ataq; //Cantidad de energia reducida al realizar un ataque.
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

    typedef struct
    {
        char accion_jugad[32];
        char accion_maquin[32];
        int vida_restante_jugador;
        int escudo_restante_jugador;
        int energia_restante_jugador;
        int vida_restante_maquina;
        int escudo_restante_maquina;
        int energia_restante_maquina;
        size_t turno;
        bool mem_ped_correct;
    }turno_t;

    /**
        @brief Esta funcion crea un arreglo dinamico de elementos de tipo turno_t 
        de capacidad tamanio.

        @param tamanio es el tamanio del arreglo que se quiere crear.

        @return un puntero a la memoria dinamica donde se aloja el recurso del 
        arreglo de turno_t(s).

        @post Se creo y retorno el recurso pedido, de tamanio tamanio.

        @invariant tamanio no cambia de valor.
    */
    turno_t *crear_arreglo_turnos(const size_t tamanio);
    
    /**
        @brief La funcion agrega una cantidad de elementos a un arreglo de turno_t(s).

        @param [out] arr_turno es un puntero al arreglo de turno_t al que se quiere
        agregar mas elementos.

        @param cant_actual es la cantidad actual de elementos del arreglo.

        @param cant_agregar es la cantidad de elementos que se quiere agregar.

        @pre cant_actual debe ser > 0. cant_agregar debe ser > 0.

        @return un puntero a un nuevo arreglo dinamico de tamanio cant_actual + 
        cant_agregar.
    */
    turno_t *agregar_turno(turno_t *arr_turno, size_t cant_actual, size_t cant_agregar);
    
    /**
        @brief Esta funcion crea un arreglo dinamico de elementos de tipo personaje_t
        de capacidad tamanio.
        
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
        @brief Esta funcion destruye memoria dinamica previamente pedida.
        
        @param [in, out] ptr_mem es un puntero al puntero que apunta a la direccion 
        dinamica que se desea liberar.

        @post Se libero la memoria dinamica y al puntero a la misma se le ha asignado 
        el valor NULL.
    */
    void destruir_memoria(void **ptr_mem);
    
    /**
        @brief Esta funcion imprime un personaje_t.

        @param [in] personaje es un puntero a la estructura de tipo personaje_t
        que desea imprimirse.

        @pre personaje debe ser un puntero a una direccion != NULL de tipo personaje_t.

        @post Se imprimio el personaje. 

        @invariant personaje no es modificado.
    */
    void imprimir_personaje(const personaje_t *const personaje);

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
        @brief Esta funcion crea un personaje con estadisticas random y lo devuelve.

        @details Esta funcion utilizara mucho la funcion rand() para obtener valores
        random dentro de un cierto rango, para asegurar que cada vez los personajes
        tengan estadisticas diferentes.Los rangos son los especificados en la 
        documentacion de la estructura personaje_t.

        @return Un personaje_t con estadisticas random.

        @post El personaje creado y retornado tiene estadisticas elegidas al azar.
    */
    personaje_t crear_personaje_random();

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
    defensa_t calcular_defensa(jugador_t *jugador_en_defensa, 
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
    const jugador_t *const jug_maquina);

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
#endif