################################################################################
# MRS Version: 2.2.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/USBLIB/CONFIG/hw_config.c \
../User/USBLIB/CONFIG/usb_desc.c \
../User/USBLIB/CONFIG/usb_endp.c \
../User/USBLIB/CONFIG/usb_istr.c \
../User/USBLIB/CONFIG/usb_prop.c \
../User/USBLIB/CONFIG/usb_pwr.c 

C_DEPS += \
./User/USBLIB/CONFIG/hw_config.d \
./User/USBLIB/CONFIG/usb_desc.d \
./User/USBLIB/CONFIG/usb_endp.d \
./User/USBLIB/CONFIG/usb_istr.d \
./User/USBLIB/CONFIG/usb_prop.d \
./User/USBLIB/CONFIG/usb_pwr.d 

OBJS += \
./User/USBLIB/CONFIG/hw_config.o \
./User/USBLIB/CONFIG/usb_desc.o \
./User/USBLIB/CONFIG/usb_endp.o \
./User/USBLIB/CONFIG/usb_istr.o \
./User/USBLIB/CONFIG/usb_prop.o \
./User/USBLIB/CONFIG/usb_pwr.o 


EXPANDS += \
./User/USBLIB/CONFIG/hw_config.c.234r.expand \
./User/USBLIB/CONFIG/usb_desc.c.234r.expand \
./User/USBLIB/CONFIG/usb_endp.c.234r.expand \
./User/USBLIB/CONFIG/usb_istr.c.234r.expand \
./User/USBLIB/CONFIG/usb_prop.c.234r.expand \
./User/USBLIB/CONFIG/usb_pwr.c.234r.expand 



# Each subdirectory must supply rules for building sources it contributes
User/USBLIB/CONFIG/%.o: ../User/USBLIB/CONFIG/%.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"c:/MRS_DATA/workspace/SD_Card_Reader_USBMSC/SD_Card_Reader_USBMS/Debug" -I"c:/MRS_DATA/workspace/SD_Card_Reader_USBMSC/SD_Card_Reader_USBMS/Core" -I"c:/MRS_DATA/workspace/SD_Card_Reader_USBMSC/SD_Card_Reader_USBMS/User" -I"c:/MRS_DATA/workspace/SD_Card_Reader_USBMSC/SD_Card_Reader_USBMS/Peripheral/inc" -I"c:/MRS_DATA/workspace/SD_Card_Reader_USBMSC/SD_Card_Reader_USBMS/User/USBLIB/CONFIG" -I"c:/MRS_DATA/workspace/SD_Card_Reader_USBMSC/SD_Card_Reader_USBMS/User/USBLIB/USB-Driver/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

