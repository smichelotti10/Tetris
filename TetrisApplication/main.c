#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rules.h"
#include "piezas.h"


/*
 * Funcion para que baje (recibe puntero a la matriz, devuelve si ya no hay mas nada que actualizar) (delay modificable)
 * Lee si se completo una fila (si encuentra, llama a la que baja) (recibe puntero a la matriz, no devuelve)
 * Funcion que rote las piezas (recibe un puntero a la pieza)
 * el sistema de puntos en general que depende del sistema de nivel
 * el sistema de nivel que depende del sistema de puntos
 * 

 */




int main(int argc, char** argv) {
    
    
  srand(time(NULL)); //genero una semilla randomizada
  
  int matriz[FIL][COL];
  clear_mat(matriz);
  
  game_stats_t jugador;
  init_jugador(&jugador); //llamamo a la función que inicializa las stats del juego
  jugador.level=5;
   pieza_t in_use;
   while(1){
        
       generador(&in_use, &jugador); //llamamos a la función que rellena los campos de la pieza
       while(!check(&in_use, matriz)){
           print_mat(&in_use, matriz);
            delay(jugador.level);
            if(move(&in_use, matriz, ABA)) //con la función de move, ya nos aseguramos que se pueda seguir bajando o no.
            {
                setear_pieza(&in_use, matriz); //guardamos la pieza en la matriz
                fila_completa(matriz, &jugador); //vemos si se completo una fila para sumar puntos y eso
                break;
            }
       }
       if(game_over(matriz)){
           printf("GAME OVER\n Final Score: %ld\n Level: %d\n", jugador.score, jugador.level);
           return 0;
       }
       
   }
}








