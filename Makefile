CFLAGS  = -O4 -Wall -pedantic

manufactory.exe:
	gcc $(CFLAGS) -I$(CURSES) -omanufactory.exe main.c $(CURSES)/wincon/pdcurses.a