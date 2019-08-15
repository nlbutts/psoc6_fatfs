################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GeneratedSource/cycfg.c \
../GeneratedSource/cycfg_clocks.c \
../GeneratedSource/cycfg_peripherals.c \
../GeneratedSource/cycfg_pins.c \
../GeneratedSource/cycfg_platform.c \
../GeneratedSource/cycfg_routing.c \
../GeneratedSource/cycfg_usbdev.c 

OBJS += \
./GeneratedSource/cycfg.o \
./GeneratedSource/cycfg_clocks.o \
./GeneratedSource/cycfg_peripherals.o \
./GeneratedSource/cycfg_pins.o \
./GeneratedSource/cycfg_platform.o \
./GeneratedSource/cycfg_routing.o \
./GeneratedSource/cycfg_usbdev.o 

C_DEPS += \
./GeneratedSource/cycfg.d \
./GeneratedSource/cycfg_clocks.d \
./GeneratedSource/cycfg_peripherals.d \
./GeneratedSource/cycfg_pins.d \
./GeneratedSource/cycfg_platform.d \
./GeneratedSource/cycfg_routing.d \
./GeneratedSource/cycfg_usbdev.d 


# Each subdirectory must supply rules for building sources it contributes
GeneratedSource/%.o: ../GeneratedSource/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -Og -ffunction-sections -fdata-sections -Wall  -g3 -DCY8C624ABZI_D44 -DDEBUG -DAPP_NAME='"USBCommFatFs_cm4"' -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/include" -I"C:\projects\psoc6_fatfs\USBCommFatFs_mainapp\fatfs" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/cmsis/include" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/drivers/include" -I"C:\projects\psoc6_fatfs\USBCommFatFs_mainapp/GeneratedSource" -I"C:\projects\psoc6_fatfs\USBCommFatFs_mainapp/Source" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/drivers/source" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/startup/cm4_low" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/startup/cm4_high" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/linker/cm4" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6mw/usb_dev" -I"C:/Users/nbutts/ModusToolbox_1.1/libraries/psoc6sw-1.1/components/psoc6pdl/devices/psoc6/cm0p/prebuilt" -std=gnu11 -mfpu=fpv4-sp-d16 -ffat-lto-objects -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


