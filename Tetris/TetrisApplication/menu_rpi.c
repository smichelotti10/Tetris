#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "../rpi_resources/disdrv.h"
#include "../rpi_resources/joydrv.h"
#include <SDL/SDL.h>
#include "../rpi_resources/libaudio.h"

#include "rules.h"
#include "raspi.h"
#include "menu_rpi.h"

extern char music[];






int menu_pausa(void){
    
    char signal;
    int option = 0;  
   print_option(option);
   while ( (signal = get_option()) != MENU)
   {   
       if (player_status()==FINISHED) //revisamos que la musica no se haya cortado
            { 	
                stop_sound();
                set_file_to_play(music);		
                play_sound(); 
            }
        switch (signal)
        {
        case DER:
             while ((get_option())) //esperamos a que vuelva para cambiar
            {
                ;
            }
                option++; 
                option = (option)%4;
                print_option(option);
            
            break;
        case IZQ:
            while ((get_option())) //esperamos a que vuelva para cambiar
            {
                ;
            }
                
                if (option==0)
                {
                    option = 3;
                }
                else{
                    option --;
                }
                print_option(option);
            
            break;
        default:
            break;
        }
        
   }
   while (get_option())
   {
       ;
   }
   
   return option;
}

void print_option(int option){
    int i, j, k, z, r; //indices que ayudan a la hora de imprimir
    dcoord_t coord; //variable para almacenar las coordenadas a imprimir
    disp_clear();

    switch (option)
    {
    case 0: //es el caso de jugar

        
        k = 13; //cantidad de leds prendidos en la fila mas alta
        z = 1; //altura a la cual quiero que empiece
        for ( i = 5; i < 12; i++) //me muevo en las columnas que imprimo
        {
            coord.x=i;
            j=k;
            r = z;
            while ((j)>0)
            {
                
                coord.y = r;
                r++;
                j--;
                disp_write(coord, D_ON);
            }
            z++;
            k = k-2;
        }

        
        break;
    case 1: //es el caso de TOP scores
        
        for (j=4; j<11; j = j+2) //las columnas que imprimo
        {
            k = 6; //altura a la que comienzo a imprimir
            for ( i = 0; i < 5; i++) // la cantidad de cuadrados por columna que imprimo
            {
                coord.x = j;
                coord.y = k;
                disp_write(coord, D_ON);
                k++;
            }
        }

        for (i = 2; i < 7; i++)
        {
            coord.x = i;
            coord.y = 4;
            disp_write(coord, D_ON);
        }
        coord.x=4;
        coord.y=5;
        disp_write(coord, D_ON);
        coord.x=7;
        coord.y=6;
        disp_write(coord, D_ON);
        coord.x=7;
        coord.y=10;
        disp_write(coord, D_ON);

        for (j=11; j<13; j++) //las columnas que imprimo
        {
            k = 6;
            for ( i = 0; i < 3; i++) // la cantidad de cuadrados por columna que imprimo
            {
                coord.x = j;
                coord.y = k;
                disp_write(coord, D_ON);
                k++;
            }
        }
        coord.x = 11;
        coord.y = 7;
        disp_write(coord, D_OFF);
        
        
        break;
    case 2: // es el caso de Abandonar Programa
        
        for (j=3; j<13; j=j+9) //las columnas que imprimo
        {
            k = 1; //altura desde la cual quiero imprimir hacia abajo
            for ( i = 0; i < 13; i++) // la cantidad de cuadrados por columna que imprimo
            {
                coord.x = j;
                coord.y = k;
                disp_write(coord, D_ON);
                k++;
            }
        }
        for (j=1; j<14; j=j+12) //las filas que imprimo
        {
            k = 4; //columna desde la cual quiero imprimir hacia la derecha
            for ( i = 0; i < 8; i++) // la cantidad de cuadrados por fila que imprimo
            {
                coord.x = k;
                coord.y = j;
                disp_write(coord, D_ON);
                k++;
            }
        }
        coord.x=9;
        coord.y=8;
        disp_write(coord, D_ON);
        coord.x=10;
        coord.y=8;
        disp_write(coord, D_ON);

        
        break;
    case 3: //es el caso de reiniciar juego
        
        k = 9; //cantidad de leds prendidos en la fila mas alta
        z = 6; //altura a la cual quiero que empiece
        for ( i = 6; i < 11; i++) //me muevo en las columnas que imprimo
        {
            coord.x=i;
            j=k;
            r = z;
            while ((j)>0)
            {
                
                coord.y = r;
                r++;
                j--;
                disp_write(coord, D_ON);
            }
            z++;
            k = k-2;
        }

        for (i = 3; i < 13; i++)
        {
            coord.x = i;
            coord.y = 3;
            disp_write(coord, D_ON);
        }

        for (j=3; j<13; j = j+9) //las columnas que imprimo
        {
            k = 4; //altura a la que comienzo a imprimir
            for ( i = 0; i < 6; i++) // la cantidad de cuadrados por columna que imprimo
            {
                coord.x = j;
                coord.y = k;
                disp_write(coord, D_ON);
                k++;
            }
        }
        
        for (i = 3; i < 6; i++)
        {
            coord.x = i;
            coord.y = 10;
            disp_write(coord, D_ON);
        }

        break;
    default:
        break;
    }
    print_flechas_horizontales();

    disp_update();
}

void print_flechas_horizontales(void){
        dcoord_t coord;
        coord.x=0;
        coord.y=7;
        disp_write(coord, D_ON);
        coord.x=1;
        coord.y=6;
        disp_write(coord, D_ON);
        coord.x=1;
        coord.y=7;
        disp_write(coord, D_ON);
        coord.x=1;
        coord.y=8;
        disp_write(coord, D_ON);
        coord.x=15;
        coord.y=7;
        disp_write(coord, D_ON);
        coord.x=14;
        coord.y=6;
        disp_write(coord, D_ON);
        coord.x=14;
        coord.y=7;
        disp_write(coord, D_ON);
        coord.x=14;
        coord.y=8;
        disp_write(coord, D_ON);
}

int menu_start(void){

    char signal;
    int option = 0;  
   print_option(option);
   while ( (signal = get_option()) != MENU)
   {   
        switch (signal)
        {
        case DER:
             while ((get_option())) //esperamos a que vuelva para cambiar
            {
                ;
            }
                option++; 
                option = (option)%3;
                print_option(option);
            
            break;
        case IZQ:
            while ((get_option())) //esperamos a que vuelva para cambiar
            {
                ;
            }
                
                if (option==0)
                {
                    option = 2;
                }
                else{
                    option --;
                }
                print_option(option);
            
            break;
        default:
            break;
        }
        
   }
    while (get_option())
    {
       ;
    }
   
   return option;
}

int menu_game_over(void){

    
    char signal;
    int option = 1;  
   print_option(option);
   while ( (signal = get_option()) != MENU)
   {   
        switch (signal)
        {
        case DER:
             while ((get_option())) //esperamos a que vuelva para cambiar
            {
                ;
            }
                if (option == 3)
                {
                    option = 1;
                }
                else{
                    option++; 
                    option = (option)%4;
                }
                print_option(option);

            break;
        case IZQ:
            while ((get_option())) //esperamos a que vuelva para cambiar
            {
                ;
            }
                
                if (option==1)
                {
                    option = 3;
                }
                else{
                    option --;
                }
                print_option(option);
            
            break;
        default:
            break;
        }
        
   }
   while (get_option())
   {
       ;
   }
   
   return option;
}