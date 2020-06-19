CC = g++

TARGET = snake

CFLAGS = -Wall -lpthread -std=c++17

INCLUDES = -I./include

LFLAGS = -L/usr/local/Cellar/sdl2/2.0.12_1/lib -L/usr/local/lib

LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

SOURCES := src/*.cpp

OBJS = $(SOURCES:.c=.o)

.PHONY: depend clean

all: $(TARGET)
	 @echo Simple compiler named mycc has been compiled


$(TARGET): $(OBJS)
		   $(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS) $(LFLAGS) $(LIBS)


.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(TARGET)

depend: $(SOURCES)
		makedepend $(INCLUDES) $^
