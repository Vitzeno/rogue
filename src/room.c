#include <rogue.h>


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

