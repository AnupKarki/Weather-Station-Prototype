################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
thirdparty/fatfs/port/mmc-msp432P401r.obj: ../thirdparty/fatfs/port/mmc-msp432P401r.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccsv7/ccs_base/arm/include" --include_path="C:/Users/i_anu/workspace_v7/EGR536_Project1" --include_path="C:/Users/i_anu/workspace_v7/EGR536_Project1/thirdparty" --include_path="C:/ti/msp/MSP432Ware_3_50_00_02/driverlib/driverlib/MSP432P4xx" --include_path="C:/ti/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=TARGET_IS_MSP432P4XX --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="thirdparty/fatfs/port/mmc-msp432P401r.d" --obj_directory="thirdparty/fatfs/port" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


