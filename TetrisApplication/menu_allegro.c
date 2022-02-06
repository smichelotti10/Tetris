#include    "rules.h"
#include    "piezas.h"
#include    "juego_allegro.h"
#include    "menu_allegro.h"

void menu_inicio (ALLEGRO_EVENT *event, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT* font, ALLEGRO_SAMPLE * sound, char* end, pieza_t* in_use, int matriz [FIL][COL], game_stats_t* jugador) {
    
    unsigned char contador = 0;
    char end_menu=0;
    
    clear_display();
    al_draw_text(font, AMARILLO, ANCHO_PANTALLA/2, TAM_BLOQUE*5, ALLEGRO_ALIGN_CENTRE, "START GAME");
    al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*7, ALLEGRO_ALIGN_CENTRE, "HIGH SCORES");
    al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*9, ALLEGRO_ALIGN_CENTRE, "COMMANDS");
    al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*11, ALLEGRO_ALIGN_CENTRE, "QUIT");
    al_flip_display();
    
    while(!end_menu) {
        al_wait_for_event(event_queue, event);
        if (event->type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (event->keyboard.keycode)
            {
                case ALLEGRO_KEY_DOWN:
                    al_play_sample(sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                    contador++;
                    break;
                case ALLEGRO_KEY_UP:
                    al_play_sample(sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                    contador--;
                    break;
                case ALLEGRO_KEY_ENTER:
                    switch (contador%4)
                    {
                        case 0:             // Inicia el juego
                            end_menu=1;
                            clear_mat(matriz);
                            generador(in_use, jugador);
                            init_jugador(jugador);
                            clear_display();
                            ask_name(jugador, event, event_queue, font);
                            break;
                        case 1:             // Top Scores
                            print_high_scores(font, event, event_queue);
                            break;
                        case 2:
                            commands(font, event, event_queue);
                            break;
                        case 3:
                            end_menu=1;
                            *end=1;         // Termina el juego
                            break;
                    }
                    break;
            }
            if (!end_menu) {
                switch (contador%4)
                {
                    case 0:
                        clear_display();
                        al_draw_text(font, AMARILLO, ANCHO_PANTALLA/2, TAM_BLOQUE*5, ALLEGRO_ALIGN_CENTRE, "START GAME");
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*7, ALLEGRO_ALIGN_CENTRE, "HIGH SCORES");
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*9, ALLEGRO_ALIGN_CENTRE, "COMMANDS");
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*11, ALLEGRO_ALIGN_CENTRE, "QUIT");
                        al_flip_display();
                        break;
                    case 1:
                        clear_display();
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*5, ALLEGRO_ALIGN_CENTRE, "START GAME");
                        al_draw_text(font, AMARILLO, ANCHO_PANTALLA/2, TAM_BLOQUE*7, ALLEGRO_ALIGN_CENTRE, "HIGH SCORES");
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*9, ALLEGRO_ALIGN_CENTRE, "COMMANDS");
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*11, ALLEGRO_ALIGN_CENTRE, "QUIT");
                        al_flip_display();
                        break;
                    case 2:
                        clear_display();
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*5, ALLEGRO_ALIGN_CENTRE, "START GAME");
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*7, ALLEGRO_ALIGN_CENTRE, "HIGH SCORES");
                        al_draw_text(font, AMARILLO, ANCHO_PANTALLA/2, TAM_BLOQUE*9, ALLEGRO_ALIGN_CENTRE, "COMMANDS");
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*11, ALLEGRO_ALIGN_CENTRE, "QUIT");
                        al_flip_display();
                        break;
                    case 3:
                        clear_display();
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*5, ALLEGRO_ALIGN_CENTRE, "START GAME");
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*7, ALLEGRO_ALIGN_CENTRE, "HIGH SCORES");
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*9, ALLEGRO_ALIGN_CENTRE, "COMMANDS");
                        al_draw_text(font, AMARILLO, ANCHO_PANTALLA/2, TAM_BLOQUE*11, ALLEGRO_ALIGN_CENTRE, "QUIT");
                        al_flip_display();
                        break;
                }
            }
        }
    }
}

