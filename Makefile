CC= gcc
CFLAGS = -g 
TARGET = prog_ajedrez
MAIN = main

OBJS = $(ls *.h | sed s/"\.h"/"\.o"/)

all: $(TARGET)

$(TARGET) : Ajedrez.c $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(TARGET) 

%.o : %.h
	$(CC) $(CFLAGS) -c $< -o $@


