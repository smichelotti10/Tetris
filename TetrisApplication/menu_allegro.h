#ifndef MENU_ALLEGRO_H
#define MENU_ALLEGRO_H

//HEADERS
#include    <stdio.h>
#include    <allegro5/allegro.h>
#include    <allegro5/allegro_ttf.h>
#include    <allegro5/allegro_font.h>
#include    <allegro5/allegro_image.h>
#include    <allegro5/allegro_acodec.h>
#include    <allegro5/allegro_audio.h>

// MACROS Y CONSTANTES
#define     TAM_BLOQUE      40
#define     ANCHO_PANTALLA  TAM_BLOQUE*(10+7)
#define     ALTO_PANTALLA   TAM_BLOQUE*(16+2)

//FUNCIONES
/*La primera recibe los punteros necesario para leer el teclado, el puntero que le pasa el tipo de letra para imprimir los textos, el puntero al sonido que debe hacer cuando se preciona una tecla, el puntero para saber cuando terminar, el puntero a la pieza, la matriz, y el jugador*/
void menu_inicio (ALLEGRO_EVENT *event, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT* font, ALLEGRO_SAMPLE * sound, char* end, pieza_t* in_use, int matriz [FIL][COL], game_stats_t* jugador);
/*Menu pausa recibe los punteros que permiten leer el teclado, el puntero al tipo de letra para poder imprimir, el puntero al sonido que debe hacer al presionar una tecla, un puntero a la pieza, la matriz, el jugador y el puntero a la pieza en hold*/
void menu_pausa (ALLEGRO_EVENT *event, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT* font, ALLEGRO_SAMPLE*sound, char* end, pieza_t* in_use, int matriz [FIL][COL], game_stats_t* jugador, pieza_t*hold);
/*Game over recibe los punteros que permiten leer el teclado, el puntero al tipo de letra para poder imprimir, el puntero al sonido que debe hacer al presionar una tecla, un puntero a la pieza, la matriz, el jugador y el puntero a la pieza en hold*/
void game_over_allegro (ALLEGRO_EVENT *event, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT* font, ALLEGRO_SAMPLE*sound, char* end, pieza_t* in_use, int matriz [FIL][COL], game_stats_t* jugador, pieza_t*hold);
/*Ask_Name recibe la informacion para crear el nik, por ello recibe el puntero al jugador donde se guarda el nick, el puntero para poder leer el teclado y el puntero al tipo de letra para poder imprimir en pantalla*/
void ask_name (game_stats_t* jugador, ALLEGRO_EVENT *event, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT* font);
/*La funcion de high Scores se usa para poder imprimir los primeros 10 puestos de los juadores, para poder hacerlo recibe el tipo de letra y los punteros para poder leer el teclado*/
void print_high_scores (ALLEGRO_FONT* font, ALLEGRO_EVENT* event, ALLEGRO_EVENT_QUEUE *event_queue);
/*La funcion de Commands se usa para poder imprimir los comandos que se utilizan en el juego, para poder hacerlo recibe el tipo de letra y los punteros para poder leer el teclado*/
void commands (ALLEGRO_FONT* font, ALLEGRO_EVENT *event, ALLEGRO_EVENT_QUEUE *event_queue);

#endif /* MENU_ALLEGRO_H */
