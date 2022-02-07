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
void print_mat_juego (pieza_t* in_use, pieza_t *to_use, pieza_t* hold, int matriz[FIL][COL], ALLEGRO_FONT* font, game_stats_t* jugador);
void print_siguiente_pieza (pieza_t* to_use, pieza_t* hold);
void print_bloque_color (int pieza, float i, float j);
void print_bordes_juego (void);
void clear_display (void);
void get_input (ALLEGRO_EVENT *event, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_SAMPLE*sound, pieza_t* in_use, pieza_t* hold, pieza_t* to_use, int mat[FIL][COL], char*end, ALLEGRO_FONT* font, game_stats_t* jugador);
void itoa (int n, char s[]);

#endif /* JUEGO_ALLEGRO_H */
