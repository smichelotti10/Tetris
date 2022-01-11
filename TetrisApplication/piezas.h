/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   piezas.h
 * Author: santiago
 *
 * Created on January 6, 2022, 1:49 AM
 */

#ifndef PIEZAS_H
#define PIEZAS_H

void generador(pieza_t * to_use, game_stats_t* jugador);
void init_jugador(game_stats_t* jugador);
void clear_mat(int mat[FIL][COL]);
int move(pieza_t* in_use, int mat[FIL][COL], char direccion);
int check(pieza_t* pieza, int mat[FIL][COL]);
void setear_pieza(pieza_t* in_use, int matriz[FIL][COL]);
void all_down(pieza_t* in_use,int matriz[FIL][COL]);
void rotar(pieza_t* in_use,int mat[FIL][COL]);
void fila_completa (int matriz[FIL][COL], game_stats_t* jugador);
void push_mat_down (int matriz[FIL][COL], int fila);
void print_mat (pieza_t* in_use, int matriz[FIL][COL]);
int game_over(int matriz[FIL][COL]);
void delay(int level);

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

#endif /* PIEZAS_H */

