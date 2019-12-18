#ifndef __RUN_H
#define __RUN_H
#include "draw.h"

#define LEFT_LIMIT 2
#define RIGHT_LIMIT 238
#define UP_LIMIT 42
#define DOWN_LIMIT 318

#define STG1_SCORE 10
#define STG2_SCORE 30
#define STG3_SCORE 50

void generate_enemy_planes(int level, int enemy_planes[ENEMY_PLANE_MAX][2]);

void move_selfPlane(int self_plane[2], int self_buttles[SELF_BUTTLE_MAX][2]);

void update_SelfButtles(int self_buttles[SELF_BUTTLE_MAX][2]);
void update_enemy_planes(int enemy_planes[ENEMY_PLANE_MAX][2]);

void check_self_plane_to_enemy_plane_collide(int *score, int *life,
		int self_plane[2], int enemy_planes[ENEMY_PLANE_MAX][2]);
void check_self_buttles_to_enemy_plane_collide(int *score,
		int self_buttles[SELF_BUTTLE_MAX][2],
		int enemy_planes[ENEMY_PLANE_MAX][2]);

// For stage switching
void clear_all_enemy_plane(int self_plane[2],
		int enemy_plane[ENEMY_PLANE_MAX][2]);

// These three function are used to shift array's zero position
// in order to speed up read speed
void arrange_self_buttles(int self_buttles[SELF_BUTTLE_MAX][2]);
void arrange_enemy_planes(int enemy_planes[ENEMY_PLANE_MAX][2]);
void arrange_enemy_buttles(int enemy_buttles[ENEMY_BUTTLE_MAX][2]);

void skip_via_KEY0(void);

#endif
