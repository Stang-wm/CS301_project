#include "run.h"

void generate_enemy_planes(int level, int enemy_planes[ENEMY_PLANE_MAX][2]) {
	int i = 0;
	int possibility_range = 0;

	// Adjust MAX enemy count
	if (level == 1) {
		possibility_range = 4;
	} else if (level == 2) {
		possibility_range = 5;
	} else if (level == 3) {
		possibility_range = 6;
	}

	for (i = 0; i < ENEMY_PLANE_MAX; i++) {
		if (enemy_planes[i][0] == 0) {
			if (i < level * 3) {
				if (rand() % 100 < possibility_range) {
					enemy_planes[i][0] = rand() % 217 + 11;
					enemy_planes[i][1] = 61;
				}
			}
			break;
		}
	}
}

// Action when user move self plane
void move_selfPlane(int self_plane[2], int self_buttles[SELF_BUTTLE_MAX][2]) {
	int key0Pressed = (HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin)
			== GPIO_PIN_RESET);
	int key1Pressed = (HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin)
			== GPIO_PIN_RESET);
	int keyWKPressed = (HAL_GPIO_ReadPin(KEY_WK_GPIO_Port, KEY_WK_Pin)
			== GPIO_PIN_SET);

	if (key0Pressed || key1Pressed || keyWKPressed) {
		// Clear previous pattern
		LCD_Fill(self_plane[0] - 10, self_plane[1] - 20, self_plane[0] + 10,
				self_plane[1] + 20, BACK_COLOR);

		// KEY_0  -> Fire
		// KEY_1  -> Move right 3px
		// KEY_WK -> Move left  3px
		if (key0Pressed) {
			int i;
			for (i = 0; i < SELF_BUTTLE_MAX; i++) {
				if (self_buttles[i][0] == 0) {
					self_buttles[i][0] = self_plane[0];
					self_buttles[i][1] = self_plane[1] - 22;
					break;
				}
			}
		}
		if (key1Pressed) {
			if (self_plane[0] + 10 < RIGHT_LIMIT) {
				self_plane[0] = self_plane[0] + 3;
			}
		}
		if (keyWKPressed) {
			if (self_plane[0] - 10 > LEFT_LIMIT) {
				self_plane[0] = self_plane[0] - 3;
			}
		}
	}
}

void update_SelfButtles(int self_buttles[SELF_BUTTLE_MAX][2]) {
	int i;
	for (i = 0; i < SELF_BUTTLE_MAX; i++) {
		if (self_buttles[i][0] != 0) {
			LCD_Fill(self_buttles[i][0] - 1, self_buttles[i][1] - 1,
					self_buttles[i][0] + 1, self_buttles[i][1] + 1, BACK_COLOR);

			self_buttles[i][1] = self_buttles[i][1] - 3;

			// Destroy at boundary
			if (self_buttles[i][1] < 42) {
				self_buttles[i][0] = 0;
				self_buttles[i][1] = 0;
			}
		}
	}
	// Array shifting
	// "y" of buttles array growth with "index"
	arrange_self_buttles(self_buttles);
}

void update_enemy_planes(int enemy_planes[ENEMY_PLANE_MAX][2]) {
	int i;

	for (i = 0; i < ENEMY_PLANE_MAX; i++) {
		if (enemy_planes[i][0] != 0) {

			LCD_Fill(enemy_planes[i][0] - 10, enemy_planes[i][1] - 20,
					enemy_planes[i][0] + 10, enemy_planes[i][1] + 20,
					BACK_COLOR);

			enemy_planes[i][1] = enemy_planes[i][1] + 1;

			// Destroy at boundary and append with next element inside array
			if (enemy_planes[i][1] > 298) {
				enemy_planes[i][0] = 0;
				enemy_planes[i][1] = 0;
			}
		}
	}
	// Array shifting
	// "y" of buttles array decrease with "index"
	arrange_enemy_planes(enemy_planes);
}

