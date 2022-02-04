#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "rules.h"
#include "piezas.h"





#ifdef RPI

#include "raspi.h"

void push_mat_down (int matriz[FIL][COL], int fila, pieza_t* next, long int level)
{
    int fil, col, i;

    for (i=0; i<COL; i++) {                 // Primero se va a limpiar la fila que se completo, podemos 
                                            // agregar un delay si queremos para que no aparezca todo de una.
        matriz[fila][i] = 0;
     
        print_mat(NULL,matriz,next,level);
        espera(0.07);                              //Parte agregada para la RPI

    }

    int aux;
    for (fil=fila; fil>0; fil--) {          // Este ciclo baja toda la batriz sobre la fila que se elimino en un bloque

        for (col=0; col<COL; col++) {           // Podemos agregar delay cada vez que realiza este for para mostrar una animacion

            aux = matriz[fil][col];
            matriz[fil][col] = matriz[fil-1][col];
            matriz[fil-1][col] = aux;
        }
    }
}
#endif

#ifdef ALLEGRO

void push_mat_down (int matriz[FIL][COL], int fila, pieza_t* next, long int level)
{
    int fil, col, i;

    for (i=0; i<COL; i++) {                 // Primero se va a limpiar la fila que se completo, podemos 
                                            // agregar un delay si queremos para que no aparezca todo de una.
        matriz[fila][i] = 0;
  
        //AGREGAR PRINT MAT DE ALLEGRO
    }

    int aux;
    for (fil=fila; fil>0; fil--) {          // Este ciclo baja toda la batriz sobre la fila que se elimino en un bloque

        for (col=0; col<COL; col++) {           // Podemos agregar delay cada vez que realiza este for para mostrar una animacion

            aux = matriz[fil][col];
            matriz[fil][col] = matriz[fil-1][col];
            matriz[fil-1][col] = aux;
        }
    }
}

#endif


void init_jugador(game_stats_t* jugador)
{
    jugador->level = 1;
    jugador->cant_piezas = 0;
    jugador->score = 0;

}

void generador(pieza_t * in_use, game_stats_t* jugador)
{
    
    int aux;
    aux = rand();
    srand(aux);
    in_use->id = rand()%7+1;
    in_use->coord_x = 3;
    in_use->coord_y = 0;
    in_use->position = 0;
    
    jugador->cant_piezas++;
    switch (jugador->cant_piezas){
        
        case LEVEL2:  
        case LEVEL3:    
        case LEVEL4:   
        case LEVEL5:  
        case LEVEL6: 
        case LEVEL7: 
        case LEVEL8:  
        case LEVEL9:
        case LEVEL10:
            jugador->level++;
            break;
        default:
            break;
            
    }
    
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

int mover_pieza(pieza_t* in_use, int mat[FIL][COL], char direccion)
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
        else
        {
            return 1; //esto es por si llego al final o si se choca una pieza, avisa para que se setee.
        }
}
return 0;
}

int check(pieza_t* pieza, int mat[FIL][COL]){

    int j;
        
        
        for(j=0; j<=3; j++){ 

            if(mat[(pieza->mat_bloque[1][j])+(pieza->coord_y)][(pieza->mat_bloque[0][j])+(pieza->coord_x)]){ //localizamos los bloques dentro de la matriz de juego //verifica que no haya superposición de los bloques
               return 1; // si devuelve 1 es porque hay error de superposición
            }
            
            
            
            if( (((pieza->mat_bloque[0][j])+(pieza->coord_x)) < 0) || (((pieza->mat_bloque[0][j])+(pieza->coord_x)) > 9) ){ //verificamos que los bloques esten dentro de la matriz
               return 1; //si devuelve 1 es porque hay error de margenes
            }
            
            if( ((pieza->mat_bloque[1][j])+(pieza->coord_y)) > 19){ //verificamos que los bloques esten dentro de la matriz
                return 1; //si devuelve 1 es porque hay error de margenes
            }    
            
            
            
        }
    return 0;
}

