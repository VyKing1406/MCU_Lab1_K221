/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
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

// MUST BE ADJUSTED FOR EACH NEW PROJECT
#define SCH_MAX_TASKS 40
#define NO_TASK_ID 0

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct {
// Pointer to the task (must be a ’ void ( void ) ’ function )
	void (*pTask)(void);
// Delay ( ti c k s ) un til the function will ( next ) be run
	uint32_t Delay;
// In t e r v al ( ti c k s ) between subsequent runs .
	uint32_t Period;
	// Incremented (by scheduler) when task i s due to execute
	uint8_t RunMe;
	//This i s a hin t to solve the question below .
	uint32_t TaskID;
} sTask;
sTask SCH_tasks_G[SCH_MAX_TASKS];
void SCH_Update(void) {
	unsigned char index;
	for (index = 0; index < SCH_MAX_TASKS; index++) {
		// Check i f there i s a task a t t hi s loca tion
		if (SCH_tasks_G[index].pTask) {
			if (SCH_tasks_G[index].Delay == 0) {
				// The task i s due to run
				// Inc . the ’RunMe’ fl a g
				SCH_tasks_G[index].RunMe += 1;
				if (SCH_tasks_G[index].Period) {
					// Schedule periodic tasks to run again
					SCH_tasks_G[index].Delay = SCH_tasks_G[index].Period;
				}
			} else {
				// Not ye t ready to run : j u s t decrement the delay
				SCH_tasks_G[index].Delay -= 1;
			}
		}
	}
}

int SCH_Add_Task(void (*pFunction)(), unsigned int DELAY,
		unsigned int PERIOD) {
	unsigned char index = 0;
	// Fi r s t find a gap in the array ( i f there i s one)
	while ((SCH_tasks_G[index].pTask != 0) && (index < SCH_MAX_TASKS)) {
		index++;
	}

	if (index == SCH_MAX_TASKS) {
		// Task l i s t i s f u l l
		// Set the global e r ro r v a ri abl e
		// Also return an e r ro r code
		return -1;
	}
	// I f we ’re here , there i s a space in the task array
	SCH_tasks_G[index].pTask = pFunction;
	SCH_tasks_G[index].Delay = DELAY;
	SCH_tasks_G[index].Period = PERIOD;
	SCH_tasks_G[index].RunMe = 0;
	// return posi tion o f task ( to allow l a t e r dele tion )
	return index;
}

void SCH_Dispatch_Tasks(void) {
	unsigned char index;
	// Dispatches (runs ) the next task ( i f one i s ready )
	for (index = 0; index < SCH_MAX_TASKS; index++) {
		if (SCH_tasks_G[index].RunMe > 0) {
			(*SCH_tasks_G[index].pTask)(); // Run the task
			SCH_tasks_G[index].RunMe -= 1; // Reset / reduce RunMe fl a g
			// Periodic tasks will au toma tically run again
			// − i f t hi s i s a ’one shot ’ task , remove i t from the array
			if (SCH_tasks_G[index].Period == 0) {
				SCH_Delete_Task(index);
			}
		}
	}
}

int SCH_Delete_Task(const int TASK_INDEX) {
	unsigned char Return_code;
	if ( SCH_tasks_G[TASK_INDEX].pTask == 0 ) {
		Return_code = 0;
	}else {
		Return_code = 1;
	}
	SCH_tasks_G [TASK_INDEX].pTask = 0x0000;
	SCH_tasks_G [TASK_INDEX].Delay = 0;
	SCH_tasks_G [TASK_INDEX].Period = 0;
	SCH_tasks_G [TASK_INDEX].RunMe = 0;
	return Return_code; // return s t a tus
}


TIM_HandleTypeDef htim2;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	SCH_Update();
}
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void task_display1(void) {
	HAL_GPIO_WritePin(GPIOA, led_1_Pin, 0);
}
void task_display2(void) {
	HAL_GPIO_WritePin(GPIOA, led_2_Pin, 0);
}
void task_display3(void) {
	HAL_GPIO_WritePin(GPIOA, led_3_Pin, 0);
}
void task_display4(void) {
	HAL_GPIO_WritePin(GPIOA, led_4_Pin, 0);
}
void task_display5(void) {
	HAL_GPIO_WritePin(GPIOA, led_5_Pin, 0);
}
void task_display6(void) {
	HAL_GPIO_WritePin(GPIOA, led_1_Pin | led_2_Pin | led_3_Pin | led_4_Pin | led_5_Pin , 1);
}
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

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim2);
	task_display6();
	void ( *tks1 ) () ;
	void ( *tks2 ) () ;
	void ( *tks3 ) () ;
	void ( *tks4 ) () ;
	void ( *tks5 ) () ;
	void ( *tks6 ) () ;
	tks1 =  task_display1 ;
	tks2 =  task_display2 ;
	tks3 =  task_display3 ;
	tks4 =  task_display4 ;
	tks5 =  task_display5 ;
	tks6 =  task_display6 ;
	SCH_Add_Task(tks6, 0, 0);
	SCH_Add_Task(tks1, 200, 1200);
	SCH_Add_Task(tks2, 400, 1200);
	SCH_Add_Task(tks3, 600, 1200);
	SCH_Add_Task(tks4, 800, 1200);
	SCH_Add_Task(tks5, 1000, 1200);
	SCH_Add_Task(tks6, 1200, 1200);
	/* USER CODE END 0 */
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

	while (1) {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		SCH_Dispatch_Tasks();
	}

}
  /* USER CODE END 3 */

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 10;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, led_1_Pin|led_2_Pin|led_3_Pin|led_4_Pin
                          |led_5_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : led_1_Pin led_2_Pin led_3_Pin led_4_Pin
                           led_5_Pin */
  GPIO_InitStruct.Pin = led_1_Pin|led_2_Pin|led_3_Pin|led_4_Pin
                          |led_5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

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
while (1) {
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
