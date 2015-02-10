compare: comparison.cpp sorts
	g++ -o compare.out comparison.cpp bubblesort.o heapsort.o insertionsort.o quicksort.o

fast: comparison.cpp sorts
	g++ -O3 -o compare-fast.out comparison.cpp bubblesort.o heapsort.o insertionsort.o quicksort.o

sorts: bubblesort.o heapsort.o insertionsort.o quicksort.o

bubblesort.o: bubble/bubblesort.cpp bubble/bubblesort.h
	g++ -c bubble/bubblesort.cpp

heapsort.o: heap/heapsort.cpp heap/heapsort.h
	g++ -c heap/heapsort.cpp

insertionsort.o: insertion/insertionsort.cpp insertion/insertionsort.h
	g++ -c insertion/insertionsort.cpp

quicksort.o: quick/quicksort.cpp quick/quicksort.h
	g++ -c quick/quicksort.cpp

clean:
	rm *.out *.o
