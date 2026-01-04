CC=gcc
CFLAGS=-I.
DEPS = src/tokeniser.h
OBJ = bin/main.o bin/tokeniser.o

bin/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bin/langtest: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
