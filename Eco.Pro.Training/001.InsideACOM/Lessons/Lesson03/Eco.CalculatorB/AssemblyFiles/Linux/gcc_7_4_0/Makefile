# source files.
SRC = \
../../../SourceFiles/CEcoCalculatorB.c \
../../../SourceFiles/CEcoCalculatorBFactory.c


# include directories
INCLUDES = \
-I ../../../HeaderFiles \
-I ../../../SharedFiles \
-I $(ECO_FRAMEWORK)/Eco.Core1/SharedFiles \
-I $(ECO_FRAMEWORK)/Eco.InterfaceBus1/SharedFiles \
-I $(ECO_FRAMEWORK)/Eco.MemoryManager1/SharedFiles

OBJ = $(SRC:.c=.o)

OUT = AE202E543CE54550899603BD70C62565.so
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

