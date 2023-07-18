#ifndef __LED__H__
#define __LED__H__

/***************************** Config *******************************/
// LED_RED
#define LED_RED_GPIO GPIOC
#define LED_RED_PIN GPIO_PIN_5
// LED_BLUE
#define LED_BLUE_GPIO GPIOB
#define LED_BLUE_PIN GPIO_PIN_2
/***************************** Config End *******************************/

enum led_id
{
    LED_RED = 0,
    LED_BLUE = 1,
    LED_TOTAL = 2,
};

enum led_state
{
    LED_OFF = 0,
    LED_ON = 1,
};

void led_init(enum led_id id);
void led_set(enum led_id id, enum led_state state);
void led_toggle(enum led_id id);

#endif
