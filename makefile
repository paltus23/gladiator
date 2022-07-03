# mingw32-make.exe

# "-fdiagnostics-color=always",
# "-std=c++14",
# "-g",
# "${workspaceFolder}\\*.cpp",
# "${workspaceFolder}\\src\\*.cpp",
# "-I",
# "include",
# "-o",
# "${workspaceFolderBasename}\\${workspaceFolderBasename}.exe"


PROGRAM_NAME = gladiator.exe
BUILD_DIR	:=./build
OBJ_DIR		:=$(BUILD_DIR)/obj
CC 			= C:/msys64/mingw64/bin/g++.exe
CC			=g++
SRC_DIR		=./src
SRC_FILES	:= $(wildcard $(SRC_DIR)/*.cpp)
SRC_FILES	+= $(wildcard $/*.cpp)
CFLAGS		= -fdiagnostics-color=always -g -std=c++14 -Iinclude 
CFLAGS		+= -MMD -MF $@.d
TEST		=$(wildcard src/*.cpp)

vpath %.cpp src:include
vpath :$(BUILD_DIR)
vpath :$(OBJ_DIR)

VPATH +=$(OBJ_DIR)
VPATH +=$(BUILD_DIR)

# String substitution for every C/C++ file.
# As an example, hello.cpp turns into ./build/hello.cpp.o
# OBJS := $(SRC_FILES:$(SRC_DIR)\\%=$(BUILD_DIR)\\%.o)

OBJS := $(patsubst %.cpp,$(OBJ_DIR)/%.o, $(notdir $(SRC_FILES)) )

# String substitution (suffix version without %).
# As an example, ./build/hello.cpp.o turns into ./build/hello.cpp.d
# DEPS := $(OBJS:.o=.d)

all: ./build/obj $(PROGRAM_NAME) 


./build/obj:
	mkdir $(BUILD_DIR)
	mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o : %.cpp
#	echo $@
	$(CC) $(CFLAGS) -c -o $@ $<


$(PROGRAM_NAME) : $(OBJS)
#	echo $(OBJS)
	$(CC) $(CFLAGS) -o $(PROGRAM_NAME) $(OBJS)
	
	
-include $(wildcard $(OBJ_DIR)/*.d)

