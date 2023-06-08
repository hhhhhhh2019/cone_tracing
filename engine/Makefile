LIBS = glfw3 gl

CC_FLAGS = -I ../include -c -g `pkg-config --cflags $(LIBS)` -Wno-implicit-function-declaration
LD_FLAGS = `pkg-config --libs $(LIBS)` -lm

CC ?= gcc
#LD = gcc
AR = ar


SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)



%.o: %.c
	$(CC) $(CC_FLAGS) $< -o $@

all: $(OBJECTS)
	$(AR) cr ../bin/engine.a $^


clean:
	rm *.o -rf
