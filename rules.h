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

#define FIL 16
#define COL 10
#define VACIO 0

typedef struct{

    int id=0;
    char sentido;
    int forma[3][3]={{0,0,0},{0,0,1},{1,1,1}};
    
    
}Orange_Ricky_t;

typedef struct{

    int id=1;
    char sentido;
    int forma[3][3]={{0,0,0},{1,0,0},{1,1,1}};
    
    
}Blue_Ricky_t;

typedef struct{

    int id=2;
    char sentido;
    int forma[3][3]={{0,0,0},{1,1,0},{0,1,1}};
    
    
}Cleveland_t;

typedef struct{

    int id=3;
    char sentido;
    int forma[3][3]={{0,0,0},{0,1,1},{1,1,0}};
    
    
}Rhode_Island_t;

typedef struct{

    int id=4;
    char sentido;
    int forma[4][4]={{0,0,0,0},{0,0,0,0},{1,1,1,1},{0,0,0,0}};
    
    
}Hero_t;

typedef struct{

    int id=5;
    char sentido;
    int forma[3][3]={{0,0,0},{0,1,0},{1,1,1}};
    
    
}Teewee_t;

typedef struct{

    int id=6;
    char sentido;
    int forma[2][2]={{1,1},{1,1}};
    
    
}SmashBoy_t;

#endif /* RULES_H */

