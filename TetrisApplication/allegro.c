#include<allegro5/allegro.h>
#include<allegro5/allegro_native_dialog.h>
#include <stdio.h>
#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>


int main() {
    ALLEGRO_DISPLAY *buffer=NULL;
    if(!al_init()){
        printf("No se pudo ejecutar allegro");
        return -1;
    }
    al_set_new_display_flags(ALLEGRO_WINDOWED);
    buffer = al_create_display(720, 480);
    if(!buffer){
        printf("No se pudo crear el bitmap");
        return -1;
    }
    al_clear_to_color(al_map_rgb(0, 0, 0));
    
    int value = al_show_native_message_box(buffer, "MessageBox", "Inicio del Juego", "Ust está por comenzar a jugar TETRIS. Desea continuar?", NULL, ALLEGRO_MESSAGEBOX_YES_NO);
    if(value!=1){
        al_rest(1.0);
        al_destroy_display(buffer);
    }
    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_FONT * font= al_load_ttf_font("nombre.ttf", 36, 0);
    al_draw_text(font, al_map_rgb(255, 255, 255), 720 / 2, 480 / 2, ALLEGRO_ALIGN_CENTRE, "TETRIS");
    al_flip_display();
    al_rest(1.0);
    al_destroy_font(font);
    al_clear_to_color(al_map_rgb(0,0,0));

    al_flip_display();
    ALLEGRO_COLOR electricblue= al_map_rgb(44, 117, 255); //Creo una variable con el color para no tener que poner siempre las coordenadas
    
    //FIGURAS:
    /*
    al_init_primitives_addon();
    al_draw_filled_triangle(50, 50, 80, 50, 55, 90, al_map_rgb(0, 255, 255));
    al_draw_filled_rounded_rectangle(10, 10, 100, 100, 5, 5, electricblue);
    al_draw_filled_rectangle(150, 150, 200, 250, al_map_rgb(255, 0, 255));
    al_draw_line(100, 200, 300, 200, electricblue, 2.0);
    al_draw_pixel(0, 0, electricblue);
    al_flip_display();
    
    al_rest(5.0);
    */
    //INTERACCIÓN 
   
    al_init_primitives_addon();
    al_install_keyboard();
    al_init_image_addon();
    //ALLEGRO_BITMAP* player = al_load_bitmap("foto.jpeg");
    ALLEGRO_EVENT_QUEUE*event_queue=al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    char done= 0;
    int x=100;
    int y=20;
    int moveSpeed=5;
    while(!done){
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue, &events);

        if(events.type=ALLEGRO_EVENT_KEY_DOWN){
            switch(events.keyboard.keycode){
                case ALLEGRO_KEY_DOWN:
                    y+=moveSpeed;
                    break;
                case ALLEGRO_KEY_UP:
                    y-=moveSpeed;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    x+=moveSpeed;
                    break;
                case ALLEGRO_KEY_LEFT:
                    x-=moveSpeed;
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    done = 1;
                    break;
            }
        }
        al_draw_filled_rectangle(x, y-10, x+15, y, al_map_rgb(255, 0, 255));
        al_draw_filled_rectangle(x, y, x+50, y+10, al_map_rgb(255, 0, 255));
        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));
        
    }
    //*
    //* * *
    //IMAGENES
    
    al_destroy_display(buffer);
    al_destroy_event_queue(event_queue);//
    //al_destroy_bitmap(player);
    
    
    return 0;
}
