################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra/fsp/src/r_rtc/r_rtc.c 

C_DEPS += \
./ra/fsp/src/r_rtc/r_rtc.d 

OBJS += \
./ra/fsp/src/r_rtc/r_rtc.o 

SREC += \
RA2E1_TESTDEMO.srec 

MAP += \
RA2E1_TESTDEMO.map 


# Each subdirectory must supply rules for building sources it contributes
ra/fsp/src/r_rtc/%.o: ../ra/fsp/src/r_rtc/%.c
	$(file > $@.in,-mcpu=cortex-m23 -mthumb -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-strict-aliasing -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g -D_RENESAS_RA_ -D_RA_CORE=CM23 -D_RA_ORDINAL=1 -DQE_TOUCH_CONFIGURATION -I"C:/Users/Administrator/e2_studio/workspace/RA2E1_TESTDEMO/src" -I"." -I"C:/Users/Administrator/e2_studio/workspace/RA2E1_TESTDEMO/ra/fsp/inc" -I"C:/Users/Administrator/e2_studio/workspace/RA2E1_TESTDEMO/ra/fsp/inc/api" -I"C:/Users/Administrator/e2_studio/workspace/RA2E1_TESTDEMO/ra/fsp/inc/instances" -I"C:/Users/Administrator/e2_studio/workspace/RA2E1_TESTDEMO/ra/arm/CMSIS_6/CMSIS/Core/Include" -I"C:/Users/Administrator/e2_studio/workspace/RA2E1_TESTDEMO/ra_gen" -I"C:/Users/Administrator/e2_studio/workspace/RA2E1_TESTDEMO/ra_cfg/fsp_cfg/bsp" -I"C:/Users/Administrator/e2_studio/workspace/RA2E1_TESTDEMO/ra_cfg/fsp_cfg" -I"C:/Users/Administrator/e2_studio/workspace/RA2E1_TESTDEMO/qe_gen" -std=c99 -Wno-stringop-overflow -Wno-format-truncation --param=min-pagesize=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

