#ifndef JUEGO_RPI_H
#define JUEGO_RPI_H


void delay(game_stats_t* jugador, pieza_t* in_use, int matriz[FIL][COL], pieza_t*next, pieza_t* hold, char* end_game, char* restart_game);
/*
Esta función se encarga de todo lo que ocurre dentro del lapso de espera entre que la pieza baja
de una fila a la siguiente. Lee los movimientos, si hay un llamado al menu de pausa, actualiza el 
display en caso de movimientos, y cuando pasa el time_out para que siga cayendo la pieza sale de la función
Recibe todas las piezas (in_use, next y hold; la matriz de juego, y la estructura del jugador).
Ademas debe recibir los flags tanto de reinicio de juego como de fin de juego.
*/

void get_name(game_stats_t* jugador);
/*
get_name es la función que se encarga de recibir el nick de 3 letras de cada jugador, se utiliza al
inicio de cada partida e imprime en el display todas las letras en forma de opciones giratorias, mientras
se va seleccionando, se guarda la información en la estructura dedicada al jugador.
*/

void print_letter(int option, int index, int offset_x, int offset_y);
/*
Es una función mayormente auxiliar, tiene hardoceado las 26 letras disponibles, recibe la letra a 
imprimir y el offset de donde se quiere imprimir de acuerdo con lo que sería la ubicacion estandar
(la ubicacion estandar es en el centro del display, no en la posicion 0,0). El index es simplemente
un offset establecido, hay posicion 0,1 y 2 para el index.
*/

void print_flechas_verticales(int offset_x);
/*
Funcion para imprimir flechas en los extremos verticales de la pantalla, se le puede establecer un offset
para moverlas de posicion sobre las columnas.
*/

void col_clear(int col);
/*
Funcion a la cual se le pasa un numero de columna de display para borrarla
*/

void print_game_over(void);
/*
Imprime el mensaje "GAME OVER" en el display
*/

void print_top_scores(void);
/*
Funcion para recorrer los top scores, lee el archivo "top_scores.txt". De no existir o no poder leer
el archivo, imprime "NULL" en el display.
Si existe, muestra los top scores guardados y los nombres de los jugadores que lo consiguieron
*/

void print_number(long int number, int offset__x, int offset_y);
/*
Función auxiliar para imprimir en display un numero de máximo 10 cifras.
*/

void show_score(game_stats_t* jugador);
/*
show score se llama al final de una partida, para mostras la puntuación obtenida.
*/

void print_mat (pieza_t* in_use, int matriz[FIL][COL], pieza_t* next, pieza_t* hold, long int level);
/*
print_mat se encarga de imprimir en display toda la informacion relevante de la partida; la pieza
en movimiento, la siguiente pieza, la pieza en hold y el nivel actual. Ademas por supuesto de las
piezas que ya cayeron
*/


#endif /* RASPI_H */