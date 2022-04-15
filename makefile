
Sorting : main.o sort.o
	gcc -o Sorting main.o sort.o

main.o: main.c sort.h
	gcc -c main.c sort.h

sort.o: sort.c sort.h
	gcc -c sort.c sort.h
	
clean:
	rm *.o Sorting

