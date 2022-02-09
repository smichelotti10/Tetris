#include    "rules.h"
#include    "backend.h"
#include    "juego_allegro.h"
#include    "menu_allegro.h"

void menu_inicio (ALLEGRO_EVENT *event, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT* font, ALLEGRO_SAMPLE * sound, char* end, pieza_t* in_use, int matriz [FIL][COL], game_stats_t* jugador) {//Esta funcion imprime el menu de opciones que se muestran al comienzo del juego.
    
    unsigned char contador = 0;//Contador para poder leer en qué opcion del menu se situa el usuario
    char end_menu=0; //Variable booleana para saber cuando salir
    
    clear_display();//SE IMPRIMEN LAS OPCIONES DEL MENU CENTRADAS
    al_draw_text(font, AMARILLO, ANCHO_PANTALLA/2, TAM_BLOQUE*5, ALLEGRO_ALIGN_CENTRE, "START GAME");
    al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*7, ALLEGRO_ALIGN_CENTRE, "HIGH SCORES");
    al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*9, ALLEGRO_ALIGN_CENTRE, "COMMANDS");
    al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*11, ALLEGRO_ALIGN_CENTRE, "QUIT");
    al_flip_display();//Se muestran en pantalla
    
    while(!end_menu) {//Si no se debe salir del menu
        al_wait_for_event(event_queue, event);//Se espera a que se precione una tecla 
        if (event->type == ALLEGRO_EVENT_KEY_DOWN)//Si se precionó
        {
            switch (event->keyboard.keycode)//Se lee cual fue la tecla precionada
            {
                case ALLEGRO_KEY_DOWN://Si se preciono la flecha hacia abajo
                    al_play_sample(sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);//Suena efecto de sonido 'golpe'
                    contador++;//Se aumenta el contador para saber que esta en la primera opción
                    break;
                case ALLEGRO_KEY_UP://Si se preciono la flecha hacia arriba
                    al_play_sample(sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);//Suena efecto de sonido 'golpe'
                    contador--;//Se decrementa el contador para saber que volvió a una opción anterior
                    break;
                case ALLEGRO_KEY_ENTER://Si se presionó enter
                    switch (contador%4)//Se calcula en qué opcion está parado
                    {
                        case 0:             // Inicia el juego
                            end_menu=1; //Se sale del menu
                            clear_mat(matriz);//Se inicia la matriz en 0
                            generador(in_use, jugador);//Se genera jugador y pieza
                            init_jugador(jugador);//Se inizializan las variables que componen al jugador como el nivel
                            clear_display();//Se borra el menu
                            ask_name(jugador, event, event_queue, font);//Se para a la funcion que permite ingresar y guardar en memoria el nombre del jugador
                            break;
                        case 1:             // Top Scores
                            print_high_scores(font, event, event_queue);//Se muestra el archivo con los resultados y el nombre dle jugador
                            break;
                        case 2:		//SE MUESTRAN COMANDOS DE JUEGO
                            commands(font, event, event_queue);
                            break;
                        case 3:		//SE SALE DEL JUEGO
                            end_menu=1;	//salimos dle menu
                            *end=1;         // Termina el juego
                            break;
                    }
                    break;
            }
            if (!end_menu) {//Mientras no se haya salido del menu
                switch (contador%4) //Ve en qué posicion está el usuario y se colorea dicha funcion en amarillo mientras que el resto de opciones aparece en blanco
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

void menu_pausa (ALLEGRO_EVENT *event, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT* font, ALLEGRO_SAMPLE*sound, char* end, pieza_t* in_use, int matriz [FIL][COL], game_stats_t* jugador, pieza_t*hold) { //Este menu se muestra cuando se preciona pausa mientras se está juando con la tecla 'ESC' o 'M'
   
    unsigned char contador = 0; //contador para porder saber en qué opción está parado el usuario
    char end_menu=0; //Variable booleana para saber cuando salir
    
    clear_display();//SE IMPRIMEN OPCIONES DEL MENU
    al_draw_text(font, AMARILLO, ANCHO_PANTALLA/2, TAM_BLOQUE*5, ALLEGRO_ALIGN_CENTRE, "PLAY");
    al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*7, ALLEGRO_ALIGN_CENTRE, "QUIT");
    al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*9, ALLEGRO_ALIGN_CENTRE, "HIGH SCORES");
    al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*11, ALLEGRO_ALIGN_CENTRE, "RESTART GAME");
    al_flip_display();
    
    while(!end_menu) {//Si no hay que salir del menu
        al_wait_for_event(event_queue, event);//Es espera a que se precione una tecla
        if (event->type == ALLEGRO_EVENT_KEY_DOWN)//Si se presionó
        {
            switch (event->keyboard.keycode)//Se lee que técla precionó
            {
                case ALLEGRO_KEY_DOWN://FLECHA PARA ABAJO
                    al_play_sample(sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);//Suena efecto de sonido 'golpe'
                    contador++;//Se incrementa el contador para saber que se paso a otra opción
                    break;
                case ALLEGRO_KEY_UP://FLECHA PARA ARRIBA
                    al_play_sample(sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);//Suena efecto de sonido
                    contador--;//Se decrementa el contador para saber que se pasó a una opción anterior
                    break;
                case ALLEGRO_KEY_ESCAPE://ESCAPE
                    end_menu=1;//Se sale del menu
                    break;
                case ALLEGRO_KEY_ENTER://ENTER
                    switch (contador%4)//Se verifica en qué opción está parado el usuario
                    {
                        case 0:             // Vuelve al juego
                            end_menu=1;	//sale del menu
                            break;
                        case 1:
                            *end=1;         // Termina el juego
                            end_menu=1;
                            break;
                        case 2:             // Top Scores
                            print_high_scores(font, event, event_queue);//Se imprime el archivo con los puntajes y los nombres
                            break;
                        case 3:	//REINICIO EL JUEGO
                            end_menu=1;//Se sale del menu
                            hold->id=0;//Se reinician todas las variables
                            hold->hold_previo=0;
                            clear_mat(matriz);//Se inizializa en 0 la matriz
                            generador(in_use, jugador);//Se genera una nueva pieza y un nuevo jugador
                            init_jugador(jugador);
                            clear_display();
                            ask_name(jugador, event, event_queue, font);//Se pregunta el nombre del jugador
                            break;
                    }
                    break;
            }
            if (!end_menu) {
                switch (contador%4)//EN ESTE SWITCH SE COLOREA DE AMARILLO LA OPCION PRESIONADA
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

void game_over_allegro (ALLEGRO_EVENT *event, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT* font, ALLEGRO_SAMPLE*sound, char* end, pieza_t* in_use, int matriz [FIL][COL], game_stats_t* jugador, pieza_t* hold) { //Menu que se muestra cuando el jugador perdió
    
    unsigned char contador = 0;//Contador para saber posición del menu
    char end_game_over=0;//bool para saber cuando salir
    char score[6];//Arreglo para imprimir el score
    itoa(jugador->score, score);//Funcion que permite trasformar el score guardado en la info del jugador como int a un char para poder imprimirlo en pantalla
    
    clear_display();//SE MUESTRAN LAS OPCIONES DEL MENU
    al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*4, ALLEGRO_ALIGN_CENTRE, "GAME OVER");
    al_draw_text(font, BLANCO, ANCHO_PANTALLA/2 + TAM_BLOQUE*3, TAM_BLOQUE*6, ALLEGRO_ALIGN_RIGHT, "YOUR SCORE: ");
    al_draw_text(font, BLANCO, ANCHO_PANTALLA/2 + TAM_BLOQUE*4, TAM_BLOQUE*6, ALLEGRO_ALIGN_LEFT, score);
    al_draw_text(font, AMARILLO, ANCHO_PANTALLA/2, TAM_BLOQUE*9, ALLEGRO_ALIGN_CENTRE, "HIGH SCORES");
    al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*11, ALLEGRO_ALIGN_CENTRE, "RESTART GAME");
    al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*13, ALLEGRO_ALIGN_CENTRE, "QUIT");
    al_flip_display();
    
    while(!end_game_over) {
        al_wait_for_event(event_queue, event);//Se espera a que se precione una tecla
        if (event->type == ALLEGRO_EVENT_KEY_DOWN)//Si se precionó
        {
            switch (event->keyboard.keycode)//Se analiza que tecla precionó
            {
                case ALLEGRO_KEY_DOWN: //FLECHA ABAJO
                    al_play_sample(sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);//Suena efecto 'golpe'
                    contador++;               
                    break;
                case ALLEGRO_KEY_UP://FLECHA ARRIBA
                    al_play_sample(sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);//Suena efecto 'golpe'
                    contador--;
                    break;
                case ALLEGRO_KEY_ENTER://ENTER
                    switch (contador%3)//se analiza en qué posición se quedó
                    {
                        case 0:             // TOP SCORES
                            print_high_scores(font, event, event_queue);//Se imprime el archivo con los puntajes y el numbre de los jugadores
                            break;                           
                        case 1:         // Vuelve al juego
                            end_game_over=1; //Se sale del game over para reiniciar
                            hold->id=0;//Se inizializan las variables de hold
                            hold->hold_previo=0;
                            clear_mat(matriz);//Se inicializa la matriz en 0
                            generador(in_use, jugador);//Se genera y a continuacion se inicializan los valores de jugador
                            init_jugador(jugador);
                            clear_display();
                            ask_name(jugador, event, event_queue, font);//Se pregunta y se guarda el nombre del jugador
                            break;
                        case 2:
                            end_game_over=1;//Se sale de la función game_over
                            *end=1;         // Termina el juego
                            break;                                                   
                    }
                    break;
            }
            if (!end_game_over) {//Si todavía no se salió del menu
                switch (contador%3)//Se analiza la posición en la que está parado el usuario
                {
                    case 0://Se colorea en amarillo la opción en la que se coloca el usuario
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

void ask_name (game_stats_t* jugador, ALLEGRO_EVENT *event, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT* font) {//Funcion que al comienzo permite preguntar el nombre del usuario y guardarlo. Esto es muy importante a la hora de mostar los high scores
    
    clear_display();
    al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, ALTO_PANTALLA/4, ALLEGRO_ALIGN_CENTRE, "Please enter your nick...");//Se escribe en la pantalla que se ingrese el apodo de 3 letras
    al_flip_display();
    
    char string[4]={' ',' ',' ','\0'};//Arreglo donde se guardarán las letras del nick
    unsigned int i=0, end=0;
    
    while ((i<=3) && (!end)) {//Mientras no se hayan colocado 3 letras
        
        al_wait_for_event(event_queue, event);//Se espera a que se precione una tecla
        if (i<3)
        {
            if (event->type == ALLEGRO_EVENT_KEY_DOWN)//Si se precionó una tecla
            {
                if ((event->keyboard.keycode)>=ALLEGRO_KEY_A && (event->keyboard.keycode)<=ALLEGRO_KEY_Z) //Se valida que sea una letra del abecedario
                {
                    jugador->nick[i]=(event->keyboard.keycode)+64; //Se guardan las letras dentro del campo nick de la estructura jugador
                    string[i]=(event->keyboard.keycode)+64;//Se guarda la letra también dentro del arreglo creado para tal fin
                    clear_display();
                    al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, ALTO_PANTALLA/4, ALLEGRO_ALIGN_CENTRE, "Please enter your nick...");//Se vuelve a mostrar el mensaje 
                    al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, ALTO_PANTALLA/2, ALLEGRO_ALIGN_CENTRE, string);//Sumando a las letras agregadas
                    i++; //Se incrementa el contador
                }
                else if((event->keyboard.keycode)==ALLEGRO_KEY_BACKSPACE)
                {//Se verifica en el caso de que haya presionado borrar y se hacen los mismos pasos anteriores
                    if (i>0)
                    {
                        i--;//se resta el contador para poder borrar la letra colocada anteriormente
                    }
                    string[i]=' ';//Se guarda el espacio
                    clear_display();//Se muestra en pantalla el cambio
                    al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, ALTO_PANTALLA/4, ALLEGRO_ALIGN_CENTRE, "Please enter your nick...");
                    al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, ALTO_PANTALLA/2, ALLEGRO_ALIGN_CENTRE, string);     
                }
                al_flip_display();
            }
        }
        
        else 
        {
            clear_display();//Si ya se completó el nick se prosigue a mostrar en pantalla el nick y que se presione enter para seguir
            al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, ALTO_PANTALLA/4, ALLEGRO_ALIGN_CENTRE, "Please enter your nick...");
            al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, ALTO_PANTALLA/2, ALLEGRO_ALIGN_CENTRE, string);
            al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, ALTO_PANTALLA*3/4, ALLEGRO_ALIGN_CENTRE, "PRESS ENTER TO CONTINUE");
            al_flip_display();
            
            if (event->type == ALLEGRO_EVENT_KEY_DOWN)//Se espera a que se precione la tecla
            {
                switch (event->keyboard.keycode) {
                    case ALLEGRO_KEY_ENTER://Si es enter se continua con el juego
                        end=1;
                        break;
                    case ALLEGRO_KEY_BACKSPACE://Si es la tecla borrar se borra la ultima letra colocada
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

void print_high_scores (ALLEGRO_FONT* font, ALLEGRO_EVENT *event, ALLEGRO_EVENT_QUEUE *event_queue) {//Funcion que muestra en pantalla los high scores
    
    FILE* pfile1;//SE INICIALIZAN LAS VARIABLES DE FILE
    jugador_top_t jugadores_top[11];//El arreglo con los valores
    int i, j;
    char c, string[4], score[6];
    
    clear_display();
    pfile1 = fopen("top_scores.txt", "r");//Se abre el archivo en modo lectura
    if (pfile1 == NULL) //Verificamos si no existía el archivo, en ese caso este puntaje sería el maximo pq es el primero
    {
        al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, ALTO_PANTALLA/4, ALLEGRO_ALIGN_CENTRE, "There are no scores");//Se imprime un mensaje de que no hay valores para mostrar
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
                    fscanf (pfile1, "%s", jugadores_top[i].name);//Leo los nombres y los acomodo en los arreglos
                    jugadores_top[i].posicion_top=i;
                }
                for (j=0; j<3; j++) {
                    string[j]=(jugadores_top[i].name)[j];
                }
                string[3]='\0';
                itoa(jugadores_top[i].score, score);//Uso esta funcion para poder pasar los numeros a char e imprimirlos a continuación
                al_draw_text(font, BLANCO, TAM_BLOQUE*4, TAM_BLOQUE*(i+4), ALLEGRO_ALIGN_LEFT, score);//Imprime el puntaje
                al_draw_text(font, BLANCO, ANCHO_PANTALLA/2, TAM_BLOQUE*(i+4), ALLEGRO_ALIGN_LEFT, string);//Imrpime el nombre
            }            
        }
        fclose(pfile1);//Se cierra el archivo
        al_flip_display();
    } 
    
    int end=0;
    
    while (!end) {
        al_wait_for_event(event_queue, event);
        if (event->type == ALLEGRO_EVENT_KEY_DOWN)//Se espera a que se precione una tecla para salir de la función
        {
            end=1;
        }
    }       
}

