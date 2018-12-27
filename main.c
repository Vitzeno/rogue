#include <ncurses.h>
#include <stdlib.h>

#define NUM_OF_ROOMS 6   

typedef struct Player {
	int xPos;
	int yPos;
	int health;	
} Player;

typedef struct Room {
	int xPos;
	int yPos;
	int width;
	int height;
} Room;


int setUpScreen();
Player * setUpPlayer();

Room * createRoom(int x, int y, int h, int w);
Room ** createRooms();
int renderRoom(Room * room);

int renderPlayer(Player * player);

int handleInput(int input, Player * player);
int checkPosition(int newyPos, int newxPos, Player * player);
int updatePlayerPosition(int newyPos, int newxPos, Player * player);






int main() {
	Player * player;
	player = setUpPlayer();
	
	setUpScreen();
	createRooms();

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

/*
This function sets up the player with initial postion and health.
*/
Player * setUpPlayer() {
	Player * newPlayer;
	newPlayer = (Player * )malloc(sizeof(Player));

	newPlayer->xPos = 15;
	newPlayer->yPos = 15;
	newPlayer->health = 3;

	return newPlayer;
}

/*
This function creates a single rooms with the defeined
specificaions.
@param x xpos of room
@param y ypos of room
@param h height of romm
@param w width of room
*/
Room * createRoom(int x, int y, int h, int w) {
	Room * newRoom;
	newRoom = malloc(sizeof(Room));

	newRoom->xPos = x;
	newRoom->yPos = y;
	newRoom->height = h;
	newRoom->width = w;

	return newRoom;
}

/*
This function creates an array of rooms.
*/
Room ** createRooms() {
	Room ** rooms;
	rooms = malloc(sizeof(Room) * NUM_OF_ROOMS);

	rooms[0] = createRoom(13, 13, 6, 8);
	rooms[1] = createRoom(40, 2, 6, 8);
	rooms[2] = createRoom(40, 10, 6, 12);

	renderRoom(rooms[0]);
	renderRoom(rooms[1]);
	renderRoom(rooms[2]);

	return rooms;
}

/*
This fucntion renders a provided room.
@param room room to render
*/
int renderRoom(Room * room) {
	int x;
	int y;

	/* rendering top and bottom of room */
	for(x = room->xPos; x < room->xPos + room->width; x++) {
		/* prints string at designated y,x location (note: y,x coordinate NOT x,y)*/
		mvprintw(room->yPos, x, "-");
		mvprintw(room->yPos + room->height - 1, x, "-");
	}

	/* rendering interior and sides of room */
	for(y = room->yPos + 1; y < room->yPos + room->height - 1; y++) {
		/* prints string at designated y,x location (note: y,x coordinate NOT x,y)*/
		mvprintw(y, room->xPos, "|");
		mvprintw(y, room->xPos + room->width - 1, "|");
		/* render interior of room */
		for(x = room->xPos + 1;x < room->xPos + room->width - 1;x++) {
			/* prints string at designated y,x location (note: y,x coordinate NOT x,y)*/
			mvprintw(y, x, ".");
		}
	}

	return 0;
}

/*
This function renders the player character and moves cursor back.
Should be calld once for every iteration of the game loop.
@param player the player struct
*/
int renderPlayer(Player * player) {
	/* prints string at designated y,x location (note: y,x coordinate NOT x,y)*/
	mvprintw(player->yPos, player->xPos, "@");
	/* mvprint moves cursor after printing, need to move back using move function */
	move(player->yPos, player->xPos);

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
			newY = player->yPos - 1;
			newX = player->xPos;
			//updatePlayerPosition(player->yPos - 1, player->xPos, player);
			break;

		/* move left */
		case 'A':
		case 'a':
			newY = player->yPos;
			newX = player->xPos - 1;
			//updatePlayerPosition(player->yPos, player->xPos - 1, player);
			break;

		/* move down */
		case 'S':
		case 's':
			newY = player->yPos + 1;
			newX = player->xPos;
			//updatePlayerPosition(player->yPos + 1, player->xPos, player);
			break;

		/* move right */
		case 'D':
		case 'd':
			newY = player->yPos;
			newX = player->xPos + 1;
			//updatePlayerPosition(player->yPos, player->xPos + 1, player);
			break;

		default:
			break;
	}

	checkPosition(newY, newX, player);

	return 0;
}

/*
This function determines whats in the postion provided at newyPos and
newyPos.
@param newyPos the new y pos to check to
@param newxPos the new x pos to check to
@param player the player struct
*/
int checkPosition(int newyPos, int newxPos, Player * player) {

	/* determines char at new position and what to do */
	switch(mvinch(newyPos, newxPos)) {
		case '.':
			updatePlayerPosition(newyPos, newxPos, player);
			break;
		default:
			/* mvinch moves cursor to new pos, need to move back */
			move(player->yPos, player->xPos);
			break;
	}


	return 0;
}


/* 
This functions updates the player position values and draws a floor tile at the
last player position.
@param newyPos the new y pos to update to
@param newxPos the new x pos to update to
@param player the player struct to update
 */
int updatePlayerPosition(int newyPos, int newxPos, Player * player) {

	mvprintw(player->yPos, player->xPos, ".");
	player->xPos = newxPos;
	player->yPos = newyPos;
	return 0;
}
