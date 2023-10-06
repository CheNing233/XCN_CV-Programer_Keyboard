################################################################################
# MRS Version: 1.9.0
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/19156/Desktop/DualModeKeyboard/HAL/MCU.c \
C:/Users/19156/Desktop/DualModeKeyboard/HAL/RTC.c \
C:/Users/19156/Desktop/DualModeKeyboard/HAL/SLEEP.c 

OBJS += \
./HAL/MCU.o \
./HAL/RTC.o \
./HAL/SLEEP.o 

C_DEPS += \
./HAL/MCU.d \
./HAL/RTC.d \
./HAL/SLEEP.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/MCU.o: C:/Users/19156/Desktop/DualModeKeyboard/HAL/MCU.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -I"C:\Users\19156\Desktop\SRC\Startup" -I"C:\Users\19156\Desktop\DualModeKeyboard\SDK\APP\include" -I"C:\Users\19156\Desktop\DualModeKeyboard\SDK\Profile\include" -I"C:\Users\19156\Desktop\SRC\StdPeriphDriver\inc" -I"C:\Users\19156\Desktop\DualModeKeyboard\HAL\include" -I"C:\Users\19156\Desktop\SRC\Ld" -I"C:\Users\19156\Desktop\DualModeKeyboard\LIB" -I"C:\Users\19156\Desktop\SRC\RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
HAL/RTC.o: C:/Users/19156/Desktop/DualModeKeyboard/HAL/RTC.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -I"C:\Users\19156\Desktop\SRC\Startup" -I"C:\Users\19156\Desktop\DualModeKeyboard\SDK\APP\include" -I"C:\Users\19156\Desktop\DualModeKeyboard\SDK\Profile\include" -I"C:\Users\19156\Desktop\SRC\StdPeriphDriver\inc" -I"C:\Users\19156\Desktop\DualModeKeyboard\HAL\include" -I"C:\Users\19156\Desktop\SRC\Ld" -I"C:\Users\19156\Desktop\DualModeKeyboard\LIB" -I"C:\Users\19156\Desktop\SRC\RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
HAL/SLEEP.o: C:/Users/19156/Desktop/DualModeKeyboard/HAL/SLEEP.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -I"C:\Users\19156\Desktop\SRC\Startup" -I"C:\Users\19156\Desktop\DualModeKeyboard\SDK\APP\include" -I"C:\Users\19156\Desktop\DualModeKeyboard\SDK\Profile\include" -I"C:\Users\19156\Desktop\SRC\StdPeriphDriver\inc" -I"C:\Users\19156\Desktop\DualModeKeyboard\HAL\include" -I"C:\Users\19156\Desktop\SRC\Ld" -I"C:\Users\19156\Desktop\DualModeKeyboard\LIB" -I"C:\Users\19156\Desktop\SRC\RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

