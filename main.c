#include <stdio.h>
#include <stdlib.h>
#include "rules.h"
/*
 * Funcion para que baje (recibe puntero a la matriz, devuelve si ya no hay mas nada que actualizar) (delay modificable)
 * Lee si se completo una fila (si encuentra, llama a la que baja) (recibe puntero a la matriz, no devuelve)
 * Funcion que rote las piezas (recibe un puntero a la pieza)
 * Funcion que mueva las piezas (capaz van juntas)
 * Funcion que genere las piezas
 */

int main(int argc, char** argv) {
   int** p_matriz;
   p_matriz = init_mat();
}

int** init_mat(void){

    int matriz[FIL][COL];
    
    int i,j;
    
    for(i=0; i < FIL; i++){
        for(j=0; j < COL; j++){
            matriz[i][j]= VACIO;
        }
    }
    return matriz;

}
