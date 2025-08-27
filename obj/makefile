################################################################################
# MRS Version: 2.2.0
# Automatically-generated file. Do not edit!
################################################################################
-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/USBLIB/USB-Driver/src/subdir.mk
-include User/USBLIB/CONFIG/subdir.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
-include Debug/subdir.mk
-include Core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
SD_Card_Reader_USBMS.hex \

SECONDARY_LIST += \
SD_Card_Reader_USBMS.lst \

SECONDARY_SIZE += \
SD_Card_Reader_USBMS.siz \


# All Target
all: 
	$(MAKE) --no-print-directory main-build 

main-build: SD_Card_Reader_USBMS.elf secondary-outputs

# Tool invocations
SD_Card_Reader_USBMS.elf: $(OBJS) $(USER_OBJS)
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -T "c:/MRS_DATA/workspace/SD_Card_Reader_USBMSC/SD_Card_Reader_USBMS/Ld/Link.ld" -nostartfiles -Xlinker --gc-sections -Xlinker --print-memory-usage -Wl,-Map,"SD_Card_Reader_USBMS.map" --specs=nano.specs --specs=nosys.specs -o "SD_Card_Reader_USBMS.elf" $(OBJS)  $(LIBS)
SD_Card_Reader_USBMS.hex: SD_Card_Reader_USBMS.elf
	@	riscv-none-embed-objcopy -O ihex "SD_Card_Reader_USBMS.elf" "SD_Card_Reader_USBMS.hex"
SD_Card_Reader_USBMS.lst: SD_Card_Reader_USBMS.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble -M xw "SD_Card_Reader_USBMS.elf" > "SD_Card_Reader_USBMS.lst"
SD_Card_Reader_USBMS.siz: SD_Card_Reader_USBMS.elf
	riscv-none-embed-size --format=berkeley "SD_Card_Reader_USBMS.elf"

# Other Targets
clean:
	-$(RM) $(OBJS) $(EXPANDS) $(CALLGRAPH_DOT) $(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(S_DEPS)$(S_UPPER_DEPS)$(ASM_DEPS)$(ASM_UPPER_DEPS)$(C_DEPS) SD_Card_Reader_USBMS.elf

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets