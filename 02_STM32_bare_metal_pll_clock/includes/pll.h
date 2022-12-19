#pragma once

#define PLL_M       8
#define PLL_N       180
#define PLL_P       0
#define PLL_Q       2

#define HCLK_FREQ       180000000
#define APB1_FREQ       (HCLK_FREQ/4)
#define APB2_FREQ       (HCLK_FREQ/2)

void clockSpeed_PLL();