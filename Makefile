CC = gcc

CFLAGS = -Wall -pthread

MATRIX_TARGET = matrix_calculator
SEARCH_TARGET = search_value

all: $(MATRIX_TARGET) $(SEARCH_TARGET)

$(MATRIX_TARGET): matrix_calculator.o
	$(CC) $(CFLAGS) -o $(MATRIX_TARGET) matrix_calculator.o -lm

matrix_calculator.o: matrix_calculator.c
	$(CC) $(CFLAGS) -c matrix_calculator.c

$(SEARCH_TARGET): search_value.o
	$(CC) $(CFLAGS) -o $(SEARCH_TARGET) search_value.o -lm

search_value.o: search_value.c
	$(CC) $(CFLAGS) -c search_value.c

clean:
	rm -f *.o $(MATRIX_TARGET) $(SEARCH_TARGET)

run_matrix: $(MATRIX_TARGET)
	./$(MATRIX_TARGET) <M> <N> <output_file> <n_threads>

run_search: $(SEARCH_TARGET)
	./$(SEARCH_TARGET) 10000 42 4
