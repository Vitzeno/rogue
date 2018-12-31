#include <rogue.h>

/*
Overview of monster attributes

1 Spider
	Symbol: X
	Levels: 1-3
	Health: 2
	Attack: 1
	Defence: 1
	Speed: 2
	Pathfinding: 0 (random)
	ChanceToSpawn: 100

2 Wizard
	Symbol: W
	Levels: 1-5
	Health: 2
	Attack: 4
	Defence: 2
	Speed: 1
	Pathfinding: 1 (intelligent)
	ChanceToSpawn: 100

3 Dragon
	Symbol: D
	Levels: 4-6
	Health: 10
	Attack: 10
	Defence: 5
	Speed: 2
	Pathfinding: 1 (intelligent)
	ChanceToSpawn: 100
*/

/*

*/
int addMonsters(Level * level) {
    level->monsters = malloc(sizeof(Monsters *) * MAX_NUM_OF_MONSTERS);
    level->numOfMonsters = 0;

    int x;
    for (x = 0; x < level->numOfRooms; x++)
    {
        if ((rand() % 2) == 0)
        {
            level->monsters[level->numOfMonsters] = generateMonster(level->level);
            setStartPosition(level->monsters[level->numOfMonsters], level->rooms[x]);
            level->numOfMonsters++;
        }
    }

    return 0;
}


/*

*/
Monsters * generateMonster(int level) {
	int monsterType;

    switch (level)
    {
        case 1:
        case 2:
        case 3:
            monsterType = (rand() % 2) + 1;
            break;
        case 4:
        case 5:
            monsterType = (rand() % 2) + 2;
            break;
        case 6:
            monsterType = 3;
            break;
    }

    mvprintw(0,0, "Monster %d", monsterType);
    getch();


     switch (monsterType)
    {
        case 1: /* spider */
            return spawnMonster('X', 2, 1, 2, 1, 0);
        case 2: /* wizard */
            return spawnMonster('W', 2, 4, 1, 2, 1);
        case 3: /* dragon */
            return spawnMonster('D', 10, 10, 2, 5, 1);
        default:
            return spawnMonster('O', 2, 2, 1, 1, 1);
    }

}

/*

*/
Monsters * spawnMonster(char symbol, int health, int attack, int speed, int defence, int pathfinding) {
    Monsters * newMonster;
    newMonster = malloc(sizeof(Monsters));

    newMonster->symbol = symbol;
    newMonster->health = health;
    newMonster->attack = attack;
    newMonster->speed = speed;
    newMonster->defence = defence;
    newMonster->pathfinding = pathfinding;
    newMonster->alive = 1;

    sprintf(newMonster->string, "%c", newMonster->symbol);

    return newMonster;
}


/*

*/
int setStartPosition(Monsters * monster, Room * room) {



    monster->position.x = (rand() % (room->width - 2)) + room->position.x + 1;
    monster->position.y = (rand() % (room->height - 2)) + room->position.y + 1;

    mvprintw(1,0, "setStartPosition for Monster %d %d",  monster->position.y,  monster->position.x);
    getch();

    mvprintw(monster->position.y, monster->position.x, monster->string);

    mvprintw(2,0, "Monster drawn %d %d",  monster->position.y,  monster->position.x);
    getch();

	return 0;
}
