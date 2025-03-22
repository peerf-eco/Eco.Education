# source files.
SRC = \
../../../SourceFiles/CEcoCalculatorE.c \
../../../SourceFiles/CEcoCalculatorEFactory.c


# include directories
INCLUDES = \
-I ../../../HeaderFiles \
-I ../../../SharedFiles \
-I ../../../../../Lesson03/Eco.CalculatorB/SharedFiles \
-I $(ECO_FRAMEWORK)/Eco.Core1/SharedFiles \
-I $(ECO_FRAMEWORK)/Eco.InterfaceBus1/SharedFiles \
-I $(ECO_FRAMEWORK)/Eco.MemoryManager1/SharedFiles

OBJ = $(SRC:.c=.o)

OUT = 872FEF1DE3314B87AD44D1E7C232C2F0.so
OUT_DIR = ../../../BuildFiles/Linux/x86_64/DynamicRelease

# C++ compiler flags (-g -O2 -Wall)
CCFLAGS = -Wall -O3 -fPIC -g -DECO_DLL -DECO_LINUX -DECO_X86_64 -DUGUID_UTILITY

# compiler
GNU =
CC = gcc
AR = gcc-ar

# library paths
LIBS =-lc -lm -lgcc

# compile flags
LDFLAGS = -g -shared

.SUFFIXES: .c

.c.o:
	$(CC) $(INCLUDES) $(CCFLAGS) -c $< -o $@

$(OUT): $(OBJ)
	mkdir -p $(OUT_DIR)
	$(CC) -o $(OUT_DIR)/$(OUT) $(OBJ) $(LDFLAGS)
	rm $(OBJ)

clean:
	rm $(OBJ) $(OUT_DIR)/$(OUT)

