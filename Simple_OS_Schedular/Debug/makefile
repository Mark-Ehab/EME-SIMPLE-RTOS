################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Simple_OS_Schedular.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Simple_OS_Schedular.list \

OBJCOPY_HEX += \
Simple_OS_Schedular.hex \

OBJCOPY_BIN += \
Simple_OS_Schedular.bin \


# All Target
all: Simple_OS_Schedular.elf secondary-outputs

# Tool invocations
Simple_OS_Schedular.elf: $(OBJS) $(USER_OBJS) E:\ARM-Workspace\Simple_OS_Schedular\STM32F103C8TX_FLASH.ld
	arm-none-eabi-gcc -o "Simple_OS_Schedular.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"E:\ARM-Workspace\Simple_OS_Schedular\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Simple_OS_Schedular.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Simple_OS_Schedular.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Simple_OS_Schedular.list"
	@echo 'Finished building: $@'
	@echo ' '

Simple_OS_Schedular.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "Simple_OS_Schedular.hex"
	@echo 'Finished building: $@'
	@echo ' '

Simple_OS_Schedular.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Simple_OS_Schedular.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
