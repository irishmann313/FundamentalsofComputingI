all:    pong

pong:   pong.o gfx3.o
        gcc pong.o gfx3.o -lm -lX11 -o pong
pong.o: pong.c
        gcc -c pong.c
gfx3.o: gfx3.c
        gcc -c gfx3.c
clean:
        rm *.o pong
