################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Drivers/watchdog/HAL_WatchdogTimer.obj: ../Drivers/watchdog/HAL_WatchdogTimer.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"E:/Code Composer/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="E:/Code Composer/ccsv6/tools/compiler/arm_5.1.6/include" -g --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Drivers/watchdog/HAL_WatchdogTimer.pp" --obj_directory="Drivers/watchdog" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/watchdog/watchdog.obj: ../Drivers/watchdog/watchdog.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"E:/Code Composer/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="E:/Code Composer/ccsv6/tools/compiler/arm_5.1.6/include" -g --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Drivers/watchdog/watchdog.pp" --obj_directory="Drivers/watchdog" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/watchdog/watchdog_test.obj: ../Drivers/watchdog/watchdog_test.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"E:/Code Composer/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="E:/Code Composer/ccsv6/tools/compiler/arm_5.1.6/include" -g --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Drivers/watchdog/watchdog_test.pp" --obj_directory="Drivers/watchdog" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


