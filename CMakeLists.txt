cmake_minimum_required(VERSION 3.16)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/stm32_gcc.cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(stm32-template C ASM)

# ############## CONFIGURATION #################################################
set(OPENOCD_INTERFACE cmsis-dap.cfg)
set(OPENOCD_TARGET stm32f4x.cfg)
set(STM32_TYPE STM32F407VE)
set(CMSIS_TYPE STM32::F407VE)
set(HAL_TYPE STM32::F4)

set(OPENOCD_SCRIPTS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/openocd.cfg")
message("OPENOCD_SCRIPTS_PATH: ${OPENOCD_SCRIPTS_PATH}")
# ##############################################################################

find_package(
  CMSIS
  COMPONENTS ${STM32_TYPE}
  REQUIRED)

find_package(
  HAL
  COMPONENTS ${STM32_TYPE}
             RCC
             GPIO
             CORTEX
             UART
             USART
             DMA
             TIM
  REQUIRED)

set(LOCAL_LINKER_SYMBOL
    -Wl,--no-warn-rwx-segments
    HAL::${HAL_TYPE}::RCC
    HAL::${HAL_TYPE}::GPIO
    HAL::${HAL_TYPE}::CORTEX
    HAL::${HAL_TYPE}::UART
    HAL::${HAL_TYPE}::USART
    HAL::${HAL_TYPE}::DMA
    HAL::${HAL_TYPE}::TIM
    HAL::${HAL_TYPE}::TIMEx
    CMSIS::${CMSIS_TYPE}
    STM32::NoSys)

include_directories(./Include/)

set(PROJECT_SOURCES
    src/main.c
    src/led.c
    src/mock.c
    src/key.c
    src/msp.c
    src/usart.c
    # src/tim.c
    src/stm32f4xx_hal_timebase_tim.c)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Dprintf=printf_hook")
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  message("Debug
  mode")
  add_executable(${PROJECT_NAME}-debug ${PROJECT_SOURCES})
  target_link_libraries(${PROJECT_NAME}-debug ${LOCAL_LINKER_SYMBOL})
  add_custom_command(
    TARGET ${PROJECT_NAME}-debug
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_NAME}-debug.elf
            ${PROJECT_NAME}-debug-stripped.elf
    COMMAND ${CMAKE_STRIP} ${PROJECT_NAME}-debug-stripped.elf
    BYPRODUCTS ${PROJECT_NAME}-debug-stripped.elf)
  stm32_print_size_of_target(${PROJECT_NAME}-debug)
  set(burn_target ${PROJECT_NAME}-debug-stripped.elf)
else()
  message("Release
  mode
  ")
  add_executable(${PROJECT_NAME}-release ${PROJECT_SOURCES})
  target_link_libraries(${PROJECT_NAME}-release ${LOCAL_LINKER_SYMBOL})
  add_custom_command(
    TARGET ${PROJECT_NAME}-release
    POST_BUILD
    COMMAND ${CMAKE_STRIP} ${PROJECT_NAME}-release.elf)
  stm32_print_size_of_target(${PROJECT_NAME}-release)
  set(burn_target ${PROJECT_NAME}-release.elf)
endif()

add_custom_target(
  burn
  COMMAND openocd -f ${OPENOCD_SCRIPTS_PATH} -c \"program
          ${CMAKE_CURRENT_BINARY_DIR}/${burn_target} verify reset exit\"
  DEPENDS ${burn_target})
