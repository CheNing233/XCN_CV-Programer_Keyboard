################################################################################
# MRS Version: 1.9.0
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/ENCODER.c \
../HAL/MCU.c \
../HAL/OLED.c \
../HAL/RTC.c 

OBJS += \
./HAL/ENCODER.o \
./HAL/MCU.o \
./HAL/OLED.o \
./HAL/RTC.o 

C_DEPS += \
./HAL/ENCODER.d \
./HAL/MCU.d \
./HAL/OLED.d \
./HAL/RTC.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/%.o: ../HAL/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -I"C:\Users\19156\Desktop\DualModeKeyboard\SDK\Startup" -I"C:\Users\19156\Desktop\DualModeKeyboard\SDK\APP\include" -I"C:\Users\19156\Desktop\DualModeKeyboard\SDK\Profile\include" -I"C:\Users\19156\Desktop\DualModeKeyboard\SDK\StdPeriphDriver\inc" -I"C:\Users\19156\Desktop\DualModeKeyboard\SDK\HAL\include" -I"C:\Users\19156\Desktop\DualModeKeyboard\SDK\Ld" -I"C:\Users\19156\Desktop\DualModeKeyboard\SDK\LIB" -I"C:\Users\19156\Desktop\DualModeKeyboard\SDK\RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

