################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/main/Figures/CircBoundaryFigure.cpp \
../src/main/Figures/CursorFigure.cpp \
../src/main/Figures/Figure.cpp \
../src/main/Figures/GrabbableFigure.cpp \
../src/main/Figures/MouseFigure.cpp \
../src/main/Figures/PlayerFigure.cpp \
../src/main/Figures/RectBoundaryFigure.cpp \
../src/main/Figures/TempFigure.cpp 

OBJS += \
./src/main/Figures/CircBoundaryFigure.o \
./src/main/Figures/CursorFigure.o \
./src/main/Figures/Figure.o \
./src/main/Figures/GrabbableFigure.o \
./src/main/Figures/MouseFigure.o \
./src/main/Figures/PlayerFigure.o \
./src/main/Figures/RectBoundaryFigure.o \
./src/main/Figures/TempFigure.o 

CPP_DEPS += \
./src/main/Figures/CircBoundaryFigure.d \
./src/main/Figures/CursorFigure.d \
./src/main/Figures/Figure.d \
./src/main/Figures/GrabbableFigure.d \
./src/main/Figures/MouseFigure.d \
./src/main/Figures/PlayerFigure.d \
./src/main/Figures/RectBoundaryFigure.d \
./src/main/Figures/TempFigure.d 


# Each subdirectory must supply rules for building sources it contributes
src/main/Figures/%.o: ../src/main/Figures/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"G:\SDL-1.2.15\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


