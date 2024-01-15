cc=gcc
prog:zpixel.o image.o main.o arbrezpixel.o stack2_x86_64.o
	$(cc) zpixel.o image.o main.o arbrezpixel.o stack2_x86_64.o -o prog -lm -lglib-2.0
zpixel.o:zpixel.c zpixel.h image.h stack2.h
	$(cc) -c zpixel.c
image.o:image.c image.h zpixel.h stack2.h
	$(cc) -c image.c
main.o:main.c zpixel.h image.h arbrezpixel.h
	$(cc) -c main.c -I/usr/include/glib-2.0 -I/usr/include/glib-2.0/glib -I/lib/x86_64-linux-gnu/glib-2.0/include/
arbrezpixel.o:arbrezpixel.c arbrezpixel.h
	$(cc) -c arbrezpixel.c -I/usr/include/glib-2.0 -I/usr/include/glib-2.0/glib -I/lib/x86_64-linux-gnu/glib-2.0/include/
clear:
	rm -f zpixel.o image.o main.o arbrezpixel.o prog
