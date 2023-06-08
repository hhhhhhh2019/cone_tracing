LIBS = glfw3 gl

CC_FLAGS = -I ../include -c -fsanitize=address -g `pkg-config --cflags $(LIBS)`
LD_FLAGS = -fsanitize=address -g `pkg-config --libs $(LIBS)` -lm

CC ?= gcc
LD = $(CC)


SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)



%.o: %.c
	$(CC) $(CC_FLAGS) $< -o $@

all: $(OBJECTS)
	$(LD) $^ ../bin/engine.a $(LD_FLAGS) -o ../bin/test


clean:
	rm *.o -rf
