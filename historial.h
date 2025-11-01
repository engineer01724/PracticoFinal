#ifndef HISTORIAL
    #define HISTORIAL

    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    #include<stdbool.h>
    #include<math.h>
    #include "combate.h"
    
    typedef struct nodo nodo_t; 
    typedef struct historial_turnos historial_turnos_t;

    /**
        @brief CONSTRUCTOR. Crea el inicio de una lista enlazada dinamica de tipo 
        historial_turnos_t haciendo uso de la funcion malloc.
        
        @details La funcion llamadora es la encargada de liberar la memoria de la 
        lista y de todos sus nodos haciendo uso de la funcion 'historial_destruir'

        @return un puntero a la direccion en el heap donde se encuentra el inicio de la 
        lista enlazada. Si fallo la operacion, devuelve NULL.

        @post Se creo el inicio de la lista dinamica, o se retorno NULL si fallo la creacion
        de la misma.
    */
    historial_turnos_t *crear_historial_turnos();

    /**
        @brief MUTADOR. Agrega un turno al final del historial de turnos de manera
        dinamica (usando el heap).

        @details La funcion llamadora es luego responsable de liberar la memoria que
        ocupan todos los nodos que fueron creados por esta funcion.

        @param [out] historial es un puntero al inicio de la lista enlazada 
        historial_turnos_t, desde donde de enlazan los turnos siguientes.

        @param [in] turno es un puntero a la estructura turno_t que se enlazara
        al final del historial.

        @pre tanto historial como turno deben ser punteros != NULL a direcciones
        de su correspondiente tipo.

        @return true si la operacion fue exitosa. false si hubo algun error.
        
        @post Se agrego un nuevo nodo al final de la lista.
    */
    bool historial_agregar_fin(historial_turnos_t *historial, turno_t *turno);

    /**
        @brief ITERADOR. Imprime el historial completo de turnos.

        @param [in] historial es un puntero a la estructura opaca historial_turnos_t
        que se quiere imprimir.

        @pre historial debe ser un puntero != NULL a una memoria de tipo historial_turnos_t.

        @post Se imprimio el historial completo de turnos.

        @invariant historial no es modificado.
    */
    void historial_imprimir(const historial_turnos_t *historial);

    /**
        @brief DESTRUCTOR. Destruye la lista completa de turnos creados dinamicamente.

        @details La funcion lidia con la posibilidad de que el puntero del parametro sea 
        ==NULL.

        @param [out] historial es un puntero al puntero a la direccion en el heap donde se 
        aloja la lista enlazada de tipo historial_turnos_t.

        @post Se libero la memoria que ucupaba el historial de turnos y se le asigno NULL
        al puntero que apuntaba a dicha memoria.
    */
    void historial_destruir(historial_turnos_t **historial);

    /**
        @brief SELECTOR. Esta funcion obtiene y devuelve una referencia al ultimo 
        turno agregado al historial.

        @param [in] historial es un puntero al historial de turnos.

        @pre historial debe ser un puntero != NULL a una esturctura opaca historial_turnos_t.

        @return un puntero hacia ultimo turno_t agregado al historial.

        @post Se leyo y devolvio una referencia del ultimo turno agregado al historial.

        @invariant historial no es modificado.
    */
    const turno_t *historial_ultim_turno(const historial_turnos_t *historial);

    /**
        @brief Esta funcion guarda la partida jugada en un archivo de nombre nombre_arch.

        @param [in] historial es un puntero al inicio del historial de turnos. Se usara para
        saber desde donde iniciar a iterar para conseguir los turnos.

        @param [in] nombre_arch es una cadena con el nombre que se le pondra al archivo en el que 
        se guardara el historial de turnos de la partida.

        @pre nombre_arch debe ser un puntero != NULL con una cadena valida para guardar el nombre 
        del archivo. historial debe ser un puntero != NULL a una estructura historial_turnos_t.

        @return true si la operacion fue un exito. false si hubo algun error al imprimir la partida
        en el archivo.

        @post Se guardo el historial de turnos en el archivo de nombre nombre_arch.

        @invariant historial y nombre_arch NO se ven modificados.
    */
    bool historial_guardar_archivo(const historial_turnos_t *historial, const char *nombre_arch);

    /**
        @brief imprime un separador en un flujo de archivo usando el caracter '='.

        @details crea un separador de 35 '='. Agrega un "\n" al final.
    */
    void imprimir_separador_archivo(FILE *archivo);

#endif