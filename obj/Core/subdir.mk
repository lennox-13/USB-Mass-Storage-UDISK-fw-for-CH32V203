################################################################################
# MRS Version: 2.2.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/core_riscv.c 

C_DEPS += \
./Core/core_riscv.d 

OBJS += \
./Core/core_riscv.o 


EXPANDS += \
./Core/core_riscv.c.234r.expand 



# Each subdirectory must supply rules for building sources it contributes
Core/%.o: ../Core/%.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"c:/MRS_DATA/workspace/SD_Card_Reader_USBMSC/SD_Card_Reader_USBMS/Debug" -I"c:/MRS_DATA/workspace/SD_Card_Reader_USBMSC/SD_Card_Reader_USBMS/Core" -I"c:/MRS_DATA/workspace/SD_Card_Reader_USBMSC/SD_Card_Reader_USBMS/User" -I"c:/MRS_DATA/workspace/SD_Card_Reader_USBMSC/SD_Card_Reader_USBMS/Peripheral/inc" -I"c:/MRS_DATA/workspace/SD_Card_Reader_USBMSC/SD_Card_Reader_USBMS/User/USBLIB/CONFIG" -I"c:/MRS_DATA/workspace/SD_Card_Reader_USBMSC/SD_Card_Reader_USBMS/User/USBLIB/USB-Driver/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

