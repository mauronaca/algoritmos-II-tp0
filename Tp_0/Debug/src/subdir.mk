################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ComplexPlane.cpp \
../src/Images.cpp \
../src/cmdline.cpp \
../src/complejo.cpp \
../src/main.cpp 

OBJS += \
./src/ComplexPlane.o \
./src/Images.o \
./src/cmdline.o \
./src/complejo.o \
./src/main.o 

CPP_DEPS += \
./src/ComplexPlane.d \
./src/Images.d \
./src/cmdline.d \
./src/complejo.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


