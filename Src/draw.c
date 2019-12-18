#include "draw.h"

// Initialize welcome stage
void draw_start_page(void) {
	Element_DrawSelfPlane(80, 80);
	Element_DrawSelfPlane(120, 80);
	Element_DrawSelfPlane(160, 80);

	LCD_ShowString(75, 140, 190, 24, 24, "Aircraft");
	LCD_ShowString(85, 180, 190, 24, 24, "Battle");

	LCD_ShowString(65, 255, 200, 12, 12, "Press KEY0 to start");
}

// Basic gaming scene
void init_play_interface(void) {
	LCD_DrawRectangle(1, 1, 238, 40);

	LCD_DrawLine(130, 1, 130, 40);

	LCD_ShowString(5, 8, 90, 24, 24, "Score");
	LCD_ShowString(135, 8, 90, 24, 24, "Life");
}

// Init three stages
void draw_stage_init(int stage) {
	LCD_Clear(WHITE);

	uint8_t stgX[8];
	snprintf(stgX, 8, "Stage %d", stage);
	uint8_t *p_stgX = stgX;

	LCD_ShowString(75, 120, 190, 24, 24, p_stgX);

	Element_DrawStar(200, 300);
	Element_DrawStar(20, 130);
	Element_DrawStar(50, 230);
	Element_DrawStar(80, 30);
	LCD_ShowString(70, 260, 200, 12, 12, "Now loading...");

}

//Clear three stages
void draw_stage_clear(int stage) {
	LCD_Clear(WHITE);

	uint8_t stgX[8];
	snprintf(stgX, 8, "Stage %d", stage);
	uint8_t *p_stgX = stgX;

	LCD_ShowString(75, 100, 190, 24, 24, p_stgX);
	LCD_ShowString(85, 140, 190, 24, 24, "Clear");

	Element_DrawStar(200, 300);
	Element_DrawStar(20, 130);
	Element_DrawStar(50, 230);
	Element_DrawStar(80, 30);

	LCD_ShowString(55, 260, 200, 12, 12, "Press KEY0 to continue");
}

// Final stage
void draw_failed(int score) {
	LCD_Clear(WHITE);

	LCD_ShowString(65, 40, 200, 24, 24, "GAME OVER");
	LCD_ShowString(87, 95, 200, 24, 24, "Score");
	LCD_ShowxNum(100, 120, score, 4, 24, 0);

	Element_DrawSelfPlane(80, 220);
	Element_DrawSelfPlane(120, 220);
	Element_DrawSelfPlane(160, 220);

	Element_DrawStar(200, 300);
	Element_DrawStar(20, 130);
	Element_DrawStar(50, 230);
	Element_DrawStar(80, 30);

	LCD_ShowString(55, 260, 200, 12, 12, "Press KEY0 to continue");
}

// Final stage: cleared
void draw_cleared(void) {
	LCD_Clear(WHITE);

	LCD_ShowString(55, 80, 200, 24, 24, "All Cleared!");

	Element_DrawSelfPlane(80, 220);
	Element_DrawSelfPlane(120, 220);
	Element_DrawSelfPlane(160, 220);

	Element_DrawStar(200, 300);
	Element_DrawStar(20, 130);
	Element_DrawStar(50, 230);
	Element_DrawStar(150, 120);
	Element_DrawStar(80, 30);

	LCD_ShowString(55, 260, 200, 12, 12, "Press KEY0 to continue");
}

void draw_play_title(int score, int life) {
	int i;
	int start_x = 195;

	// Display score
	LCD_ShowxNum(75, 8, score, 4, 24, 0);
	LCD_Fill(190, 15, 226, 25, BACK_COLOR);

	// Draw remain life
	for (i = 0; i < life; i++) {
		Element_DrawHeart(start_x + i * 13, 20);
	}
}

void draw_all_self_buttles(int self_buttles[SELF_BUTTLE_MAX][2]) {
	int i;
	for (i = 0; i < SELF_BUTTLE_MAX; i++) {
		if (self_buttles[i][0] == 0) {
			break;
		} else {
			Element_DrawSelfBullet(self_buttles[i][0], self_buttles[i][1]);
		}
	}
}

void draw_all_enemy_planes(int enemy_planes[ENEMY_PLANE_MAX][2]) {
	int i;
	for (i = 0; i < ENEMY_PLANE_MAX; i++) {
		if (enemy_planes[i][0] == 0) {
			break;
		} else {
			Element_DrawEnemyPlane(enemy_planes[i][0], enemy_planes[i][1]);
		}
	}
}

void draw_all_enemy_buttles(int enemy_buttles[ENEMY_BUTTLE_MAX][2]) {
	int i = 0;
	for (i = 0; i < ENEMY_BUTTLE_MAX; i++) {
		if (enemy_buttles[i][0] == 0) {
			break;
		} else {
			Element_DrawEnemyBullet(enemy_buttles[i][0], enemy_buttles[i][1]);
		}
	}
}

void draw_play_all(int score, int life, int self_plane[2],
		int self_buttles[SELF_BUTTLE_MAX][2],
		int enemy_planes[ENEMY_PLANE_MAX][2],
		int enemy_buttles[ENEMY_BUTTLE_MAX][2]) {
	draw_play_title(score, life);

	Element_DrawSelfPlane(self_plane[0], self_plane[1]);
	draw_all_self_buttles(self_buttles);

	draw_all_enemy_planes(enemy_planes);
	draw_all_enemy_buttles(enemy_buttles);

}

