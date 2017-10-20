#include "stm32f4xx_hal.h"

extern void Error_Handler(void);

void HAL_MspInit(void) {
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

    HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
    HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
    HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
    HAL_NVIC_SetPriority(SVCall_IRQn, 0, 0);
    HAL_NVIC_SetPriority(DebugMonitor_IRQn, 0, 0);
    HAL_NVIC_SetPriority(PendSV_IRQn, 0, 0);
    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

void HAL_RTC_MspInit(RTC_HandleTypeDef *hrtc) {
    if (hrtc->Instance == RTC) {
        __HAL_RCC_RTC_ENABLE();
    }
}

void HAL_RTC_MspDeInit(RTC_HandleTypeDef *hrtc) {
    if (hrtc->Instance == RTC) {
        __HAL_RCC_RTC_DISABLE();
    }
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim_base) {
    if (htim_base->Instance == TIM9) {
        __HAL_RCC_TIM9_CLK_ENABLE();
    }
}

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim) {
    GPIO_InitTypeDef GPIO_InitStruct;
    if (htim->Instance == TIM9) {
        GPIO_InitStruct.Pin = GPIO_PIN_5;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF3_TIM9;
        HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
    }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *htim_base) {
    if (htim_base->Instance == TIM9) {
        __HAL_RCC_TIM9_CLK_DISABLE();
    }
}
