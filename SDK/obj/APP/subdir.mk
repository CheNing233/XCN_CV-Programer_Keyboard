################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP/MAIN.c \
../APP/app_ble.c \
../APP/app_usb.c \
../APP/keyin.c \
../APP/ledout.c \
../APP/motorout.c \
../APP/protocol.c \
../APP/settingctrl.c \
../APP/usercfg.c 

OBJS += \
./APP/MAIN.o \
./APP/app_ble.o \
./APP/app_usb.o \
./APP/keyin.o \
./APP/ledout.o \
./APP/motorout.o \
./APP/protocol.o \
./APP/settingctrl.o \
./APP/usercfg.o 

C_DEPS += \
./APP/MAIN.d \
./APP/app_ble.d \
./APP/app_usb.d \
./APP/keyin.d \
./APP/ledout.d \
./APP/motorout.d \
./APP/protocol.d \
./APP/settingctrl.d \
./APP/usercfg.d 


# Each subdirectory must supply rules for building sources it contributes
APP/%.o: ../APP/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused  -g -I"C:\Users\19156\Desktop\DualModeKeyboard\SDK\LIB" -I"C:\Users\19156\Desktop\DualModeKeyboard\SDK\StdPeriphDriver\inc" -I"C:\Users\19156\Desktop\DualModeKeyboard\SDK\HAL\include" -I"C:\Users\19156\Desktop\DualModeKeyboard\SDK\Profile\include" -I"C:\Users\19156\Desktop\DualModeKeyboard\SDK\APP\include" -I"C:\Users\19156\Desktop\DualModeKeyboard\SDK\RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

