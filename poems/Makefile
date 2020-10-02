CC = gcc
CFLAG = -Wall -Wextra -ltask_helper -L ./util
EXE = tema2
OBJ = tema2.o
DEPS = util/compare.h

build: $(EXE)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAG)

$(EXE): $(OBJ)
	$(CC) $^ $(CFLAG) -o $(EXE)

run:
	./tema2

.PHONY: clean

clean:
	rm -f *.o $(EXE)
