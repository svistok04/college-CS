/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "lcd.h"
#include "project_logic.h"
#include "cmsis_os.h"
#include "sensors.h"

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
/* USER CODE BEGIN Variables */
osMutexId_t lcdMutexHandle;
osThreadId_t sensorTaskHandle;
osThreadId_t lcdTaskHandle;

const osThreadAttr_t sensorTask_attributes = {
  .name = "SensorTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

const osThreadAttr_t lcdTask_attributes = {
  .name = "LcdTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal - 1,
};
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartSensorTask(void *argument);
void StartLcdTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
    lcdMutexHandle = osMutexNew(NULL); // Optional mutex
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  sensorTaskHandle = osThreadNew(StartSensorTask, NULL, &sensorTask_attributes);
  lcdTaskHandle = osThreadNew(StartLcdTask, NULL, &lcdTask_attributes);
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void StartSensorTask(void *argument)
{
    for(;;)
    {
        if (osMutexAcquire(lcdMutexHandle, pdMS_TO_TICKS(10)) == osOK) {
            ProjectLogic_Update();
            osMutexRelease(lcdMutexHandle);
        }
        osDelay(pdMS_TO_TICKS(100));
    }
}

void StartLcdTask(void *argument)
{
    char local_line_copy[LCD_COLS + 1];
    char prev_line_displayed[LCD_COLS + 1] = {0};
    int  current_display_mode_copy = -1;
    int  mode_from_sensor_task;


    LCD_Init();
    LCD_WriteCommand(LCD_CLEAR);
    HAL_Delay(5);

    for(;;)
    {
        int mode_changed_by_sensor_task = 0;

        if (osMutexAcquire(lcdMutexHandle, pdMS_TO_TICKS(10)) == osOK) {
            strncpy(local_line_copy, line, LCD_COLS);
            local_line_copy[LCD_COLS] = '\0';
            mode_from_sensor_task = (int)display_mode;
            osMutexRelease(lcdMutexHandle);

            if (strcmp(local_line_copy, prev_line_displayed) != 0 || current_display_mode_copy != mode_from_sensor_task) {
                if (current_display_mode_copy != mode_from_sensor_task) {
                }
                LCD_WriteCommand(LCD_DDRAM_SET);
                LCD_WriteText(local_line_copy);
                strncpy(prev_line_displayed, local_line_copy, LCD_COLS + 1);
                current_display_mode_copy = mode_from_sensor_task;
            }
        }
        osDelay(pdMS_TO_TICKS(50));
    }
}

/* USER CODE END Application */

