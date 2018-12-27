#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define NUM_OF_ROOMS 6   

#define TOP "="
#define SIDE "|"
#define DOOR "+"
#define INTERIOR "."
#define HALLWAY "#"
#define PLAYER "@"

typedef struct Position {
	int x;
	int y;
} Position;

typedef struct Player {
	Position position;
	int health;	
} Player;

typedef struct Room {
	Position position;
	int width;
	int height;

	Position doors[4];
} Room;


int setUpScreen();
Player * setUpPlayer();

Room * createRoom(int x, int y, int h, int w);
Room ** createRooms();
int renderRoom(Room * room);
int connectRooms(const Position firstDoor,const Position secondDoor);

int renderPlayer(Player * player);

int handleInput(int input, Player * player);
int checkPosition(int newPositionY, int newPositionX, Player * player);
int updatePlayerPosition(int newPositionY, int newPositionX, Player * player);


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

	newPlayer->position.x = 15;
	newPlayer->position.y = 15;
	newPlayer->health = 3;

	return newPlayer;
}

/*
This function creates a single rooms with the defeined
specificaions. It is also responsible for generating
doors. Door indexes are counted counter clockwise
	===0===
	|	   |
	1	   3	
	|      |
	===2===

@param x position.x of room
@param y position.y of room
@param h height of romm
@param w width of room
*/
Room * createRoom(int x, int y, int h, int w) {
	Room * newRoom;
	newRoom = malloc(sizeof(Room));

	newRoom->position.x = x;
	newRoom->position.y = y;
	newRoom->height = h;
	newRoom->width = w;

	srand(time(NULL));

	/* top door */
	newRoom->doors[0].y = newRoom->position.y;
	newRoom->doors[0].x = rand() % (w - 2) + newRoom->position.x + 1; //(w - 2) reduce range by 2 to ensure no corner doors

	/* left door */
	newRoom->doors[1].y = rand() % (h - 2) + newRoom->position.y + 1;
	newRoom->doors[1].x = newRoom->position.x;

	/* bottom door */
	newRoom->doors[2].y = newRoom->position.y + h - 1;
	newRoom->doors[2].x = rand() % (w - 2) + newRoom->position.x + 1;

	/* right door */
	newRoom->doors[3].y = rand() % (h - 2) + newRoom->position.y + 1;
	newRoom->doors[3].x = newRoom->position.x + w - 1;

	return newRoom;
}

/*
This function creates an array of rooms.
*/
Room ** createRooms() {
	Room ** rooms;
	rooms = malloc(sizeof(Room) * NUM_OF_ROOMS);

	rooms[0] = createRoom(13, 10, 6, 8);
	rooms[1] = createRoom(40, 2, 6, 8);
	rooms[2] = createRoom(40, 20, 6, 12);

	renderRoom(rooms[0]);
	renderRoom(rooms[1]);
	renderRoom(rooms[2]);

	connectRooms(rooms[0]->doors[3], rooms[2]->doors[1]);
	connectRooms(rooms[0]->doors[0], rooms[1]->doors[1]);
	connectRooms(rooms[1]->doors[2], rooms[2]->doors[0]);

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
	for(x = room->position.x; x < room->position.x + room->width; x++) {
		/* prints string at designated y,x location (note: y,x coordinate NOT x,y)*/
		mvprintw(room->position.y, x, TOP);
		mvprintw(room->position.y + room->height - 1, x, TOP);
	}

	/* rendering interior and sides of room */
	for(y = room->position.y + 1; y < room->position.y + room->height - 1; y++) {
		/* prints string at designated y,x location (note: y,x coordinate NOT x,y)*/
		mvprintw(y, room->position.x, SIDE);
		mvprintw(y, room->position.x + room->width - 1, SIDE);
		/* render interior of room */
		for(x = room->position.x + 1;x < room->position.x + room->width - 1;x++) {
			/* prints string at designated y,x location (note: y,x coordinate NOT x,y)*/
			mvprintw(y, x, INTERIOR);
		}
	}

	/* renders doorss */
	mvprintw(room->doors[0].y, room->doors[0].x, DOOR);
	mvprintw(room->doors[1].y, room->doors[1].x, DOOR);
	mvprintw(room->doors[2].y, room->doors[2].x, DOOR);
	mvprintw(room->doors[3].y, room->doors[3].x, DOOR);

	return 0;
}

/*
This function takes two door position from different rooms and connects
them. Current method is very simplistic and naive, considering updatating to
a BFS search style algorithm.
(keep parameters const so that they are not overwritten)
@param firstDoor first door to connect 
@param secondDoor second door to connect
*/
int connectRooms(const Position firstDoor, const Position secondDoor) {
	Position temp;
	Position prev;

	int count = 0;

	temp.x = firstDoor.x;
	temp.y = firstDoor.y;

	prev = temp;

	while(1) {
		/* left */
		if((abs((temp.x - 1) - secondDoor.x) < abs(temp.x - secondDoor.x)) && (mvinch(temp.y, temp.x - 1) == ' ')) {
			prev.x = temp.x;
			temp.x = temp.x - 1;
		 }
		 /* right */
		 else if((abs((temp.x + 1) - secondDoor.x) < abs(temp.x - secondDoor.x)) && (mvinch(temp.y, temp.x + 1) == ' ')) {
			prev.x = temp.x;
			temp.x = temp.x + 1;
		 }
		 /* down */
		 else if((abs((temp.y + 1) - secondDoor.y) < abs(temp.y - secondDoor.y)) && (mvinch(temp.y + 1, temp.x) == ' ')) {
			prev.y = temp.y;
			temp.y = temp.y + 1;
		 }
		 /* up */
		 else if((abs((temp.y - 1) - secondDoor.y) < abs(temp.y - secondDoor.y)) && (mvinch(temp.y - 1, temp.x) == ' ')) {
			prev.y = temp.y;
			temp.y = temp.y - 1;
		 }
		 else {
		 	if(count == 0) {
		 		temp = prev;
		 		count++;
		 		continue;
		 	}
		 	else
		 		return 1;
		 }

		 /* prints string at designated y,x location (note: y,x coordinate NOT x,y)*/
		 mvprintw(temp.y, temp.x, HALLWAY);
		 //getch();
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