void menu_pausa (ALLEGRO_EVENT *event, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT* font, ALLEGRO_SAMPLE*sound, char* end, pieza_t* in_use, int matriz [FIL][COL], game_stats_t* jugador) {
   
    unsigned char contador = 0;
    char end_menu=0;
    
    clear_display();
    al_draw_text(font, AMARILLO, ANCHO_PANTALLA/2, TAM_BLOQUE*5, ALLEGRO_ALIGN_CENTRE, "PLAY");
    al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*7, ALLEGRO_ALIGN_CENTRE, "QUIT");
    al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*9, ALLEGRO_ALIGN_CENTRE, "HIGH SCORES");
    al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*11, ALLEGRO_ALIGN_CENTRE, "RESTART GAME");
    al_flip_display();
    
    while(!end_menu) {
        al_wait_for_event(event_queue, event);
        if (event->type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (event->keyboard.keycode)
            {
                case ALLEGRO_KEY_DOWN:
                    al_play_sample(sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                    contador++;
                    break;
                case ALLEGRO_KEY_UP:
                    al_play_sample(sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                    contador--;
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    end_menu=1;
                    break;
                case ALLEGRO_KEY_ENTER:
                    switch (contador%4)
                    {
                        case 0:             // Vuelve al juego
                            end_menu=1;
                            break;
                        case 1:
                            *end=1;         // Termina el juego
                            end_menu=1;
                            break;
                        case 2:             // Top Scores
                            print_high_scores(font, event, event_queue);
                            break;
                        case 3:
                            end_menu=1;
                            clear_mat(matriz);
                            generador(in_use, jugador);
                            init_jugador(jugador);
                            clear_display();
                            ask_name(jugador, event, event_queue, font);
                            break;
                    }
                    break;
            }
            if (!end_menu) {
                switch (contador%4)
                {
                    case 0:
                        clear_display();
                        al_draw_text(font, AMARILLO, ANCHO_PANTALLA/2, TAM_BLOQUE*5, ALLEGRO_ALIGN_CENTRE, "PLAY");
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*7, ALLEGRO_ALIGN_CENTRE, "QUIT");
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*9, ALLEGRO_ALIGN_CENTRE, "HIGH SCORES");
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*11, ALLEGRO_ALIGN_CENTRE, "RESTART GAME");
                        al_flip_display();
                        break;
                    case 1:
                        clear_display();
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*5, ALLEGRO_ALIGN_CENTRE, "PLAY");
                        al_draw_text(font, AMARILLO, ANCHO_PANTALLA/2, TAM_BLOQUE*7, ALLEGRO_ALIGN_CENTRE, "QUIT");
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*9, ALLEGRO_ALIGN_CENTRE, "HIGH SCORES");
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*11, ALLEGRO_ALIGN_CENTRE, "RESTART GAME");
                        al_flip_display();
                        break;
                    case 2:
                        clear_display();
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*5, ALLEGRO_ALIGN_CENTRE, "PLAY");
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*7, ALLEGRO_ALIGN_CENTRE, "QUIT");
                        al_draw_text(font, AMARILLO, ANCHO_PANTALLA/2, TAM_BLOQUE*9, ALLEGRO_ALIGN_CENTRE, "HIGH SCORES");
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*11, ALLEGRO_ALIGN_CENTRE, "RESTART GAME");
                        al_flip_display();
                        break;
                    case 3:
                        clear_display();
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*5, ALLEGRO_ALIGN_CENTRE, "PLAY");
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*7, ALLEGRO_ALIGN_CENTRE, "QUIT");
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*9, ALLEGRO_ALIGN_CENTRE, "HIGH SCORES");
                        al_draw_text(font, AMARILLO, ANCHO_PANTALLA/2, TAM_BLOQUE*11, ALLEGRO_ALIGN_CENTRE, "RESTART GAME");
                        al_flip_display();
                        break;
                }
            }
        }
    }
}