unsigned char all_down(pieza_t* in_use,int matriz[FIL][COL])
{
int contador;
pieza_t aux = *in_use;
for(contador = 0 ; contador < 20 ; contador++)
{
	mover_pieza(in_use,matriz,ABA);
    
}
    setear_pieza(in_use, matriz);
    return ((in_use->coord_y) - aux.coord_y);
}

void rotar(pieza_t* in_use,int mat[FIL][COL])
{
    pieza_t to_use = *in_use;
    
/*CREO UNA MATRIZ AUXILIAR PARA MANEJAR LOS DATOS DE LA ESTRUCTURA*/     
    int mat_aux[4][4];
    int fil,col; //creo contadores para luego borrar todos los datos de la matriz, luego reutilizo las mismas variables para rellenarla
    for(fil=0; fil < 4; fil++){  
        for(col=0; col < 4; col++){
            mat_aux[fil][col]= 0;
        }
    }
/*EMPIEZO A RELLENAR LA MATRIZ CON LOS DATOS*/
    int i, j; //indices de ayuda para recorrer la matriz
    for (i=0; i<4; i++){
       mat_aux[(int)to_use.mat_bloque[1][i]][(int)to_use.mat_bloque[0][i]] = (int) to_use.id;
       }
    
    if(to_use.id == HERO || to_use.id == SMASHBOY)
    {
/*ESTA ES LA PARTE QUE ROTA LA MATRIZ*/        
        for (i = 0; i < 4 / 2; i++) {
            for (j = i; j < 4 - i - 1; j++) {
        
                // Gira los elementos en cada ciclo
                // en direccion horaria
                int aux = mat_aux[i][j];
                mat_aux[i][j] = mat_aux[3 - j][i];
                mat_aux[3 - j][i] = mat_aux[3 - i][3 - j];
                mat_aux[3 - i][3 - j] = mat_aux[j][3 - i];
                mat_aux[j][3 - i] = aux;
            }
        }
        
        int bloque=0;
        
        for (int x=0; x<4; x++){
        
            for (int y=0; y<4; y++){
        
                if (mat_aux[x][y]!=0){
            
                    to_use.mat_bloque[0][bloque] = y;
                    to_use.mat_bloque[1][bloque] = x;
                    bloque++;
                }
            }
        }
        
        if(!check(&to_use, mat)){
            *in_use = to_use;
        }
    
    }
    else
    {
/*ESTA ES LA PARTE QUE ROTA LA MATRIZ*/
        for (j = 0; j < 2; j++) {
    
            // Gira los elementos en cada ciclo
            // en direccion horaria
            int aux = mat_aux[1][j+1];
            mat_aux[1][j + 1] = mat_aux[3 - j][1];
            mat_aux[3 - j][1] = mat_aux[3][3 - j];
            mat_aux[3][3 - j] = mat_aux[j + 1][3];
            mat_aux[j + 1][3] = aux;
        }
        
        int bloque=0;
        
        for (int x=0; x<4; x++){
        
            for (int y=0; y<4; y++){
        
                if (mat_aux[x][y]!=0){
            
                    to_use.mat_bloque[0][bloque] = y;
                    to_use.mat_bloque[1][bloque] = x;
                    bloque++;
                }
            }
        }
        
        if(!check(&to_use, mat)){
            *in_use = to_use;
        }
    }
}

void fila_completa (int matriz[FIL][COL], game_stats_t* jugador, pieza_t* next)
{
    int fil, col, bloques, cant=0;

    for(fil=0; fil<FIL; fil++) {

        for(col=0, bloques=0; col<COL; col++) {   // recorro cada fila de la matriz analizando si la fila esta completa o no.

            if (matriz[fil][col]!=0) {

                bloques++;
            }

        } 
        if (bloques==10) {           // Si la fila esta completa llamo a la funcion push_mat_down para desplazar una fila
            push_mat_down (matriz, fil, next, jugador->level);  //aca agregue jugador->level          // para abajo todas las filas de arriba a la que hay que eliminar
            cant ++;
        }
    }
    switch (cant){
        
        case 1:
            jugador->score +=(int) (100 * (1 + (((double)(jugador->level)-1)/10)));
            break;
        case 2:
            jugador->score +=(int) (200 * (1 + (((double)(jugador->level)-1)/10)));
            break;
        case 3:
            jugador->score +=(int) (400 * (1 + (((double)(jugador->level)-1)/10)));
            break;
        case 4:
            jugador->score +=(int) (800 * (1 + (((double)(jugador->level)-1)/10)));
            break;
    }
}

