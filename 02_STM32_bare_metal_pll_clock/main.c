#include "../STM32F446RE/stm32f4xx.h"
#include "../STM32F446RE/stm32f446xx.h"

#include "pll.h"

/*

#define PLL_M 8ul
#define PLL_N 180ul
#define PLL_P 0ul
#define PLL_Q 2ul

#define HCLK_FREQ       180000000uL
#define APB1_FREQ       (HCLK_FREQ/4)
#define APB2_FREQ       (HCLK_FREQ/2)

void sysClockCfg(){

    RCC->CR |= RCC_CR_HSION;
    while (!(RCC->CR & RCC_CR_HSIRDY));

    //RCC->PLLCFGR &=~ RCC_PLLCFGR_PLLSRC;//RCC_PLLCFGR_PLLSRC;

    RCC->PLLCFGR = (PLL_M) | (PLL_N << 6) | (PLL_P << 16) | (PLL_Q << 24);
    RCC->PLLCFGR &=~ RCC_PLLCFGR_PLLSRC;

    RCC->CFGR |= RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE2_DIV2 | RCC_CFGR_PPRE1_DIV4;


    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY));

    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    
    PWR->CR |= PWR_CR_ODEN;
    while (!(PWR->CSR & PWR_CSR_ODRDY)) ;
    
    PWR->CR |= PWR_CR_ODSWEN;
    while (!(PWR->CSR & PWR_CSR_ODSWRDY)) ;

    FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_LATENCY_5WS;

    RCC->CFGR &=~ RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL);
        //     uint32_t cfgr = RCC->CFGR;
        // cfgr &= ~RCC_CFGR_SW;
        // cfgr |= RCC_CFGR_SW_PLL;
        // RCC->CFGR = cfgr;
        // while ((RCC->CFGR & RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL) ;


}
*/



// #define SYSTICK_LOAD_VAL 180000 / 2//w zależności od częstotliwości procesora
// #define CTRL_ENABLE (1U<<0)
// #define CTRL_CLKSRC (1U<<2)
// #define CTRL_COUNTFLAG (1U<<16)

// //coretex m4 generic user guide zawiera dokumentacje

// void systickDelayMs(int delay){

// 	SysTick->LOAD = SYSTICK_LOAD_VAL;

// 	SysTick->VAL = 0;

// 	SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC;

// 	for(int i=0; i<delay; i++){

// 		while((SysTick->CTRL & CTRL_COUNTFLAG) == 0){}
// 	}

// 	SysTick->CTRL = 0;
// }


volatile uint32_t ms_counter = 0;

void SysTick_Handler(void)
{
        if (ms_counter)
                ms_counter--;
}

void delay_ms(uint32_t ms)
{
        ms_counter = ms;
        while (ms_counter);
        
}

int main(){
    // SystemInit();
    
    clockSpeed_PLL();
    // SystemCoreClock = 180000000;
    // SystemCoreClockUpdate();

    RCC->AHB1ENR |= 1;
	GPIOA->MODER |= (1U<<10);

    SysTick->LOAD = (HCLK_FREQ / 1000)- 1;
    SysTick->VAL = 0;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
                    SysTick_CTRL_TICKINT_Msk |
                    SysTick_CTRL_ENABLE_Msk;

   

	while(1){

        GPIOA -> ODR ^= (1U<<5);
        delay_ms(1000);
        
        //systickDelayMs(1000);

        // for(int i=0; i<1500000; i++){
        //     __asm("nop");
        // };

	}

}