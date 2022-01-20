#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "rules.h"
#include "piezas.h"
#include "menu.h"
#include "raspi.h"

#include "termlib.h"
#include "disdrv.h"
#include "joydrv.h"



void print_mat (pieza_t* in_use, int matriz[FIL][COL], pieza_t* next) {
    int i, j, k;
    dcoord_t coord;

    disp_clear();
    if (next != NULL)
    {       
        for ( i = 0; i < 4; i++) //En esta parte imprimimos la pieza futura
        {
            coord.x = (next->mat_bloque[0][i]) + 11;
            coord.y = (next->mat_bloque[1][i]) + 2;
            disp_write(coord, D_ON);
        }
    }

    for (i=4; i<FIL; i++) {
        
        for (j=0; j<COL; j++) {

            if (matriz[i][j]!=0) {
                coord.x = j;
                coord.y = i-4;
                disp_write(coord, D_ON);
            }
            else if(in_use != NULL){ 

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

void delay(int level, pieza_t* in_use, int matriz[FIL][COL], pieza_t* next, char* end_game, char* restart_game) {
    float number_of_seconds = 0.7 - ((float)((level) - 1) * 0.07);
    char opc;
    char exit = 0;
    char ABA_counter = 0; //esto es para ver si bajo 2 veces rapido
    int menu_option;
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
                while ((get_option()))
                {
                    ;
                }
                menu_option = menu_pausa();
                switch (menu_option)
                {
                case 0: //reanudar juego
                    
                    break;
                case 1: //Top Scores

                    break;
                case 2: //Abandonar el juego
                    *end_game = 1;
                    disp_clear();
                    break;
                case 3: //Reiniciar juego
                    *restart_game = 1;
                    break;
                default:
                    break;
                }
                break;
            default:
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
        print_letter(option, i,0,0); //0 y 0 pq no tienen offset, son los predispuestos
        print_flechas_verticales(i*6);
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
                        print_letter(option, i,0,0);
                        print_flechas_verticales(i*6);
                    
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
                        print_letter(option, i,0,0);
                        print_flechas_verticales(i*6);
                    
                    break;
                default:
                    break;
                }
                
        }
        while ((get_option())) //esperamos a que vuelva para cambiar
            {
                ;
            }
        
        jugador->nick[i] = letras[option];
        
   }
    printf("Nombre:");
    for ( i = 0; i < 4; i++)
    {
        printf("%c", jugador->nick[i]);
    }
    printf("\n");

}

void print_letter(int option, int index, int offset_x, int offset_y){
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

            for (i = 0 + offset_x; i < offset_x + 4; i++) //lo hago con logica inversa, primero prendo todo y dsp apago (mas corto a veces)
            {
                for ( j = 5 + offset_y; j < 10 + offset_y; j++)
                {
                    coord.x= i; coord.y=j;
                    disp_write(coord,D_ON);
                }
                
            }
            
            coord.x= 0 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_OFF);
            coord.x= 3 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_OFF);

            break;

        case 1: //letra B

            for (i = 0 + offset_x; i < offset_x + 4; i++) //lo hago con logica inversa, primero prendo todo y dsp apago (mas corto a veces)
            {
                for ( j = 5 + offset_y; j < 10 + offset_y; j++)
                {
                    coord.x=i; coord.y=j;
                    disp_write(coord,D_ON);
                }
                
            }
            
            coord.x= 3 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_OFF);
            coord.x= 3 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_OFF);
            coord.x= 3 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_OFF);
            
            break;

        case 2: //letra C

                        
            coord.x= 1 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);
            
            break;

        case 3: //letra D

            for (i = 0 + offset_x; i < offset_x + 4; i++) //lo hago con logica inversa, primero prendo todo y dsp apago (mas corto a veces)
            {
                for ( j = 5 + offset_y; j < 10 + offset_y; j++)
                {
                    coord.x=i; coord.y=j;
                    disp_write(coord,D_ON);
                }
                
            }
            
            coord.x= 3 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_OFF);
            coord.x= 3 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_OFF);
            
            break;
        
        case 4: //letra E

            for (i = 0 + offset_x; i < offset_x + 4; i++) //lo hago con logica inversa, primero prendo todo y dsp apago (mas corto a veces)
            {
                for ( j = 5 + offset_y; j < 10 + offset_y; j++)
                {
                    coord.x=i; coord.y=j;
                    disp_write(coord,D_ON);
                }
                
            }
            
            coord.x= 1 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_OFF);
            coord.x= 3 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_OFF);
            coord.x= 3 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_OFF);
            coord.x= 3 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_OFF);
            
            break;

        case 5: //letra F

            for (i = 0 + offset_x; i < offset_x + 4; i++) //lo hago con logica inversa, primero prendo todo y dsp apago (mas corto a veces)
            {
                for ( j = 5 + offset_y; j < 10 + offset_y; j++)
                {
                    coord.x=i; coord.y=j;
                    disp_write(coord,D_ON);
                }
                
            }
            
            coord.x= 1 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_OFF);
            coord.x= 3 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_OFF);
            coord.x= 3 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_OFF);
            coord.x= 3 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_OFF);
            coord.x= 3 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_OFF);
            
            break;

        case 6: //letra G

            for (i = 0 + offset_x; i < offset_x + 4; i++) //lo hago con logica inversa, primero prendo todo y dsp apago (mas corto a veces)
            {
                for ( j = 5 + offset_y; j < 10 + offset_y; j++)
                {
                    coord.x=i; coord.y=j;
                    disp_write(coord,D_ON);
                }
                
            }
            
            coord.x= 0 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_OFF);
            coord.x= 3 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_OFF);
            coord.x= 0 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_OFF);
            
            break;

        case 7: //letra H

            for (i = 0 + offset_x; i < offset_x + 4; i++) //lo hago con logica inversa, primero prendo todo y dsp apago (mas corto a veces)
            {
                for ( j = 5 + offset_y; j < 10 + offset_y; j++)
                {
                    coord.x=i; coord.y=j;
                    disp_write(coord,D_ON);
                }
                
            }
            
            coord.x= 1 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_OFF);
            
            break;

        case 8: //letra I

                        
            coord.x= 0 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);

            break;

        case 9: //letra J

                        
            coord.x= 3 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);
            
            break;

        case 10: //letra K

                        
            coord.x= 0 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);

            break;

        case 11: //letra L

                        
            coord.x= 0 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);

            break;

        case 12: //letra H

                        
            coord.x= 0 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);

            break;

        case 13: //letra N

                        
            coord.x= 0 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);

            break;

        case 14: //letra O

                        
            coord.x= 1 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);

            break;

        case 15: //letra P

                        
            coord.x= 0 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);

            break;

        case 16: //letra Q

                        
            coord.x= 1 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_ON);

            break;

        case 17: //letra R

            for (i = 0 + offset_x; i < offset_x + 4; i++) //lo hago con logica inversa, primero prendo todo y dsp apago (mas corto a veces)
            {
                for ( j = 5 + offset_y; j < 10 + offset_y; j++)
                {
                    coord.x=i; coord.y=j;
                    disp_write(coord,D_ON);
                }
                
            }
            
            coord.x= 3 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_OFF);
            coord.x= 3 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_OFF);
            coord.x= 3 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_OFF);
            coord.x= 1 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_OFF);
            coord.x= 2 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_OFF);
            
            
            break;

        case 18: //letra S

                        
            coord.x= 1 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);

            break;

        case 19: //letra T

            coord.x= 0 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);            
            coord.x= 1 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);

            break;

        case 20: //letra U

                      
            coord.x= 0 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);
            
            coord.x= 3 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);

            coord.x= 1 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);  
            coord.x= 2 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);

            break;

        case 21: //letra V

                      
            coord.x= 0 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_ON);
                        
            coord.x= 3 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_ON);
            

            coord.x= 1 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);  
            coord.x= 2 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);

            break;

        case 22: //letra W

                      
            coord.x= 0 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_ON);
            
            coord.x= 3 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_ON);

            coord.x= 1 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);  
            coord.x= 2 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);

            break;

        case 23: //letra X

                      
            coord.x= 0 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);
            
            coord.x= 3 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);

            break;

        case 24: //letra Y

            coord.x= 0 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);            
            coord.x= 2 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);

            break;

        case 25: //letra Z

                        
            coord.x= 0 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 5;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 6;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= offset_y + 7;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= offset_y + 8;
            disp_write(coord, D_ON);
            coord.x= 0 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);
            coord.x= 1 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);
            coord.x= 2 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);
            coord.x= 3 + offset_x; coord.y= offset_y + 9;
            disp_write(coord, D_ON);

            break;
        
        default:
            break;
        }
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

        disp_update();
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

