################################################################################
# MRS Version: 1.9.0
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP/MAIN.c \
../APP/app_ble.c \
../APP/app_usb.c \
../APP/keyin.c \
../APP/led.c \
../APP/protocol.c \
../APP/usercfg.c 

OBJS += \
./APP/MAIN.o \
./APP/app_ble.o \
./APP/app_usb.o \
./APP/keyin.o \
./APP/led.o \
./APP/protocol.o \
./APP/usercfg.o 

C_DEPS += \
./APP/MAIN.d \
./APP/app_ble.d \
./APP/app_usb.d \
./APP/keyin.d \
./APP/led.d \
./APP/protocol.d \
./APP/usercfg.d 


# Each subdirectory must supply rules for building sources it contributes
APP/%.o: ../APP/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -I"C:\Users\19156\Desktop\SRC\Startup" -I"C:\Users\19156\Desktop\DualModeKeyboard\SDK\APP\include" -I"C:\Users\19156\Desktop\DualModeKeyboard\SDK\Profile\include" -I"C:\Users\19156\Desktop\SRC\StdPeriphDriver\inc" -I"C:\Users\19156\Desktop\DualModeKeyboard\HAL\include" -I"C:\Users\19156\Desktop\SRC\Ld" -I"C:\Users\19156\Desktop\DualModeKeyboard\LIB" -I"C:\Users\19156\Desktop\SRC\RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

