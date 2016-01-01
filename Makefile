CC= gcc
CFLAGS = -g
TARGET = chess
MAIN = main

#OBJS = $(shell ls *.h | sed s/"\.h"/"\.o"/)
FILES_H = $(shell ls *.h)

all: $(TARGET)

$(TARGET) : Ajedrez.o $(FILES_H)
	$(CC) -o $(TARGET) Ajedrez.o 

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm $(TARGET) $(shell ls *.o)
