################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/NMT/Spring2023/EE481_capstone/STM_disco/LANL_Neutron_DSP/Drivers/BSP/STM32469I-Discovery/stm32469i_discovery.c \
D:/NMT/Spring2023/EE481_capstone/STM_disco/LANL_Neutron_DSP/Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_qspi.c \
D:/NMT/Spring2023/EE481_capstone/STM_disco/LANL_Neutron_DSP/Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_sdram.c \
D:/NMT/Spring2023/EE481_capstone/STM_disco/LANL_Neutron_DSP/Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_ts.c 

C_DEPS += \
./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery.d \
./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_qspi.d \
./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_sdram.d \
./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_ts.d 

OBJS += \
./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery.o \
./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_qspi.o \
./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_sdram.o \
./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_ts.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32469I-Discovery/stm32469i_discovery.o: D:/NMT/Spring2023/EE481_capstone/STM_disco/LANL_Neutron_DSP/Drivers/BSP/STM32469I-Discovery/stm32469i_discovery.c Drivers/BSP/STM32469I-Discovery/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F469xx -DDEBUG -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../TouchGFX/target -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../TouchGFX/App -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../TouchGFX/target/generated -I../../Drivers/BSP/Components/Common -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/BSP/STM32469I-Discovery -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../TouchGFX/generated/videos/include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_qspi.o: D:/NMT/Spring2023/EE481_capstone/STM_disco/LANL_Neutron_DSP/Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_qspi.c Drivers/BSP/STM32469I-Discovery/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F469xx -DDEBUG -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../TouchGFX/target -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../TouchGFX/App -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../TouchGFX/target/generated -I../../Drivers/BSP/Components/Common -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/BSP/STM32469I-Discovery -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../TouchGFX/generated/videos/include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_sdram.o: D:/NMT/Spring2023/EE481_capstone/STM_disco/LANL_Neutron_DSP/Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_sdram.c Drivers/BSP/STM32469I-Discovery/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F469xx -DDEBUG -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../TouchGFX/target -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../TouchGFX/App -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../TouchGFX/target/generated -I../../Drivers/BSP/Components/Common -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/BSP/STM32469I-Discovery -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../TouchGFX/generated/videos/include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_ts.o: D:/NMT/Spring2023/EE481_capstone/STM_disco/LANL_Neutron_DSP/Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_ts.c Drivers/BSP/STM32469I-Discovery/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F469xx -DDEBUG -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../TouchGFX/target -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../TouchGFX/App -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../TouchGFX/target/generated -I../../Drivers/BSP/Components/Common -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/BSP/STM32469I-Discovery -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../TouchGFX/generated/videos/include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-STM32469I-2d-Discovery

clean-Drivers-2f-BSP-2f-STM32469I-2d-Discovery:
	-$(RM) ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery.d ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery.o ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery.su ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_qspi.d ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_qspi.o ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_qspi.su ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_sdram.d ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_sdram.o ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_sdram.su ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_ts.d ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_ts.o ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_ts.su

.PHONY: clean-Drivers-2f-BSP-2f-STM32469I-2d-Discovery

