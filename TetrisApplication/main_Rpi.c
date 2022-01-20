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
void top_scores(game_stats_t* jugador);


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

void top_scores(game_stats_t* jugador){
    typedef struct 
    {
        long int score;
        char name[3];
        int posicion_top;

    }jugador_top_t;
    
    //Leo el archivo, ordeno todos los datos y escribo uno "nuevo" con el mismo nombre
    int i,j;
    int c;

    jugador_top_t jugadores_top[11];
    for (i = 0; i < 11; i++)
    {
        jugadores_top[i].name[0] ='N';
        jugadores_top[i].name[1] ='A';
        jugadores_top[i].name[2] ='N';
        jugadores_top[i].score = 0;
        jugadores_top[i].posicion_top=i;
    }
    

    FILE* pfile1;
    int aux=10;
    
    pfile1 = fopen("top_scores.txt", "r");
    if (pfile1 == NULL) //Verificamos si no existía el archivo, en ese caso este puntaje sería el maximo pq es el primero
    {
        jugadores_top[0].score = jugador->score;
        for (i = 0; i < 3; i++)
        {      
            jugadores_top[0].name[i] = jugador->nick[i];
        }
        pfile1 = fopen("top_scores.txt", "w");
        if (pfile1 !=NULL) //vemos si este si lo pudo crear
        {
            fprintf(pfile1,"%ld %3.3s\n",jugadores_top[0].score,jugadores_top[0].name); //3.3 es para indicar minimo 3 caracteres, maximo 3
            fclose(pfile1);
        }
        
    }
    else{ //esto es el caso en el que si existe, hay que leerlo, pasar la info a los array y luego ordenarlo con el nuevo jugador

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

        jugadores_top[10].score = jugador->score; //meto los datos del jugador actual en el array para ordenarlo
        for (i = 0; i < 3; i++)
        {      
            jugadores_top[10].name[i] = jugador->nick[i];
        }
        jugadores_top[10].posicion_top=10;

        for ( i = 10; i >=0 ; i--) //recorro todos los jugadores
        {
           if (jugadores_top[10].score >= jugadores_top[i].score)
           {
               jugadores_top[10].posicion_top --;
               jugadores_top[i].posicion_top ++;
           } 
        }        

        pfile1 = fopen("top_scores.txt", "w");

        for ( i = 0; i < aux+1; i++) //me voy a mover entre los primeros jugadores según el id de posicion que les corresponde
        {
            for (j = 0; j < 11; j++) //con esta recorro los jugadores
            {
                if (i == jugadores_top[j].posicion_top) //voy en orden imprimiendo
                {
                    fprintf(pfile1,"%ld %3.3s\n",jugadores_top[j].score,jugadores_top[j].name); //3.3 es para indicar minimo 3 caracteres, maximo 3
                    break;
                }
                
            }
        }
        fclose(pfile1);        

    }
    

}



