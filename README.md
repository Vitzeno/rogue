This is a simple attempt to create a rogue like game, with the motivation being just for fun.

Cautions

-This program uses ncurses for drawing terminal UI, the terminal is reset once the program ends successfully. Currently if a segmentaion fault occurs or the program ends unexpectedly the terminal will not be rest. In the case of this type "reset" or restart terminal. Reset command works for linux systems and windows 10 WSL.

-If a segmentation fault occurs the makefile will not delete the old build, therefore this should be done manually or by calling "make clean". (This made fixing seg faults take longer than they should have).

-Coordinate system for ncurses starts from the top left hand corner of ths screen. This means +y is downwards. Furthermore ncurses functions such as mvprintw work using a (y, x) system instead of a (x, y) like usual.