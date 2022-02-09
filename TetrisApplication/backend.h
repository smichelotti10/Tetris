#ifndef BACKEND_H
#define BACKEND_H

/*Recibe un puntero a la pieza que va a generar y un puntero a las estadisticas del jugador.
Esta función inicializa los campos de in_use con una pieza aleatoria. Devuleve nada*/
void generador(pieza_t * to_use, game_stats_t* jugador);

/*Recibe un puntero a las estadisticas del jugador actual. Esta funcion inicializa los
campos del jugador. Devuleve nada.*/
void init_jugador(game_stats_t* jugador);

/*Recibe un puntero a una matriz de COLxFIL para setear ceros en todos sus elementos. Devueve nada*/
void clear_mat(int mat[FIL][COL]);

/*Esta funcion es encargada de actualizar la posición de la pieza que esta en juego. Recibe
un puntero a la pieza, la matriz del juego y la direccion de movimiento que se quiere hacer.
Devuelve un 0 si pudo realizar el movimiento, sino devuleve un 1.*/
int mover_pieza(pieza_t* in_use, int mat[FIL][COL], char direccion);

/*Esta funcion analiza si se va a poder realizar el proximo movimiento que se desea hacer.
Recibe un puntero a la pieza y la matriz de juego. Devuelve un 1 si no será posible hacer
el movimiento*/
int check(pieza_t* pieza, int mat[FIL][COL]);

/*Esta funcion coloca en mat los bloques de la pieza en el lugar donde cae. Recibe un
puntero a la pieza y a la pieza en hold, y la matriz de juego. Devuelve nada*/
void setear_pieza(pieza_t* pieza, pieza_t* hold, int mat[FIL][COL]);

/*Recibe un puntero a la pieza en juego, a la pieza en hold y la matriz de juego. Esta
funcion mueve la pieza hacia abajo hasta que choque con otra pieza seteada o con el borde
inferior de la matriz. Devuelve*/  //////////////////////////
unsigned char all_down(pieza_t* in_use, pieza_t* hold, int matriz[FIL][COL]);

/*Recibe un puntero a la pieza y la matriz de juego. Esta funcion rota 90° la pieza. Devuelve nada*/
void rotar(pieza_t* in_use,int mat[FIL][COL]);

/*Esta funcion analiza si hay alguna fila de la matriz completa, es decir, que tenga sus 10 
elementos distintos de 0. Si esta completa Setea en toda la fila 0 indicando que se elimino la 
fila. Recibe un puntero a la matriz de juego, a las estadisticas del jugador y a las piezas
siguiente y la que se encuentra en hold. Devuelve nada*/
int fila_completa (int matriz[FIL][COL], game_stats_t* jugador, pieza_t* next, pieza_t* hold);

/*Esta funcion desplaza toda la matriz una fila hacia abajo desde la fila que recibe como parámetro.
Recibe un puntero a la matriz de juego, a la piezas siguiente y la que está en hold, la fila de
referencia y el nivel del jugador.*/
void push_mat_down (int matriz[FIL][COL], int fila, pieza_t* next, pieza_t* hold, long int level);

/*Esta función analiza si el jugador perdi{o o no. Recibe la matriz de juego y devuelve un 1
si perdió o un o si no perdió.*/
int game_over(int matriz[FIL][COL]);

/*Recibe la cantidad de segundos que va estar en "pausa" el programa. Devuelve nada*/
void espera(float cantidad_segs);

/*Recibe un puntero a las estadisticas del jugador y analiza si hay puntajes previos. Si los hay
los ordena y sino crea un archivo (top_scores.txt) y lo llea con la lista de puntajes actualizados.
Devuelve nada.*/
void top_scores(game_stats_t* jugador);

/*Esta función le da la opción al jugador de poder guardar una sola pieza para poder usarla más adelante.
Recibe un puntero a la pieza actual, a la siguiente, a la que se encuentra en hold, y a las estadisticas
del jugador. Devuelve nada*/
void funcion_hold (pieza_t *in_use, pieza_t *hold, pieza_t* to_use, game_stats_t* jugador);

enum nombres_bloques
{
    ORANGERICKY = 1,
    BLUERICKY,
    CLEVELANDZ,
    RHODEISLANDZ,
    HERO,
    TEEWEE,
    SMASHBOY
};

#endif /* BACKEND_H */
