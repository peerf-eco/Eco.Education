ifeq ($(OS), Windows_NT)
	#WINDOWS USE THESE DEFINITIONS
	RM = -del /q /f
	SLASH = \\
	SWALLOW_OUTPUT = >nul 2>nul
	TOOLCHAIN = 
	TOOL = 
else
	#LINUX USE THESE DEFINITIONS
	RM = -rm -f
	SLASH = /
	SWALLOW_OUTPUT =
	TOOLCHAIN = 
	TOOL = 
endif 

ifeq ($(TARGET), 1)
OUT_TARGET = DemoCalculator2
ifeq ($(DEBUG), 1)
CONFIG_TARGET = StaticDebug
CCFLAGS_TARGET = -Wall -g -DECO_LIB
LDFLAGS_TARGET =
ARCH_TARGET = arm64-v8a
UNIKERNEL_TARGET = StaticRelease
else
CONFIG_TARGET = StaticRelease
CCFLAGS_TARGET = -O3 -DECO_LIB
LDFLAGS_TARGET =
ARCH_TARGET = arm64-v8a
UNIKERNEL_TARGET = StaticRelease
endif
else
OUT_TARGET = DemoCalculator2
ifeq ($(DEBUG), 1)
CONFIG_TARGET = DynamicDebug
CCFLAGS_TARGET = -Wall -g -DECO_DLL
LDFLAGS_TARGET = 
ARCH_TARGET = arm64-v8a
UNIKERNEL_TARGET = DynamicRelease
else
CONFIG_TARGET = DynamicRelease
CCFLAGS_TARGET = -O3 -DECO_DLL
LDFLAGS_TARGET = 
ARCH_TARGET = arm64-v8a
UNIKERNEL_TARGET = DynamicRelease
endif
endif

# source files.
SRC = \
..$(SLASH)..$(SLASH)..$(SLASH)SourceFiles$(SLASH)EcoDemoCalculator2.c \
..$(SLASH)..$(SLASH)..$(SLASH)SourceFiles$(SLASH)EcoDemoDialogX11.c

# include directories
INCLUDES = \
-I ..$(SLASH)..$(SLASH)..$(SLASH)HeaderFiles \
-I ..$(SLASH)..$(SLASH)..$(SLASH)SharedFiles \
-I ..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)Lesson02$(SLASH)Eco.CalculatorA$(SLASH)SharedFiles \
-I ..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)Lesson03$(SLASH)Eco.CalculatorB$(SLASH)SharedFiles \
-I ..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)Lesson05$(SLASH)Eco.CalculatorC$(SLASH)SharedFiles \
-I ..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)Lesson06$(SLASH)Eco.CalculatorD$(SLASH)SharedFiles \
-I ..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)Lesson07$(SLASH)Eco.CalculatorE$(SLASH)SharedFiles \
-I ..$(SLASH)..$(SLASH)..$(SLASH)UnitTestFiles$(SLASH)HeaderFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.Core1$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.InterfaceBus1$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.FileSystemManagement1$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.MemoryManager1$(SLASH)SharedFiles

# libraries directories
LIB_DIR = \
-L ..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)Lesson02$(SLASH)Eco.CalculatorA$(SLASH)BuildFiles$(SLASH)Linux$(SLASH)$(ARCH_TARGET)$(SLASH)$(CONFIG_TARGET) \
-L $(ECO_FRAMEWORK)$(SLASH)Eco.InterfaceBus1$(SLASH)BuildFiles$(SLASH)Linux$(SLASH)$(ARCH_TARGET)$(SLASH)StaticRelease \
-L $(ECO_FRAMEWORK)$(SLASH)Eco.FileSystemManagement1$(SLASH)BuildFiles$(SLASH)Linux$(SLASH)$(ARCH_TARGET)$(SLASH)StaticRelease \
-L $(ECO_FRAMEWORK)$(SLASH)Eco.MemoryManager1$(SLASH)BuildFiles$(SLASH)Linux$(SLASH)$(ARCH_TARGET)$(SLASH)StaticRelease \
-L $(ECO_FRAMEWORK)$(SLASH)Eco.System1$(SLASH)BuildFiles$(SLASH)Linux$(SLASH)$(ARCH_TARGET)$(SLASH)$(UNIKERNEL_TARGET)

OBJ = $(SRC:.c=.o)

OUT = $(OUT_TARGET)
OUT_DIR = ..$(SLASH)..$(SLASH)..$(SLASH)BuildFiles$(SLASH)Linux$(SLASH)$(ARCH_TARGET)$(SLASH)$(CONFIG_TARGET)

# C++ compiler flags (-g -O2 -Wall)
CCFLAGS = $(CCFLAGS_TARGET) -DLINUX -DUGUID_UTILITY -DECO_LINUX 

# compiler
GNU = $(TOOLCHAIN)
CC = $(TOOL)gcc
AR = $(TOOL)gcc-ar

ifeq ($(TARGET), 1)
LIBS_TARGET=-l00000000000000000000000042757331 -l0000000000000000000000004D656D31 -l00000000000000000000000046534D31 -l4828F6552E4540E78121EBD220DC360E
else
LIBS_TARGET=
endif

# library paths
LIBS = $(LIB_DIR) -lX11 -lm -lc -lgcc -ldl -l00000000000000000000000000000100 $(LIBS_TARGET)

# compile flags
LDFLAGS = $(LDFLAGS_TARGET) $(LIBS)

.SUFFIXES: .c

.c.o:
	$(GNU)$(CC) $(INCLUDES) $(CCFLAGS) -c $< -o $@

$(OUT): $(OBJ)
	mkdir -p $(OUT_DIR)
	$(GNU)$(CC) ${LDFLAGS} -o $(OUT_DIR)/$(OUT) $(OBJ) $(LDFLAGS)
	rm $(OBJ)

clean:
	rm $(OBJ) $(OUT_DIR)/$(OUT)

