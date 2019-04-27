#include <stdint.h>
#include "reg.h"
#include "blink.h"

int main(void)
{
	//RCC Enable GPIOA
	SET_BIT(RCC_BASE + RCC_AHB1ENR_OFFSET, GPIO_EN_BIT(GPIO_PORTA)); //IRQ6

	//GPIO Configurations
		//MODER BUTTON pin = 00 => General purpose input mode
		WRITE_BITS(RCC_BASE + GPIOx_MODER_OFFSET, MODERy_1_BIT(0), MODERy_0_BIT(0), 0b00)
		//PUPDR led pin = 00 => No pull-up, pull-down
		WRITE_BITS(GPIO_BASE(GPIO_PORTA),GPIOx_PUPDR_OFFSET, MODERy_1_BIT(0), MODERy_0_BIT(0), 0b00)
	//RCC Enable SYSCFG
	SET_BIT(RCC_BASE + RCC_APB2ENR_OFFSET, GPIO_EN_BIT(SYSCFGEN_BIT)); //IRQ6

	//SYSCFG Configurations
	WRITE_BITS(SYSCFG_BASE, SYSCFG_EXTICR1_OFFSET, EXTI0_0_BIT, EXTI0_3_BIT, 0b0000)

	//EXTI Configurations
	SET_BIT(EXTI_BASE+EXTI_RTSR_OFFSET,TRx_BIT(0))
	SET_BIT(EXTI_BASE+EXTI_FTSR_OFFSET,TRx_BIT(0))
	CLEAR_BIT(EXTI_BASE+EXTI_IMR_OFFSET,MRx_BIT(0))
	SET_BIT(EXTI_BASE+EXTI_PR_OFFSET,PRx_BIT(0))


	//NVIC Configurations
	SET_BIT(NVIC_ISER_BASE + EXTI_IMR_OFFSET, 6); //IRQ6

	blink(LED_BLUE);
}

void exti0_handler(void)
{
	blink_count(LED_ORANGE, 10);

	//clear pending
	SET_BIT(EXTI_BASE + EXTI_IMR, 0);
}