void check_self_plane_to_enemy_plane_collide(int *score, int *life,
		int self_plane[2], int enemy_planes[ENEMY_PLANE_MAX][2]) {
	int i = 0;
	int temp = 0;

	for (i = 0; i < ENEMY_PLANE_MAX; i++) {
		if (enemy_planes[i][0] != 0) {
			if (abs(enemy_planes[i][0] - self_plane[0]) <= 20) {
				if (abs(enemy_planes[i][1] - self_plane[1]) <= 40) {
					LCD_Fill(self_plane[0] - 10, self_plane[1] - 20,
							self_plane[0] + 10, self_plane[1] + 20, BACK_COLOR);
					LCD_Fill(enemy_planes[i][0] - 10, enemy_planes[i][1] - 20,
							enemy_planes[i][0] + 10, enemy_planes[i][1] + 20,
							BACK_COLOR);

					// Toggle RED LED
					HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
					HAL_Delay(100);
					HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);

					self_plane[0] = 120;
					self_plane[1] = 290;

					enemy_planes[i][0] = 0;
					enemy_planes[i][1] = 0;

					temp = (*score);
					(*score) = temp + 1;

					temp = (*life);
					(*life) = temp - 1;
					break;
				}
			}
		}
	}
	arrange_enemy_planes(enemy_planes);
}

void check_self_buttles_to_enemy_plane_collide(int *score,
		int self_buttles[SELF_BUTTLE_MAX][2],
		int enemy_planes[ENEMY_PLANE_MAX][2]) {
	int i = 0;
	int j = 0;
	int temp = 0;

	for (i = 0; i < ENEMY_PLANE_MAX; i++) {
		if (enemy_planes[i][0] != 0) {
			for (j = 0; j < SELF_BUTTLE_MAX; j++) {
				if (abs(self_buttles[j][0] - enemy_planes[i][0]) <= 12) {
					if (abs(self_buttles[j][1] - enemy_planes[i][1]) <= 22) {
						LCD_Fill(enemy_planes[i][0] - 10,
								enemy_planes[i][1] - 20,
								enemy_planes[i][0] + 10,
								enemy_planes[i][1] + 20, BACK_COLOR);

						self_buttles[j][0] = 0;
						self_buttles[j][1] = 0;

						enemy_planes[i][0] = 0;
						enemy_planes[i][1] = 0;

						// Toggle RED LED
						HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
						HAL_Delay(100);
						HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);

						temp = (*score);
						(*score) = temp + 1;
						break;
					}
				}
			}
			arrange_enemy_planes(enemy_planes);
		}
	}
	arrange_self_buttles(self_buttles);
}

void clear_all_enemy_plane(int my_plane[2], int enemy_plane[10][2]) {
	int i = 0;

	for (i = 0; i < 10; i++) {
		enemy_plane[i][0] = 0;
		enemy_plane[i][1] = 0;
	}
	LCD_Fill(1, 41, 239, 318, BACK_COLOR);

	Element_DrawSelfPlane(my_plane[0], my_plane[1]);
}

void arrange_self_buttles(int self_buttles[SELF_BUTTLE_MAX][2]) {
	int i;
	if (self_buttles[0][0] == 0) {
		for (i = 0; i < SELF_BUTTLE_MAX - 1; i++) {
			self_buttles[i][0] = self_buttles[i + 1][0];
			self_buttles[i][1] = self_buttles[i + 1][1];
		}
	}
}

void arrange_enemy_planes(int enemy_planes[ENEMY_PLANE_MAX][2]) {
	int i;
	if (enemy_planes[0][0] == 0) {
		for (i = 0; i < ENEMY_PLANE_MAX - 1; i++) {
			enemy_planes[i][0] = enemy_planes[i + 1][0];
			enemy_planes[i][1] = enemy_planes[i + 1][1];
		}
	}
}

void arrange_enemy_buttles(int enemy_buttles[ENEMY_BUTTLE_MAX][2]) {
	int i = 0;
	if (enemy_buttles[0][0] == 0) {
		for (i = 0; i < ENEMY_BUTTLE_MAX - 1; i++) {
			enemy_buttles[i][0] = enemy_buttles[i + 1][0];
			enemy_buttles[i][1] = enemy_buttles[i + 1][1];
		}
	}
}

// wait until a KEY0 press was made
void skip_via_KEY0(void) {
	int wait = 1;
	while (wait) {
		if (HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin) == GPIO_PIN_RESET) {
			wait = 0;
			HAL_Delay(100);
		}
	}
}

