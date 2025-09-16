ifeq ($(TARGET), 1)
OUT_TARGET = lib1F5DF16EE1BF43B999A434ED38FE8F3A.a
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
OUT_TARGET = 1F5DF16EE1BF43B999A434ED38FE8F3A.so
ifeq ($(DEBUG), 1)
CONFIG_TARGET = DynamicDebug
CCFLAGS_TARGET = -Wall -O3 -fPIC -g -DECO_DLL
LDFLAGS_TARGET = -shared
else
CONFIG_TARGET = DynamicRelease
CCFLAGS_TARGET = -O3 -fPIC -DECO_DLL
LDFLAGS_TARGET = -shared
endif
endif

# source files.
SRC = \
../../../SourceFiles/CEcoLab1.c \
../../../SourceFiles/CEcoLab1Factory.c

# include directories
INCLUDES = \
-I ../../../HeaderFiles \
-I ../../../SharedFiles \
-I $(ECO_FRAMEWORK)/Eco.Core1/SharedFiles \
-I $(ECO_FRAMEWORK)/Eco.InterfaceBus1/SharedFiles \
-I $(ECO_FRAMEWORK)/Eco.MemoryManager1/SharedFiles

OBJ = $(SRC:.c=.o)

OUT = $(OUT_TARGET)
OUT_DIR = ../../../BuildFiles/Linux/x86_64/$(CONFIG_TARGET)

# C++ compiler flags (-g -O2 -Wall)
CCFLAGS = $(CCFLAGS_TARGET) -DECO_LINUX -DECO_X86_64 -DUGUID_UTILITY

# compiler
GNU =
CC = gcc
AR = gcc-ar

ifeq ($(TARGET), 1)
CMD_TARGET=$(AR) rcs
else
CMD_TARGET=$(CC) -o
endif

# library paths
LIBS =-lc -lm -lgcc

# link flags
LDFLAGS = $(LDFLAGS_TARGET)

.SUFFIXES: .c

.c.o:
	$(CC) $(INCLUDES) $(CCFLAGS) -c $< -o $@

$(OUT): $(OBJ)
	mkdir -p $(OUT_DIR)
	$(CMD_TARGET) $(OUT_DIR)/$(OUT) $(OBJ) $(LDFLAGS)
	rm $(OBJ)

clean:
	rm $(OBJ) $(OUT_DIR)/$(OUT)

