ALLEGRO_LIBRARIES =  allegro-5 allegro_font-5 allegro_ttf-5 allegro_primitives-5 allegro_dialog-5 allegro_image-5 allegro_acodec-5 allegro_audio-5
ALLEGRO_FLAGS = $(shell pkg-config --cflags --libs $(ALLEGRO_LIBRARIES))

tetrisR:main_Rpi.o menu_Rpi.o juego_Rpi.o backendR.o
	gcc ../rpi_resources/disdrv.o ../rpi_resources/joydrv.o main_Rpi.o menu_Rpi.o juego_Rpi.o backendR.o ../rpi_resources/libAudioSDL1.o -I/usr/local/include -L/usr/local/lib -lSDL -o tetrisR 
tetrisA:juego_allegro.o main_allegro.o menu_allegro.o backendA.o
	gcc juego_allegro.o main_allegro.o menu_allegro.o backendA.o $(ALLEGRO_FLAGS) -o tetrisA 
main_Rpi.o: main_Rpi.c rules.h ../rpi_resources/disdrv.h ../rpi_resources/joydrv.h ../rpi_resources/libaudio.h backend.h menu_Rpi.h juego_Rpi.h
	gcc -c -Wall main_Rpi.c
menu_Rpi.o: menu_Rpi.c menu_Rpi.h ../rpi_resources/disdrv.h ../rpi_resources/joydrv.h rules.h juego_Rpi.h 
	gcc -c -Wall menu_Rpi.c
juego_Rpi.o: juego_Rpi.c rules.h backend.h menu_Rpi.h juego_Rpi.h ../rpi_resources/disdrv.h ../rpi_resources/joydrv.h
	gcc -c -Wall juego_Rpi.c
backendR.o: backend.c backend.h rules.h
	gcc -c -Wall backend.c -o backendR.o -D RPI
backendA.o: backend.c backend.h rules.h
	gcc -c -Wall backend.c -o backendA.o -D ALLEGRO
juego_allegro.o: juego_allegro.c juego_allegro.h menu_allegro.h rules.h backend.h
	gcc -c -Wall juego_allegro.c 
main_allegro.o: main_allegro.c rules.h backend.h menu_allegro.h juego_allegro.h
	gcc -c -Wall main_allegro.c 
menu_allegro.o: menu_allegro.c menu_allegro.h rules.h juego_allegro.h
	gcc -c -Wall menu_allegro.c
clean:
	rm -f *.o
	
