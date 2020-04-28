CC = g++


all: format

format: main.o Logger.o
	$(CC) main.o Logger.o -o format

main.o: main.cpp
	$(CC) -c main.cpp

logger.o: Logger.cpp
	$(CC) -c Logger.cpp

clean:
	rm -rf *.o