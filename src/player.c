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

	int newY;
	int newX;
	
	switch(input) {
		/* move up */
		case 'W':
		case 'w':
			newY = player->position.y - 1;
			newX = player->position.x;
			//updatePlayerPosition(player->position.y - 1, player->position.x, player);
			break;

		/* move left */
		case 'A':
		case 'a':
			newY = player->position.y;
			newX = player->position.x - 1;
			//updatePlayerPosition(player->position.y, player->position.x - 1, player);
			break;

		/* move down */
		case 'S':
		case 's':
			newY = player->position.y + 1;
			newX = player->position.x;
			//updatePlayerPosition(player->position.y + 1, player->position.x, player);
			break;

		/* move right */
		case 'D':
		case 'd':
			newY = player->position.y;
			newX = player->position.x + 1;
			//updatePlayerPosition(player->position.y, player->position.x + 1, player);
			break;

		default:
			break;
	}

	checkPosition(newY, newX, player);

	return 0;
}


/*
This function determines whats in the postion provided at newPositionY and
newPositionY.
@param newPositionY the new y pos to check to
@param newPositionX the new x pos to check to
@param player the player struct
*/
int checkPosition(int newPositionY, int newPositionX, Player * player) {

	/* determines char at new position and what to do */
	switch(mvinch(newPositionY, newPositionX)) {
		case '+':
		case '#':
		case '.':
			updatePlayerPosition(newPositionY, newPositionX, player);
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
int updatePlayerPosition(int newPositionY, int newPositionX, Player * player) {

	mvprintw(player->position.y, player->position.x, INTERIOR);
	player->position.x = newPositionX;
	player->position.y = newPositionY;
	return 0;
}
