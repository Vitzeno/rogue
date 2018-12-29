#include <rogue.h>


int main() {
	Player * player;
	player = setUpPlayer();
	
	setUpScreen();
	createMap();

	/* save positions only after creating map */
	char ** levelState = saveLevelState();
	Position * newPosition;


	int input;
	/* emulates main game loop */
	while((input = getch()) != 'q') {
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	    mvprintw(0, 0, "lines %d columns %d", w.ws_row, w.ws_col);

		newPosition = handleInput(input, player);
		checkPosition(newPosition, player, levelState);
		renderPlayer(player);
	}

	/* ends the ncurses mode */
	endwin();	

	return 0;
}


/*
This function sets up the ncurses window.
*/
int setUpScreen() {
	/* starts the ncurses mode */
	initscr();	
	/* prints string at cursor location */
	printw("Rogue");
	/* turns of echo when typing */
	noecho();	
	refresh();

	return 0;
}
