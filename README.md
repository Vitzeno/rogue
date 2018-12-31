This is a simple attempt to create a roguelike game. This project serves as a small learning experience for me, as I've mostly been coding in Java and C++ and wanted to keep my C skills relevant. I was also bored over the Christmas holiday and needed something fun and useful to do other than exam revision.

Cautions

-This program uses ncurses for drawing terminal UI, the terminal is reset once the program ends successfully. Currently, if a segmentation fault occurs or the program ends unexpectedly the terminal will not be rest. In the case of this type "reset" or restart terminal. Reset command works for Linux systems and windows 10 WSL.

-If a segmentation fault occurs the makefile will not delete the old build, therefore this should be done manually or by calling "make clean". (This made fixing segfaults take longer than they should have).

-The coordinate system for ncurses starts from the top left-hand corner of the screen. This means +y is downwards. Furthermore ncurses functions such as mvprintw work using a (y, x) system instead of a (x, y) like usual.

-A NUM_OF_ROOMS constant is definied in rogue.h, when usiing the createRooms() function in level.c make sure the same number of rooms are created to avoid segmentation faults. This should be remidied in the future once rooms are randomly generated.

For some parts of this project I have been following an online tutorial, I've made changes where I've seen fit and made sense. Furthermore, since the tutorial series is incomplete I plan to take this project further in my spare time.