################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/main/Exception.cpp \
../src/main/SDLAbstractionLayer.cpp \
../src/main/Test.cpp 

OBJS += \
./src/main/Exception.o \
./src/main/SDLAbstractionLayer.o \
./src/main/Test.o 

CPP_DEPS += \
./src/main/Exception.d \
./src/main/SDLAbstractionLayer.d \
./src/main/Test.d 


# Each subdirectory must supply rules for building sources it contributes
src/main/%.o: ../src/main/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"G:\SDL-1.2.15\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


