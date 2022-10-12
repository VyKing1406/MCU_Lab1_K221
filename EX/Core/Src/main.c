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
int counter = 0;
int counter2 = 0;
int state = 0;
int flag_led = 0;
int led_status = 0;
int seg7_status = 0;
const int MAX_LED = 4;
int index_led = 0;
int led_buffer[4] = { 0, 0, 0, 0 };
void Led_Timer_2() {
	if (led_status == 0) {
		HAL_GPIO_WritePin(DOT_GPIO_Port, DOT_Pin, 0);
	}
	if (led_status == 1) {
		HAL_GPIO_WritePin(DOT_GPIO_Port, DOT_Pin, 1);
	}
	led_status = !led_status;
}
void settimer_Led(int duration) {
	counter2 = duration;
	flag_led = 0;
}
void Led_run() {
	if (counter2 > 0) {
		counter2--;
	}
	if (counter2 <= 0) {
		flag_led = 1;
	}
}
void settimer_7SEG(int duration) {
	counter = duration;
	seg7_status = 0;
}
void seg7_run() {
	if (counter > 0) {
		counter--;
	}
	if (counter <= 0) {
		seg7_status = 1;
	}
}
void SEG7_Timer_1() {
	uint8_t temp = GPIOA->ODR;   // init temp to work;
	temp = temp & 0xFC3F; // new temp will change 4 bit from 7->10 th (for 6, 7, 8, 9) equa 0;
	if (state == 0) {
		GPIOA->ODR = temp | 0x380; // or to add 1110 to 7->10 th to enable EN0, and set 1 for EN1,2,3.
		display7SEG(0);
	}
	if (state == 1) {
		GPIOA->ODR = temp | 0x340; // similar for enable EN1.
		display7SEG(1);
	}
	if (state == 2) {
		GPIOA->ODR = temp | 0x2C0; // enable EN2
		display7SEG(2);
	}
	if (state == 3) {
		GPIOA->ODR = temp | 0x1C0; //enable EN3
		display7SEG(3);
	}
	state++; // update state to know what 7SEG is lighted.
	if (state == 4) {
		state = 0;
	}
}
void display7SEG(int index) {
	int num = led_buffer[index];
	if (num == 0) {
		GPIOB->ODR = 0x00000040; // hex to display 0 in 7SEG
	}
	if (num == 1) {
		GPIOB->ODR = 0x00000079; //similar
	}
	if (num == 2) {
		GPIOB->ODR = 0x00000024; //similar
	}
	if (num == 3) {
		GPIOB->ODR = 0x00000030; //similar
	}
	if (num == 4) {
		GPIOB->ODR = 0x00000019; //similar
	}
	if (num == 5) {
		GPIOB->ODR = 0x00000012;
	}
	if (num == 6) {
		GPIOB->ODR = 0x00000002;
	}
	if (num == 7) {
		GPIOB->ODR = 0x00000078;
	}
	if (num == 8) {
		GPIOB->ODR = 0x00000000;
	}
	if (num == 9) {
		GPIOB->ODR = 0x00000010;
	}

}
int timer1_counter = 0;
int timer1_flag = 0;

void set_timer1(int duration) {
	timer1_counter = duration;
	timer1_flag = 0;
}
void timer1_run() {
	if (timer1_counter > 0) {
		timer1_counter--;
	}
	if (timer1_counter <= 0) {
		timer1_flag = 1;
	}
}
int hour = 0, minute = 10, second = 0;
void updateClockBuffer() {
	led_buffer[3] = minute - (minute / 10) * 10;
	led_buffer[2] = minute / 10;
	led_buffer[1] = hour - (hour / 10) * 10;
	led_buffer[0] = hour / 10;
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	seg7_run(); //timer for 7SEG;
	Led_run(); //timer for 2 LEDs;
	timer1_run();
}
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

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_TIM2_Init();
	/* USER CODE BEGIN 2 */
	HAL_GPIO_WritePin(GPIOB,
	SEG0_Pin | SEG1_Pin | SEG2_Pin | SEG3_Pin | SEG4_Pin | SEG5_Pin | SEG6_Pin,
			1);
	HAL_TIM_Base_Start_IT(&htim2);

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */
		/* USER CODE BEGIN 3 */
		if (counter <= 0) {
			settimer_7SEG(50);
			SEG7_Timer_1(); // funtionn to switch EN0 and EN1, and call display7SEG.
		}
		if (flag_led == 1) {
			settimer_Led(100);
			Led_Timer_2(); //funtionn to switch  and 2 LEDs.
		}
		if (timer1_flag == 1) {
			set_timer1(0);
			second++; // count for second
			if (second >= 60) {
				second = 0;
				minute++; //over 60 second comback equa 0, minute ++
			}
			if (minute >= 60) {
				minute = 0;
				hour++;   //over 60 minute comback equa 0, minute ++
			}
			if (hour >= 24) {
				hour = 0;
			}
			updateClockBuffer();
		}
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief TIM2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM2_Init(void) {

	/* USER CODE BEGIN TIM2_Init 0 */

	/* USER CODE END TIM2_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	/* USER CODE BEGIN TIM2_Init 1 */

	/* USER CODE END TIM2_Init 1 */
	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 7999;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 9;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim2) != HAL_OK) {
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK) {
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig)
			!= HAL_OK) {
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
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA,
	DOT_Pin | Led_Red_Pin | EN0_Pin | EN1_Pin | EN2_Pin | EN3_Pin,
			GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB,
	SEG0_Pin | SEG1_Pin | SEG2_Pin | SEG3_Pin | SEG4_Pin | SEG5_Pin | SEG6_Pin,
			GPIO_PIN_RESET);

	/*Configure GPIO pins : DOT_Pin Led_Red_Pin EN0_Pin EN1_Pin
	 EN2_Pin EN3_Pin */
	GPIO_InitStruct.Pin = DOT_Pin | Led_Red_Pin | EN0_Pin | EN1_Pin | EN2_Pin
			| EN3_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : SEG0_Pin SEG1_Pin SEG2_Pin SEG3_Pin
	 SEG4_Pin SEG5_Pin SEG6_Pin */
	GPIO_InitStruct.Pin = SEG0_Pin | SEG1_Pin | SEG2_Pin | SEG3_Pin | SEG4_Pin
			| SEG5_Pin | SEG6_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
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
