CC = gcc

CFLAGS = -Wall

LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

TARGET = sudoku

SRC = core.c sudoku.c main.c

OBJS = $(SRC:.c=.o)

all: $(TARGET)
	 @echo Compiler named sudoku has been compiled

$(TARGET): $(OBJS)
		   $(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $<  -o $@

clean:
	$(RM) *.o *~ $(TARGET)
