#ifndef __KEY_H__
#define __KEY_H__

#include <stm32f4xx_hal.h>

// KEY_1_WKUP, 闲时下拉，按下时被置高电平
#define KEY1_Pin GPIO_PIN_0
#define KEY1_GPIO_Port GPIOA
#define KEY1_EXTI_IRQn EXTI0_IRQn
// KEY_2, 闲时上拉，按下时被置低电平
#define KEY2_Pin GPIO_PIN_1
#define KEY2_GPIO_Port GPIOA
#define KEY2_EXTI_IRQn EXTI1_IRQn
// KEY_3, 闲时上拉，按下时被置低电平
#define KEY3_Pin GPIO_PIN_4
#define KEY3_GPIO_Port GPIOA
#define KEY3_EXTI_IRQn EXTI4_IRQn

void key_init(void);
#endif   // !__KEY_H__
