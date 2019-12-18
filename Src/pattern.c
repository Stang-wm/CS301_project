#include <pattern.h>

// Isosceles triangle with given central position, width and height
void Element_DrawForwardTrigon(int x, int y, int width, int height) {
	int x1, y1, x2, y2, x3, y3;
	x1 = x - width / 2;
	y1 = y;
	x2 = x;
	y2 = y - height;
	x3 = x + width / 2;
	y3 = y;

	LCD_DrawLine(x1, y1, x2, y2);
	LCD_DrawLine(x1, y1, x3, y3);
	LCD_DrawLine(x2, y2, x3, y3);
}

void Element_DrawReverseTrigon(int x, int y, int width, int height) {
	int x1, y1, x2, y2, x3, y3;
	x1 = x - width / 2;
	y1 = y;
	x2 = x;
	y2 = y + height;
	x3 = x + width / 2;
	y3 = y;

	LCD_DrawLine(x1, y1, x2, y2);
	LCD_DrawLine(x1, y1, x3, y3);
	LCD_DrawLine(x2, y2, x3, y3);
}

void Element_DrawSelfPlane(int x, int y) {
	Element_DrawForwardTrigon(x, y + 15, BIG_TRIGON_WIDTH, BIG_TRIGON_HEIGHT);
	Element_DrawForwardTrigon(x, y + 20, SMALL_TRIGON_WIDTH,
	SMALL_TRIGON_HEIGHT);
}

void Element_DrawEnemyPlane(int x, int y) {
	Element_DrawReverseTrigon(x, y - 15, BIG_TRIGON_WIDTH, BIG_TRIGON_HEIGHT);
	Element_DrawReverseTrigon(x, y - 20, SMALL_TRIGON_WIDTH,
	SMALL_TRIGON_HEIGHT);
}

void Element_DrawSelfBullet(int x, int y) {
	LCD_DrawPoint(x, y - 1);

	LCD_DrawPoint(x - 1, y);
	LCD_DrawPoint(x, y);
	LCD_DrawPoint(x + 1, y);

	LCD_DrawPoint(x - 1, y + 1);
	LCD_DrawPoint(x, y + 1);
	LCD_DrawPoint(x + 1, y + 1);
}

void Element_DrawEnemyBullet(int x, int y) {
	LCD_DrawPoint(x - 1, y - 1);
	LCD_DrawPoint(x, y - 1);
	LCD_DrawPoint(x + 1, y - 1);

	LCD_DrawPoint(x - 1, y);
	LCD_DrawPoint(x, y);
	LCD_DrawPoint(x + 1, y);

	LCD_DrawPoint(x, y + 1);
}

void Element_DrawCross(int x, int y) {
	LCD_DrawLine(x - CROSS_WIDTH / 2, y - CROSS_HEIGHT / 2, x + CROSS_WIDTH / 2,
			y + CROSS_HEIGHT / 2);
	LCD_DrawLine(x - CROSS_WIDTH / 2, y + CROSS_HEIGHT / 2, x + CROSS_WIDTH / 2,
			y - CROSS_HEIGHT / 2);
}

// Life, not a "heart" symbol as you may imagined(
void Element_DrawHeart(int x, int y) {
	LCD_DrawLine(x - HEART_WIDTH / 2, y - HEART_HEIGHT / 2, x + HEART_WIDTH / 2,
			y + HEART_HEIGHT / 2);
	LCD_DrawLine(x - HEART_WIDTH / 2, y + HEART_HEIGHT / 2, x + HEART_WIDTH / 2,
			y - HEART_HEIGHT / 2);
	LCD_DrawLine(x - HEART_WIDTH / 2, y, x + HEART_WIDTH / 2, y);
	LCD_DrawLine(x, y + HEART_HEIGHT / 2, x, y - HEART_HEIGHT / 2);
}

void Element_DrawStar(int x, int y) {
	// Vertical is a little longer than horizontal
	LCD_DrawLine(x, y - STAR_HEIGHT / 2, x, y + STAR_HEIGHT / 2);
	LCD_DrawLine(x - STAR_WIDTH / 2, y, x + STAR_WIDTH / 2, y);
}
