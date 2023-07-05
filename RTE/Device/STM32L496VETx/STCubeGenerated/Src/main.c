/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"
#include "key.h"
#include "snake.h"

#include "perf_counter.h"
#include "arm_2d.h"
#include "arm_2d_disp_adapters.h"
#include "arm_2d_scenes.h"

#include "rtthread.h"

#include "layer_management.h"
#include "event_management.h"
#include "snake_v2.h"

#define THREAD_PRIORITY         25
#define THREAD_STACK_SIZE       512
#define THREAD_TIMESLICE        5

static volatile int64_t s_lTimeStamp;

__OVERRIDE_WEAK
void arm_2d_helper_perf_counter_start(void)
{
    s_lTimeStamp = get_system_ticks();
}

__OVERRIDE_WEAK
int32_t arm_2d_helper_perf_counter_stop(void)
{
    return (int32_t)(get_system_ticks() - s_lTimeStamp);
}
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

extern 
int32_t Disp0_DrawBitmap(int16_t x, 
                        int16_t y, 
                        int16_t width, 
                        int16_t height, 
                        const uint8_t *bitmap);

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
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
	//SystemCoreClock = 80000000ul;
	init_cycle_counter(true);
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
	LCD_Init();
	Key_Init();
  /* USER CODE BEGIN 2 */
	arm_irq_safe {
			arm_2d_init();
	}
  /* USER CODE END 2 */
	
	arm_2d_tile_t* draw_cell_handler = (arm_2d_tile_t *)malloc(sizeof(arm_2d_tile_t));
	uint8_t* cell_handler_buffer = (uint8_t *)malloc(20 * 20 * 2 * sizeof(uint8_t));
	
	draw_cell_handler->tRegion.tLocation.iX = 0;
	draw_cell_handler->tRegion.tLocation.iY = 0;
	draw_cell_handler->tRegion.tSize.iWidth = 20;
	draw_cell_handler->tRegion.tSize.iHeight = 20;
	draw_cell_handler->pchBuffer = cell_handler_buffer;
	
	arm_2dp_fill_colour_with_opacity(
			NULL, 
			draw_cell_handler, 
			&draw_cell_handler->tRegion,
			//ecb.ptLayer->ptCells[i].tColor,
			//ecb.ptLayer->ptCells[i].chOpacity
			(__arm_2d_color_t){GLCD_COLOR_BLUE},
			255-128
		);	
	Disp0_DrawBitmap(draw_cell_handler->tRegion.tLocation.iX,
                    draw_cell_handler->tRegion.tLocation.iY,
                    draw_cell_handler->tRegion.tSize.iWidth,
                    draw_cell_handler->tRegion.tSize.iHeight,
                    (const uint8_t *)draw_cell_handler->pchBuffer);
	while(1);
	
	
	rt_thread_t engineTid = RT_NULL, eventTid = RT_NULL, gameTid = RT_NULL;
	
	engineTid = rt_thread_create("engine", GameEngineEntry, RT_NULL, THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
	if (engineTid != RT_NULL) {
		rt_thread_startup(engineTid);
	}
	
//	eventTid = rt_thread_create("event", EventProcessEntry, RT_NULL, THREAD_STACK_SIZE, THREAD_PRIORITY-1, THREAD_TIMESLICE);
//	if (eventTid != RT_NULL) {
//		rt_thread_startup(eventTid);
//	}
	
	gameTid = rt_thread_create("game", SnakeGameEntry, RT_NULL, THREAD_STACK_SIZE, THREAD_PRIORITY-2, THREAD_TIMESLICE);
	if (gameTid != RT_NULL) {
		rt_thread_startup(gameTid);
	}
	
#if 0
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	disp_adapter0_init();
	arm_2d_scene0_init(&DISP0_ADAPTER);
	arm_2d_scene1_init(&DISP0_ADAPTER);
	arm_2d_scene2_init(&DISP0_ADAPTER);
//	arm_2d_scene_player_set_switching_mode(&DISP0_ADAPTER, ARM_2D_SCENE_SWITCH_MODE_NONE);
//	arm_2d_scene_player_set_switching_period(&DISP0_ADAPTER, 3000);
//	arm_2d_scene_player_switch_to_next_scene(&DISP0_ADAPTER);
	
	
	
  while (1)
  {
		disp_adapter0_task();
    /* USER CODE END WHILE */
		
    /* USER CODE BEGIN 3 */
//		LCD_Clear(WHITE);
//		HAL_Delay(1000);
//		LCD_Clear(BLACK);
//		HAL_Delay(1000);
  }
  /* USER CODE END 3 */
  
#endif
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 20;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
