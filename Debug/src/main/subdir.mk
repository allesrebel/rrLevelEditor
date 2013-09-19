################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/main/CircBoundaryFigure.cpp \
../src/main/CursorFigure.cpp \
../src/main/Exception.cpp \
../src/main/Figure.cpp \
../src/main/GrabbableFigure.cpp \
../src/main/MouseFigure.cpp \
../src/main/PlayerFigure.cpp \
../src/main/RectBoundaryFigure.cpp \
../src/main/SDLAbstractionLayer.cpp \
../src/main/TempFigure.cpp \
../src/main/Test.cpp 

OBJS += \
./src/main/CircBoundaryFigure.o \
./src/main/CursorFigure.o \
./src/main/Exception.o \
./src/main/Figure.o \
./src/main/GrabbableFigure.o \
./src/main/MouseFigure.o \
./src/main/PlayerFigure.o \
./src/main/RectBoundaryFigure.o \
./src/main/SDLAbstractionLayer.o \
./src/main/TempFigure.o \
./src/main/Test.o 

CPP_DEPS += \
./src/main/CircBoundaryFigure.d \
./src/main/CursorFigure.d \
./src/main/Exception.d \
./src/main/Figure.d \
./src/main/GrabbableFigure.d \
./src/main/MouseFigure.d \
./src/main/PlayerFigure.d \
./src/main/RectBoundaryFigure.d \
./src/main/SDLAbstractionLayer.d \
./src/main/TempFigure.d \
./src/main/Test.d 


# Each subdirectory must supply rules for building sources it contributes
src/main/%.o: ../src/main/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"G:\SDL-1.2.15\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


