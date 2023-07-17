#pragma once

#include <memory>
#include <stm32f4xx_hal.h>
#include <unordered_map>

class LedCtrl
{
public:
    enum class LED
    {
        RED,
        BLUE
    };


    static std::shared_ptr<LedCtrl> instance()
    {
        static std::shared_ptr<LedCtrl> instance(new LedCtrl());
        return instance;
    }

    void append(LED led, GPIO_TypeDef* gpio, unsigned int pin)
    {
        m_gpioName[led] = std::make_pair(gpio, pin);
    }

    bool init(LED led);

    void setLed(LED led, bool state);

    void toggleLed(LED led);

private:
    using LEDINFO = std::pair<GPIO_TypeDef*, unsigned int>;
    LedCtrl();

    LedCtrl(const LedCtrl&) = delete;
    LedCtrl& operator=(const LedCtrl&) = delete;

    std::unordered_map<LED, LEDINFO> m_gpioName;
};
