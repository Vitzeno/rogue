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


/**/
int setUpScreen();


/* player related functions in player.c */
Player * setUpPlayer();
int renderPlayer(Player * player);
Position * handleInput(int input, Player * player);
int checkPosition(Position * newPosition, Player * player, char ** levelState);
int updatePlayerPosition(Position * newPosition, Player * player, char ** levelState);


/* room related functions in room.c */
Room * createRoom(int x, int y, int h, int w);
int renderRoom(Room * room);
int connectRooms(const Position firstDoor,const Position secondDoor);


/* level related functions in level.c */
Room ** createMap();
char ** saveLevelState();

#endif
