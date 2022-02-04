#include    "juego_allegro.h"

void print_mat_juego (pieza_t* in_use, pieza_t *to_use, int matriz[FIL][COL],ALLEGRO_FONT* font, game_stats_t* jugador)
{
    int y, x, k;
    char puntaje[6], nivel[10];
    
    itoa(jugador->score, puntaje);
    itoa(jugador->level, nivel);

    clear_display();
    
    print_bordes_juego();
    print_siguiente_pieza(to_use);
    al_draw_text(font, al_map_rgb(255, 255, 255), TAM_BLOQUE*14, TAM_BLOQUE*6.5, ALLEGRO_ALIGN_CENTRE, "score");
    al_draw_text(font, al_map_rgb(255, 255, 255), TAM_BLOQUE*14, TAM_BLOQUE*7.5, ALLEGRO_ALIGN_CENTRE, puntaje);
    al_draw_text(font, al_map_rgb(255, 255, 255), TAM_BLOQUE*14, TAM_BLOQUE*9.5, ALLEGRO_ALIGN_CENTRE, "level");
    al_draw_text(font, al_map_rgb(255, 255, 255), TAM_BLOQUE*14, TAM_BLOQUE*10.5, ALLEGRO_ALIGN_CENTRE, nivel);

    for (y=4; y<FIL; y++) {
        for (x=0; x<COL; x++) {
            if (matriz[y][x]!=0)
            {
                print_bloque_color(matriz[y][x], y+1, x+1);
            }
            else { 
                for (k=0; k<4; k++) {
                    if (x==((in_use->mat_bloque[0][k])+(in_use->coord_x)) && y==((in_use->mat_bloque[1][k])+(in_use->coord_y)))
                    {
                        print_bloque_color((int)in_use->id, y+1, x+1);
                    }
                }
            }
        }
    }
    al_flip_display();
}

void print_siguiente_pieza (pieza_t* to_use) {
    
    int k;
    
    for (k=0; k<4; k++) {
        
        switch (to_use->id) {
            case 1:
            al_draw_filled_rounded_rectangle(TAM_BLOQUE*(11.5+to_use->mat_bloque[0][k]),TAM_BLOQUE*(1+to_use->mat_bloque[1][k]),TAM_BLOQUE*(12.5+to_use->mat_bloque[0][k]),TAM_BLOQUE*(2+to_use->mat_bloque[1][k]),5,5,NARANJA);
            break;
        case 2:
            al_draw_filled_rounded_rectangle(TAM_BLOQUE*(11.5+to_use->mat_bloque[0][k]),TAM_BLOQUE*(1+to_use->mat_bloque[1][k]),TAM_BLOQUE*(12.5+to_use->mat_bloque[0][k]),TAM_BLOQUE*(2+to_use->mat_bloque[1][k]),5,5,AZUL);
            break;
        case 3:
            al_draw_filled_rounded_rectangle(TAM_BLOQUE*(11.5+to_use->mat_bloque[0][k]),TAM_BLOQUE*(1+to_use->mat_bloque[1][k]),TAM_BLOQUE*(12.5+to_use->mat_bloque[0][k]),TAM_BLOQUE*(2+to_use->mat_bloque[1][k]),5,5,ROJO);
            break;
        case 4:
            al_draw_filled_rounded_rectangle(TAM_BLOQUE*(11.5+to_use->mat_bloque[0][k]),TAM_BLOQUE*(1+to_use->mat_bloque[1][k]),TAM_BLOQUE*(12.5+to_use->mat_bloque[0][k]),TAM_BLOQUE*(2+to_use->mat_bloque[1][k]),5,5,VERDE);
            break;
        case 5:
            al_draw_filled_rounded_rectangle(TAM_BLOQUE*(12+to_use->mat_bloque[0][k]),TAM_BLOQUE*(1+to_use->mat_bloque[1][k]),TAM_BLOQUE*(13+to_use->mat_bloque[0][k]),TAM_BLOQUE*(2+to_use->mat_bloque[1][k]),5,5,CYAN);
            break;
        case 6:
            al_draw_filled_rounded_rectangle(TAM_BLOQUE*(11.5+to_use->mat_bloque[0][k]),TAM_BLOQUE*(1+to_use->mat_bloque[1][k]),TAM_BLOQUE*(12.5+to_use->mat_bloque[0][k]),TAM_BLOQUE*(2+to_use->mat_bloque[1][k]),5,5,MORADO);
            break;
        case 7:   
            al_draw_filled_rounded_rectangle(TAM_BLOQUE*(12+to_use->mat_bloque[0][k]),TAM_BLOQUE*(1+to_use->mat_bloque[1][k]),TAM_BLOQUE*(13+to_use->mat_bloque[0][k]),TAM_BLOQUE*(2+to_use->mat_bloque[1][k]),5,5,AMARILLO);
            break;
        }
    }
}
 
