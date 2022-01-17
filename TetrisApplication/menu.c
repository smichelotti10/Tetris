#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rules.h"
#include "termlib.h"
#include "disdrv.h"
#include "joydrv.h"



void print_option(int option);
void print_flechas_horizontales(void);
char get_option (void); 

int main(void){

    char signal;
    int option = 0;
    joy_init();
    disp_init();  
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
   return 0;
}

void print_option(int option){
    int i, j, k, z, r; //indices que ayudan a la hora de imprimir
    dcoord_t coord; //variable para almacenar las coordenadas a imprimir
    
    switch (option)
    {
    case 0: //es el caso de jugar

        disp_clear();
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

        print_flechas_horizontales();

        disp_update();
        break;
    case 1: //es el caso de TOP scores
        disp_clear();
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
        
        print_flechas_horizontales();

        disp_update();
        break;
    case 2: // es el caso de Abandonar Programa
        disp_clear();
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

        print_flechas_horizontales();

        disp_update();
        break;
    case 3: //es el caso de reiniciar juego
        disp_clear();
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

        print_flechas_horizontales();    

        disp_update();
        break;
    default:
        break;
    }

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