void print_game_over(void){

    disp_clear();
    print_letter(6,3,0,-4); //G
    print_letter(0,3,4,-4); //A
    print_letter(12,3,8,-4); //M
    print_letter(4,3,12,-4); //E

    print_letter(14,3,0,4); //O
    print_letter(21,3,4,4); //V
    print_letter(4,3,8,4); //E
    print_letter(17,3,12,4); //R

    while (get_option() != MENU) //esperamos que toque el menu para salir de nuevo
    {
        ;
    }
    while (get_option())
    {
        ;
    }
    
}


void print_top_scores(void){
    typedef struct 
    {
        long int score;
        char name[3];
        int posicion_top;

    }jugador_top_t;
    
    //Leo el archivo, ordeno todos los datos y escribo uno "nuevo" con el mismo nombre
    int i,j;
    int c;

    jugador_top_t jugadores_top[10];   

    FILE* pfile1;
    int aux=10;
    
    pfile1 = fopen("top_scores.txt", "r");
    if (pfile1 != NULL) //Verificamos si no existía el archivo, en ese caso este puntaje sería el maximo pq es el primero
    {
        while(!feof(pfile1)) //Hasta que no llegue al EOF seguimos leyendo
        {
            for ( i = 0; i < 10; i++) //lenamos los datos de los jugadores del 0 al 9
            {
                c = fgetc(pfile1); //Hasta que no llegue al EOF seguimos leyendo EL PRIMERO ES EL ULTIMO \n
                c = fgetc(pfile1); //Asi que leo el segundo tambien
                if ( c == EOF )
                {
                    aux = i;
                    break;
                }
                else
                {
                    fseek(pfile1, -2,SEEK_CUR);
                    fscanf (pfile1, "%ld", &(jugadores_top[i].score)); //Leo los datos y los acomodo en los array
                    fscanf (pfile1, "%s", jugadores_top[i].name);
                    jugadores_top[i].posicion_top=i;
                }
                
            }
            
        }
        fclose(pfile1);

        for ( i = 0; i < aux; i++)
        {
            print_number(jugadores_top[i].score);
        }
        print_flechas_verticales(6);

    }
    
    

}

void print_number(long int number){
    
}