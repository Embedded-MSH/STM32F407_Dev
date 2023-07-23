#ifndef __MAIN_H__
#define __MAIN_H__

#include "stm32f4xx_hal.h"

namespace blinky {

void init();
static void blinkTask(void* args);

}   // namespace blinky


#endif   //! __MAIN_H__
