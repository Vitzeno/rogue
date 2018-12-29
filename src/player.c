#include <rogue.h>


/*
This function sets up the player with initial postion and health.
*/
Player * setUpPlayer() {
	Player * newPlayer;
	newPlayer = (Player * )malloc(sizeof(Player));

	newPlayer->position.x = 16;
	newPlayer->position.y = 14;
	newPlayer->health = 3;

	return newPlayer;
}


/*
This function renders the player character and moves cursor back.
Should be calld once for every iteration of the game loop.
@param player the player struct
*/
int renderPlayer(Player * player) {
	/* prints string at designated y,x location (note: y,x coordinate NOT x,y)*/
	mvprintw(player->position.y, player->position.x, PLAYER);
	/* mvprint moves cursor after printing, need to move back using move function */
	move(player->position.y, player->position.x);

	return 0;
}


/*
This function determines user input and handles each case.
@param input the provided char intput in int form
@param player the player struct
*/
Position * handleInput(int input, Player * player) {

	Position * newPosition;
	newPosition = malloc(sizeof(Position));
	
	switch(input) {
		/* move up */
		case 'W':
		case 'w':
			newPosition->y = player->position.y - 1;
			newPosition->x = player->position.x;
			break;

		/* move left */
		case 'A':
		case 'a':
			newPosition->y = player->position.y;
			newPosition->x = player->position.x - 1;
			break;

		/* move down */
		case 'S':
		case 's':
			newPosition->y = player->position.y + 1;
			newPosition->x = player->position.x;
			break;

		/* move right */
		case 'D':
		case 'd':
			newPosition->y = player->position.y;
			newPosition->x = player->position.x + 1;
			break;

		default:
			break;
	}

	//checkPosition(newPosition, player);

	return newPosition;
}


/*
This function determines whats in the postion provided by the position
struct. Furthermore this function calls the updatePlayerPosition
functions if positions is valid.
@param newPosition the new position struct to check 
@param player the player struct
@param levelState char array contatining level state
*/
int checkPosition(Position * newPosition, Player * player, char ** levelState) {

	/* determines char at new position and what to do */
	switch(mvinch(newPosition->y, newPosition->x)) {
		case '+':
		case '#':
		case '.':
			updatePlayerPosition(newPosition, player, levelState);
			break;
		default:
			/* mvinch moves cursor to new pos, need to move back */
			move(player->position.y, player->position.x);
			break;
	}

	return 0;
}


/* 
This functions updates the player position values and draws a floor tile at the
last player position.
@param newPosition the new position struct to check 
@param player the player struct to update
@param levelState char array contatining level state
 */
int updatePlayerPosition(Position * newPosition, Player * player, char ** levelState) {

	char buffer[8];
	sprintf(buffer, "%c", levelState[player->position.y][player->position.x]);

	mvprintw(player->position.y, player->position.x, buffer);
	player->position.x = newPosition->x;
	player->position.y = newPosition->y;
	return 0;
}
