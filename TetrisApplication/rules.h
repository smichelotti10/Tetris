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
#define IZQ -1
#define ABA 0

#define LEVEL2 20
#define LEVEL3 45
#define LEVEL4 75
#define LEVEL5 110
#define LEVEL6 150
#define LEVEL7 195
#define LEVEL8 245
#define LEVEL9 300
#define LEVEL10 360


typedef struct
{
    char id;  //1 blue ricky, 2 rhode island 
    unsigned char position;

    char coord_x;
    char coord_y;

    char mat_bloque[2][4]; //matriz de las coordenadas de los bloques, X es la fila 0 e Y la fila 1
}pieza_t;

typedef struct
{
    int level;
    long int score;
    long int cant_piezas;
    char* nick;
}game_stats_t;

#endif /* RULES_H */

