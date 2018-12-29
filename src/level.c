#include <rogue.h>


/*
This function creates an array of rooms.
*/
Room ** createMap() {
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
This function iterates though y and x and save the character at that
position into a char array which it then returns.
*/
char ** saveLevelState() {
	int x, y;
	char ** positions;
	positions = malloc(sizeof(char *) * 25);

	for(y = 0;y < 25;y++) {
		positions[y] = malloc(sizeof(char) * 100);
		for(x = 0;x < 100;x++) {
			positions[y][x] = mvinch(y, x);
		}
	}

	return positions;
}