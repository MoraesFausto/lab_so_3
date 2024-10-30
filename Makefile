CC = g++
CFLAGS = -Wall -pthread
TARGET = matrix_mean

all: $(TARGET)

$(TARGET): main.cpp
	$(CC) $(CFLAGS) main.cpp -o $(TARGET) -lm

clean:
	rm -f $(TARGET) *.o
