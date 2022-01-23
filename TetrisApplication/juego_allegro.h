#ifndef JUEGO_ALLEGRO_H
#define JUEGO_ALLEGRO_H

//HEADERS
#include    "rules.h"
#include    "piezas.h"
#include    "menu_allegro.h"
#include    <allegro5/allegro.h>
#include    <allegro5/allegro_primitives.h>
#include    <allegro5/allegro_ttf.h>
#include    <allegro5/allegro_font.h>

//FUNCIONES
void print_mat_juego (pieza_t* in_use, pieza_t *to_use, int matriz[FIL][COL],ALLEGRO_FONT* font, game_stats_t* jugador);
void print_siguiente_pieza (pieza_t* to_use);
void print_bloque_color (int pieza, float i, float j);
void print_bordes_juego (void);
void clear_display (void);
void get_input (ALLEGRO_EVENT *event, ALLEGRO_EVENT_QUEUE *event_queue, pieza_t* in_use, int mat[FIL][COL], char*end, ALLEGRO_FONT* font, game_stats_t* jugador);
void itoa (int n, char s[]);

#endif /* JUEGO_ALLEGRO_H */