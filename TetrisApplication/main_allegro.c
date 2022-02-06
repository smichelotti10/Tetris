#include    <stdio.h>
#include    <stdlib.h>
#include    "rules.h"
#include    "piezas.h"
#include    "menu_allegro.h"
#include    "juego_allegro.h"
#include    <allegro5/allegro.h>
#include    <allegro5/allegro_native_dialog.h>


int main (void) {

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
    pieza_t hold;
    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_EVENT event;
    ALLEGRO_FONT* font;
    ALLEGRO_SAMPLE * sound1;
    ALLEGRO_SAMPLE * sound2;
    ALLEGRO_SAMPLE * sound3;
    ALLEGRO_SAMPLE * sound4;
    ALLEGRO_SAMPLE * song;
    ALLEGRO_SAMPLE * cjuego;
    ALLEGRO_SAMPLE_INSTANCE* songInstance;
    ALLEGRO_SAMPLE_INSTANCE* songInstance2;
    
    //INICIALIZO LAS VARIABLES Y BIBLIOTECAS
    srand(time(NULL));      //genero una semilla randomizada
    clear_mat(matriz);    
    init_jugador(&jugador);         //llamamo a la función que inicializa las stats del juego
    generador(&in_use, &jugador);       //llamamos a la función que rellena los campos de la pieza
    generador(&to_use, &jugador);
    hold.id=0;
    hold.hold_previo=0;
    
    al_install_keyboard();
    al_install_audio();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_init_acodec_addon();
    
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());  
    display = al_create_display(ANCHO_PANTALLA, ALTO_PANTALLA);   
    al_set_new_display_flags(ALLEGRO_FRAMELESS);   
    al_set_window_title(display, "Tetris");
    al_set_window_position(display, 200, 5);
    font = al_load_ttf_font("../allegro_files/nombre.ttf", 36, 0);
    sound1=al_load_sample("../allegro_files/efectotecla.wav");
    sound2=al_load_sample("../allegro_files/efectocae.wav");
    sound3=al_load_sample("../allegro_files/efectofila.wav");
    sound4=al_load_sample("../allegro_files/gameover.wav");
    song=al_load_sample("../allegro_files/intro.ogg");
    cjuego=al_load_sample("../allegro_files/cjuego.ogg");;
    songInstance2=al_create_sample_instance(cjuego);
    songInstance=al_create_sample_instance(song);
    al_reserve_samples(5);
    
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
        al_destroy_sample(sound1);
        al_destroy_sample(sound2);
        al_destroy_sample(sound3);
        al_destroy_sample(sound4);
        al_destroy_sample(song);
        al_destroy_sample_instance(songInstance);
        al_destroy_sample(cjuego);
        al_destroy_sample_instance(songInstance2);
        
        return 0;
    }
     
    al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, ALTO_PANTALLA/2, ALLEGRO_ALIGN_CENTRE, "TETRIS");
    al_flip_display();
    al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());
    al_play_sample_instance(songInstance);
    al_rest(4.0);
    al_destroy_sample(song);
    al_destroy_sample_instance(songInstance);

    // JUEGO
    unsigned long int time = 0;
    char end=0;
    
    menu_inicio(&event, event_queue, font, sound1, &end, &in_use, matriz, &jugador);
    
    while(!end) {

        al_set_sample_instance_playmode(songInstance2, ALLEGRO_PLAYMODE_LOOP);
        al_attach_sample_instance_to_mixer(songInstance2, al_get_default_mixer());
        al_play_sample_instance(songInstance2);
        print_mat_juego (&in_use, &to_use, &hold, matriz, font, &jugador);
        if (time==0)
        {
            time = (0.7-(jugador.level-1)*0.069)*CLOCKS_PER_SEC*70;
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
                al_play_sample(sound2, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                setear_pieza(&in_use, &hold, matriz); //guardamos la pieza en la matriz
                int var = fila_completa(matriz, &jugador, &to_use, &hold); //vemos si se completo una fila para sumar puntos y eso
                if(var==1){
                    al_play_sample(sound3, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                }
                in_use = to_use;
                generador(&to_use, &jugador);    // genero la siguiente pieza 
                print_mat_juego (&in_use, &to_use, &hold, matriz, font, &jugador);
            }
        }
        else 
        {
            get_input(&event, event_queue, sound1, &in_use, &hold, &to_use, matriz, &end, font, &jugador);
        }
        
        if(game_over(matriz))
        {
            al_stop_sample_instance(songInstance2);
            al_play_sample(sound4, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
            top_scores(&jugador);
            game_over_allegro(&event, event_queue, font, sound1, &end, &in_use, matriz, &jugador, &hold);
	    
        } 
    }

    // ELIMINO MEMORIA RESERVADA DINAMICAMENTE
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);
    al_destroy_sample(sound1);
    al_destroy_sample(sound2);
    al_destroy_sample(sound3);
    al_destroy_sample(sound4);
    al_destroy_sample(cjuego);
    al_destroy_sample_instance(songInstance2);


    return 0;
}
