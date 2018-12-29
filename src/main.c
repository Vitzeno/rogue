#include <rogue.h>


int main() {
	Player * player;
	player = setUpPlayer();
	
	setUpScreen();
	createMap();

	/* save positions only after creating map */
	char ** level = saveLevelState();

	int input;
	/* emulates main game loop */
	while((input = getch()) != 'q') {
		handleInput(input, player);
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
