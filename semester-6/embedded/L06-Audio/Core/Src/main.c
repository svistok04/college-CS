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
#include "dac.h"
#include "dma.h"
#include "i2c.h"
#include "i2s.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "MY_CS43L22.h"
#include <math.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define PI 3.14159f
#define F_SAMPLE 50000.0f
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
typedef struct {
    float freq;
    uint32_t duration_ms;
} Note;

const Note melody[7] = {
    {262.0f, 400},
    {294.0f, 400},
    {0.0f,   100},
    {330.0f, 400},
    {262.0f, 400},
	{0.0f,   50},
	{303.0f, 400},
};

#define F_SAMPLE 50000.0f
#define PI 3.14159f
float mySinVal; //wartość generowanego sinusa
float sample_dt; //odległość pomiędzy próbkami
uint16_t sample_N; //ilość próbek
uint16_t i_t; //numer próbki
uint32_t myDacVal; //sinus dla DAC
uint16_t I2S_dummy[4]; //obsługa transmisji I2S
float F_OUT = 80.0f;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	sample_dt=F_OUT/F_SAMPLE; //odległość pomiędzy próbkami
	sample_N=F_SAMPLE/F_OUT; //ilość próbek do wygenerowania dla 1s
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
  MX_DMA_Init();
  MX_DAC_Init();
  MX_I2C1_Init();
  MX_I2S3_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  CS43_Init(hi2c1, MODE_ANALOG);
  CS43_SetVolume(60);
  CS43_Enable_RightLeft(CS43_RIGHT_LEFT);
  CS43_Start();
  HAL_DAC_Start(&hdac,DAC_CHANNEL_1);
  HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if( HAL_I2S_Transmit (&hi2s3, I2S_dummy , 0x10, 10 ) == HAL_OK)
	  {
	  HAL_GPIO_WritePin(GPIOD, LED4_Pin, 1);
	  };
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
  RCC_OscInitStruct.PLL.PLLN = 168;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	/* USER CODE BEGIN Callback 0 */
	/* USER CODE END Callback 0 */
	if (htim->Instance == TIM14) {
	HAL_IncTick();
	}
	/* USER CODE BEGIN Callback 1 */
  // task 1
  /*
  static uint32_t sweep_counter = 0; // formerly chirp_counter
  if(htim->Instance == TIM2) {
      sweep_counter++;
      if (sweep_counter >= 5000) {
          F_OUT += 100.0f;
          if(F_OUT > 15000.0f) {
              F_OUT = 80.0f;
          }
          sample_dt = F_OUT / F_SAMPLE;
          sample_N = F_SAMPLE / F_OUT;
          sweep_counter = 0;
      }
	mySinVal = sinf(i_t * 2 * PI * sample_dt);
	myDacVal = (mySinVal + 1) * 127;
	//konwersja do całkowitych dodatnich
	HAL_DAC_SetValue(&hdac,DAC_CHANNEL_1,DAC_ALIGN_8B_R,myDacVal); //wysłaniedo konwertera danych 8 bitowych na kanale 1
	i_t++;
	if(i_t>=sample_N) {
      i_t = 0;
    }
	}
  */


  // task 2
	if(htim->Instance == TIM2) {
	    static uint32_t note_elapsed = 0;
	    static uint8_t curr_note = 0;
	    static uint32_t note_duration = 0;

	    if(note_elapsed == 0) {
	        F_OUT = melody[curr_note].freq;
	        note_duration = (uint32_t)(F_SAMPLE * (melody[curr_note].duration_ms / 1000.0f));
	        if(F_OUT > 1.0f) {
	            sample_dt = F_OUT / F_SAMPLE;
	            sample_N = F_SAMPLE / F_OUT;
	        }
	        i_t = 0;
	    }

	    if(F_OUT > 1.0f) {
	        mySinVal = sinf(i_t * 2 * PI * sample_dt);
	        myDacVal = (mySinVal + 1) * 127;
	        HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_8B_R, myDacVal);
	        i_t++;
	        if(i_t >= sample_N) i_t = 0;
	    } else {
	        HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_8B_R, 128);
	    }

	    note_elapsed++;
	    if(note_elapsed >= note_duration) {
	        note_elapsed = 0;
	        curr_note++;
	        if(curr_note >= 7) curr_note = 0;
	    }
	}

	/* USER CODE END Callback 1 */
}
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
