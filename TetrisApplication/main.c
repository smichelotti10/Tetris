#include <stdio.h>
#include <stdlib.h>
#include "rules.h"
#include "piezas.h"
#define DER 1
#define IZQ -1
#define ABA 0
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
        
   int matriz[FIL][COL];
   clear_mat(matriz);
    
   pieza_t in_use;
	 generador(&in_use); //llamamos a la función que rellena los campos de la pieza
	//for(int cont = 10 ; cont <= 19 ; cont++){	
	//for(int contador = 0; contador < 10 ; contador++)
	//{   
	matriz[18][4]=1;
	//}	}
	printf("id = %d\ncoordy = %d\n",in_use.id,in_use.coord_y);

	all_down(&in_use,matriz);

	printf("id = %d\ncoordy = %d\n",in_use.id,in_use.coord_y);

    move(&in_use, matriz,ABA);
    	

	printf("id = %d\ncoordy = %d\n",in_use.id,in_use.coord_y);   

  
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
