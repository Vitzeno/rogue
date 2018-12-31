#include <rogue.h>

/*
This functions exists to create the level
@param level this is the current level numbr to create
*/
Level * createLevel(int level) {
	Level * newLevel;
	newLevel = malloc(sizeof(Level));

	newLevel->level = level;
	newLevel->numOfRooms = NUM_OF_ROOMS;
	newLevel->rooms = createRooms();
	newLevel->tiles = saveLevelState();

	addMonsters(newLevel);

	return newLevel;
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
This function iterates though y and x and save the character at that
position into a char array which it then returns.
*/
char ** saveLevelState() {
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminalAttrib);
	int t_sizeY = terminalAttrib.ws_row;
	int t_sizeX = terminalAttrib.ws_col;

	int x, y;
	char ** positions;
	positions = malloc(sizeof(char *) * t_sizeY);

	

	for(y = 0;y < t_sizeY;y++) {
		positions[y] = malloc(sizeof(char) * t_sizeX);
		for(x = 0;x < t_sizeX;x++) {
			positions[y][x] = mvinch(y, x);
		}
	}

	return positions;
}