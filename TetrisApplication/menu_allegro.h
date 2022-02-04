#ifndef MENU_ALLEGRO_H
#define MENU_ALLEGRO_H

//HEADERS
#include    <stdio.h>
#include    "rules.h"
#include    "juego_allegro.h"
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
void menu_inicio (ALLEGRO_EVENT *event, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT* font, ALLEGRO_SAMPLE * sound, char* end, pieza_t* in_use, int matriz [FIL][COL], game_stats_t* jugador);
void menu_pausa (ALLEGRO_EVENT *event, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT* font, ALLEGRO_SAMPLE* sound, char* end, pieza_t* in_use, int matriz [FIL][COL], game_stats_t* jugador);
void game_over_allegro (ALLEGRO_EVENT *event, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT* font, char* end, pieza_t* in_use, int matriz [FIL][COL], game_stats_t* jugador);
void ask_name (game_stats_t* jugador, ALLEGRO_EVENT *event, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT* font);
void print_high_scores (ALLEGRO_FONT* font, ALLEGRO_EVENT* event, ALLEGRO_EVENT_QUEUE *event_queue);
void commands (ALLEGRO_FONT* font, ALLEGRO_EVENT *event, ALLEGRO_EVENT_QUEUE *event_queue);

#endif /* MENU_ALLEGRO_H */
