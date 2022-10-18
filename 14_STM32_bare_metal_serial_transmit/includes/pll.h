#pragma once

#define PLL_M       8ul
#define PLL_N       180ul
#define PLL_P       0ul
#define PLL_Q       2ul

#define HCLK_FREQ       180000000uL
#define APB1_FREQ       (HCLK_FREQ/4)
#define APB2_FREQ       (HCLK_FREQ/2)

void clockSpeed_PLL();