void game_over_allegro (ALLEGRO_EVENT *event, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT* font, ALLEGRO_SAMPLE*sound, char* end, pieza_t* in_use, int matriz [FIL][COL], game_stats_t* jugador) {
    
    unsigned char contador = 0;
    char end_game_over=0;
    char score[6];
    itoa(jugador->score, score);
    
    clear_display();
    al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*4, ALLEGRO_ALIGN_CENTRE, "GAME OVER");
    al_draw_text(font, BLANCO, ANCHO_PANTALLA/2 + TAM_BLOQUE*3, TAM_BLOQUE*6, ALLEGRO_ALIGN_RIGHT, "YOUR SCORE: ");
    al_draw_text(font, BLANCO, ANCHO_PANTALLA/2 + TAM_BLOQUE*4, TAM_BLOQUE*6, ALLEGRO_ALIGN_LEFT, score);
    al_draw_text(font, AMARILLO, ANCHO_PANTALLA/2, TAM_BLOQUE*9, ALLEGRO_ALIGN_CENTRE, "HIGH SCORES");
    al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*11, ALLEGRO_ALIGN_CENTRE, "RESTART GAME");
    al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*13, ALLEGRO_ALIGN_CENTRE, "QUIT");
    al_flip_display();
    
    while(!end_game_over) {
        al_wait_for_event(event_queue, event);
        if (event->type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (event->keyboard.keycode)
            {
                case ALLEGRO_KEY_DOWN: 
                    al_play_sample(sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                    contador++;               
                    break;
                case ALLEGRO_KEY_UP:
                    al_play_sample(sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                    contador--;
                    break;
                case ALLEGRO_KEY_ENTER:
                    switch (contador%3)
                    {
                        case 0:             // TOP SCORES
                            print_high_scores(font, event, event_queue);
                            break;                           
                        case 1:         // Vuelve al juego
                            end_game_over=1;
                            clear_mat(matriz);
                            generador(in_use, jugador);
                            init_jugador(jugador);
                            clear_display();
                            ask_name(jugador, event, event_queue, font);
                            break;
                        case 2:
                            end_game_over=1;
                            *end=1;         // Termina el juego
                            break;                                                   
                    }
                    break;
            }
            if (!end_game_over) {
                switch (contador%3)
                {
                    case 0:
                        clear_display();
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*4, ALLEGRO_ALIGN_CENTRE, "GAME OVER");
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2 + TAM_BLOQUE*3, TAM_BLOQUE*6, ALLEGRO_ALIGN_RIGHT, "YOUR SCORE: ");
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2 + TAM_BLOQUE*4, TAM_BLOQUE*6, ALLEGRO_ALIGN_LEFT, score);
                        al_draw_text(font, AMARILLO, ANCHO_PANTALLA/2, TAM_BLOQUE*9, ALLEGRO_ALIGN_CENTRE, "HIGH SCORES");
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*11, ALLEGRO_ALIGN_CENTRE, "RESTART GAME");
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*13, ALLEGRO_ALIGN_CENTRE, "QUIT");
                        al_flip_display();
                        break;
                    case 1:
                        clear_display();
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*4, ALLEGRO_ALIGN_CENTRE, "GAME OVER");
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2 + TAM_BLOQUE*3, TAM_BLOQUE*6, ALLEGRO_ALIGN_RIGHT, "YOUR SCORE: ");
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2 + TAM_BLOQUE*4, TAM_BLOQUE*6, ALLEGRO_ALIGN_LEFT, score);
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*9, ALLEGRO_ALIGN_CENTRE, "HIGH SCORES");
                        al_draw_text(font, AMARILLO, ANCHO_PANTALLA/2, TAM_BLOQUE*11, ALLEGRO_ALIGN_CENTRE, "RESTART GAME");
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*13, ALLEGRO_ALIGN_CENTRE, "QUIT");
                        al_flip_display();
                        break;
                    case 2:
                        clear_display();
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*4, ALLEGRO_ALIGN_CENTRE, "GAME OVER");
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2 + TAM_BLOQUE*3, TAM_BLOQUE*6, ALLEGRO_ALIGN_RIGHT, "YOUR SCORE: ");
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2 + TAM_BLOQUE*4, TAM_BLOQUE*6, ALLEGRO_ALIGN_LEFT, score);
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*9, ALLEGRO_ALIGN_CENTRE, "HIGH SCORES");
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*11, ALLEGRO_ALIGN_CENTRE, "RESTART GAME");
                        al_draw_text(font, AMARILLO, ANCHO_PANTALLA/2, TAM_BLOQUE*13, ALLEGRO_ALIGN_CENTRE, "QUIT");
                        al_flip_display();
                        break;
                }
            }
        }
    }
}

