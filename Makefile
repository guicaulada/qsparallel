FLAGS=-O3 -fopenmp

CC=gcc

RM=rm -f

EXEC=quicksort

all: $(EXEC)

$(EXEC):
	$(CC) $(FLAGS) $(EXEC).c -o $(EXEC)

run:
	./$(EXEC)

clean:
	$(RM) main.o $(EXEC).o $(EXEC)
