################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := E:/Code Composer/ccsv6/tools/compiler/arm_5.1.6

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./main.obj" \
"./tm4c123gh6pm_startup_ccs.obj" \
"./Drivers/watchdog/HAL_WatchdogTimer.obj" \
"./Drivers/watchdog/watchdog.obj" \
"./Drivers/watchdog/watchdog_test.obj" \
"./Drivers/uart/HAL_UART.obj" \
"./Drivers/uart/uart.obj" \
"./Drivers/uart/uartTest.obj" \
"./Drivers/timer/HAL_Timer_TivaC.obj" \
"./Drivers/timer/Timer_TivaC.obj" \
"./Drivers/timer/timer.obj" \
"./Drivers/sysctl/sysctl.obj" \
"./Drivers/interrupt/interrupt.obj" \
"./Drivers/i2c/HAL_i2c_TivaC.obj" \
"./Drivers/i2c/i2c.obj" \
"./Drivers/i2c/i2c_test.obj" \
"./Drivers/gpio/gpio.obj" \
"./Drivers/cpu/cpu.obj" \
"./Drivers/adc/ADC_HAL_TIVA.obj" \
"./Drivers/adc/adc.obj" \
"./Drivers/adc/adc_test.obj" \
"../tm4c123gh6pm.cmd" \
"../Drivers/rvmdk/driverlib.lib" \
"../Drivers/ccs/Debug/driverlib.lib" \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include Drivers/watchdog/subdir_vars.mk
-include Drivers/uart/subdir_vars.mk
-include Drivers/timer/subdir_vars.mk
-include Drivers/sysctl/subdir_vars.mk
-include Drivers/rvmdk/subdir_vars.mk
-include Drivers/interrupt/subdir_vars.mk
-include Drivers/i2c/subdir_vars.mk
-include Drivers/gpio/subdir_vars.mk
-include Drivers/gcc/subdir_vars.mk
-include Drivers/ewarm/Exe/subdir_vars.mk
-include Drivers/cpu/subdir_vars.mk
-include Drivers/ccs/Debug/subdir_vars.mk
-include Drivers/adc/subdir_vars.mk
-include subdir_rules.mk
-include Drivers/watchdog/subdir_rules.mk
-include Drivers/uart/subdir_rules.mk
-include Drivers/timer/subdir_rules.mk
-include Drivers/sysctl/subdir_rules.mk
-include Drivers/rvmdk/subdir_rules.mk
-include Drivers/interrupt/subdir_rules.mk
-include Drivers/i2c/subdir_rules.mk
-include Drivers/gpio/subdir_rules.mk
-include Drivers/gcc/subdir_rules.mk
-include Drivers/ewarm/Exe/subdir_rules.mk
-include Drivers/cpu/subdir_rules.mk
-include Drivers/ccs/Debug/subdir_rules.mk
-include Drivers/adc/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
TivaHAL.out \

EXE_OUTPUTS__QUOTED += \
"TivaHAL.out" \

BIN_OUTPUTS += \
TivaHAL.hex \

BIN_OUTPUTS__QUOTED += \
"TivaHAL.hex" \


# All Target
all: TivaHAL.out

# Tool invocations
TivaHAL.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(A_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linker'
	"E:/Code Composer/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -g --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --display_error_number --diag_warning=225 --diag_wrap=off -z -m"TivaHAL.map" --heap_size=0 --stack_size=512 -i"E:/Code Composer/ccsv6/tools/compiler/arm_5.1.6/lib" -i"E:/Code Composer/ccsv6/tools/compiler/arm_5.1.6/include" --reread_libs --warn_sections --display_error_number --diag_wrap=off --xml_link_info="TivaHAL_linkInfo.xml" --rom_model -o "TivaHAL.out" $(ORDERED_OBJS) $(A_SRCS)
	@echo 'Finished building target: $@'
	@echo ' '

TivaHAL.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: ARM Hex Utility'
	"E:/Code Composer/ccsv6/tools/compiler/arm_5.1.6/bin/armhex"  -o "TivaHAL.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "main.pp" "tm4c123gh6pm_startup_ccs.pp" "Drivers\watchdog\HAL_WatchdogTimer.pp" "Drivers\watchdog\watchdog.pp" "Drivers\watchdog\watchdog_test.pp" "Drivers\uart\HAL_UART.pp" "Drivers\uart\uart.pp" "Drivers\uart\uartTest.pp" "Drivers\timer\HAL_Timer_TivaC.pp" "Drivers\timer\Timer_TivaC.pp" "Drivers\timer\timer.pp" "Drivers\sysctl\sysctl.pp" "Drivers\interrupt\interrupt.pp" "Drivers\i2c\HAL_i2c_TivaC.pp" "Drivers\i2c\i2c.pp" "Drivers\i2c\i2c_test.pp" "Drivers\gpio\gpio.pp" "Drivers\cpu\cpu.pp" "Drivers\adc\ADC_HAL_TIVA.pp" "Drivers\adc\adc.pp" "Drivers\adc\adc_test.pp" 
	-$(RM) "main.obj" "tm4c123gh6pm_startup_ccs.obj" "Drivers\watchdog\HAL_WatchdogTimer.obj" "Drivers\watchdog\watchdog.obj" "Drivers\watchdog\watchdog_test.obj" "Drivers\uart\HAL_UART.obj" "Drivers\uart\uart.obj" "Drivers\uart\uartTest.obj" "Drivers\timer\HAL_Timer_TivaC.obj" "Drivers\timer\Timer_TivaC.obj" "Drivers\timer\timer.obj" "Drivers\sysctl\sysctl.obj" "Drivers\interrupt\interrupt.obj" "Drivers\i2c\HAL_i2c_TivaC.obj" "Drivers\i2c\i2c.obj" "Drivers\i2c\i2c_test.obj" "Drivers\gpio\gpio.obj" "Drivers\cpu\cpu.obj" "Drivers\adc\ADC_HAL_TIVA.obj" "Drivers\adc\adc.obj" "Drivers\adc\adc_test.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

