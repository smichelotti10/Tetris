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

void generador(pieza_t * to_use);
void move(pieza_t* in_use, int mat[FIL][COL], char direccion);
int check(pieza_t*, int mat[FIL][COL]);

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

