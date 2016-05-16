DIRINCLUDE=./include
DIROBJETO=./obj
CC=g++
CFLAGS=-I$(DIRINCLUDE) -g

_DEPEND = matriz.h
DEPEND = $(patsubst %,$(DIRINCLUDE)/%,$(_DEPEND))

_OBJETO = matriz.o main.o
OBJETO = $(patsubst %,$(DIROBJETO)/%,$(_OBJETO))

$(DIROBJETO)/%.o: %.cpp $(DEPEND)
	$(CC) -c -o $@ $< $(CFLAGS)

pcc_geneticos.out: $(OBJETO)
	$(CC) -o ./bin/$@ $^ $(CFLAGS)
