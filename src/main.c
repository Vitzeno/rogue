#include <rogue.h>


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