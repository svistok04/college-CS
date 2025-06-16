/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "gpio.h"
#include "lcd.h"

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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  /* USER CODE BEGIN 2 */
  // task 1
  LCD_Init(); //inicjalizacja wysietlacza
//  LCD_WriteCommand(LCD_CLEAR); //wyczyszczenie wyświetlacza
//  LCD_WriteCommand(LCD_DDRAM_SET + 5);
//  LCD_WriteText("WI ZUT");
//  LCD_WriteCommand(LCD_DDRAM_SET + 0x40 + 5);
//  LCD_WriteText("WI ZUT");


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  int i = 0;
  char* text = "WI ZUT";
  int len = 5;
  int left = LCD_DISPLAY_CURSOR_SHIFT | LCD_SHIFT_DISPLAY | LCD_SHIFT_LEFT;
  int right = LCD_DISPLAY_CURSOR_SHIFT | LCD_SHIFT_DISPLAY | LCD_SHIFT_RIGHT;
  int direction = -1; // -1 - left, 1 - right;
  LCD_WriteCommand(LCD_CLEAR);
  LCD_WriteCommand(LCD_ENTRY_MODE | LCD_EM_INCREMENT);
//  LCD_WriteCommand(LCD_DDRAM_SET + 16); // task 2
  LCD_WriteCommand(LCD_DDRAM_SET + 10); // task 3
  // task 4
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
  LCD_WriteText(text);
  while (1)
  {
    /* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */
	  // task 2
//	  LCD_WriteCommand(left);
//	  HAL_Delay(200);
//	  if (i++ == 22) {
//		  LCD_WriteCommand(LCD_CLEAR);
//		  LCD_WriteCommand(LCD_DDRAM_SET + 16);
//		  LCD_WriteText(text);
//		  i = 0;
//	  }
	  // task 3
//	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
//	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15 , GPIO_PIN_RESET);
//	  for (int i = 16 - len; i > 1; i--) {
//		  LCD_WriteCommand(left);
//		  HAL_Delay(200);
//	  }
//	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
//	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
//	  for (int i = 1; i < 16 - len; i++) {
//		  LCD_WriteCommand(right);
//		  HAL_Delay(200);
//	  }

	  // task 4
	  if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)) {
		  direction *= -1;
		  HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
		  HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
		  HAL_Delay(300);
	  }

	  LCD_WriteCommand(direction == -1 ? left : right);

	  i += direction;

	  if (i < 0 || i > 22) {
	      i = (direction == -1) ? 22 : 0;
	      LCD_WriteCommand(LCD_CLEAR);
	      LCD_WriteCommand(direction == -1 ? LCD_DDRAM_SET + 16 : LCD_DDRAM_SET);
	      if (direction == 1) {
	    	  for (int i = 0; i < len; i++) {
	    		  LCD_WriteCommand(left);
	    	  }
	      }
	      LCD_WriteText(text);
	  }
	  HAL_Delay(200);
  }
  /* USER CODE END 3 */
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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
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
