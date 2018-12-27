#include <ncurses.h>
#include <stdlib.h>

typedef struct Player
{
	int xPos;
	int yPos;
	int health;	
} Player;


int setUpScreen();
Player * setUpPlayer();

int renderMap();
int renderPlayer(Player * player);

int handleInput(int input, Player * player);
int updatePlayerPosition(int newyPos, int newxPos, Player * player);


int main() {
	Player * player;
	player = setUpPlayer();
	int input;

	setUpScreen();
	renderMap();
	
	
	/* emulates main game loop */
	while((input = getch()) != 'q') {
		handleInput(input, player);
		renderPlayer(player);
	}

	/* ends the ncurses mode */
	endwin();	

	return 0;
}


int setUpScreen() {
	/* starts the ncurses mode */
	initscr();	
	/* prints string at cursor location */
	printw("ncurses: Hello World");
	/* turns of echo when typing */
	noecho();	
	refresh();

	return 0;
}


Player * setUpPlayer() {
	Player * newPlayer;
	newPlayer = (Player * )malloc(sizeof(Player));

	newPlayer->xPos = 15;
	newPlayer->yPos = 15;
	newPlayer->health = 3;

	return newPlayer;
}


int renderMap() {
	/* prints string at designated y,x location (note: y,x coordinate NOT x,y)*/
	mvprintw(13, 13, "--------");
	mvprintw(14, 13, "|......|");
	mvprintw(15, 13, "|......|");
	mvprintw(16, 13, "|......|");
	mvprintw(17, 13, "|......|");
	mvprintw(18, 13, "--------");

	return 0;
}


int renderPlayer(Player * player) {
	/* prints string at designated y,x location (note: y,x coordinate NOT x,y)*/
	mvprintw(player->yPos, player->xPos, "@");
	/* mvprint moves cursor after printing, need to move back using move function */
	move(player->yPos, player->xPos);

	return 0;
}


int handleInput(int input, Player * player) {

	switch(input) {
		/* move up */
		case 'W':
		case 'w':
			updatePlayerPosition(player->yPos - 1, player->xPos, player);
			break;

		/* move left */
		case 'A':
		case 'a':
			updatePlayerPosition(player->yPos, player->xPos - 1, player);
			break;

		/* move down */
		case 'S':
		case 's':
			updatePlayerPosition(player->yPos + 1, player->xPos, player);
			break;

		/* move right */
		case 'D':
		case 'd':
			updatePlayerPosition(player->yPos, player->xPos + 1, player);
			break;

		default:
			break;
	}

	return 0;
}

/* This functions updates the player position values and draws a floor tile at the
   last player position.
 */
int updatePlayerPosition(int newyPos, int newxPos, Player * player) {

	mvprintw(player->yPos, player->xPos, ".");
	player->xPos = newxPos;
	player->yPos = newyPos;
	return 0;
}
