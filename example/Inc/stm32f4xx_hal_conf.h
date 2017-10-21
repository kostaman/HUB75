#ifndef __STM32F4xx_HAL_CONF_H
#define __STM32F4xx_HAL_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

#if !defined  (HSE_VALUE)
#define HSE_VALUE    ((uint32_t)8000000U)
#endif

#if !defined  (HSE_STARTUP_TIMEOUT)
#define HSE_STARTUP_TIMEOUT    ((uint32_t)100U)
#endif

#if !defined  (HSI_VALUE)
#define HSI_VALUE    ((uint32_t)16000000U)
#endif

#if !defined  (LSI_VALUE)
#define LSI_VALUE  ((uint32_t)32000U)
#endif

#if !defined  (LSE_VALUE)
#define LSE_VALUE  ((uint32_t)32768U)
#endif

#if !defined  (LSE_STARTUP_TIMEOUT)
#define LSE_STARTUP_TIMEOUT    ((uint32_t)5000U)
#endif

#if !defined  (EXTERNAL_CLOCK_VALUE)
#define EXTERNAL_CLOCK_VALUE    ((uint32_t)12288000U)
#endif

#define  VDD_VALUE              ((uint32_t)3300U)
#define  TICK_INT_PRIORITY            ((uint32_t)0U)
#define  USE_RTOS                     0U
#define  PREFETCH_ENABLE              1U
#define  INSTRUCTION_CACHE_ENABLE     1U
#define  DATA_CACHE_ENABLE            1U


#define HAL_MODULE_ENABLED
#define HAL_RTC_MODULE_ENABLED
#define HAL_TIM_MODULE_ENABLED
#define HAL_GPIO_MODULE_ENABLED
#define HAL_DMA_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED
#define HAL_FLASH_MODULE_ENABLED
#define HAL_PWR_MODULE_ENABLED
#define HAL_CORTEX_MODULE_ENABLED

#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_dma.h"
#include "stm32f4xx_hal_cortex.h"
#include "stm32f4xx_hal_flash.h"
#include "stm32f4xx_hal_pwr.h"
#include "stm32f4xx_hal_rtc.h"
#include "stm32f4xx_hal_tim.h"

#define assert_param(expr) ((void)0U)

#ifdef __cplusplus
}
#endif

#endif
