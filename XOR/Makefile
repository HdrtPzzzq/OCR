all: neural_network

neural_network: neural_network.o activation.o
    gcc neural_network.o activation.o - o neural_network

neural_network.o: neural_network.c activation.h
    gcc -c neural_network.c

activation.o: activation.c
    gcc -c activation.c

clean:
    rm -rf *.o
