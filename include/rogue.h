#ifndef ROGUE_H
#define ROGUE_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_OF_ROOMS 3

#define TOP "="
#define SIDE "|"
#define DOOR "+"
#define INTERIOR "."
#define HALLWAY "#"
#define PLAYER "@"

#define MAX_NUM_OF_MONSTERS 3



/* used to get the size of the terminal */
struct winsize terminalAttrib;

typedef struct Position {
	int y;
	int x;
} Position;

typedef struct Player {
	Position position;
	int health;	
} Player;

typedef struct Monsters {
	Position position;
	char symbol;
	char string[2];
	int alive;
	int health;
	int attack;
	int defence;
	int speed;
	int pathfinding;
	int chanceToSpawn;
} Monsters;

typedef struct Level {
	char ** tiles;
	int level;
	int numOfRooms;
	struct Room ** rooms;
	int numOfMonsters;
	struct Monsters ** monsters;
} Level;

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


/* level related functions in level.c */
Level * createLevel(int level);
Room ** createRooms();
char ** saveLevelState();


/* room related functions in room.c */
Room * createRoom(int x, int y, int h, int w);
int renderRoom(Room * room);
int connectRooms(const Position firstDoor,const Position secondDoor);


/* monster related functions in monster.c */
int addMonsters(Level * level);
Monsters * generateMonster(int level);
Monsters * spawnMonster(char symbol, int health, int attack, int speed, int defence, int pathfinding);
int setStartPosition(Monsters * monster, Room * room);

#endif
