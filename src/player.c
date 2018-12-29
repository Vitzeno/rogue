#include <rogue.h>


/*
This function sets up the player with initial postion and health.
*/
Player * setUpPlayer() {
	Player * newPlayer;
	newPlayer = (Player * )malloc(sizeof(Player));

	newPlayer->position.x = 15;
	newPlayer->position.y = 15;
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
int handleInput(int input, Player * player) {

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

	checkPosition(newPosition, player);

	return 0;
}


/*
This function determines whats in the postion provided at newPositionY and
newPositionY.
@param newPositionY the new y pos to check to
@param newPositionX the new x pos to check to
@param player the player struct
*/
int checkPosition(Position * newPosition, Player * player) {

	/* determines char at new position and what to do */
	switch(mvinch(newPosition->y, newPosition->x)) {
		case '+':
		case '#':
		case '.':
			updatePlayerPosition(newPosition, player);
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
@param newPositionY the new y pos to update to
@param newPositionX the new x pos to update to
@param player the player struct to update
 */
int updatePlayerPosition(Position * newPosition, Player * player) {

	mvprintw(player->position.y, player->position.x, INTERIOR);
	player->position.x = newPosition->x;
	player->position.y = newPosition->y;
	return 0;
}
