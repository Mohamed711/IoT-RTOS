################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/ti2/ccsv6/tools/compiler/ti-cgt-arm_15.12.0.LTS

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./Initialize.obj" \
"./Process.obj" \
"./ReSched.obj" \
"./contextSwitch.obj" \
"./main.obj" \
"./mmu.obj" \
"./queue.obj" \
"./realTimeClock.obj" \
"./tm4c123gh6pm_startup_ccs.obj" \
"./TivaDrivers/uart/uart.obj" \
"./TivaDrivers/sysctl/sysctl.obj" \
"./TivaDrivers/interrupt/interrupt.obj" \
"./TivaDrivers/i2c/HAL_i2c_TivaC.obj" \
"./TivaDrivers/i2c/i2c.obj" \
"./TivaDrivers/i2c/i2c_test.obj" \
"./TivaDrivers/gpio/gpio.obj" \
"./TivaDrivers/cpu/cpu.obj" \
"./TivaDrivers/Timer/HAL_Timer_TivaC.obj" \
"./TivaDrivers/Timer/Timer_TivaC.obj" \
"./TivaDrivers/Timer/timer.obj" \
"../tm4c123gh6pm.cmd" \
"../TivaDrivers/rvmdk/driverlib.lib" \
"../TivaDrivers/ccs/Debug/driverlib.lib" \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include TivaDrivers/uart/subdir_vars.mk
-include TivaDrivers/sysctl/subdir_vars.mk
-include TivaDrivers/rvmdk/subdir_vars.mk
-include TivaDrivers/interrupt/subdir_vars.mk
-include TivaDrivers/i2c/subdir_vars.mk
-include TivaDrivers/gpio/subdir_vars.mk
-include TivaDrivers/gcc/subdir_vars.mk
-include TivaDrivers/ewarm/Exe/subdir_vars.mk
-include TivaDrivers/cpu/subdir_vars.mk
-include TivaDrivers/ccs/Debug/subdir_vars.mk
-include TivaDrivers/Timer/subdir_vars.mk
-include subdir_rules.mk
-include TivaDrivers/uart/subdir_rules.mk
-include TivaDrivers/sysctl/subdir_rules.mk
-include TivaDrivers/rvmdk/subdir_rules.mk
-include TivaDrivers/interrupt/subdir_rules.mk
-include TivaDrivers/i2c/subdir_rules.mk
-include TivaDrivers/gpio/subdir_rules.mk
-include TivaDrivers/gcc/subdir_rules.mk
-include TivaDrivers/ewarm/Exe/subdir_rules.mk
-include TivaDrivers/cpu/subdir_rules.mk
-include TivaDrivers/ccs/Debug/subdir_rules.mk
-include TivaDrivers/Timer/subdir_rules.mk
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
Scheduler.out \

EXE_OUTPUTS__QUOTED += \
"Scheduler.out" \

BIN_OUTPUTS += \
Scheduler.hex \

BIN_OUTPUTS__QUOTED += \
"Scheduler.hex" \


# All Target
all: Scheduler.out

# Tool invocations
Scheduler.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(A_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linker'
	"D:/ti2/ccsv6/tools/compiler/ti-cgt-arm_15.12.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --advice:power=all -g --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi -z -m"Scheduler.map" --stack_size=512 --heap_size=0 -i"D:/ti2/ccsv6/tools/compiler/ti-cgt-arm_15.12.0.LTS/lib" -i"D:/ti2/ccsv6/tools/compiler/ti-cgt-arm_15.12.0.LTS/include" --reread_libs --warn_sections --diag_wrap=off --display_error_number --xml_link_info="Scheduler_linkInfo.xml" --rom_model -o "Scheduler.out" $(ORDERED_OBJS) $(A_SRCS)
	@echo 'Finished building target: $@'
	@echo ' '

Scheduler.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: ARM Hex Utility'
	"D:/ti2/ccsv6/tools/compiler/ti-cgt-arm_15.12.0.LTS/bin/armhex"  -o "Scheduler.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "Initialize.pp" "Process.pp" "ReSched.pp" "contextSwitch.pp" "main.pp" "mmu.pp" "queue.pp" "realTimeClock.pp" "tm4c123gh6pm_startup_ccs.pp" "TivaDrivers\uart\uart.pp" "TivaDrivers\sysctl\sysctl.pp" "TivaDrivers\interrupt\interrupt.pp" "TivaDrivers\i2c\HAL_i2c_TivaC.pp" "TivaDrivers\i2c\i2c.pp" "TivaDrivers\i2c\i2c_test.pp" "TivaDrivers\gpio\gpio.pp" "TivaDrivers\cpu\cpu.pp" "TivaDrivers\Timer\HAL_Timer_TivaC.pp" "TivaDrivers\Timer\Timer_TivaC.pp" "TivaDrivers\Timer\timer.pp" 
	-$(RM) "Initialize.obj" "Process.obj" "ReSched.obj" "contextSwitch.obj" "main.obj" "mmu.obj" "queue.obj" "realTimeClock.obj" "tm4c123gh6pm_startup_ccs.obj" "TivaDrivers\uart\uart.obj" "TivaDrivers\sysctl\sysctl.obj" "TivaDrivers\interrupt\interrupt.obj" "TivaDrivers\i2c\HAL_i2c_TivaC.obj" "TivaDrivers\i2c\i2c.obj" "TivaDrivers\i2c\i2c_test.obj" "TivaDrivers\gpio\gpio.obj" "TivaDrivers\cpu\cpu.obj" "TivaDrivers\Timer\HAL_Timer_TivaC.obj" "TivaDrivers\Timer\Timer_TivaC.obj" "TivaDrivers\Timer\timer.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

