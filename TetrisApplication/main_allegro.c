#include    <stdio.h>
#include    <stdlib.h>
#include    "rules.h"
#include    "piezas.h"
#include    <allegro5/allegro.h>
#include    <allegro5/allegro_native_dialog.h>
#include    <allegro5/allegro_primitives.h>
#include    <allegro5/allegro_ttf.h>
#include    <allegro5/allegro_font.h>

#define     TAM_BLOQUE      40

#define     ANCHO_PANTALLA  TAM_BLOQUE*(10+7)
#define     ALTO_PANTALLA   TAM_BLOQUE*(16+2)

void print_mat_juego (pieza_t* in_use, pieza_t *to_use, int matriz[FIL][COL],ALLEGRO_FONT* font, game_stats_t* jugador);
void print_bloque_color (int pieza, float i, float j);
void clear_display (void);
void print_siguiente_pieza (pieza_t* to_use);
void print_bordes_juego (void);
void get_input (ALLEGRO_EVENT event, ALLEGRO_EVENT_QUEUE *event_queue, pieza_t* in_use, int mat[FIL][COL], char*end, ALLEGRO_FONT* font, game_stats_t* jugador);
void menu_pausa (ALLEGRO_EVENT event, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT* font, char* end, pieza_t* in_use, int matriz [FIL][COL], game_stats_t* jugador);
void itoa (int n, char s[]);
void game_over_allegro (ALLEGRO_EVENT event, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT* font, char* end, pieza_t* in_use, int matriz [FIL][COL], game_stats_t* jugador);

int main(void) {

    //INICIALIZO ALLEGRO
    if (!al_init()) {
        al_show_native_message_box(NULL,NULL,NULL, "No se pudo inicializar Allegro", NULL, 0);
        return -1;
    }
   
    // CREO VARIABLES QUE SE UTILIZARAN DURNTE EL JUEGO
    int matriz[FIL][COL];
    game_stats_t jugador;
    pieza_t in_use;
    pieza_t to_use;
    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_EVENT event;
    ALLEGRO_FONT* font;
    
    //INICIALIZO LAS VARIABLES Y BIBLIOTECAS
    srand(time(NULL)); //genero una semilla randomizada
    clear_mat(matriz);    
    init_jugador(&jugador); //llamamo a la función que inicializa las stats del juego
    generador(&in_use, &jugador); //llamamos a la función que rellena los campos de la pieza
    generador(&to_use, &jugador);
    
    al_install_keyboard();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());  
    display = al_create_display(ANCHO_PANTALLA, ALTO_PANTALLA);   
    al_set_new_display_flags(ALLEGRO_FRAMELESS);   
    al_set_window_title(display, "Tetris");
    al_set_window_position(display, 200, 5);
    font = al_load_ttf_font("nombre.ttf", 36, 0);
    
    if(!display) {
        al_show_native_message_box(NULL,NULL,NULL, "No se pudo crear un display", NULL, 0);
        return -1;
    }
    
    int value = al_show_native_message_box(display, "MessageBox", "Inicio del Juego", "Ust está por comenzar a jugar TETRIS. Desea continuar?", NULL, ALLEGRO_MESSAGEBOX_YES_NO);
    if(value!=1)
    {
        al_rest(1.0);
        al_destroy_display(display);
        al_destroy_event_queue(event_queue);
        al_destroy_font(font);
        
        return 0;
    }
     
    al_draw_text(font, al_map_rgb(255, 255, 255), ANCHO_PANTALLA/2, ALTO_PANTALLA/2, ALLEGRO_ALIGN_CENTRE, "TETRIS");
    al_flip_display();
    al_rest(1.0);
    
    jugador.nick[0]='E';
    jugador.nick[1]='Z';
    jugador.nick[2]='E';
    // JUEGO
    unsigned long int time = 0;
    char end=0;
    
    
    
    while(!end){
        
        print_mat_juego (&in_use,&to_use,matriz,font, &jugador);
        if (time==0)
        {
            time = (0.7-(jugador.level-1)*0.069)*10000000;
        }

        while (--time) {
            al_get_next_event(event_queue, &event);
            if (event.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                break;
            }
        }

        if (time==0)
        {
            if(mover_pieza(&in_use, matriz, ABA)) //con la función de move, ya nos aseguramos que se pueda seguir bajando o no.
            {
                setear_pieza(&in_use, matriz); //guardamos la pieza en la matriz
                fila_completa(matriz, &jugador, &to_use); //vemos si se completo una fila para sumar puntos y eso
                in_use = to_use;
                generador(&to_use, &jugador);    // genero la siguiente pieza 
                print_mat_juego (&in_use,&to_use,matriz,font, &jugador);
            }
        }
        else 
        {
            get_input(event, event_queue, &in_use,matriz, &end, font, &jugador);
        }
        
        if(game_over(matriz))
        {
            top_scores(&jugador);
            game_over_allegro(event, event_queue, font, &end, &in_use, matriz, &jugador);
        } 
    }

    // ELIMINO MEMORIA RESERVADA DINAMICAMENTE
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);
    
    return 0;
}

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

