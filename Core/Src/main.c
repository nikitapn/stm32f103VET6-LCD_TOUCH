#include "main.h"
#include "FreeRTOS.h"
#include "task.h"

#include "stm32f1xx_hal_sram.h"
#include "stm32f1xx_ll_fsmc.h"

SRAM_HandleTypeDef hsram1;
RTC_HandleTypeDef hrtc;

void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
	/* This function will get called if a task overflows its stack.   If the
	parameters are corrupt then inspect pxCurrentTCB to find which was the
	offending task. */

	(void)pxTask;
	(void)pcTaskName;

	for (;;)
		;
}

/**
 * @brief System Clock Configuration
 * @retval None
 */

void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
	RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_LSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	RCC_OscInitStruct.LSEState = RCC_LSE_ON;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
	{
		Error_Handler();
	}
	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
	PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
 * @brief RTC Initialization Function
 * @param None
 * @retval None
 */
static void MX_RTC_Init(void)
{

	/* USER CODE BEGIN RTC_Init 0 */

	/* USER CODE END RTC_Init 0 */

	/* USER CODE BEGIN RTC_Init 1 */

	/* USER CODE END RTC_Init 1 */

	/** Initialize RTC Only
	 */
	hrtc.Instance = RTC;
	hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
	hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
	if (HAL_RTC_Init(&hrtc) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN RTC_Init 2 */

	/* USER CODE END RTC_Init 2 */
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
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
//  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin : PE2 */
//  GPIO_InitStruct.Pin = GPIO_PIN_2;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PC6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

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

#ifdef USE_FULL_ASSERT
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

void vTask1(void *pvParameters)
{
	//HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6);
	const TickType_t xDelay500ms = pdMS_TO_TICKS(500);
	TickType_t xLastWakeTime;

	xLastWakeTime = xTaskGetTickCount();

	for (;;)
	{
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6);
		/* Delay for a period. This time a call to vTaskDelay() is used which places
			the task into the Blocked state until the delay period has expired. The
			parameter takes a time specified in ‘ticks’, and the pdMS_TO_TICKS() macro
			is used (where the xDelay500ms constant is declared) to convert 500
			milliseconds into an equivalent time in ticks. */
		vTaskDelayUntil(&xLastWakeTime, xDelay500ms);
	}
}

/* FSMC initialization function */
//static void MX_FSMC_Init(void)
//{
//
//  /* USER CODE BEGIN FSMC_Init 0 */
//
//  /* USER CODE END FSMC_Init 0 */
//
//  FSMC_NORSRAM_TimingTypeDef Timing = {0};
//
//  /* USER CODE BEGIN FSMC_Init 1 */
//
//  /* USER CODE END FSMC_Init 1 */
//
//  /** Perform the SRAM1 memory initialization sequence
//  */
//  hsram1.Instance = FSMC_NORSRAM_DEVICE;
//  hsram1.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
//  /* hsram1.Init */
//  hsram1.Init.NSBank = FSMC_NORSRAM_BANK1;
//  hsram1.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
//  hsram1.Init.MemoryType = FSMC_MEMORY_TYPE_NOR;
//  hsram1.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
//  hsram1.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;
//  hsram1.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
//  hsram1.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;
//  hsram1.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
//  hsram1.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
//  hsram1.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
//  hsram1.Init.ExtendedMode = FSMC_EXTENDED_MODE_DISABLE;
//  hsram1.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
//  hsram1.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;
//  /* Timing */
//  Timing.AddressSetupTime = 0x02;
//  Timing.AddressHoldTime = 0x00;
//  Timing.DataSetupTime = 0x05;
//  Timing.BusTurnAroundDuration = 0x00;
//  Timing.CLKDivision = 0x00;
//  Timing.DataLatency = 0x00;
//  Timing.AccessMode = FSMC_ACCESS_MODE_B;
//  /* ExtTiming */
//
//  if (HAL_SRAM_Init(&hsram1, &Timing, NULL) != HAL_OK)
//  {
//    Error_Handler( );
//  }
//
//  /** Disconnect NADV
//  */
//
//  __HAL_AFIO_FSMCNADV_DISCONNECTED();
//
//  /* USER CODE BEGIN FSMC_Init 2 */
//
//  /* USER CODE END FSMC_Init 2 */
//}

int main(void)
{
	HAL_Init();
	SystemClock_Config();

	// Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_RTC_Init();
//	MX_FSMC_Init();

	/* Create one of the two tasks. Note that a real application should check
	the return value of the xTaskCreate() call to ensure the task was created
	successfully. */
	xTaskCreate(vTask1,										/* Pointer to the function that implements the task. */
							"Task 1",									/* Text name for the task. This is to facilitate
															 debugging only. */
							configMINIMAL_STACK_SIZE, /* Stack depth - small microcontrollers will use much
							less stack than this. */
							NULL,											/* This example does not use the task parameter. */
							tskIDLE_PRIORITY + 1,			/* This task will run at priority 1. */
							NULL);										/* This example does not use the task handle. */
	/* Create the other task in exactly the same way and at the same priority. */
	// xTaskCreate(vTask2, "Task 2", 1000, NULL, 1, NULL);

	/* Start the scheduler so the tasks start executing. */
	vTaskStartScheduler();

	/* If all is well then main() will never reach here as the scheduler will
	now be running the tasks. If main() does reach here then it is likely that
	there was insufficient heap memory available for the idle task to be created.
	Chapter 2 provides more information on heap memory management. */

	for (;;)
		;
}