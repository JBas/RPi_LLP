CC = gcc
CFLAGS = -g -Wall
TARGET = main

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) -g $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	$(RM) main
