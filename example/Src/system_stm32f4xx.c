#include "stm32f4xx.h"

#ifndef HSE_VALUE
#define HSE_VALUE    ((uint32_t)25000000)
#endif

#ifndef HSI_VALUE
#define HSI_VALUE    ((uint32_t)16000000)
#endif

#define VECT_TAB_OFFSET  0x00

uint32_t SystemCoreClock = 16000000;
const uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
const uint8_t APBPrescTable[8] = {0, 0, 0, 0, 1, 2, 3, 4};

void SystemInit(void) {
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));
#endif
    RCC->CR |= (uint32_t) 0x00000001;
    RCC->CFGR = 0x00000000;
    RCC->CR &= (uint32_t) 0xFEF6FFFF;
    RCC->PLLCFGR = 0x24003010;
    RCC->CR &= (uint32_t) 0xFFFBFFFF;
    RCC->CIR = 0x00000000;
    SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET;
}

void SystemCoreClockUpdate(void) {
    uint32_t tmp = 0, pllvco = 0, pllp = 2, pllsource = 0, pllm = 2;

    tmp = RCC->CFGR & RCC_CFGR_SWS;

    switch (tmp) {
        case 0x00:
            SystemCoreClock = HSI_VALUE;
            break;
        case 0x04:
            SystemCoreClock = HSE_VALUE;
            break;
        case 0x08:
            pllsource = (RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) >> 22;
            pllm = RCC->PLLCFGR & RCC_PLLCFGR_PLLM;

            if (pllsource != 0) {
                pllvco = (HSE_VALUE / pllm) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);
            } else {
                pllvco = (HSI_VALUE / pllm) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);
            }

            pllp = (((RCC->PLLCFGR & RCC_PLLCFGR_PLLP) >> 16) + 1) * 2;
            SystemCoreClock = pllvco / pllp;
            break;
        default:
            SystemCoreClock = HSI_VALUE;
            break;
    }
    tmp = AHBPrescTable[((RCC->CFGR & RCC_CFGR_HPRE) >> 4)];
    SystemCoreClock >>= tmp;
}
