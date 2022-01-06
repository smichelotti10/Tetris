#include <stdio.h>
#include <stdlib.h>
#include "rules.h"
#include "piezas.h"
/*
 * Funcion para que baje (recibe puntero a la matriz, devuelve si ya no hay mas nada que actualizar) (delay modificable)
 * Lee si se completo una fila (si encuentra, llama a la que baja) (recibe puntero a la matriz, no devuelve)
 * Funcion que rote las piezas (recibe un puntero a la pieza)
 * Funcion que mueva las piezas (capaz van juntas)
 * Funcion que genere las piezas
 */
void clear_mat(int mat[FIL][COL]);

int check(pieza_t*, int mat[FIL][COL]);

int main(int argc, char** argv) {
        
   int matriz[FIL][COL];
   clear_mat(matriz);
    
   pieza_t in_use;
   pieza_t to_use;

   generador(&in_use); //llamamos a la función que rellena los campos de la pieza
   to_use = in_use;
   //estoy en el borde y quiero moverlo hacia la izquierda
   to_use.coord_x += 1;
   to_use.coord_y += 1;
   
   if(check(&to_use, matriz)){
       printf("No podes hacer ese movimiento \n");
   }
   
   return 0;
}

void clear_mat(int mat[FIL][COL]){ //función que borra la matriz
    
    int i,j;
    
    for(i=0; i < FIL; i++){
        for(j=0; j < COL; j++){
            mat[i][j]= 0;
        }
    }

}


int check(pieza_t* pieza, int mat[FIL][COL]){

    int j;
        
        
        for(j=0; j<=3; j++){ 
            
            if(mat[(pieza->mat_bloque[0][j])+(pieza->coord_x)][(pieza->mat_bloque[1][j])+(pieza->coord_y)]){ //localizamos los bloques dentro de la matriz de juego //verifica que no haya superposición de los bloques
                return 1; // si devuelve 1 es porque hay error de superposición
            }
            
            
            
            if( (((pieza->mat_bloque[0][j])+(pieza->coord_x)) < 0) || (((pieza->mat_bloque[0][j])+(pieza->coord_x)) > 9) ){ //verificamos que los bloques esten dentro de la matriz
                return 1; //si devuelve 1 es porque hay error de margenes
            }
            
            if( (((pieza->mat_bloque[1][j])+(pieza->coord_y)) < 0)  || (((pieza->mat_bloque[1][j])+(pieza->coord_y)) > 19)){ //verificamos que los bloques esten dentro de la matriz
                return 1; //si devuelve 1 es porque hay error de margenes
            }    
            
            
            
        }
    return 0;
}
