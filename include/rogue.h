#ifndef ROGUE_H
#define ROGUE_H

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

Room * createRoom(int x, int y, int h, int w);
Room ** createRooms();
int renderRoom(Room * room);
int connectRooms(const Position firstDoor,const Position secondDoor);

Player * setUpPlayer();
int renderPlayer(Player * player);
int handleInput(int input, Player * player);
int checkPosition(int newPositionY, int newPositionX, Player * player);
int updatePlayerPosition(int newPositionY, int newPositionX, Player * player);

#endif
