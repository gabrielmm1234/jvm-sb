CASM = nasm
CCPP = g++
CC   = gcc
CFLAGS   = -Wextra -g -m32 -std=c99
NFLAGS   = 
INCLUDE  = 
TARGET   = jvm.exe
SOURCES_ASM = $(wildcard *.asm)
SOURCES_C   = $(wildcard *.c)
SOURCES_CPP = $(wildcard *.cpp)
OBJECTS_ASM = $(SOURCES_ASM:.asm=.obj)
OBJECTS_C   = $(SOURCES_C:.c=.obj)
OBJECTS_CPP = $(SOURCES_CPP:.cpp=.obj)
OBJECTS  = $(OBJECTS_ASM) $(OBJECTS_CPP) $(OBJECTS_C)
DEPENDS  = $(OBJECTS_C:.obj=.d) $(OBJECTS_CPP:.obj=.d) $(OBJECTS_ASM:.obj=.d)

ifeq ($(OS),Windows_NT)
    REMOVE = rm
    NFLAGS += -fwin32 --PREFIX _
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),MINGW32_NT-6.3)
		REMOVE = rm
	endif
else
    REMOVE = rm -f
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        NFLAGS += -felf32 
    endif
    ifeq ($(UNAME_S),Darwin)
        NFLAGS += -fmacho32 --PREFIX _
    endif
    
endif

$(TARGET): $(OBJECTS)
	$(CC) -m32 -o $@ $^ 

%.obj: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<
	
%.obj: %.cpp
	$(CCPP) $(CFLAGS) $(INCLUDE) -o $@ -c $<

%.obj: %.asm
	$(CASM) $(NFLAGS) -o $@ $<


all: clean $(TARGET)

clean:
	$(REMOVE) $(OBJECTS) $(TARGET)
	
test:
	echo $(OBJECTS)
