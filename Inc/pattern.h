#ifndef __BASICDRAW_H
#define __BASICDRAW_H
#include "lcd.h"
#include "data.h"

// Notice: (x, y) stores the central point of a given element
// so an interesting fact is that all the width and height are odd numbers
#define BIG_TRIGON_WIDTH 21
#define BIG_TRIGON_HEIGHT 35
#define SMALL_TRIGON_WIDTH 11
#define SMALL_TRIGON_HEIGHT 11

#define CROSS_WIDTH 15
#define CROSS_HEIGHT 15

#define HEART_WIDTH 11
#define HEART_HEIGHT 11

#define STAR_WIDTH 5
#define STAR_HEIGHT 9

void Element_DrawForwardTrigon(int x, int y, int width, int height);
void Element_DrawReverseTrigon(int x, int y, int width, int height);

// Size: 21*41
void Element_DrawSelfPlane(int x, int y);
void Element_DrawEnemyPlane(int x, int y);

void Element_DrawSelfBullet(int x, int y);
void Element_DrawEnemyBullet(int x, int y);

void Element_DrawCross(int x, int y);
void Element_DrawHeart(int x, int y);
void Element_DrawStar(int x, int y);

#endif
