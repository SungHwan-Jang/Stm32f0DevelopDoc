/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions
#include <stdio.h>

#include "stm32f0xx.h"
#include "stm32f051x8.h"
#include "stm32f0xx_hal.h"

/* Private variables ---------------------------------------------------------*/
osThreadId LEDThread1Handle;
osThreadId LEDThread2Handle;

/* Private function prototypes -----------------------------------------------*/
static void LED_Thread1(void const *argument);
static void LED_Thread2(void const *argument);

void SystemClock_Config(void);
void bsp_led_config(void);

/*
 * main: initialize and start the system
 */
int main (void) {
	
	HAL_Init();
	SystemClock_Config();
	bsp_led_config();
	
	osThreadDef(LED_Thread1, osPriorityNormal, 0, 0);
	osThreadDef(LED_Thread2, osPriorityNormal, 0, 0);
	
	LEDThread1Handle = osThreadCreate(osThread(LED_Thread1), NULL);
	LEDThread2Handle = osThreadCreate(osThread(LED_Thread2), NULL);
	
	osKernelStart ();
	
	while(1){
		;
	}
}

void SystemClock_Config(void){
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;
	
	/* Select HSE Oscillator as PLL source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK){
		/* Initialization Error */
		while(1);
	}

	/* Select PLL as system clock source and configure the HCLK and PCLK1 clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1)!= HAL_OK){
		/* Initialization Error */
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

static void LED_Thread1(void const *argument){
	
	(void) argument;

	while(1){
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_9);
		osDelay(200);
	}
}

static void LED_Thread2(void const *argument){
	
	(void) argument;

	while(1){
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_8);
		osDelay(500);
	}
}

