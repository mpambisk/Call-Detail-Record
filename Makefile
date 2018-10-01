OBJS	= main.o Bucket.o Cdr.o Heap.o Utils.o
SOURCE	= main.cpp Bucket.cpp Cdr.cpp Heap.cpp Utils.cpp
HEADER	= Hash.h Bucket.h Cdr.h List.h Heap.h Utils.h Secondary.h
OUT	= exe
CC	= g++
FLAGS	= -g -c

#executable
$(OUT): $(OBJS)
	$(CC) -g $(OBJS) -o $@
#object files
main.o: main.cpp
	$(CC) $(FLAGS)	$?
#Hash.o: Hash.cpp
#	$(CC) $(FLAGS) $?
Bucket.o: Bucket.cpp
	$(CC) $(FLAGS) $?
Cdr.o: Cdr.cpp
	$(CC) $(FLAGS) $?
Heap.o: Heap.cpp
	$(CC) $(FLAGS) $?
Utils.o: Utils.cpp
	$(CC) $(FLAGS) $?
#default execution command
run:
	./exe
#delete object files and exe
clean:
	rm -f *.o exe
#count lines
count:
	wc -l $(SOURCE) $(HEADER)
valgrind:
	valgrind --leak-check=yes --show-reachable=yes --track-fds=yes ./exe -o test.txt
