#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rules.h"
#include "piezas.h"
#define DER 1
#define IZQ -1
#define ABA 0
void generador(pieza_t * in_use)
{
    srand(time(NULL)); //genero una semilla randomizada
    
    in_use->id = rand()%7+1;
    in_use->coord_x = 3;
    in_use->coord_y = 0;
    in_use->position = 0;
    
    switch  (in_use->id)
    {
        case ORANGERICKY:
            {
            in_use->mat_bloque[0][0] = 3;
            in_use->mat_bloque[0][1] = 3;
            in_use->mat_bloque[0][2] = 2;
            in_use->mat_bloque[0][3] = 1;
            in_use->mat_bloque[1][0] = 1;
            in_use->mat_bloque[1][1] = 2;
            in_use->mat_bloque[1][2] = 2;
            in_use->mat_bloque[1][3] = 2;
            break;
            }
        case BLUERICKY:
            {
            in_use->mat_bloque[0][0] = 1;
            in_use->mat_bloque[0][1] = 1;
            in_use->mat_bloque[0][2] = 2;
            in_use->mat_bloque[0][3] = 3;
            in_use->mat_bloque[1][0] = 1;
            in_use->mat_bloque[1][1] = 2;
            in_use->mat_bloque[1][2] = 2;
            in_use->mat_bloque[1][3] = 2;
            break;    
            }
        case CLEVELANDZ:
            {
            in_use->mat_bloque[0][0] = 1;
            in_use->mat_bloque[0][1] = 2;
            in_use->mat_bloque[0][2] = 2;
            in_use->mat_bloque[0][3] = 3;
            in_use->mat_bloque[1][0] = 1;
            in_use->mat_bloque[1][1] = 1;
            in_use->mat_bloque[1][2] = 2;
            in_use->mat_bloque[1][3] = 2;
            break;
            }
        case RHODEISLANDZ:
            {
            in_use->mat_bloque[0][0] = 3;
            in_use->mat_bloque[0][1] = 2;
            in_use->mat_bloque[0][2] = 2;
            in_use->mat_bloque[0][3] = 1;
            in_use->mat_bloque[1][0] = 1;
            in_use->mat_bloque[1][1] = 1;
            in_use->mat_bloque[1][2] = 2;
            in_use->mat_bloque[1][3] = 2;
            break;
            }
        case HERO:
            {
            in_use->mat_bloque[0][0] = 0;
            in_use->mat_bloque[0][1] = 1;
            in_use->mat_bloque[0][2] = 2;
            in_use->mat_bloque[0][3] = 3;
            in_use->mat_bloque[1][0] = 2;
            in_use->mat_bloque[1][1] = 2;
            in_use->mat_bloque[1][2] = 2;
            in_use->mat_bloque[1][3] = 2;
            break;
            }
        case TEEWEE:
            {
            in_use->mat_bloque[0][0] = 2;
            in_use->mat_bloque[0][1] = 1;
            in_use->mat_bloque[0][2] = 2;
            in_use->mat_bloque[0][3] = 3;
            in_use->mat_bloque[1][0] = 1;
            in_use->mat_bloque[1][1] = 2;
            in_use->mat_bloque[1][2] = 2;
            in_use->mat_bloque[1][3] = 2;
            break;}
        case SMASHBOY:  
            {
            in_use->mat_bloque[0][0] = 1;
            in_use->mat_bloque[0][1] = 2;
            in_use->mat_bloque[0][2] = 1;
            in_use->mat_bloque[0][3] = 2;
            in_use->mat_bloque[1][0] = 1;
            in_use->mat_bloque[1][1] = 1;
            in_use->mat_bloque[1][2] = 2;
            in_use->mat_bloque[1][3] = 2;
            break;
            }
    }
}

void move(pieza_t* in_use, int mat[FIL][COL], char direccion)
{
pieza_t to_use = *in_use;

if(direccion == DER) //#define DER 'd'
{
	(to_use.coord_x)++;
	if(!check(&to_use,mat))
	{
		*in_use = to_use;
	}
}
else if (direccion == IZQ)
{
	(to_use.coord_x)--;	
	if(!check(&to_use,mat))
	{
		*in_use = to_use;
	}
}
else if (direccion == ABA)
{
	(to_use.coord_y)++;
	if(!check(&to_use,mat))
	{
		*in_use = to_use;
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
