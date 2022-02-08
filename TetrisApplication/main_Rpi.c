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

#include "../rpi_resources/disdrv.h"
#include "../rpi_resources/joydrv.h"

#include "backend.h"
#include "menu_Rpi.h"
#include "juego_Rpi.h"

#include <SDL/SDL.h>
#include "../rpi_resources/libaudio.h"

char music[]="../rpi_resources/juego.wav";
char game_over_sound[]="../rpi_resources/sound_gameover.wav";

void juego(char* end_progam);


/*
 * 
 */

int main(void) {
    char finish = 0;
    joy_init(); //inicialización de display y joystick
    disp_init();
    init_sound();

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
            print_top_scores();
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
    
    
    while (!(*end_program)) //mientras no se active el flag para terminar programa
    {
        if (player_status()==FINISHED || player_status()==PLAYING || player_status()==PAUSED )
        {
            stop_sound();
        }
        
        set_file_to_play(music);      // Load file 			
	
	    play_sound(); 
        // CREAMOS VARIABLES NECESARIAS PARA EL JUEGO
        int matriz[FIL][COL];
        game_stats_t jugador;
        pieza_t in_use; //pieza cayendo
        pieza_t next; //pieza siguiente
        pieza_t hold; //pieza en hold
        hold.id=0; //le damos un id invalido al inicio para que no imprima nada
        hold.hold_previo=0; //esto habilita el holdeo de la siguiente pieza
        
        get_name(&jugador); //obtenemos el nick del jugador

        // INICIALIZACION VARIABLES
        clear_mat(matriz);
        init_jugador(&jugador); //llamamo a la función que inicializa las stats del juego  
        
        //jugador.level = 8;
        

        char fin_partida = 0; //inicializamos un flag que avisa el fin de la partida
        generador(&in_use, &jugador); //le damos los atributos a la pieza en uso

        while(!fin_partida && !(*end_program)){
            
            
            generador(&next, &jugador); //llamamos a la función que rellena los campos de la pieza
            
            while(!check(&in_use, matriz) && !fin_partida && !(*end_program)){
                
                if (player_status()==FINISHED) //revisamos que la musica no se haya cortado
                { 	
                    stop_sound();
                    set_file_to_play(music);	//si se corto, la reproducimos de nuevo	
                    play_sound(); 
                }

                print_mat(&in_use, matriz, &next, &hold, jugador.level); //actualizamos la pantalla led
                delay(&jugador, &in_use, matriz, &next, &hold, end_program, &fin_partida); //funcion que toma los movimientos y espera el tiempo para bajar
                if(mover_pieza(&in_use, matriz, ABA)) //con la función de mover, ya nos aseguramos que se pueda seguir bajando o no.
                {
                    setear_pieza(&in_use, &hold, matriz); //guardamos la pieza en la matriz
                    fila_completa(matriz, &jugador, &next, &hold); //vemos si se completo una fila para sumar puntos y eso
                    in_use = next; //igualamos la pieza que trabajamos a la siguiente
                    break;
                }
            }
            if(game_over(matriz)){
                int menu_option;
                stop_sound(); 
                set_file_to_play(game_over_sound);      // Load file 			
	            play_sound();
                //printf("GAME OVER\n Final Score: %ld\n Level: %d\n", jugador.score, jugador.level);
                top_scores(&jugador);
                print_game_over(); //imprimimos pantalla final
                show_score(&jugador);
                while (!fin_partida)
                {
                    menu_option = menu_game_over();
                    switch (menu_option)
                    {
                    case 1: //mostrar TOP Scores
                        print_top_scores();
                        break;
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
}




