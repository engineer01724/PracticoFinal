#ifndef ARCHIVOS
    #define ARCHIVOS

    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    #include<stdbool.h>
    #include "combate.h"
     
    typedef struct 
    {
        int puntaje_humano;
        int puntaje_maquina;
    }score_t;
    
    /**
        @brief Esta funcion lee el score global desde el archivo 'score.txt'.

        @details Si 'score.txt' tiene formato incorrecto o no existe, lo crea e 
        inicializa a 0-0.

        @param [out] score es un puntero a una estructura de tipo score_t
        la cual se llenara con los datos obtenidos del archivo.

        @pre score debe ser un puntero != NULL a una estructura score_t.

        @return true si la operacion exitosa. false si se prudujo algun error.

        @post Se lleno la estructura score.
    */
    bool obtener_score_global(score_t *score);

    /**
        @brief Escribe o sobreescribe los datos que muestra el archivo 'score.txt'.

        @param [in] score es un puntero a una estructura score_t que contiene los datos
        actuales que se quieren guardar.

        @pre score debe ser un puntero != NULL a una estructura score_t.

        @return true si la operacion fue exitosa. false si se producjo algun error.
    */
    bool escribir_score_global(const score_t *score);

    /**
        @brief Modifica el score con puntajes proporcionados por parametros.

        @details La funcion recibe el puntaje que se le quiere sumar al humano, el
        que se quiere sumar a la maquina y un puntero a la estructura que se quiere
        modificar.

        @param [out] score es un puntero a una estructura score_t que se quiere modificar.

        @param puntaje_humano es el puntaje que se quiere sumar al humano.

        @param puntaje_maquina es el puntaje que se quiere sumar a la maquina.

        @pre score debe ser un puntero != NULL a una estructura score_t.

        @post Se edito la estructura score proporcionada por parametros, en base a los 
        valores proporcionados.
    */
    void modificar_score(score_t *score, int puntaje_humano, int puntaje_maquina);

    /**
        @brief Esta funcion modifica una estruct. score_t dependiendo de quien haya
        perdido.

        @details La funcion aumenta en 1 el puntaje del jugador que no perdio la partida.
        Se usa el parametro del perdedor y no del ganador por conveniencia, ya que el 
        juego proporciona informacion del jugador que perdio, no del que gano.

        @param [in] score es un puntero a una estructura score_t la cual sera modificada
        segun quien perdio.

        @param perdedor es el valor que representa el jugador que perdio la partida. 
        
        @pre score debe ser un puntero != NULL a una estruc. score_t.

        @post Se modifico score de manera acorde al perdedor y al ganador de la partida.
    */
    void modif_score_segun_ganad(score_t *score, int perdedor);

    /**
        @brief Esta funcion imprime quien va ganando en el score global.

        @details. La funcion evalua quien esta ganando segun la estructura
        score_t proporcionada y escribe quien va ganando.

        @param [in] score es un puntero a una estructura score_t con los datos
        del score entre el jugador y la maquina.

        @pre score debe ser un puntero != NULL a una estructura score_t.

        @post Se imprimio quien es el jugador que va adelante en el marcador.
    */
    void escribir_lider_score(const score_t *score);

    
#endif