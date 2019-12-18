#ifndef __DATA_H
#define __DATA_H

#define SELF_BUTTLE_MAX 100
#define ENEMY_BUTTLE_MAX 300
#define ENEMY_PLANE_MAX 10

struct Data {
	int score;
	int life;
	int level;
	int clear;  // if a enemy_plane clear action is required
	int pass;  // pass or fail
	int speed;

	int self_plane[2];
	int self_buttles[SELF_BUTTLE_MAX][2];

	int enemy_planes[ENEMY_PLANE_MAX][2];
	int enemy_buttles[ENEMY_BUTTLE_MAX][2];
};

#endif
