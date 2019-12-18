/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "run.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
struct Data data;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void init_interface_info(void);
void draw_all_through_struct(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	LCD_Init();
	BACK_COLOR = WHITE;
	POINT_COLOR = BLACK;  // black font colour
	LCD_Clear(WHITE);

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_USART1_UART_Init();
	/* USER CODE BEGIN 2 */
	Welcome:

	LCD_Clear(WHITE);

	// Firstly DOWN two LED lights
	HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);

	draw_start_page();  // Draw welcome stage
	init_interface_info();  // initialize game data

	// Light UP LED0 (red)
	HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);
	skip_via_KEY0();
	HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);
	LCD_Clear(WHITE);

	draw_stage_init(1);
	HAL_Delay(3000);
	LCD_Clear(WHITE);

	init_play_interface();  // Draw main game stage
	draw_all_through_struct();  //惰性渲染相关的东西
	HAL_Delay(1000);

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */

		// Exit loop if all lives lost
		if (data.life == 0)
			break;

		if (data.score == STG3_SCORE) {
			data.pass = 1;
			break;
		}

		// Stage switch
		if ((data.score == STG1_SCORE || data.score == STG2_SCORE)
				&& data.clear == 0) {
			data.level++;

			clear_all_enemy_plane(data.self_plane, data.enemy_planes);

			data.clear = 1;
			data.self_plane[0] = 120;
			data.self_plane[1] = 290;
			if (data.score == STG1_SCORE) {
				draw_stage_clear(1);
				HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
				skip_via_KEY0();
				HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
				draw_stage_init(2);
				HAL_Delay(3000);
				LCD_Clear(WHITE);
				init_play_interface();
				draw_all_through_struct();
				data.speed = 8;
				HAL_Delay(1000);

			}
			if (data.score == STG2_SCORE) {
				draw_stage_clear(2);
				HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
				skip_via_KEY0();
				HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
				draw_stage_init(3);
				HAL_Delay(3000);
				LCD_Clear(WHITE);
				init_play_interface();
				draw_all_through_struct();
				data.speed = 1;
				HAL_Delay(1000);

			}
		}

		if (data.score != STG1_SCORE && data.score != STG2_SCORE
				&& data.clear == 1) {
			data.clear = 0;
		}

		move_selfPlane(data.self_plane, data.self_buttles);
		update_SelfButtles(data.self_buttles);

		update_enemy_planes(data.enemy_planes);
		generate_enemy_planes(data.level, data.enemy_planes);
		check_self_plane_to_enemy_plane_collide(&(data.score), &(data.life),
				data.self_plane, data.enemy_planes);
		check_self_buttles_to_enemy_plane_collide(&(data.score),
				data.self_buttles, data.enemy_planes);

		draw_all_through_struct();

		HAL_Delay(data.speed);
	}

	if (data.pass == 0)
		draw_failed(data.score);
	else if (data.pass == 1)
		draw_cleared();

	HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);
	skip_via_KEY0();
	HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);

	/* USER CODE BEGIN 3 */
	goto Welcome;
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */

void init_interface_info(void) {
	int i;

	data.score = 0;
	data.life = 3;
	data.level = 1;
	data.clear = 0;
	data.pass = 0;
	data.speed = 20;

	data.self_plane[0] = 120;
	data.self_plane[1] = 290;

	for (i = 0; i < SELF_BUTTLE_MAX; i++) {
		data.self_buttles[i][0] = 0;
		data.self_buttles[i][1] = 0;
	}

	for (i = 0; i < ENEMY_PLANE_MAX; i++) {
		data.enemy_planes[i][0] = 0;
		data.enemy_planes[i][1] = 0;
	}

	for (i = 0; i < ENEMY_BUTTLE_MAX; i++) {
		data.enemy_buttles[i][0] = 0;
		data.enemy_buttles[i][1] = 0;
	}
}

void draw_all_through_struct(void) {
	draw_play_all(data.score, data.life, data.self_plane, data.self_buttles,
			data.enemy_planes, data.enemy_buttles);
}

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */

	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
