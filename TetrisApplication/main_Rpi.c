/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Rpi.c
 * Author: ezequiel
 *
 * Created on January 12, 2022, 6:29 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "rules.h"
#include "termlib.h"
#include "disdrv.h"
#include "joydrv.h"

#include "piezas.h"
#include "menu.h"
#include "raspi.h"




void juego(char* end_progam);


/*
 * 
 */

int main(void) {
    char finish = 0;
    joy_init(); //inicialización de display y joystick
    disp_init();

    while (!finish)
    {         
           
           
        srand(time(NULL)); //genero una semilla randomizada

        
        int menu_option = menu_start();
        switch (menu_option)
        {
        case 0: //juego
            juego(&finish);
            break;
        case 1: //Top
            break;
        case 2: //Abandonar
            finish =1;
            disp_clear();
            break;
        default:
            break;
        }
        
    }
    return 0;
}


void juego(char* end_program){
    /*EMPIEZA LA PARTE DEL JUEGO*/
    while (!(*end_program)) //esto es una doble verificacion, por ahora no veo otra forma
    {
    
        // CREO VARIABLES NECESARIAS PARA EL JUEGO
        int matriz[FIL][COL];
        game_stats_t jugador;
        pieza_t in_use;
        pieza_t next;
        
        get_name(&jugador);

        // INICIALIZACION VARIABLES
        clear_mat(matriz);
        init_jugador(&jugador); //llamamo a la función que inicializa las stats del juego  
        
        jugador.level = 7;
        

        char fin_partida = 0;
        generador(&in_use, &jugador);

        while(!fin_partida && !(*end_program)){
            
            generador(&next, &jugador); //llamamos a la función que rellena los campos de la pieza
            
            while(!check(&in_use, matriz) && !fin_partida && !(*end_program)){
                
                print_mat(&in_use, matriz, &next);
                delay(jugador.level, &in_use, matriz, &next, end_program, &fin_partida);
                if(mover_pieza(&in_use, matriz, ABA)) //con la función de mover, ya nos aseguramos que se pueda seguir bajando o no.
                {
                    setear_pieza(&in_use, matriz); //guardamos la pieza en la matriz
                    fila_completa(matriz, &jugador, &in_use, &next); //vemos si se completo una fila para sumar puntos y eso
                    in_use = next; //igualamos la pieza que trabajamos a la siguiente
                    break;
                }
            }
            if(game_over(matriz)){
                int menu_option;
                printf("GAME OVER\n Final Score: %ld\n Level: %d\n", jugador.score, jugador.level);
                top_scores(&jugador);
                print_game_over(); //imprimimos pantalla final
                menu_option = menu_game_over();
                switch (menu_option)
                {
                case 2: //terminar programa
                    fin_partida = 1;
                    *end_program =1;
                    disp_clear();
                    break;
                case 3: //reiniciar partida
                    fin_partida = 1;
                    break;
                default:
                    break;
                }
                
                
            }
        
        }
    }
}