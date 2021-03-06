# ==========================================
#   Unity Project - A Test Framework for C
#   Copyright (c) 2007 Mike Karlesky, Mark VanderVoord, Greg Williams
#   [Released under MIT License. Please refer to license.txt for details]
# ==========================================

#We try to detect the OS we are running on, and adjust commands as needed
ifeq ($(OS),Windows_NT)
  ifeq ($(shell uname -s),) # not in a bash-like shell
	CLEANUP = del /F /Q
	MKDIR = mkdir
  else # in a bash-like shell, like msys
	CLEANUP = rm -f
	MKDIR = mkdir -p
  endif
	TARGET_EXTENSION=.exe
else
	CLEANUP = rm -f
	MKDIR = mkdir -p
	TARGET_EXTENSION=.out
endif

C_COMPILER=gcc

UNITY_ROOT= /home/matt/Unity

CFLAGS=-std=c99
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Wpointer-arith
CFLAGS += -Wcast-align
CFLAGS += -Wwrite-strings
CFLAGS += -Wswitch-default
CFLAGS += -Wunreachable-code
CFLAGS += -Winit-self
CFLAGS += -Wmissing-field-initializers
CFLAGS += -Wno-unknown-pragmas
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wundef
CFLAGS += -Wold-style-definition
CFLAGS += -Wno-implicit-function-declaration
CFLAGS += -Wno-incompatible-pointer-types 
#CFLAGS += -Wno-misleading-indentation

TARGET_BASE1 = test1
TARGET1 = $(TARGET_BASE1)$(TARGET_EXTENSION)
SRC_FILES1=\
  ./unity_tests/LedDriver/LedDriverTest.c \
  ./unity_tests/LedDriver/LedDriverTestRunner.c \
  ./unity_tests/AllTests.c \
  ./src/LedDriver/LedDriver.c \
  ./mocks/RuntimeErrorStub.c \
  $(UNITY_ROOT)/src/unity.c \
  $(UNITY_ROOT)/extras/fixture/src/unity_fixture.c \
  $(UNITY_ROOT)/extras/memory/src/unity_memory.c \
  #src/ProductionCode.c \
  # src/ProductionCode2.c \
  #test/TestProductionCode.c \
  # test/TestProductionCode2.c \
  #test/test_runners/TestProductionCode_Runner.c \
  # test/test_runners/TestProductionCode2_Runner.c \
  #test/test_runners/all_tests.c

INC_DIRS= \
  -Isrc \
  -I$(UNITY_ROOT)/src/\
  -I$(UNITY_ROOT)/extras/fixture/src \
  -I$(UNITY_ROOT)/extras/fixture/test \
  -I$(UNITY_ROOT)/extras/memory/src \
  -I./src/LedDriver \
  -I./include/util \
  -I./mocks \
  
SYMBOLS=-DUNITY_FIXTURE_NO_EXTRAS


all: clean default

default: $(SRC_FILES1)$(SRC_FILES2)
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(SRC_FILES1) -o $(TARGET1)
	- ./$(TARGET1) -v


clean:
	$(CLEANUP) $(TARGET1)

ci: CFLAGS += -Werror
ci: default 
