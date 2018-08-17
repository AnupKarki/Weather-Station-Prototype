################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Transmission.obj: ../Transmission.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccsv7/ccs_base/arm/include" --include_path="C:/Users/i_anu/workspace_v7/EGR536_Project1" --include_path="C:/Users/i_anu/workspace_v7/EGR536_Project1/thirdparty" --include_path="C:/ti/msp/MSP432Ware_3_50_00_02/driverlib/driverlib/MSP432P4xx" --include_path="C:/ti/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=TARGET_IS_MSP432P4XX --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="Transmission.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

bme280.obj: ../bme280.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccsv7/ccs_base/arm/include" --include_path="C:/Users/i_anu/workspace_v7/EGR536_Project1" --include_path="C:/Users/i_anu/workspace_v7/EGR536_Project1/thirdparty" --include_path="C:/ti/msp/MSP432Ware_3_50_00_02/driverlib/driverlib/MSP432P4xx" --include_path="C:/ti/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=TARGET_IS_MSP432P4XX --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="bme280.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

bme280nterfacing.obj: ../bme280nterfacing.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccsv7/ccs_base/arm/include" --include_path="C:/Users/i_anu/workspace_v7/EGR536_Project1" --include_path="C:/Users/i_anu/workspace_v7/EGR536_Project1/thirdparty" --include_path="C:/ti/msp/MSP432Ware_3_50_00_02/driverlib/driverlib/MSP432P4xx" --include_path="C:/ti/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=TARGET_IS_MSP432P4XX --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="bme280nterfacing.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

i2c.obj: ../i2c.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccsv7/ccs_base/arm/include" --include_path="C:/Users/i_anu/workspace_v7/EGR536_Project1" --include_path="C:/Users/i_anu/workspace_v7/EGR536_Project1/thirdparty" --include_path="C:/ti/msp/MSP432Ware_3_50_00_02/driverlib/driverlib/MSP432P4xx" --include_path="C:/ti/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=TARGET_IS_MSP432P4XX --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="i2c.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccsv7/ccs_base/arm/include" --include_path="C:/Users/i_anu/workspace_v7/EGR536_Project1" --include_path="C:/Users/i_anu/workspace_v7/EGR536_Project1/thirdparty" --include_path="C:/ti/msp/MSP432Ware_3_50_00_02/driverlib/driverlib/MSP432P4xx" --include_path="C:/ti/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=TARGET_IS_MSP432P4XX --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="main.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

msp432_spi.obj: ../msp432_spi.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccsv7/ccs_base/arm/include" --include_path="C:/Users/i_anu/workspace_v7/EGR536_Project1" --include_path="C:/Users/i_anu/workspace_v7/EGR536_Project1/thirdparty" --include_path="C:/ti/msp/MSP432Ware_3_50_00_02/driverlib/driverlib/MSP432P4xx" --include_path="C:/ti/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=TARGET_IS_MSP432P4XX --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="msp432_spi.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

msprf24.obj: ../msprf24.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccsv7/ccs_base/arm/include" --include_path="C:/Users/i_anu/workspace_v7/EGR536_Project1" --include_path="C:/Users/i_anu/workspace_v7/EGR536_Project1/thirdparty" --include_path="C:/ti/msp/MSP432Ware_3_50_00_02/driverlib/driverlib/MSP432P4xx" --include_path="C:/ti/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=TARGET_IS_MSP432P4XX --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="msprf24.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

printfOverride.obj: ../printfOverride.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccsv7/ccs_base/arm/include" --include_path="C:/Users/i_anu/workspace_v7/EGR536_Project1" --include_path="C:/Users/i_anu/workspace_v7/EGR536_Project1/thirdparty" --include_path="C:/ti/msp/MSP432Ware_3_50_00_02/driverlib/driverlib/MSP432P4xx" --include_path="C:/ti/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=TARGET_IS_MSP432P4XX --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="printfOverride.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

rtcInterface.obj: ../rtcInterface.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccsv7/ccs_base/arm/include" --include_path="C:/Users/i_anu/workspace_v7/EGR536_Project1" --include_path="C:/Users/i_anu/workspace_v7/EGR536_Project1/thirdparty" --include_path="C:/ti/msp/MSP432Ware_3_50_00_02/driverlib/driverlib/MSP432P4xx" --include_path="C:/ti/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=TARGET_IS_MSP432P4XX --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="rtcInterface.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

spiDriver.obj: ../spiDriver.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccsv7/ccs_base/arm/include" --include_path="C:/Users/i_anu/workspace_v7/EGR536_Project1" --include_path="C:/Users/i_anu/workspace_v7/EGR536_Project1/thirdparty" --include_path="C:/ti/msp/MSP432Ware_3_50_00_02/driverlib/driverlib/MSP432P4xx" --include_path="C:/ti/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=TARGET_IS_MSP432P4XX --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="spiDriver.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

startup_msp432p401r_ccs.obj: ../startup_msp432p401r_ccs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccsv7/ccs_base/arm/include" --include_path="C:/Users/i_anu/workspace_v7/EGR536_Project1" --include_path="C:/Users/i_anu/workspace_v7/EGR536_Project1/thirdparty" --include_path="C:/ti/msp/MSP432Ware_3_50_00_02/driverlib/driverlib/MSP432P4xx" --include_path="C:/ti/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=TARGET_IS_MSP432P4XX --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="startup_msp432p401r_ccs.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

supportfunctions.obj: ../supportfunctions.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccsv7/ccs_base/arm/include" --include_path="C:/Users/i_anu/workspace_v7/EGR536_Project1" --include_path="C:/Users/i_anu/workspace_v7/EGR536_Project1/thirdparty" --include_path="C:/ti/msp/MSP432Ware_3_50_00_02/driverlib/driverlib/MSP432P4xx" --include_path="C:/ti/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=TARGET_IS_MSP432P4XX --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="supportfunctions.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

system_msp432p401r.obj: ../system_msp432p401r.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccsv7/ccs_base/arm/include" --include_path="C:/Users/i_anu/workspace_v7/EGR536_Project1" --include_path="C:/Users/i_anu/workspace_v7/EGR536_Project1/thirdparty" --include_path="C:/ti/msp/MSP432Ware_3_50_00_02/driverlib/driverlib/MSP432P4xx" --include_path="C:/ti/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=TARGET_IS_MSP432P4XX --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="system_msp432p401r.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