void espera(float number_of_seconds)
{

    //float miliseconds = number_of_seconds * 1000;
    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + number_of_seconds * CLOCKS_PER_SEC)
        ;
}

void setear_pieza(pieza_t* pieza, int mat[FIL][COL])
{
    int j;
    for(j=0; j<=3; j++){ 
        mat[(pieza->mat_bloque[1][j])+(pieza->coord_y)][(pieza->mat_bloque[0][j])+(pieza->coord_x)] = pieza->id;
    }

}

int game_over(int matriz[FIL][COL])
{
    int j;
    
    for(j=0; j<COL; j++){
        if(matriz[3][j] != 0)
        {
            return 1;
        }
    
    }
    return 0;
}

void clear_mat(int mat[FIL][COL]){ //función que borra la matriz, podriamos hacerla general.
    
    int i,j;
    
    for(i=0; i < FIL; i++){
        for(j=0; j < COL; j++){
            mat[i][j]= 0;
        }
    }

}

void top_scores(game_stats_t* jugador){
    
    
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
        jugadores_top[i].vacio=1;
    }

    FILE* pfile1;
    
    pfile1 = fopen("top_scores.txt", "r");
    if (pfile1 == NULL) //Verificamos si no existía el archivo, en ese caso este puntaje sería el maximo pq es el primero
    {
        jugadores_top[0].score = jugador->score;
        for (i = 0; i < 3; i++) {           
            jugadores_top[0].name[i] = jugador->nick[i];
        }
        pfile1 = fopen("top_scores.txt", "w");
        if (pfile1 !=NULL) //vemos si este si lo pudo crear
        {
            fprintf(pfile1,"%ld %3.3s\n",jugadores_top[0].score,jugadores_top[0].name); //3.3 es para indicar minimo 3 caracteres, maximo 3
            fclose(pfile1);
        }
    }
    else { //esto es el caso en el que si existe, hay que leerlo, pasar la info a los array y luego ordenarlo con el nuevo jugador

        while(!feof(pfile1)) //Hasta que no llegue al EOF seguimos leyendo
        {
            for ( i = 0; i < 10; i++) //leemos los datos de los jugadores del 0 al 9
            {
                c = fgetc(pfile1); //Hasta que no llegue al EOF seguimos leyendo EL PRIMERO ES EL ULTIMO \n
                c = fgetc(pfile1); //Asi que leo el segundo tambien
                if ( c == EOF )
                {
                    break;
                }
                else
                {
                    fseek(pfile1, -2,SEEK_CUR);
                    fscanf (pfile1, "%ld", &(jugadores_top[i].score)); //Leo los datos y los acomodo en los array
                    fscanf (pfile1, "%s", jugadores_top[i].name);
                    jugadores_top[i].posicion_top=i;
                    jugadores_top[i].vacio=0;
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
        jugadores_top[10].vacio=0;

        for (i=10; i >=0 ; i--) //recorro todos los jugadores
        {  
            if (jugadores_top[10].score >= jugadores_top[i].score)
            {
                jugadores_top[10].posicion_top --;
                jugadores_top[i].posicion_top ++;
            } 
        }       

        pfile1 = fopen("top_scores.txt", "w");
        for (i = 0; i < 10; i++) //me voy a mover entre los primeros jugadores según el id de posicion que les corresponde
        {
            for (j = 0; j < 11; j++) //con esta recorro el arreglo donde estn los jugadores
            {
                if (!(jugadores_top[j].vacio) && (i == jugadores_top[j].posicion_top)) //voy en orden imprimiendo
                {
                    fprintf(pfile1,"%ld %3.3s\n",jugadores_top[j].score,jugadores_top[j].name); //3.3 es para indicar minimo 3 caracteres, maximo 3
                    break;
                }
            }
        }
        fclose(pfile1);        
    }
}
