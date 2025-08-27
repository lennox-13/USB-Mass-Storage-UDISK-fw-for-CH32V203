################################################################################
# MRS Version: 2.2.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/SPI_SD.c \
../User/SW_UDISK.c \
../User/ch32v20x_it.c \
../User/main.c \
../User/system_ch32v20x.c 

C_DEPS += \
./User/SPI_SD.d \
./User/SW_UDISK.d \
./User/ch32v20x_it.d \
./User/main.d \
./User/system_ch32v20x.d 

OBJS += \
./User/SPI_SD.o \
./User/SW_UDISK.o \
./User/ch32v20x_it.o \
./User/main.o \
./User/system_ch32v20x.o 


EXPANDS += \
./User/SPI_SD.c.234r.expand \
./User/SW_UDISK.c.234r.expand \
./User/ch32v20x_it.c.234r.expand \
./User/main.c.234r.expand \
./User/system_ch32v20x.c.234r.expand 



# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"c:/MRS_DATA/workspace/SD_Card_Reader_USBMSC/SD_Card_Reader_USBMS/Debug" -I"c:/MRS_DATA/workspace/SD_Card_Reader_USBMSC/SD_Card_Reader_USBMS/Core" -I"c:/MRS_DATA/workspace/SD_Card_Reader_USBMSC/SD_Card_Reader_USBMS/User" -I"c:/MRS_DATA/workspace/SD_Card_Reader_USBMSC/SD_Card_Reader_USBMS/Peripheral/inc" -I"c:/MRS_DATA/workspace/SD_Card_Reader_USBMSC/SD_Card_Reader_USBMS/User/USBLIB/CONFIG" -I"c:/MRS_DATA/workspace/SD_Card_Reader_USBMSC/SD_Card_Reader_USBMS/User/USBLIB/USB-Driver/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

