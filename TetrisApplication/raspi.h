#ifndef RASPI_H
#define RASPI_H


void delay(int level, pieza_t* in_use, int matriz[FIL][COL], pieza_t*next, char* end_game, char* restart_game);
void get_name(game_stats_t* jugador);
void print_letter(int option, int index, int offset_x, int offset_y);
void print_flechas_verticales(int offset_x);
void col_clear(int col);
void print_game_over(void);



#endif /* RASPI_H */