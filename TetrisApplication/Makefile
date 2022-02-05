ALLEGRO_LIBRARIES =  allegro-5 allegro_font-5 allegro_ttf-5 allegro_primitives-5 allegro_dialog-5 allegro_image-5 allegro_acodec-5 allegro_audio-5
ALLEGRO_FLAGS = $(shell pkg-config --cflags --libs $(ALLEGRO_LIBRARIES))

tetrisR:main_Rpi.o menu_rpi.o raspi.o piezasR.o
	gcc ../rpi_resources/disdrv.o ../rpi_resources/joydrv.o main_Rpi.o menu_rpi.o raspi.o piezasR.o ../rpi_resources/libAudioSDL1.o -I/usr/local/include -L/usr/local/lib -lSDL -o tetrisR 
tetrisA:juego_allegro.o main_allegro.o menu_allegro.o piezasA.o
	gcc juego_allegro.o main_allegro.o menu_allegro.o piezasA.o $(ALLEGRO_FLAGS) -o tetrisA 
main_Rpi.o: main_Rpi.c rules.h ../rpi_resources/disdrv.h ../rpi_resources/joydrv.h ../rpi_resources/libaudio.h piezas.h menu_rpi.h raspi.h
	gcc -c -Wall main_Rpi.c
menu_rpi.o: menu_rpi.c menu_rpi.h ../rpi_resources/disdrv.h ../rpi_resources/joydrv.h rules.h raspi.h 
	gcc -c -Wall menu_rpi.c
raspi.o: raspi.c rules.h piezas.h menu_rpi.h raspi.h ../rpi_resources/disdrv.h ../rpi_resources/joydrv.h
	gcc -c -Wall raspi.c
piezasR.o: piezas.c piezas.h rules.h
	gcc -c -Wall piezas.c -o piezasR.o -D RPI
piezasA.o: piezas.c piezas.h rules.h
	gcc -c -Wall piezas.c -o piezasA.o -D ALLEGRO
juego_allegro.o: juego_allegro.c juego_allegro.h
	gcc -c -Wall juego_allegro.c 
main_allegro.o: main_allegro.c rules.h piezas.h menu_allegro.h juego_allegro.h
	gcc -c -Wall main_allegro.c 
menu_allegro.o: menu_allegro.c menu_allegro.h
	gcc -c -Wall menu_allegro.c
clean:
	rm -f *i.o
	rm -f *o.o
	rm -f *s.o
	rm -f piezas*.o
	
