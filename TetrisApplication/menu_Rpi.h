
#ifndef MENU_RPI_H
#define MENU_RPI_H

int menu_pausa(void);
/*
Función que recorre las opciones del menu de pausa (reanudar, reiniciar partida, ir a top scores y abandonar)
Imprime en el display las opciones y devuelve la opcion seleccionada
*/

int menu_start(void);
/*
Idem que menu_pausa pero con las opciones de inicio, es decir sin reiniciar partida
*/

int menu_game_over(void);
/* 
  Idem con las opciones de game_over, es decir sin reanudar juego
*/

void print_option(int option);
/*
Funcion para imprimir en display las figuras del menu
*/

void print_flechas_horizontales(void);
/*
Imprime las flechas horizontales en los extremos horizontales del display, a mitad de altura
*/

char get_option(void);
/*
get_option se utiliza para leer el joystick y devuelve 5 posibles valores; las 4 direcciones y el "Enter"
*/


#endif /* MENU_RPI_H */