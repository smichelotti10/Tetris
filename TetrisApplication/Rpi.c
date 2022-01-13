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

char get_option (void);
void print_mat (pieza_t* in_use, int matriz[FIL][COL], pieza_t*next);
void delay(int level, pieza_t* in_use, int matriz[FIL][COL], pieza_t*next);

/*
 * 
 */
int main(void) {
    char finish = 0;
    while (!finish)
    {
           
        srand(time(NULL)); //genero una semilla randomizada
    
        // CREO VARIABLES NECESARIAS PARA EL JUEGO
        int matriz[FIL][COL];
        game_stats_t jugador;
        pieza_t in_use;
        pieza_t next;
        
        // INICIALIZACION VARIABLES
        clear_mat(matriz);
        init_jugador(&jugador); //llamamo a la función que inicializa las stats del juego  
        joy_init();
        disp_init();
        jugador.level = 5;
        char fin_partida = 0;
        generador(&in_use, &jugador);
        while(!fin_partida){
            
            generador(&next, &jugador); //llamamos a la función que rellena los campos de la pieza
            
            while(!check(&in_use, matriz)){
                print_mat(&in_use, matriz, &next);
                    delay(jugador.level, &in_use, matriz, &next);
                    if(mover_pieza(&in_use, matriz, ABA)) //con la función de move, ya nos aseguramos que se pueda seguir bajando o no.
                    {
                        setear_pieza(&in_use, matriz); //guardamos la pieza en la matriz
                        fila_completa(matriz, &jugador); //vemos si se completo una fila para sumar puntos y eso
                        in_use = next;
                        break;
                    }
            }
            if(game_over(matriz)){
                printf("GAME OVER\n Final Score: %ld\n Level: %d\n", jugador.score, jugador.level);
                fin_partida = 1;
            }
        
        }
    }
    return 0;
}

char get_option (void) {
    
    jcoord_t coordenada;
    jswitch_t boton;
    
    // ANALIZA SI SE APRETÓ EL SWITCH
    joy_update();    
    boton = joy_get_switch();
    
    if (boton == J_PRESS) {
        return MENU;
    }    
    
    // ANALIZA SI SE MOVIO EL JOYSTICK
    joy_update();
    coordenada = joy_get_coord();
    
    if ((coordenada.x > -3)&&(coordenada.x < 3)&&(coordenada.y > -3)&&(coordenada.y < 3)) {
        return VACIO;
    }
    else {
        if (((-coordenada.x)>(coordenada.y))&&((-coordenada.x)>(-coordenada.y))) {
            return IZQ;
        }
        else if (((coordenada.x)>(coordenada.y))&&((coordenada.x)>(-coordenada.y))) {
            return DER;
        }
        else if (((-coordenada.x)<=(-coordenada.y))&&((coordenada.x)<=(-coordenada.y))) {
            return ABA;
        }
        else if (((-coordenada.x)<=(coordenada.y))&&((coordenada.x)<=(coordenada.y))) {
            return ROTAR;
        }
    }
    return VACIO;    
}

void print_mat (pieza_t* in_use, int matriz[FIL][COL], pieza_t* next) {
    int i, j, k;
    dcoord_t coord;

    disp_clear();
    
    for ( i = 0; i < 4; i++)
    {
        coord.x = (next->mat_bloque[0][i]) + 11;
        coord.y = (next->mat_bloque[1][i]) + 2;
        disp_write(coord, D_ON);
    }
    

    for (i=4; i<FIL; i++) {
        
        for (j=0; j<COL; j++) {

            if (matriz[i][j]!=0) {
                coord.x = j;
                coord.y = i-4;
                disp_write(coord, D_ON);
            }
            else { 

                int print = 0;
                for (k=0; k<4; k++) {
                    if ( j == ((in_use->mat_bloque[0][k])+(in_use->coord_x)) && i == ((in_use->mat_bloque[1][k])+(in_use->coord_y))) {

                        print=1;
                    }
                }
                
                coord.x = j;
                coord.y = i-4;
                
                if (print==1) {
                    disp_write(coord, D_ON);
                }
                else {
                    disp_write(coord, D_OFF);
                }
            }
        }
        
    }
    
    disp_update();
}

void delay(int level, pieza_t* in_use, int matriz[FIL][COL], pieza_t* next) {
    float number_of_seconds = 0.7 - ((float)((level) - 1) * 0.07);
    char opc;
    char exit = 0;
    char ABA_counter = 0;
    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (!exit) {
        opc = get_option();
        
        switch (opc) {
            case ABA:
                if (!(get_option()))
                {
                    ABA_counter++;
                    if (ABA_counter >=2)
                    {
                        all_down(in_use, matriz);
                    }
                    else{
                    mover_pieza(in_use, matriz, opc);
                    print_mat(in_use, matriz, next);
                    }
                }               
                break;
            case DER:
            case IZQ:
                if (!(get_option()))
                {
                    mover_pieza(in_use, matriz, opc);
                    print_mat(in_use, matriz, next);
                }               
                break;
            case ROTAR:
                if (!(get_option()))
                {
                    rotar(in_use, matriz);
                    print_mat(in_use, matriz, next);
                }
                break;
            case MENU:
                    
                break;
        }
        if(clock() >= start_time + number_of_seconds * CLOCKS_PER_SEC){
            exit = 1;
        }
    }
}