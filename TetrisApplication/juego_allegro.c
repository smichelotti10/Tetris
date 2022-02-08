#include    "rules.h"
#include    "backend.h"
#include    "juego_allegro.h"
#include    "menu_allegro.h"

void print_mat_juego (pieza_t* in_use, pieza_t *to_use, pieza_t* hold, int matriz[FIL][COL],ALLEGRO_FONT* font, game_stats_t* jugador)
{
    int y, x, k;
    char puntaje[6], nivel[10];
    
    itoa(jugador->score, puntaje);      // Convierto el nuvel y el puntaje del jugador a formato char*
    itoa(jugador->level, nivel);        // para poder imprimirlo con las funciones de allegro

    clear_display();
    
    // IMPRIMO BORDES DEL JUEGO E INFORMACION ADICIONAL DEL JUEGO
    print_bordes_juego();
    print_siguiente_pieza(to_use,hold);
    al_draw_text(font, al_map_rgb(255, 255, 255), TAM_BLOQUE*14, TAM_BLOQUE*11.5, ALLEGRO_ALIGN_CENTRE, "score");
    al_draw_text(font, al_map_rgb(255, 255, 255), TAM_BLOQUE*14, TAM_BLOQUE*12.5, ALLEGRO_ALIGN_CENTRE, puntaje);
    al_draw_text(font, al_map_rgb(255, 255, 255), TAM_BLOQUE*14, TAM_BLOQUE*14, ALLEGRO_ALIGN_CENTRE, "level");
    al_draw_text(font, al_map_rgb(255, 255, 255), TAM_BLOQUE*14, TAM_BLOQUE*15, ALLEGRO_ALIGN_CENTRE, nivel);

    // IMPIRMO LA PANTALLA DE JUEGO
    for (y=4; y<FIL; y++) {     // Recorro la matriz e imprimo las piezas que caen y las que ya estan seteadas 
        for (x=0; x<COL; x++) {
            if (matriz[y][x]!=0)  // Si hay una pieza ya seteada se va a imprimir aqui
            {
                print_bloque_color(matriz[y][x], y+1, x+1);
            }
            else {                          // Si la pieza todavia esta en juego hay que imprimirla tomando como
                for (k=0; k<4; k++) {       // referencia coor_x y coord_y de la pieza
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

void print_siguiente_pieza (pieza_t* to_use, pieza_t* hold) {
    
    int k;
    
    for (k=0; k<4; k++) {   
        
        switch (to_use->id) {  // Este bloque es el encargado de imprimir las piezas que van a aparecer proximamente
            case ORANGERICKY:
                al_draw_filled_rounded_rectangle(TAM_BLOQUE*(11.5+to_use->mat_bloque[0][k]),TAM_BLOQUE*(1+to_use->mat_bloque[1][k]),TAM_BLOQUE*(12.5+to_use->mat_bloque[0][k]),TAM_BLOQUE*(2+to_use->mat_bloque[1][k]),5,5,NARANJA);
                break;
            case BLUERICKY:
                al_draw_filled_rounded_rectangle(TAM_BLOQUE*(11.5+to_use->mat_bloque[0][k]),TAM_BLOQUE*(1+to_use->mat_bloque[1][k]),TAM_BLOQUE*(12.5+to_use->mat_bloque[0][k]),TAM_BLOQUE*(2+to_use->mat_bloque[1][k]),5,5,AZUL);
                break;
            case CLEVELANDZ:
                al_draw_filled_rounded_rectangle(TAM_BLOQUE*(11.5+to_use->mat_bloque[0][k]),TAM_BLOQUE*(1+to_use->mat_bloque[1][k]),TAM_BLOQUE*(12.5+to_use->mat_bloque[0][k]),TAM_BLOQUE*(2+to_use->mat_bloque[1][k]),5,5,ROJO);
                break;
            case RHODEISLANDZ:
                al_draw_filled_rounded_rectangle(TAM_BLOQUE*(11.5+to_use->mat_bloque[0][k]),TAM_BLOQUE*(1+to_use->mat_bloque[1][k]),TAM_BLOQUE*(12.5+to_use->mat_bloque[0][k]),TAM_BLOQUE*(2+to_use->mat_bloque[1][k]),5,5,VERDE);
                break;
            case HERO:
                al_draw_filled_rounded_rectangle(TAM_BLOQUE*(12+to_use->mat_bloque[0][k]),TAM_BLOQUE*(1+to_use->mat_bloque[1][k]),TAM_BLOQUE*(13+to_use->mat_bloque[0][k]),TAM_BLOQUE*(2+to_use->mat_bloque[1][k]),5,5,CYAN);
                break;
            case TEEWEE:
                al_draw_filled_rounded_rectangle(TAM_BLOQUE*(11.5+to_use->mat_bloque[0][k]),TAM_BLOQUE*(1+to_use->mat_bloque[1][k]),TAM_BLOQUE*(12.5+to_use->mat_bloque[0][k]),TAM_BLOQUE*(2+to_use->mat_bloque[1][k]),5,5,MORADO);
                break;
            case SMASHBOY:   
                al_draw_filled_rounded_rectangle(TAM_BLOQUE*(12+to_use->mat_bloque[0][k]),TAM_BLOQUE*(1+to_use->mat_bloque[1][k]),TAM_BLOQUE*(13+to_use->mat_bloque[0][k]),TAM_BLOQUE*(2+to_use->mat_bloque[1][k]),5,5,AMARILLO);
                break;
        }
        
        switch (hold->id) {     // Este bloque es el encargado de imprimir las piezas que el jugador holdea o guarda para usar despues
            case ORANGERICKY:
                al_draw_filled_rounded_rectangle(TAM_BLOQUE*(11.5+hold->mat_bloque[0][k]),TAM_BLOQUE*(6+hold->mat_bloque[1][k]),TAM_BLOQUE*(12.5+hold->mat_bloque[0][k]),TAM_BLOQUE*(7+hold->mat_bloque[1][k]),5,5,NARANJA);
                break;
            case BLUERICKY:
                al_draw_filled_rounded_rectangle(TAM_BLOQUE*(11.5+hold->mat_bloque[0][k]),TAM_BLOQUE*(6+hold->mat_bloque[1][k]),TAM_BLOQUE*(12.5+hold->mat_bloque[0][k]),TAM_BLOQUE*(7+hold->mat_bloque[1][k]),5,5,AZUL);
                break;
            case CLEVELANDZ:
                al_draw_filled_rounded_rectangle(TAM_BLOQUE*(11.5+hold->mat_bloque[0][k]),TAM_BLOQUE*(6+hold->mat_bloque[1][k]),TAM_BLOQUE*(12.5+hold->mat_bloque[0][k]),TAM_BLOQUE*(7+hold->mat_bloque[1][k]),5,5,ROJO);
                break;
            case RHODEISLANDZ:
                al_draw_filled_rounded_rectangle(TAM_BLOQUE*(11.5+hold->mat_bloque[0][k]),TAM_BLOQUE*(6+hold->mat_bloque[1][k]),TAM_BLOQUE*(12.5+hold->mat_bloque[0][k]),TAM_BLOQUE*(7+hold->mat_bloque[1][k]),5,5,VERDE);
                break;
            case HERO:
                al_draw_filled_rounded_rectangle(TAM_BLOQUE*(12+hold->mat_bloque[0][k]),TAM_BLOQUE*(6+hold->mat_bloque[1][k]),TAM_BLOQUE*(13+hold->mat_bloque[0][k]),TAM_BLOQUE*(7+hold->mat_bloque[1][k]),5,5,CYAN);
                break;
            case TEEWEE:
                al_draw_filled_rounded_rectangle(TAM_BLOQUE*(11.5+hold->mat_bloque[0][k]),TAM_BLOQUE*(6+hold->mat_bloque[1][k]),TAM_BLOQUE*(12.5+hold->mat_bloque[0][k]),TAM_BLOQUE*(7+hold->mat_bloque[1][k]),5,5,MORADO);
                break;
            case SMASHBOY:
                al_draw_filled_rounded_rectangle(TAM_BLOQUE*(12+hold->mat_bloque[0][k]),TAM_BLOQUE*(6+hold->mat_bloque[1][k]),TAM_BLOQUE*(13+hold->mat_bloque[0][k]),TAM_BLOQUE*(7+hold->mat_bloque[1][k]),5,5,AMARILLO);
                break;
        }      
    }
}
 
void print_bloque_color (int pieza, float i, float j) {
    
    switch (pieza) {   // La funcion va recibir el id de la pieza y la posicion para imprimir un solo bloque del color correspondiente
        case ORANGERICKY:
            al_draw_filled_rounded_rectangle(j*TAM_BLOQUE,(i-4)*TAM_BLOQUE,(j+1)*TAM_BLOQUE,(i+1-4)*TAM_BLOQUE,5,5,NARANJA);
            break;
        case BLUERICKY:
            al_draw_filled_rounded_rectangle(j*TAM_BLOQUE,(i-4)*TAM_BLOQUE,(j+1)*TAM_BLOQUE,(i+1-4)*TAM_BLOQUE,5,5,AZUL);
            break;
        case CLEVELANDZ:
            al_draw_filled_rounded_rectangle(j*TAM_BLOQUE,(i-4)*TAM_BLOQUE,(j+1)*TAM_BLOQUE,(i+1-4)*TAM_BLOQUE,5,5,ROJO);
            break;
        case RHODEISLANDZ:
            al_draw_filled_rounded_rectangle(j*TAM_BLOQUE,(i-4)*TAM_BLOQUE,(j+1)*TAM_BLOQUE,(i+1-4)*TAM_BLOQUE,5,5,VERDE);
            break;
        case HERO:
            al_draw_filled_rounded_rectangle(j*TAM_BLOQUE,(i-4)*TAM_BLOQUE,(j+1)*TAM_BLOQUE,(i+1-4)*TAM_BLOQUE,5,5,CYAN);
            break;
        case TEEWEE:
            al_draw_filled_rounded_rectangle(j*TAM_BLOQUE,(i-4)*TAM_BLOQUE,(j+1)*TAM_BLOQUE,(i+1-4)*TAM_BLOQUE,5,5,MORADO);
            break;
        case SMASHBOY:   
            al_draw_filled_rounded_rectangle(j*TAM_BLOQUE,(i-4)*TAM_BLOQUE,(j+1)*TAM_BLOQUE,(i+1-4)*TAM_BLOQUE,5,5,AMARILLO);
            break;
    }
}

void print_bordes_juego (void) {
    
    int fil, col;
    
    for (fil=0; fil<ALTO_PANTALLA; fil++) {             // Este bloque va a recorrer todo el display e ir pintando cuadrados en 
        for (col=0; col<ANCHO_PANTALLA; col++) {        // los bordes del espacio donde aparezcan las piezas y el puntaje
            
            if ( col==0 || col== 11 || col== 16 || fil==0 || fil== 17 || ( col>11 && col<16 && fil==5) || ( col>11 && col<16 && fil==10))
            {
                al_draw_filled_rounded_rectangle(TAM_BLOQUE*col,TAM_BLOQUE*fil,TAM_BLOQUE*(col+1),TAM_BLOQUE*(fil+1),5,5,GRIS);
            }
        }
    }
}

void clear_display (void) {
    
    al_clear_to_color(al_map_rgb(0,0,0));  //Seteo todos los pixeles del display en negro
}

void get_input (ALLEGRO_EVENT *event, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_SAMPLE*sound, pieza_t* in_use, pieza_t* hold, pieza_t* to_use, int mat[FIL][COL], char*end, ALLEGRO_FONT* font, game_stats_t* jugador) {
       
    switch (event->keyboard.keycode)
    {
        case ALLEGRO_KEY_DOWN:                  // Si se apreto la tecla "flecha abajo", mueve 
            mover_pieza(in_use,mat,ABA);        // la pieza una posicion hacia abajo
            break;
        case ALLEGRO_KEY_RIGHT:                 // Si se apreto la tecla "flecha derecha", mueve
            mover_pieza(in_use,mat,DER);        // la pieza una posicion hacia la derecha
            break;
        case ALLEGRO_KEY_LEFT:                  // Si se apreto la tecla "flecha izquierda", mueve
            mover_pieza(in_use,mat,IZQ);        // la pieza una posicion hacia la izquierda
            break;
        case ALLEGRO_KEY_UP:                    // Si se apreto la tecla "flecha arriba", mueve
            rotar(in_use, mat);                 // la pieza una posicion hacia arriba
            break;
        case ALLEGRO_KEY_SPACE:                 // Si se apreto la barra espaciadora, baja la pieza hasta el final
            jugador->score+=((jugador->level)*(all_down(in_use, hold, mat))*3);
            break;
        case ALLEGRO_KEY_ESCAPE:                // La tecla "esc" entra al menu de pausa dentro del juego
            menu_pausa(event, event_queue, font, sound, end, in_use, mat, jugador, hold);                 
            break;
        case ALLEGRO_KEY_C:                     // Si se apreto la tecla "c", guarda la pieza acutal para el futuro y aparece una nueva pieza
            funcion_hold(in_use,hold,to_use,jugador);
            break;
            
    }
}  

void itoa (int numero, char s[]) {
    
    int i, j, signo;

    if ((signo = numero) < 0) {
        numero = -numero;          
    }   
    i = 0;
    do {       
        s[i++] = numero % 10 + '0';   
    } while ((numero /= 10) > 0);     
     
    if (signo < 0) {
        s[i++] = '-';
    } 
    s[i] = '\0';
    
    char c;
    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
     }
} 
