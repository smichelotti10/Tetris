#include    <stdio.h>
#include    <stdlib.h>
#include    "rules.h"
#include    "piezas.h"
#include    <allegro5/allegro.h>
#include    <allegro5/allegro_native_dialog.h>
#include    <allegro5/allegro_primitives.h>

#define     TAM_BLOQUE      40

#define     ANCHO_PANTALLA  TAM_BLOQUE*(10+7)
#define     ALTO_PANTALLA   TAM_BLOQUE*(16+2)

void print_mat_juego (pieza_t* in_use, pieza_t *to_use, int matriz[FIL][COL]);
void print_bloque_color (int pieza, float i, float j);
void clear_display (void);
//void get_input (pieza_t* in_use, int mat[FIL][COL], ALLEGRO_KEYBOARD_STATE* estado_teclado);
void print_siguiente_pieza (pieza_t* to_use);
void print_bordes_juego (void);
void get_input (ALLEGRO_EVENT event, pieza_t* in_use, int mat[FIL][COL]);

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
    
    //INICIALIZO LAS VARIABLES Y BIBLIOTECAS
    srand(time(NULL)); //genero una semilla randomizada
    clear_mat(matriz);    
    init_jugador(&jugador); //llamamo a la función que inicializa las stats del juego
    generador(&in_use, &jugador); //llamamos a la función que rellena los campos de la pieza
    generador(&to_use, &jugador);
    
    al_install_keyboard();
    
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_init_primitives_addon(); 
    display = al_create_display(ANCHO_PANTALLA, ALTO_PANTALLA);   
    al_set_new_display_flags(ALLEGRO_FRAMELESS);   
    al_set_window_title(display, "Tetris");
    al_set_window_position(display, 200, 5);
    
    if(!display) {
        al_show_native_message_box(NULL,NULL,NULL, "No se pudo crear un display", NULL, 0);
        return -1;
    }
    
    // JUEGO
    unsigned long int time = 0;
    int end=0;
    
    while(!end){
        
        print_mat_juego (&in_use,&to_use,matriz);
        if (time==0)
        {
            time = 0.7*10000000 - ((jugador.level - 1) * 0.07);
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
                fila_completa(matriz, &jugador); //vemos si se completo una fila para sumar puntos y eso
                in_use = to_use;
                generador(&to_use, &jugador);    // genero la siguiente pieza 
                print_mat_juego (&in_use,&to_use,matriz);
            }
        }
        else 
        {
            get_input(event,&in_use,matriz);
        }
        
        if(game_over(matriz))
        {
            printf("GAME OVER\n Final Score: %ld\n Level: %d\n", jugador.score, jugador.level);
            return 0;
        }
        
        
    }

    // ELIMINO MEMORIA RESERVADA DINAMICAMENTE
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    
    return 0;
}

void print_mat_juego (pieza_t* in_use, pieza_t *to_use, int matriz[FIL][COL])
{
    int y, x, k;

    clear_display();
    
    for (y=0; y<ALTO_PANTALLA; y++) {
        for (x=0; x<ANCHO_PANTALLA; x++) {
            
            if ( x==0 || x== 11 || x== 16 || y==0 || y== 17)
            {
                al_draw_filled_rounded_rectangle(TAM_BLOQUE*x,TAM_BLOQUE*y,TAM_BLOQUE*(x+1),TAM_BLOQUE*(y+1),5,5,DORADO);
            }
        }
    }
    print_siguiente_pieza(to_use);

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
    al_flip_display();
}

void print_bordes_juego (void) {
    
    int fil, col;
    
    for (fil=0; fil<ALTO_PANTALLA; fil++) {
        for (col=0; col<ANCHO_PANTALLA; col++) {
            
            if ( col==0 || col== 11 || col== 16 || fil==0 || fil== 17)
            {
                al_draw_filled_rounded_rectangle(TAM_BLOQUE*col,TAM_BLOQUE*fil,TAM_BLOQUE*(col+1),TAM_BLOQUE*(fil+1),5,5,DORADO);
            }
        }
    }
    al_flip_display();
}

void get_input (ALLEGRO_EVENT event, pieza_t* in_use, int mat[FIL][COL]) {
       
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
    }
}        