void clear_display (void) {
    
    al_clear_to_color(al_map_rgb(0,0,0));
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

void get_input (ALLEGRO_EVENT event, ALLEGRO_EVENT_QUEUE *event_queue, pieza_t* in_use, int mat[FIL][COL], char*end, ALLEGRO_FONT* font, game_stats_t* jugador) {
       
    switch (event.keyboard.keycode)
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
            all_down(in_use, mat);
            break;
        case ALLEGRO_KEY_ESCAPE:
            *end=1;
            break;
        case ALLEGRO_KEY_M:
            menu_pausa(event, event_queue, font, end, in_use, mat, jugador);                 // PLAY/PAUSE, ESCAPE, TOP-SCORES, REINICIAR JUEGO
            break;
            
    }
}  

void menu_pausa (ALLEGRO_EVENT event, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT* font, char* end, pieza_t* in_use, int matriz [FIL][COL], game_stats_t* jugador) {
   
    char contador = 0;
    char end_menu=0;
    
    clear_display();
    al_draw_text(font, AMARILLO, ANCHO_PANTALLA/2, TAM_BLOQUE*5, ALLEGRO_ALIGN_CENTRE, "PLAY");
    al_draw_text(font, al_map_rgb(255,255,255), ANCHO_PANTALLA/2, TAM_BLOQUE*7, ALLEGRO_ALIGN_CENTRE, "QUIT");
    al_draw_text(font, al_map_rgb(255,255,255), ANCHO_PANTALLA/2, TAM_BLOQUE*9, ALLEGRO_ALIGN_CENTRE, "HIGH SCORES");
    al_draw_text(font, al_map_rgb(255,255,255), ANCHO_PANTALLA/2, TAM_BLOQUE*11, ALLEGRO_ALIGN_CENTRE, "REINICIAR JUEGO");
    al_flip_display();
    
    while(!end_menu) {
        al_wait_for_event(event_queue, &event);
        if (event.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                switch (event.keyboard.keycode)
                {
                    case ALLEGRO_KEY_DOWN: 
                        contador++;               
                        break;
                    case ALLEGRO_KEY_UP:
                        contador--;
                        break;
                    case ALLEGRO_KEY_ENTER:
                        end_menu=1;
                        switch (contador%4)
                        {
                            case 0:             // Vuelve al juego
                                break;
                            case 1:
                                *end=1;         // Termina el juego
                                break;
                            case 2:             // Top Scores
                                break;
                            case 3:    
                                clear_mat(matriz);
                                generador(in_use, jugador);
                                init_jugador(jugador);
                                clear_display();
                                break;                        
                        }
                        break;
            }
            switch (contador%4)
            {
                case 0:
                    clear_display();
                    al_draw_text(font, AMARILLO, ANCHO_PANTALLA/2, TAM_BLOQUE*5, ALLEGRO_ALIGN_CENTRE, "PLAY");
                    al_draw_text(font, al_map_rgb(255,255,255), ANCHO_PANTALLA/2, TAM_BLOQUE*7, ALLEGRO_ALIGN_CENTRE, "QUIT");
                    al_draw_text(font, al_map_rgb(255,255,255), ANCHO_PANTALLA/2, TAM_BLOQUE*9, ALLEGRO_ALIGN_CENTRE, "HIGH SCORES");
                    al_draw_text(font, al_map_rgb(255,255,255), ANCHO_PANTALLA/2, TAM_BLOQUE*11, ALLEGRO_ALIGN_CENTRE, "REINICIAR JUEGO");
                    al_flip_display();
                    break;
                case 1:
                    clear_display();
                    al_draw_text(font, al_map_rgb(255,255,255), ANCHO_PANTALLA/2, TAM_BLOQUE*5, ALLEGRO_ALIGN_CENTRE, "PLAY");
                    al_draw_text(font, AMARILLO, ANCHO_PANTALLA/2, TAM_BLOQUE*7, ALLEGRO_ALIGN_CENTRE, "QUIT");
                    al_draw_text(font, al_map_rgb(255,255,255), ANCHO_PANTALLA/2, TAM_BLOQUE*9, ALLEGRO_ALIGN_CENTRE, "HIGH SCORES");
                    al_draw_text(font, al_map_rgb(255,255,255), ANCHO_PANTALLA/2, TAM_BLOQUE*11, ALLEGRO_ALIGN_CENTRE, "REINICIAR JUEGO");
                    al_flip_display();
                    break;
                case 2:
                    clear_display();
                    al_draw_text(font, al_map_rgb(255,255,255), ANCHO_PANTALLA/2, TAM_BLOQUE*5, ALLEGRO_ALIGN_CENTRE, "PLAY");
                    al_draw_text(font, al_map_rgb(255,255,255), ANCHO_PANTALLA/2, TAM_BLOQUE*7, ALLEGRO_ALIGN_CENTRE, "QUIT");
                    al_draw_text(font, AMARILLO, ANCHO_PANTALLA/2, TAM_BLOQUE*9, ALLEGRO_ALIGN_CENTRE, "HIGH SCORES");
                    al_draw_text(font, al_map_rgb(255,255,255), ANCHO_PANTALLA/2, TAM_BLOQUE*11, ALLEGRO_ALIGN_CENTRE, "REINICIAR JUEGO");
                    al_flip_display();
                    break;
                case 3:
                    clear_display();
                    al_draw_text(font, al_map_rgb(255,255,255), ANCHO_PANTALLA/2, TAM_BLOQUE*5, ALLEGRO_ALIGN_CENTRE, "PLAY");
                    al_draw_text(font, al_map_rgb(255,255,255), ANCHO_PANTALLA/2, TAM_BLOQUE*7, ALLEGRO_ALIGN_CENTRE, "QUIT");
                    al_draw_text(font, al_map_rgb(255,255,255), ANCHO_PANTALLA/2, TAM_BLOQUE*9, ALLEGRO_ALIGN_CENTRE, "HIGH SCORES");
                    al_draw_text(font, AMARILLO, ANCHO_PANTALLA/2, TAM_BLOQUE*11, ALLEGRO_ALIGN_CENTRE, "REINICIAR JUEGO");
                    al_flip_display();
                    break;
            }
        }
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

void game_over_allegro (ALLEGRO_EVENT event, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT* font, char* end, pieza_t* in_use, int matriz [FIL][COL], game_stats_t* jugador) {
    
    char contador = 0;
    char end_game_over=0;
    
    clear_display();
    al_draw_text(font, al_map_rgb(255,255,255), ANCHO_PANTALLA/2, TAM_BLOQUE*4, ALLEGRO_ALIGN_CENTRE, "GAME OVER");
    al_draw_text(font, AMARILLO, ANCHO_PANTALLA/2, TAM_BLOQUE*7, ALLEGRO_ALIGN_CENTRE, "REINICIAR JUEGO");
    al_draw_text(font, al_map_rgb(255,255,255), ANCHO_PANTALLA/2, TAM_BLOQUE*9, ALLEGRO_ALIGN_CENTRE, "SALIR");
    al_flip_display();
    
    while(!end_game_over) {
        al_wait_for_event(event_queue, &event);
        if (event.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                switch (event.keyboard.keycode)
            {
                case ALLEGRO_KEY_DOWN: 
                    contador++;               
                    break;
                case ALLEGRO_KEY_UP:
                    contador--;
                    break;
                case ALLEGRO_KEY_ENTER:
                    end_game_over=1;
                    switch (contador%2)
                    {
                        case 0:             // Vuelve al juego
                            clear_mat(matriz);
                            generador(in_use, jugador);
                            init_jugador(jugador);
                            clear_display();
                            break;;
                        case 1:
                            *end=1;         // Termina el juego
                            break;                                                   
                    }
                    break;
            }
            switch (contador%2)
            {
                case 0:
                    clear_display();
                    al_draw_text(font, al_map_rgb(255,255,255), ANCHO_PANTALLA/2, TAM_BLOQUE*4, ALLEGRO_ALIGN_CENTRE, "GAME OVER");
                    al_draw_text(font, AMARILLO, ANCHO_PANTALLA/2, TAM_BLOQUE*7, ALLEGRO_ALIGN_CENTRE, "REINICIAR JUEGO");
                    al_draw_text(font, al_map_rgb(255,255,255), ANCHO_PANTALLA/2, TAM_BLOQUE*9, ALLEGRO_ALIGN_CENTRE, "SALIR");
                    al_flip_display();
                    break;
                case 1:
                    clear_display();
                    al_draw_text(font, al_map_rgb(255,255,255), ANCHO_PANTALLA/2, TAM_BLOQUE*4, ALLEGRO_ALIGN_CENTRE, "GAME OVER");
                    al_draw_text(font, al_map_rgb(255,255,255), ANCHO_PANTALLA/2, TAM_BLOQUE*7, ALLEGRO_ALIGN_CENTRE, "REINICIAR JUEGO");
                    al_draw_text(font, AMARILLO, ANCHO_PANTALLA/2, TAM_BLOQUE*9, ALLEGRO_ALIGN_CENTRE, "SALIR");
                    al_flip_display();
                    break;
            }
        }
    }
}