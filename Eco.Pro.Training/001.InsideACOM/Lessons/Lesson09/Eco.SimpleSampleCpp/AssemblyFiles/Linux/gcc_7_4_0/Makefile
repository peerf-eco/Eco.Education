ifeq ($(TARGET), 1)
OUT_TARGET = EcoSimpleSampleCpp
ifeq ($(DEBUG), 1)
CONFIG_TARGET = StaticDebug
CCFLAGS_TARGET = -Wall -O3 -g -DECO_LIB
LDFLAGS_TARGET =
else
CONFIG_TARGET = StaticRelease
CCFLAGS_TARGET = -O3 -DECO_LIB
LDFLAGS_TARGET =
endif
else
OUT_TARGET = EcoSimpleSampleCpp
ifeq ($(DEBUG), 1)
CONFIG_TARGET = DynamicDebug
CCFLAGS_TARGET = -Wall -O3 -g -DECO_DLL
LDFLAGS_TARGET = 
else
CONFIG_TARGET = DynamicRelease
CCFLAGS_TARGET = -g  -DECO_DLL
LDFLAGS_TARGET = 
endif
endif

# source files.
SRC = \
../../../SourceFiles/EcoSimpleSampleCpp.cpp


# include directories
INCLUDES = \
-I ../../../HeaderFiles \
-I ../../../SharedFiles \
-I ../../../../../Lesson02/Eco.CalculatorA/SharedFiles \
-I ../../../../../Lesson03/Eco.CalculatorB/SharedFiles \
-I $(ECO_FRAMEWORK)/Eco.Core1/SharedFiles \
-I $(ECO_FRAMEWORK)/Eco.InterfaceBus1/SharedFiles \
-I $(ECO_FRAMEWORK)/Eco.FileSystemManagement1/SharedFiles \
-I $(ECO_FRAMEWORK)/Eco.MemoryManager1/SharedFiles

# libraries directories
LIB_DIR = \
-L ../../../BuildFiles/Linux/x86_64/$(CONFIG_TARGET) \
-L $(ECO_FRAMEWORK)/Eco.InterfaceBus1/BuildFiles/Linux/x86_64/StaticRelease \
-L $(ECO_FRAMEWORK)/Eco.FileSystemManagement1/BuildFiles/Linux/x86_64/StaticRelease \
-L $(ECO_FRAMEWORK)/Eco.MemoryManager1/BuildFiles/Linux/x86_64/StaticRelease \
-L $(ECO_FRAMEWORK)/Eco.System1/BuildFiles/Linux/x86_64/StaticRelease

OBJ = $(SRC:.cpp=.o)

OUT = $(OUT_TARGET)
OUT_DIR = ../../../BuildFiles/Linux/x86_64/$(CONFIG_TARGET)

# C++ compiler flags (-g -O2 -Wall)
CCFLAGS = $(CCFLAGS_TARGET) -DLINUX -DUGUID_UTILITY -DECO_X86_64 -DECO_LINUX 

# compiler
GNU =
CC = gcc
AR = gcc-ar

ifeq ($(TARGET), 1)
LIBS_TARGET=
else
LIBS_TARGET=
endif

# library paths
LIBS = $(LIB_DIR) -lX11 -lm -lc -lgcc -ldl -l00000000000000000000000053595333 -l00000000000000000000000042757331 -l0000000000000000000000004D656D31 -l00000000000000000000000046534D31 $(LIBS_TARGET) -lGL -LGLX

# compile flags
LDFLAGS = $(LDFLAGS_TARGET) $(LIBS)

.SUFFIXES: .cpp

.cpp.o:
	$(CC) $(INCLUDES) $(CCFLAGS) -c $< -o $@

$(OUT): $(OBJ)
	mkdir -p $(OUT_DIR)
	$(CC) ${LDFLAGS} -o $(OUT_DIR)/$(OUT) $(OBJ) $(LDFLAGS)
	rm $(OBJ)

clean:
	rm $(OBJ) $(OUT_DIR)/$(OUT)

