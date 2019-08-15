################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6mw/usb_dev/cy_usb_dev.c \
C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6mw/usb_dev/cy_usb_dev_audio.c \
C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6mw/usb_dev/cy_usb_dev_cdc.c \
C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6mw/usb_dev/cy_usb_dev_hid.c 

OBJS += \
./psoc6sw-1.1/components/psoc6mw/usb_dev/cy_usb_dev.o \
./psoc6sw-1.1/components/psoc6mw/usb_dev/cy_usb_dev_audio.o \
./psoc6sw-1.1/components/psoc6mw/usb_dev/cy_usb_dev_cdc.o \
./psoc6sw-1.1/components/psoc6mw/usb_dev/cy_usb_dev_hid.o 

C_DEPS += \
./psoc6sw-1.1/components/psoc6mw/usb_dev/cy_usb_dev.d \
./psoc6sw-1.1/components/psoc6mw/usb_dev/cy_usb_dev_audio.d \
./psoc6sw-1.1/components/psoc6mw/usb_dev/cy_usb_dev_cdc.d \
./psoc6sw-1.1/components/psoc6mw/usb_dev/cy_usb_dev_hid.d 


# Each subdirectory must supply rules for building sources it contributes
psoc6sw-1.1/components/psoc6mw/usb_dev/cy_usb_dev.o: C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6mw/usb_dev/cy_usb_dev.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -Og -ffunction-sections -fdata-sections -Wall  -g3 -DCY8C624ABZI_D44 -DDEBUG -DAPP_NAME='"USBCommFatFs_cm4"' -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/include" -I"C:\projects\psoc6_fatfs\USBCommFatFs_mainapp\fatfs" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/cmsis/include" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/drivers/include" -I"C:\projects\psoc6_fatfs\USBCommFatFs_mainapp/GeneratedSource" -I"C:\projects\psoc6_fatfs\USBCommFatFs_mainapp/Source" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/drivers/source" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/startup/cm4_low" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/startup/cm4_high" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/linker/cm4" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6mw/usb_dev" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/cm0p/prebuilt" -std=gnu11 -mfpu=fpv4-sp-d16 -ffat-lto-objects -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

psoc6sw-1.1/components/psoc6mw/usb_dev/cy_usb_dev_audio.o: C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6mw/usb_dev/cy_usb_dev_audio.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -Og -ffunction-sections -fdata-sections -Wall  -g3 -DCY8C624ABZI_D44 -DDEBUG -DAPP_NAME='"USBCommFatFs_cm4"' -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/include" -I"C:\projects\psoc6_fatfs\USBCommFatFs_mainapp\fatfs" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/cmsis/include" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/drivers/include" -I"C:\projects\psoc6_fatfs\USBCommFatFs_mainapp/GeneratedSource" -I"C:\projects\psoc6_fatfs\USBCommFatFs_mainapp/Source" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/drivers/source" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/startup/cm4_low" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/startup/cm4_high" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/linker/cm4" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6mw/usb_dev" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/cm0p/prebuilt" -std=gnu11 -mfpu=fpv4-sp-d16 -ffat-lto-objects -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

psoc6sw-1.1/components/psoc6mw/usb_dev/cy_usb_dev_cdc.o: C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6mw/usb_dev/cy_usb_dev_cdc.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -Og -ffunction-sections -fdata-sections -Wall  -g3 -DCY8C624ABZI_D44 -DDEBUG -DAPP_NAME='"USBCommFatFs_cm4"' -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/include" -I"C:\projects\psoc6_fatfs\USBCommFatFs_mainapp\fatfs" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/cmsis/include" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/drivers/include" -I"C:\projects\psoc6_fatfs\USBCommFatFs_mainapp/GeneratedSource" -I"C:\projects\psoc6_fatfs\USBCommFatFs_mainapp/Source" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/drivers/source" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/startup/cm4_low" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/startup/cm4_high" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/linker/cm4" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6mw/usb_dev" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/cm0p/prebuilt" -std=gnu11 -mfpu=fpv4-sp-d16 -ffat-lto-objects -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

psoc6sw-1.1/components/psoc6mw/usb_dev/cy_usb_dev_hid.o: C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6mw/usb_dev/cy_usb_dev_hid.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -Og -ffunction-sections -fdata-sections -Wall  -g3 -DCY8C624ABZI_D44 -DDEBUG -DAPP_NAME='"USBCommFatFs_cm4"' -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/include" -I"C:\projects\psoc6_fatfs\USBCommFatFs_mainapp\fatfs" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/cmsis/include" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/drivers/include" -I"C:\projects\psoc6_fatfs\USBCommFatFs_mainapp/GeneratedSource" -I"C:\projects\psoc6_fatfs\USBCommFatFs_mainapp/Source" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/drivers/source" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/startup/cm4_low" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/startup/cm4_high" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/linker/cm4" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6mw/usb_dev" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/cm0p/prebuilt" -std=gnu11 -mfpu=fpv4-sp-d16 -ffat-lto-objects -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


