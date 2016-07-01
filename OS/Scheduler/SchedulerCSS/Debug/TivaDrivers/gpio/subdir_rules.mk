################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
TivaDrivers/gpio/gpio.obj: ../TivaDrivers/gpio/gpio.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/ti2/ccsv6/tools/compiler/ti-cgt-arm_15.12.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/ti2/ccsv6/tools/compiler/ti-cgt-arm_15.12.0.LTS/include" --advice:power=all -g --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="TivaDrivers/gpio/gpio.pp" --obj_directory="TivaDrivers/gpio" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


