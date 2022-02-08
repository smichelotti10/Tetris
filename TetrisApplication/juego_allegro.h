#ifndef JUEGO_ALLEGRO_H
#define JUEGO_ALLEGRO_H

//HEADERS

#include    <allegro5/allegro.h>
#include    <allegro5/allegro_primitives.h>
#include    <allegro5/allegro_ttf.h>
#include    <allegro5/allegro_font.h>
#include    <allegro5/allegro_acodec.h>
#include    <allegro5/allegro_audio.h>


//FUNCIONES

/*Recibe la matriz de juego, los datos del jugador, la pieza que se esta usando, la próximapieza, y si la hay, la
pieza que esta en "hold". Ademas va a recibir algunos parametros necesarios para trabajar con la biblioteca de allegro.
Esta funcion es la encargada de imprimir todo lo que hay en el display. No devuelve nada*/
void print_mat_juego (pieza_t* in_use, pieza_t *to_use, pieza_t* hold, int matriz[FIL][COL], ALLEGRO_FONT* font, game_stats_t* jugador);

/*Recibe la siguiente y si la hay, lapieza que esta en "hold". Esta función imprime cuando la llaman las piezas "next"
y "hold" en el display. No devuelve nada.*/
void print_siguiente_pieza (pieza_t* to_use, pieza_t* hold);

/*Recibe el id de una pieza y coordenadas x e y. Imprime unicamente un solo bloque del color que se necesita.
No devuelve nada*/
void print_bloque_color (int pieza, float i, float j);

/*No recive ni devuelve nada. Esta función imprime los bordes del juego en el display de allegro*/
void print_bordes_juego (void);

/*No recibe ni devuelve nada. Esta funcion borra todo lo que hay en el duisplay y lo deja en color negro.*/
void clear_display (void);

/*Esta función evalua que tecla se presioo y en dependiendo de eso llama a la funcion que se solicita. Recibe los
parametros que pueden llegar a necesitar las funciones asociadas a cada tecla (Parametros necesarios para trabajar
con allegro, pieza en uso, siguiente y la que se encuentra en hold, la matriz, los datos del jugador y una
variable, end, que indica el final del juego). No devuelve nada*/
void get_input (ALLEGRO_EVENT *event, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_SAMPLE*sound, pieza_t* in_use, pieza_t* hold, pieza_t* to_use, int mat[FIL][COL], char*end, ALLEGRO_FONT* font, game_stats_t* jugador);

/*Recibe un numero entero y un arreglo de char. Convierte los numeros de int a char* para que puedan ser impresos por
las funciones de allegro. No devuelve nada*/
void itoa (int numero, char s[]);

#endif /* JUEGO_ALLEGRO_H */
