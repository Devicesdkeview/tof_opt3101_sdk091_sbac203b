################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
MSP430/%.obj: ../MSP430/%.cpp $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-msp430_21.6.0.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccs1100/ccs/ccs_base/msp430/include" --include_path="C:/Users/a0491839/Downloads/sbac203a (1)/release_0p9p1/OPT3101_SDK" --include_path="C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-msp430_21.6.0.LTS/include" --advice:power="all" --define=__MSP430F5529__ -g --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="MSP430/$(basename $(<F)).d_raw" --obj_directory="MSP430" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

MSP430/%.obj: ../MSP430/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-msp430_21.6.0.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccs1100/ccs/ccs_base/msp430/include" --include_path="C:/Users/a0491839/Downloads/sbac203a (1)/release_0p9p1/OPT3101_SDK" --include_path="C:/ti/ccs1100/ccs/tools/compiler/ti-cgt-msp430_21.6.0.LTS/include" --advice:power="all" --define=__MSP430F5529__ -g --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="MSP430/$(basename $(<F)).d_raw" --obj_directory="MSP430" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


