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

typedef struct
{
    char id;  //1 blue ricky, 2 rhode island 
    unsigned char position;

    char coord_x;
    char coord_y;

    char mat_bloque[2][4]; //matriz de las coordenadas de los bloques, X es la fila 0 e Y la fila 1
}pieza_t;

#endif /* RULES_H */

