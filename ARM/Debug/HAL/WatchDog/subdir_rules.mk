################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
HAL/WatchDog/HAL_WatchdogTimer.obj: ../HAL/WatchDog/HAL_WatchdogTimer.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/include" --include_path="C:/Users/Reem/Desktop/IoT-RTOS/ARM" -g --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="HAL/WatchDog/HAL_WatchdogTimer.pp" --obj_directory="HAL/WatchDog" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


