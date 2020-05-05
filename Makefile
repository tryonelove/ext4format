CC = g++
CFLAGS = -Wall -g
SOURCES=main.cpp Logger.cpp Formatter.cpp

all: format clean

format: main.o Formatter.o Disk.o Logger.o
	$(CC) $(CFLAGS) main.o Formatter.o Disk.o Logger.o -o format

main.o: main.cpp
	$(CC) -c main.cpp

Disk.o: Disk.cpp
	$(CC) -c Disk.cpp

Formatter.o: Formatter.cpp
	$(CC) -c Formatter.cpp

Logger.o: Logger.cpp
	$(CC) -c Logger.cpp

run: ./format clean
	./format /dev/sdd1

clean:
	rm -rf *.o