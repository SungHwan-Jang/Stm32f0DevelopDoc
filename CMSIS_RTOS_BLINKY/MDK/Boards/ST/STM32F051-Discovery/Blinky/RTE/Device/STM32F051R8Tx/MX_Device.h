/******************************************************************************
 * File Name   : MX_Device.h
 * Date        : 16/01/2018 13:37:57
 * Description : STM32Cube MX parameter definitions
 * Note        : This file is generated by STM32CubeMX (DO NOT EDIT!)
 ******************************************************************************/

#ifndef __MX_DEVICE_H
#define __MX_DEVICE_H

/*---------------------------- Clock Configuration ---------------------------*/

#define MX_LSI_VALUE                            40000
#define MX_LSE_VALUE                            32768
#define MX_HSI_VALUE                            8000000
#define MX_HSE_VALUE                            8000000
#define MX_HSI14_VALUE                          14000000
#define MX_HSI48_VALUE                          48000000
#define MX_PLLCLKFreq_Value                     48000000
#define MX_PLLMCOFreq_Value                     24000000
#define MX_SYSCLKFreq_VALUE                     48000000
#define MX_HCLKFreq_Value                       48000000
#define MX_MCOFreq_Value                        48000000
#define MX_FCLKCortexFreq_Value                 48000000
#define MX_TimSysFreq_Value                     48000000
#define MX_AHBFreq_Value                        48000000
#define MX_APB1Freq_Value                       48000000
#define MX_APB1TimFreq_Value                    48000000
#define MX_ADCoutputFreq_Value                  14000000
#define MX_FLITFCLKFreq_Value                   8000000
#define MX_CECFreq_Value                        32786
#define MX_I2C1Freq_Value                       8000000
#define MX_I2SFreq_Value                        48000000
#define MX_USART1Freq_Value                     48000000
#define MX_USART2Freq_Value                     8000000
#define MX_RTCFreq_Value                        40000
#define MX_RTCHSEDivFreq_Value                  250000
#define MX_USBFreq_Value                        48000000
#define MX_WatchDogFreq_Value                   40000
#define MX_VCOOutput2Freq_Value                 4000000

/*-------------------------------- SYS        --------------------------------*/

#define MX_SYS                                  1

/* GPIO Configuration */

/*-------------------------------- NVIC       --------------------------------*/

#define MX_NVIC                                 1

/*-------------------------------- GPIO       --------------------------------*/

#define MX_GPIO                                 1

/* GPIO Configuration */

/* Pin PC8 */
#define MX_PC8_GPIO_Speed                       GPIO_SPEED_FREQ_LOW
#define MX_PC8_Pin                              PC8
#define MX_PC8_GPIOx                            GPIOC
#define MX_PC8_PinState                         GPIO_PIN_RESET
#define MX_PC8_GPIO_PuPd                        GPIO_NOPULL
#define MX_PC8_GPIO_Pin                         GPIO_PIN_8
#define MX_PC8_GPIO_ModeDefaultOutputPP         GPIO_MODE_OUTPUT_PP

/* Pin PC9 */
#define MX_PC9_GPIO_Speed                       GPIO_SPEED_FREQ_LOW
#define MX_PC9_Pin                              PC9
#define MX_PC9_GPIOx                            GPIOC
#define MX_PC9_PinState                         GPIO_PIN_RESET
#define MX_PC9_GPIO_PuPd                        GPIO_NOPULL
#define MX_PC9_GPIO_Pin                         GPIO_PIN_9
#define MX_PC9_GPIO_ModeDefaultOutputPP         GPIO_MODE_OUTPUT_PP

/* Pin PA0 */
#define MX_PA0_Pin                              PA0
#define MX_PA0_GPIOx                            GPIOA
#define MX_PA0_GPIO_PuPd                        GPIO_NOPULL
#define MX_PA0_GPIO_Pin                         GPIO_PIN_0
#define MX_PA0_GPIO_Mode                        GPIO_MODE_INPUT

#endif  /* __MX_DEVICE_H */
