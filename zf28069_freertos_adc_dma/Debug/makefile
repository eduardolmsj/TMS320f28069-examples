################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
-lrts2800_fpu32_fast_supplement.lib \
-lrts2800_fpu32.lib \
"./F2806x_Adc.obj" \
"./F2806x_CodeStartBranch.obj" \
"./F2806x_CpuTimers.obj" \
"./F2806x_DefaultIsr.obj" \
"./F2806x_Dma.obj" \
"./F2806x_GlobalVariableDefs.obj" \
"./F2806x_PieCtrl.obj" \
"./F2806x_PieVect.obj" \
"./F2806x_Sci.obj" \
"./F2806x_SysCtrl.obj" \
"./F2806x_usDelay.obj" \
"./main.obj" \
"./FreeRTOS/list.obj" \
"./FreeRTOS/queue.obj" \
"./FreeRTOS/tasks.obj" \
"./FreeRTOS/port/porASM.obj" \
"./FreeRTOS/port/port.obj" \
"./Methods/functions/adc.obj" \
"./Methods/functions/gpio.obj" \
"./Methods/functions/insertion.obj" \
"./Methods/functions/pid.obj" \
"./Methods/functions/sci.obj" \
"C:/ti/C2000Ware_DigitalPower_SDK_5_00_01_00/c2000ware/device_support/f2806x/common/cmd/28069_RAM_lnk.cmd" \
"C:/ti/C2000Ware_DigitalPower_SDK_5_00_01_00/c2000ware/device_support/f2806x/headers/cmd/F2806x_Headers_nonBIOS.cmd" \
$(GEN_CMDS__FLAG) \
-lIQmath_fpu32.lib \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include FreeRTOS/subdir_vars.mk
-include FreeRTOS/port/subdir_vars.mk
-include Methods/functions/subdir_vars.mk
-include subdir_rules.mk
-include FreeRTOS/subdir_rules.mk
-include FreeRTOS/port/subdir_rules.mk
-include Methods/functions/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
Example_2806xDMA_ram_to_ram.out \

EXE_OUTPUTS__QUOTED += \
"Example_2806xDMA_ram_to_ram.out" \


# All Target
all: Example_2806xDMA_ram_to_ram.out

# Tool invocations
Example_2806xDMA_ram_to_ram.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --preinclude="C:/Users/Eduardo/workspace_v12/zf28069_freertos_adc_dma/Methods/headers/teste.h" --define=_DEBUG --define=LARGE_MODEL -g --diag_suppress=10063 --diag_warning=225 --issue_remarks --verbose_diagnostics --quiet --abi=coffabi -z -m"Example_2806xDMA_ram_to_ram.map" --stack_size=0x200 --warn_sections -i"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/lib" -i"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" -i"C:/ti/C2000Ware_DigitalPower_SDK_5_00_01_00/c2000ware/device_support/f2806x/common/lib" -i"C:/ti/C2000Ware_DigitalPower_SDK_5_00_01_00/c2000ware/libraries/math/IQmath/c28/lib" -i"C:/ti/C2000Ware_DigitalPower_SDK_5_00_01_00/c2000ware/libraries/math/FPUfastRTS/c28/lib" --priority --reread_libs --issue_remarks --verbose_diagnostics --xml_link_info="Example_2806xDMA_ram_to_ram_linkInfo.xml" --entry_point=code_start --rom_model -o "Example_2806xDMA_ram_to_ram.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "F2806x_Adc.obj" "F2806x_CodeStartBranch.obj" "F2806x_CpuTimers.obj" "F2806x_DefaultIsr.obj" "F2806x_Dma.obj" "F2806x_GlobalVariableDefs.obj" "F2806x_PieCtrl.obj" "F2806x_PieVect.obj" "F2806x_Sci.obj" "F2806x_SysCtrl.obj" "F2806x_usDelay.obj" "main.obj" "FreeRTOS\list.obj" "FreeRTOS\queue.obj" "FreeRTOS\tasks.obj" "FreeRTOS\port\porASM.obj" "FreeRTOS\port\port.obj" "Methods\functions\adc.obj" "Methods\functions\gpio.obj" "Methods\functions\insertion.obj" "Methods\functions\pid.obj" "Methods\functions\sci.obj" 
	-$(RM) "F2806x_Adc.d" "F2806x_CpuTimers.d" "F2806x_DefaultIsr.d" "F2806x_Dma.d" "F2806x_GlobalVariableDefs.d" "F2806x_PieCtrl.d" "F2806x_PieVect.d" "F2806x_Sci.d" "F2806x_SysCtrl.d" "main.d" "FreeRTOS\list.d" "FreeRTOS\queue.d" "FreeRTOS\tasks.d" "FreeRTOS\port\port.d" "Methods\functions\adc.d" "Methods\functions\gpio.d" "Methods\functions\insertion.d" "Methods\functions\pid.d" "Methods\functions\sci.d" 
	-$(RM) "F2806x_CodeStartBranch.d" "F2806x_usDelay.d" "FreeRTOS\port\porASM.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

