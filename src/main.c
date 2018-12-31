#include <rogue.h>


int main() {
	setUpScreen();

	Player * player;
	player = setUpPlayer();

	Position * newPosition;

	Level * level;
	level = createLevel(1);

	int input;
	/* emulates main game loop */
	while((input = getch()) != 'q') {
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminalAttrib);
	    mvprintw(0, 0, "Rogue (lines: %d columns: %d)", terminalAttrib.ws_row, terminalAttrib.ws_col);

		newPosition = handleInput(input, player);
		checkPosition(newPosition, player, level->tiles);
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
	/* turns of echo when typing */
	noecho();	
	refresh();

	return 0;
}
