#include    <stdio.h>
#include    <stdlib.h>
#include    "rules.h"
#include    "backend.h"
#include    "menu_allegro.h"
#include    "juego_allegro.h"
#include    <allegro5/allegro.h>
#include    <allegro5/allegro_native_dialog.h>


int main (void) {

    //INICIALIZO ALLEGRO
    if (!al_init()) {
        al_show_native_message_box(NULL,NULL,NULL, "No se pudo inicializar Allegro", NULL, 0);  //En el caso que no se haya podido inicializar muestra mensaje de error
        return -1;
    }
   
    // CREO VARIABLES QUE SE UTILIZARAN DURNTE EL JUEGO
    int matriz[FIL][COL]; //Matriz del juego
    game_stats_t jugador; //Estructura del jugador
    pieza_t in_use; //Piezas
    pieza_t to_use;
    pieza_t hold;
    ALLEGRO_DISPLAY* display; //Puntero que se utilizará para mostrar el display del juego
    ALLEGRO_EVENT_QUEUE *event_queue; //Variable utilizada para leer el teclado
    ALLEGRO_EVENT event;
    ALLEGRO_FONT* font; //Variable para inlcuir el tipo de letra con la que se escribe en el juego
    ALLEGRO_SAMPLE * sound1; //Variables para cada uno de los efectos de sonido
    ALLEGRO_SAMPLE * sound2;
    ALLEGRO_SAMPLE * sound3;
    ALLEGRO_SAMPLE * sound4;
    ALLEGRO_SAMPLE * song; //Variables de música de fondo y musica de introducción
    ALLEGRO_SAMPLE * cjuego;
    ALLEGRO_SAMPLE_INSTANCE* songInstance;
    ALLEGRO_SAMPLE_INSTANCE* songInstance2;
    
    //INICIALIZO LAS VARIABLES Y BIBLIOTECAS
    srand(time(NULL));      //genero una semilla randomizada
    clear_mat(matriz);    
    init_jugador(&jugador);         //llamamo a la función que inicializa las stats del juego
    generador(&in_use, &jugador);       //llamamos a la función que rellena los campos de la pieza
    generador(&to_use, &jugador);
    hold.id=0; //La información de hold empieza vacia para no mostrar una pieza al comenzar la partida
    hold.hold_previo=0;
    
    al_install_keyboard(); //Se instala el teclado para poder leerlo
    al_install_audio(); //Esto permite poder utilizar audio en el juego
    al_init_primitives_addon();
    al_init_font_addon(); //Esto permite utilizar el tipo de letra elegido
    al_init_ttf_addon();
    al_init_image_addon(); //Esto permite utilizar las imagenes
    al_init_acodec_addon();
    
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());  //Se crea el evento que registrará lo que ocurra en el teclado
    display = al_create_display(ANCHO_PANTALLA, ALTO_PANTALLA);   
    al_set_new_display_flags(ALLEGRO_FRAMELESS); //Se crea el display del juego  
    al_set_window_title(display, "Tetris"); //Se imprime el nombre del juego en la pestaña
    al_set_window_position(display, 200, 5); //Se setea la posición
    font = al_load_ttf_font("../allegro_files/nombre.ttf", 36, 0);//Se carga la letra con el archivo y el tamaño de la misma
    sound1=al_load_sample("../allegro_files/efectotecla.wav"); //Se cargan todos los sonidos que se utilizaran
    sound2=al_load_sample("../allegro_files/efectocae.wav");
    sound3=al_load_sample("../allegro_files/efectofila.wav");
    sound4=al_load_sample("../allegro_files/gameover.wav");
    song=al_load_sample("../allegro_files/intro.ogg");//se cargan las canciones de intro y de fondo con sus arespectivos archivos 
    cjuego=al_load_sample("../allegro_files/cjuego.ogg");;
    songInstance2=al_create_sample_instance(cjuego); //Esto permitirá poder reproducir la musica por un intervalo de tiempo indefinido hasta que se le indique
    songInstance=al_create_sample_instance(song);
    al_reserve_samples(5); //se reserva la cantidad de sonidos a utilizar
    
    if(!display) { //Se verifica que se haya inicializado bien el display
        al_show_native_message_box(NULL,NULL,NULL, "No se pudo crear un display", NULL, 0);
        return -1;
    }
    
    int value = al_show_native_message_box(display, "MessageBox", "Inicio del Juego", "Ust está por comenzar a jugar TETRIS. Desea continuar?", NULL, ALLEGRO_MESSAGEBOX_YES_NO);//Mnesaje en la pantalla de si o no antes de comenzar el juego para esperar confirmación del usuario
    if(value!=1){ //En el caso de que se haya precionado 'NO'

	//Se destruyen todas las variables y punteros creados
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
    //En caso de que se haya presionado 'SI' comienza el juego
    al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, ALTO_PANTALLA/2, ALLEGRO_ALIGN_CENTRE, "TETRIS"); //A modo de introduccion se imprime en el centro de la pantalla el nombre del juego
    al_flip_display();
    al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);//Con las próximas funciones se reproduce indefinidamente la musica de introducción
    al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());
    al_play_sample_instance(songInstance);
    al_rest(4.0);//Espera a que el timepo se cumpla
    al_destroy_sample(song); //Se detiene la cancion de fondo
    al_destroy_sample_instance(songInstance); //Se borra la pantalla

    // JUEGO
    unsigned long int time = 0; //Variables del juego
    char end=0;
    
    menu_inicio(&event, event_queue, font, sound1, &end, &in_use, matriz, &jugador); //Funcion que muestra el menu de inicio del juego
    
    while(!end) { //Si aun no se a precionado 'QUIT' entonces sigue el juego

        al_set_sample_instance_playmode(songInstance2, ALLEGRO_PLAYMODE_LOOP);//Comienza a sonar la musica de fondo que perdura en todo momento del juego
        al_attach_sample_instance_to_mixer(songInstance2, al_get_default_mixer());
        al_play_sample_instance(songInstance2);
        print_mat_juego (&in_use, &to_use, &hold, matriz, font, &jugador);//Se imprime la matriz del juego
        if (time==0)
        {
            time = (0.7-(jugador.level-1)*0.069)*CLOCKS_PER_SEC*70;//Setea la velocidad con la que caen las piezas de acuerdo al nivel del jugador
        }

        while (--time) {
            al_get_next_event(event_queue, &event);//Esta funcion permite esperar a que se precione una tecla
            if (event.type == ALLEGRO_EVENT_KEY_DOWN)//Si fue así y se precionó alguna
            {
                break; //Sale del break y sino sigue esperando hasta que se cumple el tiempo de bajar la pieza
            }
        }

        if (time==0)//Si salio del break debido a que se cumplio el tiempo entonces:
        {
            if(mover_pieza(&in_use, matriz, ABA)){ //Se mueve la pieza para abajo
                al_play_sample(sound2, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);//Se hace el sonido de que llegó hasta abajo
                setear_pieza(&in_use, &hold, matriz); //guardamos la pieza en la matriz
                int var = fila_completa(matriz, &jugador, &to_use, &hold); //vemos si se completo una fila para sumar puntos               
		if(var==1){ //Si la funcion devuelve 1 es porque se eliminó al menos 1 fila
                    al_play_sample(sound3, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);//Se prosigue a emitir el sonido cuando se eliminan filas
                }
                in_use = to_use;//Se pasa a la siguiente pieza
                generador(&to_use, &jugador);    // genero la siguiente pieza 
                print_mat_juego (&in_use, &to_use, &hold, matriz, font, &jugador);//Se imprime la nueva matriz
            }
        }
        else 
        {
            get_input(&event, event_queue, sound1, &in_use, &hold, &to_use, matriz, &end, font, &jugador);//Si el tiempo no se cumplio es porque precionó una tecla el usuario y se prosigue a interpretarla
        }
        
        if(game_over(matriz)) //Si perdió
        {
            al_stop_sample_instance(songInstance2);//Se para la musica de fondo
            al_play_sample(sound4, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);//Suena la musica de game over
            top_scores(&jugador);//Se guarda el puntaje
            game_over_allegro(&event, event_queue, font, sound1, &end, &in_use, matriz, &jugador, &hold);//Salta a la ultima funcion
	    
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