void print_bloque_color (int pieza, float i, float j) {
    
    switch (pieza) {
        case 1:
            al_draw_filled_rounded_rectangle(j*TAM_BLOQUE,(i-4)*TAM_BLOQUE,(j+1)*TAM_BLOQUE,(i+1-4)*TAM_BLOQUE,5,5,NARANJA);
            break;
        case 2:
            al_draw_filled_rounded_rectangle(j*TAM_BLOQUE,(i-4)*TAM_BLOQUE,(j+1)*TAM_BLOQUE,(i+1-4)*TAM_BLOQUE,5,5,AZUL);
            break;
        case 3:
            al_draw_filled_rounded_rectangle(j*TAM_BLOQUE,(i-4)*TAM_BLOQUE,(j+1)*TAM_BLOQUE,(i+1-4)*TAM_BLOQUE,5,5,ROJO);
            break;
        case 4:
            al_draw_filled_rounded_rectangle(j*TAM_BLOQUE,(i-4)*TAM_BLOQUE,(j+1)*TAM_BLOQUE,(i+1-4)*TAM_BLOQUE,5,5,VERDE);
            break;
        case 5:
            al_draw_filled_rounded_rectangle(j*TAM_BLOQUE,(i-4)*TAM_BLOQUE,(j+1)*TAM_BLOQUE,(i+1-4)*TAM_BLOQUE,5,5,CYAN);
            break;
        case 6:
            al_draw_filled_rounded_rectangle(j*TAM_BLOQUE,(i-4)*TAM_BLOQUE,(j+1)*TAM_BLOQUE,(i+1-4)*TAM_BLOQUE,5,5,MORADO);
            break;
        case 7:   
            al_draw_filled_rounded_rectangle(j*TAM_BLOQUE,(i-4)*TAM_BLOQUE,(j+1)*TAM_BLOQUE,(i+1-4)*TAM_BLOQUE,5,5,AMARILLO);
            break;
    }
}

void print_bordes_juego (void) {
    
    int fil, col;
    
    for (fil=0; fil<ALTO_PANTALLA; fil++) {
        for (col=0; col<ANCHO_PANTALLA; col++) {
            
            if ( col==0 || col== 11 || col== 16 || fil==0 || fil== 17 || ( col>11 && col<16 && fil==5))
            {
                al_draw_filled_rounded_rectangle(TAM_BLOQUE*col,TAM_BLOQUE*fil,TAM_BLOQUE*(col+1),TAM_BLOQUE*(fil+1),5,5,GRIS);
            }
        }
    }
}

void clear_display (void) {
    
    al_clear_to_color(al_map_rgb(0,0,0));
}

void get_input (ALLEGRO_EVENT *event, ALLEGRO_EVENT_QUEUE *event_queue, pieza_t* in_use, int mat[FIL][COL], char*end, ALLEGRO_FONT* font, game_stats_t* jugador) {
       
    switch (event->keyboard.keycode)
    {
        case ALLEGRO_KEY_DOWN: 
            mover_pieza(in_use,mat,ABA);
            break;
        case ALLEGRO_KEY_RIGHT:
            mover_pieza(in_use,mat,DER);
            break;
        case ALLEGRO_KEY_LEFT: 
            mover_pieza(in_use,mat,IZQ);
            break;
        case ALLEGRO_KEY_UP:
            rotar(in_use, mat);
            break;
        case ALLEGRO_KEY_SPACE:
            jugador->score+=((jugador->level)*(all_down(in_use, mat))*3);
            break;
        case ALLEGRO_KEY_ESCAPE:
            menu_pausa(event, event_queue, font, end, in_use, mat, jugador);                 // PLAY/PAUSE, ESCAPE, TOP-SCORES, REINICIAR JUEGO
            break;
            
    }
}  

void itoa (int n, char s[]) {
    
    int i, signo;

    if ((signo = n) < 0)  
    {
        n = -n;          
    }
    
    i = 0;
    
    do {       
        s[i++] = n % 10 + '0';   
    } while ((n /= 10) > 0);     
     
    if (signo < 0)
    {
        s[i++] = '-';
    }
    
    s[i] = '\0';
    
    int j;
    char c;

    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
     }
} 