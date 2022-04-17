DIRINCLUDE=./include
DIROBJETO=./obj
DIRBIN=./bin
CC=g++
CFLAGS=-I$(DIRINCLUDE) -g

_DEPEND = matriz.h InstanceReader.h
DEPEND = $(patsubst %,$(DIRINCLUDE)/%,$(_DEPEND))

_OBJETO = matriz.o InstanceReader.o main.o
OBJETO = $(patsubst %,$(DIROBJETO)/%,$(_OBJETO))

$(DIROBJETO)/%.o: %.cpp $(DEPEND)
	mkdir -p $(DIROBJETO)
	$(CC) -c -o $@ $< $(CFLAGS)

pcc_geneticos.out: $(OBJETO)
	mkdir -p $(DIRBIN)
	$(CC) -o ./bin/$@ $^ $(CFLAGS)