void commands (ALLEGRO_FONT* font, ALLEGRO_EVENT *event, ALLEGRO_EVENT_QUEUE *event_queue) {//ESTA FUNCION SOLO IMPRIME LOS NOMBRES DE LOS MOVIMIENTOS Y LAS TECLAS Y SE MUESTRA UNA IMAGEN A MODO ILUSTRATIVO DE LA TECLA 
    
    ALLEGRO_BITMAP* imagen;//Se crea el bitmap para poder mostrar todo
    
    clear_display();   
    
    al_draw_text(font, BLANCO, ANCHO_PANTALLA/4, TAM_BLOQUE*1, ALLEGRO_ALIGN_CENTER, "rotate");
    imagen = al_load_bitmap("../allegro_files/flecha_arriba.PNG");
    al_draw_bitmap(imagen, ANCHO_PANTALLA*0.6, TAM_BLOQUE*0.5,0);

    al_draw_text(font, BLANCO, ANCHO_PANTALLA/4, TAM_BLOQUE*3.5, ALLEGRO_ALIGN_CENTER, "move right");
    imagen = al_load_bitmap("../allegro_files/flecha_der.PNG");
    al_draw_bitmap(imagen, ANCHO_PANTALLA*0.6, TAM_BLOQUE*3,0);

    al_draw_text(font, BLANCO, ANCHO_PANTALLA/4, TAM_BLOQUE*6, ALLEGRO_ALIGN_CENTER, "move left");
    imagen = al_load_bitmap("../allegro_files/flecha_izq.PNG");
    al_draw_bitmap(imagen, ANCHO_PANTALLA*0.6, TAM_BLOQUE*5.5,0);

    al_draw_text(font, BLANCO, ANCHO_PANTALLA/4, TAM_BLOQUE*8.5, ALLEGRO_ALIGN_CENTER, "soft drop");
    imagen = al_load_bitmap("../allegro_files/flecha_abajo.PNG");
    al_draw_bitmap(imagen, ANCHO_PANTALLA*0.6, TAM_BLOQUE*8,0);

    al_draw_text(font, BLANCO, ANCHO_PANTALLA/4, TAM_BLOQUE*11, ALLEGRO_ALIGN_CENTER, "hard drop");
    imagen = al_load_bitmap("../allegro_files/space_bar.PNG");
    al_draw_bitmap(imagen, ANCHO_PANTALLA*0.6, TAM_BLOQUE*11,0);

    al_draw_text(font, BLANCO, ANCHO_PANTALLA/4, TAM_BLOQUE*13.75, ALLEGRO_ALIGN_CENTER, "menu");
    imagen = al_load_bitmap("../allegro_files/esc_key.PNG");
    al_draw_bitmap(imagen, ANCHO_PANTALLA*0.6, TAM_BLOQUE*13.75,0);

    al_draw_text(font, BLANCO, ANCHO_PANTALLA/4, TAM_BLOQUE*16, ALLEGRO_ALIGN_CENTER, "hold piece");
    imagen = al_load_bitmap("../allegro_files/hold_key.png");
    al_draw_bitmap(imagen, ANCHO_PANTALLA*0.6, TAM_BLOQUE*16,0);

    al_flip_display();
    
    int end=0;
    
    while (!end) {
        al_wait_for_event(event_queue, event);//Se espera a que se precione una tecla para salir
        if (event->type == ALLEGRO_EVENT_KEY_DOWN)
        {
            end=1;
        }
    } 
    
    al_destroy_bitmap(imagen);
}
