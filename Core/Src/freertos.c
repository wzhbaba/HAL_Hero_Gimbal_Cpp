/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
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
#include "FreeRTOS.h"

#include "cmsis_os.h"
#include "main.h"
#include "task.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Communication.h"
#include "Hero_Gimbal.h"
#include "Remote_Keyboard.h"
#include "SolveTrajectory.h"
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

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId remoteTaskHandle;
osThreadId imuTaskHandle;
osThreadId refereeTaskHandle;
osThreadId visionRecTaskHandle;
osThreadId visionSendTaskHandle;
osThreadId gimbalTaskHandle;
osThreadId modeTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const *argument);
void StartRemoteTask(void const *argument);
void StartIMUTask(void const *argument);
void StartRefereeTask(void const *argument);
void StartVisionRecTask(void const *argument);
void StartVisionSendTask(void const *argument);
void StartGimbalTask(void const *argument);
void StartModeTask(void const *argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize);

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
{
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
    *ppxIdleTaskStackBuffer = &xIdleStack[0];
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
    /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void)
{
    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
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
    /* definition and creation of defaultTask */
    osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
    defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

    /* definition and creation of remoteTask */
    osThreadDef(remoteTask, StartRemoteTask, osPriorityAboveNormal, 0, 128);
    remoteTaskHandle = osThreadCreate(osThread(remoteTask), NULL);

    /* definition and creation of imuTask */
    osThreadDef(imuTask, StartIMUTask, osPriorityHigh, 0, 128);
    imuTaskHandle = osThreadCreate(osThread(imuTask), NULL);

    /* definition and creation of refereeTask */
    osThreadDef(refereeTask, StartRefereeTask, osPriorityRealtime, 0, 256);
    refereeTaskHandle = osThreadCreate(osThread(refereeTask), NULL);

    /* definition and creation of visionRecTask */
    osThreadDef(visionRecTask, StartVisionRecTask, osPriorityAboveNormal, 0, 256);
    visionRecTaskHandle = osThreadCreate(osThread(visionRecTask), NULL);

    /* definition and creation of visionSendTask */
    osThreadDef(visionSendTask, StartVisionSendTask, osPriorityAboveNormal, 0, 256);
    visionSendTaskHandle = osThreadCreate(osThread(visionSendTask), NULL);

    /* definition and creation of gimbalTask */
    osThreadDef(gimbalTask, StartGimbalTask, osPriorityAboveNormal, 0, 128);
    gimbalTaskHandle = osThreadCreate(osThread(gimbalTask), NULL);

    /* definition and creation of modeTask */
    osThreadDef(modeTask, StartModeTask, osPriorityAboveNormal, 0, 128);
    modeTaskHandle = osThreadCreate(osThread(modeTask), NULL);

    /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
    /* USER CODE END RTOS_THREADS */
}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const *argument)
{
    /* init code for USB_DEVICE */
    MX_USB_DEVICE_Init();
    /* USER CODE BEGIN StartDefaultTask */
    /* Infinite loop */
    for (;;) {
        HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin);
        HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_G_Pin);
        osDelay(500);
        HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin);
        HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_G_Pin);
        osDelay(500);
    }
    /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartRemoteTask */
/**
 * @brief Function implementing the RemoteTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartRemoteTask */
void StartRemoteTask(void const *argument)
{
    /* USER CODE BEGIN StartRemoteTask */
    /* Infinite loop */
    for (;;) {
        RemoteTask();
    }
    /* USER CODE END StartRemoteTask */
}

/* USER CODE BEGIN Header_StartIMUTask */
/**
 * @brief Function implementing the IMUTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartIMUTask */
void StartIMUTask(void const *argument)
{
    /* USER CODE BEGIN StartIMUTask */
    /* Infinite loop */
    for (;;) {
        IMUTask();
    }
    /* USER CODE END StartIMUTask */
}

/* USER CODE BEGIN Header_StartRefereeTask */
/**
 * @brief Function implementing the RefereeTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartRefereeTask */
void StartRefereeTask(void const *argument)
{
    /* USER CODE BEGIN StartRefereeTask */
    /* Infinite loop */
    for (;;) {
        RefereeTask();
    }
    /* USER CODE END StartRefereeTask */
}

/* USER CODE BEGIN Header_StartVisionRecTask */
/**
 * @brief Function implementing the visionRecTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartVisionRecTask */
void StartVisionRecTask(void const *argument)
{
    /* USER CODE BEGIN StartVisionRecTask */
    /* Infinite loop */
    for (;;) {
        VisionRecTask();
        osDelay(5);
    }
    /* USER CODE END StartVisionRecTask */
}

/* USER CODE BEGIN Header_StartVisionSendTask */
/**
 * @brief Function implementing the visionSendTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartVisionSendTask */
void StartVisionSendTask(void const *argument)
{
    /* USER CODE BEGIN StartVisionSendTask */
    TrajectoryParams_Init();
    /* Infinite loop */
    for (;;) {
        VisionSendTask();
        osDelay(5);
    }
    /* USER CODE END StartVisionSendTask */
}

/* USER CODE BEGIN Header_StartGimbalTask */
/**
 * @brief Function implementing the gimbalTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartGimbalTask */
void StartGimbalTask(void const *argument)
{
    /* USER CODE BEGIN StartGimbalTask */
    GimbalInit();
    /* Infinite loop */
    for (;;) {
        HeroGimbalTask();
        osDelay(5);
    }
    /* USER CODE END StartGimbalTask */
}

/* USER CODE BEGIN Header_StartModeTask */
/**
 * @brief Function implementing the modeTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartModeTask */
void StartModeTask(void const *argument)
{
    /* USER CODE BEGIN StartModeTask */
    /* Infinite loop */
    for (;;) {
        ModeTask();
        osDelay(1);
    }
    /* USER CODE END StartModeTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
