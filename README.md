# STM32F407_Dev

STM32F407 开发学习项目。

## 环境配置

1. 环境搭建使用 [ObKo/stm32-cmake](https://github.com/ObKo/stm32-cmake)，在 cmake 目录中。
2. 依赖 [STMicroelectronics/STM32CubeF4](https://github.com/STMicroelectronics/STM32CubeF4)。
3. 依赖 [openocd](https://openocd.org/)。
4. 交叉编译器：[Arm GNU Toolchain Downloads – Arm Developer](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)
5. 工程环境变量添加：
   ```shell
   > export STM32_CUBE_F4_PATH=path/to/STM32CubeF4
   > export STM32_TOOLCHAIN_PATH=~/workspace/arm/arm-gnu-toolchain-12.2.mpacbti-rel1-x86_64-arm-none-eabi/bin/
   > export TARGET_TRIPLET=arm-none-eabi
   ```

## 烧写

1. 烧写命令：`ninja/make burn`
