#pragma once

#include <memory>
#include <stm32f4xx_hal.h>
#include <unordered_map>
/***************************** Config *******************************/
// LED_RED
#define LED_RED_GPIO GPIOC
#define LED_RED_PIN GPIO_PIN_5

// LED_BLUE
#define LED_BLUE_GPIO GPIOB
#define LED_BLUE_PIN GPIO_PIN_2
/***************************** Config End *******************************/

enum LED_ID
{
    LED_RED = 0,
    LED_BLUE = 1,
    LED_TOTAL = 2,
};

enum LED_STATE
{
    LED_OFF = 0,
    LED_ON = 1,
};

class LedCtrl
{
public:
    static std::shared_ptr<LedCtrl> instance()
    {
        static std::shared_ptr<LedCtrl> instance(new LedCtrl());
        return instance;
    }

    void init(LED_ID id);

    void setLed(LED_ID id, LED_STATE state);

    void toggleLed(LED_ID id);

private:
    LedCtrl() = default;
    LedCtrl(const LedCtrl&) = delete;
    LedCtrl& operator=(const LedCtrl&) = delete;

    void initOneLed(LED_ID id);
    void setOneLed(LED_ID id, LED_STATE state);
    void toggleOneLed(LED_ID id);
};
