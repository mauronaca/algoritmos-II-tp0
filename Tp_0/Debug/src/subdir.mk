################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Complejo.cpp \
../src/ComplexPlane.cpp \
../src/ComplexTransform.cpp \
../src/Images.cpp \
../src/cmdline.cpp \
../src/main.cpp 

OBJS += \
./src/Complejo.o \
./src/ComplexPlane.o \
./src/ComplexTransform.o \
./src/Images.o \
./src/cmdline.o \
./src/main.o 

CPP_DEPS += \
./src/Complejo.d \
./src/ComplexPlane.d \
./src/ComplexTransform.d \
./src/Images.d \
./src/cmdline.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


