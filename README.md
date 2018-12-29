This is a simple attempt to create a rogue like game, with the motivation being just for fun.

Cautions

-This program uses ncurses for drawing terminal UI, the terminal is reset once the program ends successfully. Currently if a segmentaion fault occurs or the program ends unexpectedly the terminal will not be rest. In the case of this type "reset" or restart terminal. Reset command works for linux systems and windows 10 WSL.