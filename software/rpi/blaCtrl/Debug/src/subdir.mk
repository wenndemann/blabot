################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Client.cpp \
../src/Sensor.cpp \
../src/blaCtrl.cpp \
../src/i2c.cpp \
../src/tools.cpp 

OBJS += \
./src/Client.o \
./src/Sensor.o \
./src/blaCtrl.o \
./src/i2c.o \
./src/tools.o 

CPP_DEPS += \
./src/Client.d \
./src/Sensor.d \
./src/blaCtrl.d \
./src/i2c.d \
./src/tools.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabi-g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


