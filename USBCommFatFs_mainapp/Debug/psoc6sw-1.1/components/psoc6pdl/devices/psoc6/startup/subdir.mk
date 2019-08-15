################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../psoc6sw-1.1/components/psoc6pdl/devices/psoc6/startup/system_psoc6_cm4.c 

OBJS += \
./psoc6sw-1.1/components/psoc6pdl/devices/psoc6/startup/system_psoc6_cm4.o 

C_DEPS += \
./psoc6sw-1.1/components/psoc6pdl/devices/psoc6/startup/system_psoc6_cm4.d 


# Each subdirectory must supply rules for building sources it contributes
psoc6sw-1.1/components/psoc6pdl/devices/psoc6/startup/%.o: ../psoc6sw-1.1/components/psoc6pdl/devices/psoc6/startup/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -Og -ffunction-sections -fdata-sections -Wall  -g3 -DCY8C624ABZI_D44 -DDEBUG -DAPP_NAME='"USBCommFatFs_cm4"' -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/include" -I"C:\projects\psoc6_fatfs\USBCommFatFs_mainapp\fatfs" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/cmsis/include" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/drivers/include" -I"C:\projects\psoc6_fatfs\USBCommFatFs_mainapp/GeneratedSource" -I"C:\projects\psoc6_fatfs\USBCommFatFs_mainapp/Source" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/drivers/source" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/startup/cm4_low" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/startup/cm4_high" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/linker/cm4" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6mw/usb_dev" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/cm0p/prebuilt" -std=gnu11 -mfpu=fpv4-sp-d16 -ffat-lto-objects -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


