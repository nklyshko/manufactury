CFLAGS  = -O4 -Wall -pedantic

manufactury.exe:
	gcc $(CFLAGS) -I$(CURSES) -omanufactory.exe main.c $(CURSES)/wincon/pdcurses.a
    
tuidemo.exe:
	gcc $(CFLAGS) -I$(CURSES) -otuidemo.exe tui.c tuidemo.c $(CURSES)/wincon/pdcurses.a