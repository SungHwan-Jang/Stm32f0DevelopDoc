/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions
#include <stdio.h>

#include "stm32f0xx.h"
#include "stm32f051x8.h"
#include "stm32f0xx_hal.h"

#define DEBUG			1
	
/* Private variables ---------------------------------------------------------*/
osThreadId LEDThread1Handle;
osThreadId LEDThread2Handle;

UART_HandleTypeDef UartHandle;

/* Buffer used for transmission */
uint8_t aTxBuffer[] = " * HELLO * \n\r";

/* Private function prototypes -----------------------------------------------*/

void SystemClock_Config(void);
void bsp_led_config(void);
void uart1_config(void);

__asm void HardFault_Handler(void){
	BX	R2
}

static void Thread1(void const *argument){
	
	(void) argument;
	
#if DEBUG
	uint8_t th1TxBuffer[] = "* THREAD 1 ENTER     *\n\r";
	HAL_UART_Transmit(&UartHandle, (uint8_t*)th1TxBuffer, sizeof(th1TxBuffer), 2);
#endif
	
	while(1){
		
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_9);
		osDelay(256);
#if DEBUG
		sprintf((char*) th1TxBuffer, "* THREAD 1 RUNNING *\n\r");
		HAL_UART_Transmit(&UartHandle, (uint8_t*)th1TxBuffer, sizeof(th1TxBuffer), 2);
#endif
	}
}

static void Thread2(void const *argument){
	
	(void) argument;
	
#if DEBUG
	uint8_t th2TxBuffer[] = "// THREAD 2 ENTER     //\n\r";
	HAL_UART_Transmit(&UartHandle, (uint8_t*)th2TxBuffer, sizeof(th2TxBuffer), 2);
#endif
	
	while(1){
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_8);
		osDelay(512);
#if DEBUG
		sprintf((char*) th2TxBuffer, "// THREAD 2 RUNNING //\n\r");
		HAL_UART_Transmit(&UartHandle, (uint8_t*)th2TxBuffer, sizeof(th2TxBuffer), 2);
		
#endif
	}
}

/*
 * main: initialize and start the system
 */
int main (void) {
	
	HAL_Init();
	SystemClock_Config();
	bsp_led_config();
	uart1_config();
	
	osThreadDef(Thread1, osPriorityNormal, 0, 0);
	osThreadDef(Thread2, osPriorityNormal, 0, 0);
	
	LEDThread1Handle = osThreadCreate(osThread(Thread1), NULL);
	LEDThread2Handle = osThreadCreate(osThread(Thread2), NULL);
	
	osKernelStart ();
	
	//osDelay(osWaitForever);
	
	while(1){
		HAL_UART_Transmit(&UartHandle, (uint8_t*)"MAIN RUNNING\n\r", sizeof("MAIN RUNNING\n\r"), 2);
		osDelay(1024);
	}
}

void SystemClock_Config(void){
	
	/*
	* Initializes the CPU, AHB and APB busses clocks 
	*/
  
  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();
  
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    while(1);
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    while(1);
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    while(1);
  }
}

void bsp_led_config(void){
	
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	/* Enable the GPIO_LED clock */
	__HAL_RCC_GPIOC_CLK_ENABLE();

	/* Configure the GPIO_LED pin */
	GPIO_InitStruct.Pin = GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);
	
	GPIO_InitStruct.Pin = GPIO_PIN_8;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
}

void uart1_config(void){
	
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	__HAL_RCC_USART1_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
	
    /*
	*USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
	
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF1_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	UartHandle.Instance        = USART1;
	
	UartHandle.Init.BaudRate   = 115200;
	UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits   = UART_STOPBITS_1;
	UartHandle.Init.Parity     = UART_PARITY_NONE;
	UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	UartHandle.Init.Mode       = UART_MODE_TX_RX;
	
	UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
	UartHandle.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	UartHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  
	if(HAL_UART_DeInit(&UartHandle) != HAL_OK){
		while(1);
	}
	
	if(HAL_UART_Init(&UartHandle) != HAL_OK){
		while(1);
	}
}


