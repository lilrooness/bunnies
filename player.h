/**
Author: Joseph Frangoudes
Assignemnt: Graphics 3 Rendering
*/

#ifndef PLAYER_H
#define PLAYER_H

typedef int bool;
#define true 1
#define false 0

typedef struct {
	float xpos, ypos, xdir, ydir;
	bool fwd, bck, lft, rt;
	float angle, turnspeed;
}Player;

void update(Player *player, char *map);
bool check_collisions(Player *player, char *map, int width, int stride);

#endif