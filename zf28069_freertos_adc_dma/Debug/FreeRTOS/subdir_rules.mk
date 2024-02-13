################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/list.obj: C:/Users/Eduardo/workspace_v12/blinky_f28069/FreeRTOS/list.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/Users/Eduardo/workspace_v12/zf28069_freertos_adc_dma" --include_path="C:/Users/Eduardo/Documents/GitHub/freertos_c28x/FreeRTOS/include" --include_path="C:/Users/Eduardo/Documents/GitHub/freertos_c28x/FreeRTOS" --include_path="C:/Users/Eduardo/Documents/GitHub/freertos_c28x/FreeRTOS/portable" --include_path="C:/Users/Eduardo/workspace_v12/zf28069_freertos_adc_dma/Methods/headers" --include_path="C:/Users/Eduardo/workspace_v12/zf28069_freertos_adc_dma/Methods/functions" --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="C:/ti/C2000Ware_DigitalPower_SDK_5_00_01_00/c2000ware/device_support/f2806x/headers/include" --include_path="C:/ti/C2000Ware_DigitalPower_SDK_5_00_01_00/c2000ware/device_support/f2806x/common/include" --include_path="C:/ti/C2000Ware_DigitalPower_SDK_5_00_01_00/c2000ware/libraries/math/IQmath/c28/include" --include_path="C:/ti/C2000Ware_DigitalPower_SDK_5_00_01_00/c2000ware/libraries/math/FPUfastRTS/c28/include" --include_path="C:/Users/Eduardo/workspace_v12/blinky_f28069/FreeRTOS/port" --preinclude="C:/Users/Eduardo/workspace_v12/zf28069_freertos_adc_dma/Methods/headers/teste.h" --define=_DEBUG --define=LARGE_MODEL -g --diag_suppress=10063 --diag_warning=225 --issue_remarks --verbose_diagnostics --quiet --abi=coffabi --preproc_with_compile --preproc_dependency="FreeRTOS/$(basename $(<F)).d_raw" --obj_directory="FreeRTOS" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

FreeRTOS/queue.obj: C:/Users/Eduardo/workspace_v12/blinky_f28069/FreeRTOS/queue.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/Users/Eduardo/workspace_v12/zf28069_freertos_adc_dma" --include_path="C:/Users/Eduardo/Documents/GitHub/freertos_c28x/FreeRTOS/include" --include_path="C:/Users/Eduardo/Documents/GitHub/freertos_c28x/FreeRTOS" --include_path="C:/Users/Eduardo/Documents/GitHub/freertos_c28x/FreeRTOS/portable" --include_path="C:/Users/Eduardo/workspace_v12/zf28069_freertos_adc_dma/Methods/headers" --include_path="C:/Users/Eduardo/workspace_v12/zf28069_freertos_adc_dma/Methods/functions" --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="C:/ti/C2000Ware_DigitalPower_SDK_5_00_01_00/c2000ware/device_support/f2806x/headers/include" --include_path="C:/ti/C2000Ware_DigitalPower_SDK_5_00_01_00/c2000ware/device_support/f2806x/common/include" --include_path="C:/ti/C2000Ware_DigitalPower_SDK_5_00_01_00/c2000ware/libraries/math/IQmath/c28/include" --include_path="C:/ti/C2000Ware_DigitalPower_SDK_5_00_01_00/c2000ware/libraries/math/FPUfastRTS/c28/include" --include_path="C:/Users/Eduardo/workspace_v12/blinky_f28069/FreeRTOS/port" --preinclude="C:/Users/Eduardo/workspace_v12/zf28069_freertos_adc_dma/Methods/headers/teste.h" --define=_DEBUG --define=LARGE_MODEL -g --diag_suppress=10063 --diag_warning=225 --issue_remarks --verbose_diagnostics --quiet --abi=coffabi --preproc_with_compile --preproc_dependency="FreeRTOS/$(basename $(<F)).d_raw" --obj_directory="FreeRTOS" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

FreeRTOS/tasks.obj: C:/Users/Eduardo/workspace_v12/blinky_f28069/FreeRTOS/tasks.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/Users/Eduardo/workspace_v12/zf28069_freertos_adc_dma" --include_path="C:/Users/Eduardo/Documents/GitHub/freertos_c28x/FreeRTOS/include" --include_path="C:/Users/Eduardo/Documents/GitHub/freertos_c28x/FreeRTOS" --include_path="C:/Users/Eduardo/Documents/GitHub/freertos_c28x/FreeRTOS/portable" --include_path="C:/Users/Eduardo/workspace_v12/zf28069_freertos_adc_dma/Methods/headers" --include_path="C:/Users/Eduardo/workspace_v12/zf28069_freertos_adc_dma/Methods/functions" --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="C:/ti/C2000Ware_DigitalPower_SDK_5_00_01_00/c2000ware/device_support/f2806x/headers/include" --include_path="C:/ti/C2000Ware_DigitalPower_SDK_5_00_01_00/c2000ware/device_support/f2806x/common/include" --include_path="C:/ti/C2000Ware_DigitalPower_SDK_5_00_01_00/c2000ware/libraries/math/IQmath/c28/include" --include_path="C:/ti/C2000Ware_DigitalPower_SDK_5_00_01_00/c2000ware/libraries/math/FPUfastRTS/c28/include" --include_path="C:/Users/Eduardo/workspace_v12/blinky_f28069/FreeRTOS/port" --preinclude="C:/Users/Eduardo/workspace_v12/zf28069_freertos_adc_dma/Methods/headers/teste.h" --define=_DEBUG --define=LARGE_MODEL -g --diag_suppress=10063 --diag_warning=225 --issue_remarks --verbose_diagnostics --quiet --abi=coffabi --preproc_with_compile --preproc_dependency="FreeRTOS/$(basename $(<F)).d_raw" --obj_directory="FreeRTOS" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


