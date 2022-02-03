/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rules.h
 * Author: santiago
 *
 * Created on January 2, 2022, 10:46 AM
 */

#ifndef RULES_H
#define RULES_H

#define FIL 20
#define COL 10

#define VACIO 0
#define DER 1
#define IZQ 2
#define ABA 3
#define ROTAR 4
#define MENU 5

#define LEVEL2 20
#define LEVEL3 45
#define LEVEL4 75
#define LEVEL5 110
#define LEVEL6 150
#define LEVEL7 195
#define LEVEL8 245
#define LEVEL9 300
#define LEVEL10 360

#define AMARILLO al_map_rgb(255,255,0)
#define AZUL al_map_rgb(0,0,172)
#define ROJO al_map_rgb(255,0,0)
#define MORADO al_map_rgb(205,0,205)
#define CYAN al_map_rgb(0,255,255)
#define NARANJA al_map_rgb(255,120,0)
#define VERDE al_map_rgb(0,255,0)
#define GRIS al_map_rgb(120,120,120)
#define BLANCO al_map_rgb(255,255,255)

typedef struct
{
    char id;  //1 blue ricky, 2 rhode island 
    unsigned char position;

    signed char coord_x;
    signed char coord_y;

    char mat_bloque[2][4]; //matriz de las coordenadas de los bloques, X es la fila 0 e Y la fila 1
}pieza_t;

typedef struct
{
    int level;
    long int score;
    long int cant_piezas;
    char nick [3];
}game_stats_t;

typedef struct 
{
    long int score;
    char name[3];
    int posicion_top;
    char vacio;
    
}jugador_top_t;

#endif /* RULES_H */