void ask_name (game_stats_t* jugador, ALLEGRO_EVENT *event, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT* font) {
    
    clear_display();
    al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, ALTO_PANTALLA/4, ALLEGRO_ALIGN_CENTRE, "Please enter your nick...");
    al_flip_display();
    
    char string[4]={' ',' ',' ','\0'};
    unsigned int i=0, end=0;
    
    while ((i<=3) && (!end)) {
        
        al_wait_for_event(event_queue, event);
        if (i<3)
        {
            if (event->type == ALLEGRO_EVENT_KEY_DOWN)
            {
                if ((event->keyboard.keycode)>=ALLEGRO_KEY_A && (event->keyboard.keycode)<=ALLEGRO_KEY_Z) 
                {
                    jugador->nick[i]=(event->keyboard.keycode)+64;
                    string[i]=(event->keyboard.keycode)+64;
                    clear_display();
                    al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, ALTO_PANTALLA/4, ALLEGRO_ALIGN_CENTRE, "Please enter your nick...");
                    al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, ALTO_PANTALLA/2, ALLEGRO_ALIGN_CENTRE, string);
                    i++;
                }
                else if((event->keyboard.keycode)==ALLEGRO_KEY_BACKSPACE)
                {
                    if (i>0)
                    {
                        i--;
                    }
                    string[i]=' ';
                    clear_display();
                    al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, ALTO_PANTALLA/4, ALLEGRO_ALIGN_CENTRE, "Please enter your nick...");
                    al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, ALTO_PANTALLA/2, ALLEGRO_ALIGN_CENTRE, string);     
                }
                al_flip_display();
            }
        }
        
        else 
        {
            clear_display();
            al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, ALTO_PANTALLA/4, ALLEGRO_ALIGN_CENTRE, "Please enter your nick...");
            al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, ALTO_PANTALLA/2, ALLEGRO_ALIGN_CENTRE, string);
            al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, ALTO_PANTALLA*3/4, ALLEGRO_ALIGN_CENTRE, "PRESS ENTER TO CONTINUE");
            al_flip_display();
            
            if (event->type == ALLEGRO_EVENT_KEY_DOWN)
            {
                switch (event->keyboard.keycode) {
                    case ALLEGRO_KEY_ENTER:
                        end=1;
                        break;
                    case ALLEGRO_KEY_BACKSPACE:
                        i--;
                        string[i]=' ';
                        clear_display();
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, ALTO_PANTALLA/4, ALLEGRO_ALIGN_CENTRE, "Please enter your nick...");
                        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, ALTO_PANTALLA/2, ALLEGRO_ALIGN_CENTRE, string);
                        al_flip_display();
                        break;
                }                
            }
            
        }
    }
}

