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

void delay(int level, pieza_t* in_use, int matriz[FIL][COL], pieza_t*next);
void get_name(game_stats_t* jugador);
void print_letter(int option, int index);
void print_flechas_verticales(int offset_x);
void col_clear(int col);

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

        get_name(&jugador);

        char fin_partida = 0;
        generador(&in_use, &jugador);
        jugador.level=5;

        while(!fin_partida){
            
            generador(&next, &jugador); //llamamos a la función que rellena los campos de la pieza
            
            while(!check(&in_use, matriz)){
                
                print_mat(&in_use, matriz, &next);
                delay(jugador.level, &in_use, matriz, &next);
                if(mover_pieza(&in_use, matriz, ABA)) //con la función de mover, ya nos aseguramos que se pueda seguir bajando o no.
                {
                    setear_pieza(&in_use, matriz); //guardamos la pieza en la matriz
                    fila_completa(matriz, &jugador, &in_use, &next); //vemos si se completo una fila para sumar puntos y eso
                    in_use = next; //igualamos la pieza que trabajamos a la siguiente
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
    
    // ANALIZA SI SE MOVIO EL JOYSTICK (unsigned)((u<0)?-u:u)
    joy_update();
    coordenada = joy_get_coord();
        
    if ((coordenada.x > -75)&&(coordenada.x < 75)&&(coordenada.y > -75)&&(coordenada.y < 75)) {
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



void delay(int level, pieza_t* in_use, int matriz[FIL][COL], pieza_t* next) {
    float number_of_seconds = 0.7 - ((float)((level) - 1) * 0.07);
    char opc;
    char exit = 0;
    char ABA_counter = 0; //esto es para ver si bajo 2 veces rapido
    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (!exit) {
        opc = get_option();
        
        switch (opc) {
            case ABA:
                while ((get_option())) //esperamos a que vuelva para cambiar
                {
                    if(clock() >= start_time + number_of_seconds * CLOCKS_PER_SEC)
                    {
                        break;
                    }
                }
                    ABA_counter++;
                    if (ABA_counter >=2)
                    {
                        all_down(in_use, matriz);
                    }
                    else{
                    mover_pieza(in_use, matriz, opc);
                    print_mat(in_use, matriz, next);
                    }
                               
                break;
            case DER:
            case IZQ:
                while ((get_option())) //esperamos a que vuelva para cambiar
                {
                    if(clock() >= start_time + number_of_seconds * CLOCKS_PER_SEC)
                    {
                        break;
                    }
                }
                    mover_pieza(in_use, matriz, opc);
                    print_mat(in_use, matriz, next);
                               
                break;
            case ROTAR:
                while ((get_option())) //esperamos a que vuelva para cambiar
                {
                    if(clock() >= start_time + number_of_seconds * CLOCKS_PER_SEC)
                    {
                        break;
                    }
                }
                    rotar(in_use, matriz);
                    print_mat(in_use, matriz, next);
                
                break;
            case MENU:
                    
                break;
        }
        if(clock() >= start_time + number_of_seconds * CLOCKS_PER_SEC){
            exit = 1;
        }
    }
}

void get_name(game_stats_t* jugador){
    char signal;
    char letras[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    int option = 0; 
    int i=0;
    disp_clear();
    
   
   for (i = 0; i < 3; i++)
   {   
        print_letter(option, i);
        while ( (signal = get_option()) != MENU)
        {   
                switch (signal)
                {
                case ABA:
                    while ((get_option())) //esperamos a que vuelva para cambiar
                    {
                        ;
                    }
                        option++; 
                        option = (option)%26;
                        print_letter(option, i);
                    
                    break;
                case ROTAR:
                    while ((get_option())) //esperamos a que vuelva para cambiar
                    {
                        ;
                    }
                        
                        if (option==0)
                        {
                            option = 25;
                        }
                        else{
                            option --;
                        }
                        print_letter(option, i);
                    
                    break;
                default:
                    break;
                }
                
        }
        while ((get_option())) //esperamos a que vuelva para cambiar
            {
                ;
            }
        printf("%c\n",letras[option]);
        //jugador->nick[i] = letras[option];
   }


}

void print_letter(int option, int index){
        int offset_x;
        dcoord_t coord;
        int i,j;
        switch (index) //es para ver que casilla de letra imprimir, la 1era, 2da o 3era
        {
        case 0:
                       
            offset_x=0;
            for ( i = offset_x; i < offset_x+4; i++)
            {
                col_clear(i);
            }
            break;
        case 1:
            offset_x=6;
            for ( i = offset_x; i < offset_x+4; i++)
            {
                col_clear(i);
            }
            
            break;
        case 2:
            offset_x=12;
            for ( i = offset_x; i < offset_x+4; i++)
            {
                col_clear(i);
            }

            break;
        default:
            break;
        }

        switch (option) //Aca imprimimos la letra que corresponde
        {
        case 0: //letra A

            for (i = 0; i < 4; i++) //lo hago con logica inversa, primero prendo todo y dsp apago (mas corto a veces)
            {
                for ( j = 5; j < 10; j++)
                {
                    coord.x= i + offset_x; coord.y=j;
                    disp_write(coord,D_ON);
                }
                
            }
            
            coord.x= 0 + offset_x; coord.y= 5;
            disp_write(coord, D_OFF);
            coord.x= 3 + offset_x; coord.y= 5;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= 6;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= 6;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= 8;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= 8;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= 9;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= 9;
            disp_write(coord, D_OFF);

            break;

        case 1: //letra B

            for (i = 0 + offset_x; i < offset_x + 4; i++) //lo hago con logica inversa, primero prendo todo y dsp apago (mas corto a veces)
            {
                for ( j = 5; j < 10; j++)
                {
                    coord.x=i; coord.y=j;
                    disp_write(coord,D_ON);
                }
                
            }
            
            coord.x= 3 + offset_x; coord.y= 5;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= 6;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= 6;
            disp_write(coord, D_OFF);
            coord.x= 3 + offset_x; coord.y= 7;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= 8;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= 8;
            disp_write(coord, D_OFF);
            coord.x= 3 + offset_x; coord.y= 9;
            disp_write(coord, D_OFF);
            
            break;

        case 2: //letra C

                        
            coord.x= 1 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 6;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 7;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 8;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);
            
            break;

        case 3: //letra D

            for (i = 0 + offset_x; i < offset_x + 4; i++) //lo hago con logica inversa, primero prendo todo y dsp apago (mas corto a veces)
            {
                for ( j = 5; j < 10; j++)
                {
                    coord.x=i; coord.y=j;
                    disp_write(coord,D_ON);
                }
                
            }
            
            coord.x= 3 + offset_x; coord.y= 5;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= 6;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= 6;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= 7;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= 7;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= 8;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= 8;
            disp_write(coord, D_OFF);
            coord.x= 3 + offset_x; coord.y= 9;
            disp_write(coord, D_OFF);
            
            break;
        
        case 4: //letra E

            for (i = 0 + offset_x; i < offset_x + 4; i++) //lo hago con logica inversa, primero prendo todo y dsp apago (mas corto a veces)
            {
                for ( j = 5; j < 10; j++)
                {
                    coord.x=i; coord.y=j;
                    disp_write(coord,D_ON);
                }
                
            }
            
            coord.x= 1 + offset_x; coord.y= 6;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= 6;
            disp_write(coord, D_OFF);
            coord.x= 3 + offset_x; coord.y= 6;
            disp_write(coord, D_OFF);
            coord.x= 3 + offset_x; coord.y= 7;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= 8;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= 8;
            disp_write(coord, D_OFF);
            coord.x= 3 + offset_x; coord.y= 8;
            disp_write(coord, D_OFF);
            
            break;

        case 5: //letra F

            for (i = 0 + offset_x; i < offset_x + 4; i++) //lo hago con logica inversa, primero prendo todo y dsp apago (mas corto a veces)
            {
                for ( j = 5; j < 10; j++)
                {
                    coord.x=i; coord.y=j;
                    disp_write(coord,D_ON);
                }
                
            }
            
            coord.x= 1 + offset_x; coord.y= 6;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= 6;
            disp_write(coord, D_OFF);
            coord.x= 3 + offset_x; coord.y= 6;
            disp_write(coord, D_OFF);
            coord.x= 3 + offset_x; coord.y= 7;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= 8;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= 8;
            disp_write(coord, D_OFF);
            coord.x= 3 + offset_x; coord.y= 8;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= 9;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= 9;
            disp_write(coord, D_OFF);
            coord.x= 3 + offset_x; coord.y= 9;
            disp_write(coord, D_OFF);
            
            break;

        case 6: //letra G

            for (i = 0 + offset_x; i < offset_x + 4; i++) //lo hago con logica inversa, primero prendo todo y dsp apago (mas corto a veces)
            {
                for ( j = 5; j < 10; j++)
                {
                    coord.x=i; coord.y=j;
                    disp_write(coord,D_ON);
                }
                
            }
            
            coord.x= 0 + offset_x; coord.y= 5;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= 6;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= 6;
            disp_write(coord, D_OFF);
            coord.x= 3 + offset_x; coord.y= 6;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= 7;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= 8;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= 8;
            disp_write(coord, D_OFF);
            coord.x= 0 + offset_x; coord.y= 9;
            disp_write(coord, D_OFF);
            
            break;

        case 7: //letra H

            for (i = 0 + offset_x; i < offset_x + 4; i++) //lo hago con logica inversa, primero prendo todo y dsp apago (mas corto a veces)
            {
                for ( j = 5; j < 10; j++)
                {
                    coord.x=i; coord.y=j;
                    disp_write(coord,D_ON);
                }
                
            }
            
            coord.x= 1 + offset_x; coord.y= 5;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= 5;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= 6;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= 6;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= 8;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= 8;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= 9;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= 9;
            disp_write(coord, D_OFF);
            
            break;

        case 8: //letra I

                        
            coord.x= 0 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 6;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 7;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 8;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);

            break;

        case 9: //letra J

                        
            coord.x= 3 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 6;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 7;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 8;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 8;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);
            
            break;

        case 10: //letra K

                        
            coord.x= 0 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 6;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 7;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 8;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= 6;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= 7;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= 8;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);

            break;

        case 11: //letra L

                        
            coord.x= 0 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 6;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 7;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 8;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);

            break;

        case 12: //letra H

                        
            coord.x= 0 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 6;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 7;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 8;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= 6;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= 6;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 6;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 7;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 8;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);

            break;

        case 13: //letra N

                        
            coord.x= 0 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 6;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 7;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 8;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= 7;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= 8;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 6;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 7;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 8;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);

            break;

        case 14: //letra O

                        
            coord.x= 1 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 6;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 6;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 7;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 7;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 8;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 8;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);

            break;

        case 15: //letra P

                        
            coord.x= 0 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 6;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 6;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 7;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= 7;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= 7;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 8;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);

            break;

        case 16: //letra Q

                        
            coord.x= 1 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 6;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 6;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 7;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 7;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 8;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 8;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= 8;
            disp_write(coord, D_ON);

            break;

        case 17: //letra R

            for (i = 0 + offset_x; i < offset_x + 4; i++) //lo hago con logica inversa, primero prendo todo y dsp apago (mas corto a veces)
            {
                for ( j = 5; j < 10; j++)
                {
                    coord.x=i; coord.y=j;
                    disp_write(coord,D_ON);
                }
                
            }
            
            coord.x= 3 + offset_x; coord.y= 5;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= 6;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= 6;
            disp_write(coord, D_OFF);
            coord.x= 3 + offset_x; coord.y= 7;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= 8;
            disp_write(coord, D_OFF);
            coord.x= 3 + offset_x; coord.y= 8;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= 9;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= 9;
            disp_write(coord, D_OFF);
            
            
            break;

        case 18: //letra S

                        
            coord.x= 1 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 6;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= 7;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= 7;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 8;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);

            break;

        case 19: //letra T

            coord.x= 0 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);            
            coord.x= 1 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= 6;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= 7;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= 8;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);

            break;

        case 20: //letra U

                      
            coord.x= 0 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 6;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 7;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 8;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);
            
            coord.x= 3 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 6;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 7;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 8;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);

            coord.x= 1 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);  
            coord.x= 2 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);

            break;

        case 21: //letra V

                      
            coord.x= 0 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 6;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 7;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 8;
            disp_write(coord, D_ON);
                        
            coord.x= 3 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 6;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 7;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 8;
            disp_write(coord, D_ON);
            

            coord.x= 1 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);  
            coord.x= 2 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);

            break;

        case 22: //letra W

                      
            coord.x= 0 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 6;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 7;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 8;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= 8;
            disp_write(coord, D_ON);
            
            coord.x= 3 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 6;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 7;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 8;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= 8;
            disp_write(coord, D_ON);

            coord.x= 1 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);  
            coord.x= 2 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);

            break;

        case 23: //letra X

                      
            coord.x= 0 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 6;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= 7;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= 8;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);
            
            coord.x= 3 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 6;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= 7;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= 8;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);

            break;

        case 24: //letra Y

            coord.x= 0 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);            
            coord.x= 2 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 6;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= 6;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 7;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= 7;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= 7;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= 8;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);

            break;

        case 25: //letra Z

                        
            coord.x= 0 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 5;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 6;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= 7;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= 8;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= 9;
            disp_write(coord, D_ON);

            break;
        
        default:
            break;
        }
        print_flechas_verticales(offset_x);
        disp_update();
}

void print_flechas_verticales(int offset_x){
        dcoord_t coord;
        coord.x= 1 + offset_x;
        coord.y=0;
        disp_write(coord, D_ON);
        coord.x= 0 + offset_x;
        coord.y=1;
        disp_write(coord, D_ON);
        coord.x= 1 + offset_x;
        coord.y=1;
        disp_write(coord, D_ON);
        coord.x= 2 + offset_x;
        coord.y=1;
        disp_write(coord, D_ON);
        coord.x= 1 + offset_x;
        coord.y=15;
        disp_write(coord, D_ON);
        coord.x= 0 + offset_x;
        coord.y=14;
        disp_write(coord, D_ON);
        coord.x= 1 + offset_x;
        coord.y=14;
        disp_write(coord, D_ON);
        coord.x= 2 + offset_x;
        coord.y= 14;
        disp_write(coord, D_ON);
}

void col_clear(int col){
    int i;
    dcoord_t coord;
    coord.x = col; 
    for (i = 0; i < 16; i++)
    {
        coord.y=i;
        disp_write(coord, D_OFF);
    }
    

}