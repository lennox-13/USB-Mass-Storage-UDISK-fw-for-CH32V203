################################################################################
# MRS Version: 2.2.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/USBLIB/USB-Driver/src/usb_core.c \
../User/USBLIB/USB-Driver/src/usb_init.c \
../User/USBLIB/USB-Driver/src/usb_int.c \
../User/USBLIB/USB-Driver/src/usb_mem.c \
../User/USBLIB/USB-Driver/src/usb_regs.c \
../User/USBLIB/USB-Driver/src/usb_sil.c 

C_DEPS += \
./User/USBLIB/USB-Driver/src/usb_core.d \
./User/USBLIB/USB-Driver/src/usb_init.d \
./User/USBLIB/USB-Driver/src/usb_int.d \
./User/USBLIB/USB-Driver/src/usb_mem.d \
./User/USBLIB/USB-Driver/src/usb_regs.d \
./User/USBLIB/USB-Driver/src/usb_sil.d 

OBJS += \
./User/USBLIB/USB-Driver/src/usb_core.o \
./User/USBLIB/USB-Driver/src/usb_init.o \
./User/USBLIB/USB-Driver/src/usb_int.o \
./User/USBLIB/USB-Driver/src/usb_mem.o \
./User/USBLIB/USB-Driver/src/usb_regs.o \
./User/USBLIB/USB-Driver/src/usb_sil.o 


EXPANDS += \
./User/USBLIB/USB-Driver/src/usb_core.c.234r.expand \
./User/USBLIB/USB-Driver/src/usb_init.c.234r.expand \
./User/USBLIB/USB-Driver/src/usb_int.c.234r.expand \
./User/USBLIB/USB-Driver/src/usb_mem.c.234r.expand \
./User/USBLIB/USB-Driver/src/usb_regs.c.234r.expand \
./User/USBLIB/USB-Driver/src/usb_sil.c.234r.expand 



# Each subdirectory must supply rules for building sources it contributes
User/USBLIB/USB-Driver/src/%.o: ../User/USBLIB/USB-Driver/src/%.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"c:/MRS_DATA/workspace/SD_Card_Reader_USBMSC/SD_Card_Reader_USBMS/Debug" -I"c:/MRS_DATA/workspace/SD_Card_Reader_USBMSC/SD_Card_Reader_USBMS/Core" -I"c:/MRS_DATA/workspace/SD_Card_Reader_USBMSC/SD_Card_Reader_USBMS/User" -I"c:/MRS_DATA/workspace/SD_Card_Reader_USBMSC/SD_Card_Reader_USBMS/Peripheral/inc" -I"c:/MRS_DATA/workspace/SD_Card_Reader_USBMSC/SD_Card_Reader_USBMS/User/USBLIB/CONFIG" -I"c:/MRS_DATA/workspace/SD_Card_Reader_USBMSC/SD_Card_Reader_USBMS/User/USBLIB/USB-Driver/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

