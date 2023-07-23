#include "main.h"

#include "led.h"

#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>


// STM32H743ZI blue LED
#define LED_PORT GPIOB
#define LED_PIN GPIO_PIN_2
#define LED_PORT_CLK_ENABLE __HAL_RCC_GPIOB_CLK_ENABLE
#include <stm32f4xx_hal.h>


static void blinky::blinkTask(void* arg)
{
    for (;;) {
        vTaskDelay(500);
        LedCtrl::instance()->toggleLed(LED_ID::LED_TOTAL);
    }
}

int main(void)
{
    SystemInit();
    LedCtrl::instance()->init(LED_ID::LED_TOTAL);
    xTaskCreate(blinky::blinkTask,
                "blinky",
                configMINIMAL_STACK_SIZE,
                NULL,
                tskIDLE_PRIORITY + 1,
                NULL);

    vTaskStartScheduler();
    for (;;)
        ;

    return 0;
}

extern "C" void vApplicationTickHook(void)
{ }

extern "C" void vApplicationIdleHook(void)
{ }

extern "C" void vApplicationMallocFailedHook(void)
{
    taskDISABLE_INTERRUPTS();
    for (;;)
        ;
}

extern "C" void vApplicationStackOverflowHook(TaskHandle_t pxTask,
                                              char* pcTaskName)
{
    (void)pcTaskName;
    (void)pxTask;

    taskDISABLE_INTERRUPTS();
    for (;;)
        ;
}
