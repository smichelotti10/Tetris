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

void clear_mat(int mat[FIL][COL]);


int main(int argc, char** argv) {
  srand(time(NULL)); //genero una semilla randomizada
  int matriz[FIL][COL];
  clear_mat(matriz);
  for(int i=0; i<COL; i++){
      matriz[5][i]=1;
      
  }
   pieza_t in_use;
   generador(&in_use); //llamamos a la función que rellena los campos de la pieza
   
}


void clear_mat(int mat[FIL][COL]){ //función que borra la matriz, podriamos hacerla general.
    
    int i,j;
    
    for(i=0; i < FIL; i++){
        for(j=0; j < COL; j++){
            mat[i][j]= 0;
        }
    }

}





