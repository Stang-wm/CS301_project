#ifndef __DRAW_H
#define __DRAW_H
#include "pattern.h"

void draw_start_page(void);
void init_play_interface(void);

void draw_stage_init(int stage);
void draw_stage_clear(int stage);
void draw_failed(int score);
void draw_cleared(void);

void draw_play_title(int score, int life);
void draw_all_self_buttles(int self_buttles[SELF_BUTTLE_MAX][2]);
void draw_all_enemy_planes(int enemy_planes[ENEMY_PLANE_MAX][2]);
void draw_all_enemy_buttles(int enemy_buttles[ENEMY_BUTTLE_MAX][2]);

void draw_play_all(int score, int life, int self_plane[2],
		int self_buttles[SELF_BUTTLE_MAX][2],
		int enemy_planes[ENEMY_PLANE_MAX][2],
		int enemy_buttles[ENEMY_BUTTLE_MAX][2]);
#endif
