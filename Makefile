CC = gcc
CFLAGS = -Wall -pthread -lm
TARGET = matrix_calculator

all: $(TARGET)

$(TARGET): main.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o $(TARGET)

run: $(TARGET)
	./$(TARGET) <M> <N> <output_file> <n_threads>