void print_high_scores (ALLEGRO_FONT* font, ALLEGRO_EVENT *event, ALLEGRO_EVENT_QUEUE *event_queue) {
    
    FILE* pfile1;
    jugador_top_t jugadores_top[11];
    int i, j;
    char c, string[4], score[6];
    
    clear_display();
    pfile1 = fopen("top_scores.txt", "r");
    if (pfile1 == NULL) //Verificamos si no existía el archivo, en ese caso este puntaje sería el maximo pq es el primero
    {
        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, ALTO_PANTALLA/4, ALLEGRO_ALIGN_CENTRE, "There are no scores");
        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, ALTO_PANTALLA/4+TAM_BLOQUE, ALLEGRO_ALIGN_CENTRE, "registered in this computer");
        al_flip_display();
    }
    else
    {
        while(!feof(pfile1)) //Hasta que no llegue al EOF seguimos leyendo
        {
            for ( i = 0; i < 10; i++) //lenamos los datos de los jugadores del 0 al 9
            {
                c = fgetc(pfile1); //Hasta que no llegue al EOF seguimos leyendo EL PRIMERO ES EL ULTIMO \n
                c = fgetc(pfile1); //Asi que leo el segundo tambien
                if ( c == EOF )
                {
                    break;
                }
                else
                {
                    fseek(pfile1, -2,SEEK_CUR);
                    fscanf (pfile1, "%ld", &(jugadores_top[i].score)); //Leo los datos y los acomodo en los array
                    fscanf (pfile1, "%s", jugadores_top[i].name);
                    jugadores_top[i].posicion_top=i;
                }
                for (j=0; j<3; j++) {
                    string[j]=(jugadores_top[i].name)[j];
                }
                string[3]='\0';
                itoa(jugadores_top[i].score, score);
                al_draw_text(font, BLANCO, TAM_BLOQUE*4, TAM_BLOQUE*(i+4), ALLEGRO_ALIGN_LEFT, score);
                al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*(i+4), ALLEGRO_ALIGN_LEFT, string);
            }            
        }
        fclose(pfile1);
        al_flip_display();
    } 
    
    int end=0;
    
    while (!end) {
        al_wait_for_event(event_queue, event);
        if (event->type == ALLEGRO_EVENT_KEY_DOWN)
        {
            end=1;
        }
    }       
}

void commands (ALLEGRO_FONT* font, ALLEGRO_EVENT *event, ALLEGRO_EVENT_QUEUE *event_queue) {
    
    ALLEGRO_BITMAP* imagen;
    
    clear_display();   
    
    al_draw_text(font, BLANCO, ANCHO_PANTALLA/4, TAM_BLOQUE*1.5, ALLEGRO_ALIGN_CENTER, "rotate");
    imagen = al_load_bitmap("../allegro_files/flecha_arriba.PNG");
    al_draw_bitmap(imagen, ANCHO_PANTALLA*0.75, TAM_BLOQUE,0);
    
    al_draw_text(font, BLANCO, ANCHO_PANTALLA/4, TAM_BLOQUE*4.5, ALLEGRO_ALIGN_CENTER, "move right");
    imagen = al_load_bitmap("../allegro_files/flecha_der.PNG");
    al_draw_bitmap(imagen, ANCHO_PANTALLA*0.75, TAM_BLOQUE*4,0);
    
    al_draw_text(font, BLANCO, ANCHO_PANTALLA/4, TAM_BLOQUE*7.5, ALLEGRO_ALIGN_CENTER, "move left");
    imagen = al_load_bitmap("../allegro_files/flecha_izq.PNG");
    al_draw_bitmap(imagen, ANCHO_PANTALLA*0.75, TAM_BLOQUE*7,0);
    
    al_draw_text(font, BLANCO, ANCHO_PANTALLA/4, TAM_BLOQUE*10.5, ALLEGRO_ALIGN_CENTER, "soft drop");
    imagen = al_load_bitmap("../allegro_files/flecha_abajo.PNG");
    al_draw_bitmap(imagen, ANCHO_PANTALLA*0.75, TAM_BLOQUE*10,0);
    
    al_draw_text(font, BLANCO, ANCHO_PANTALLA/4, TAM_BLOQUE*13.5, ALLEGRO_ALIGN_CENTER, "hard drop");
    imagen = al_load_bitmap("../allegro_files/space_bar.PNG");
    al_draw_bitmap(imagen, ANCHO_PANTALLA*0.75, TAM_BLOQUE*13,0);
    
    al_draw_text(font, BLANCO, ANCHO_PANTALLA/4, TAM_BLOQUE*16.5, ALLEGRO_ALIGN_CENTER, "menu");
    imagen = al_load_bitmap("../allegro_files/esc_key.PNG");
    al_draw_bitmap(imagen, ANCHO_PANTALLA*0.75, TAM_BLOQUE*16,0);

    al_flip_display();
    
    int end=0;
    
    while (!end) {
        al_wait_for_event(event_queue, event);
        if (event->type == ALLEGRO_EVENT_KEY_DOWN)
        {
            end=1;
        }
    } 
    
    al_destroy_bitmap(imagen);
}
