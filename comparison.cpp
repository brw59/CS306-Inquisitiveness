#include <string>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iostream>
#include <iomanip>
#include <math.h>

#include "quick/quicksort.h"
#include "bubble/bubblesort.h"
#include "insertion/insertionsort.h"
#include "heap/heapsort.h"

using namespace std;

void readFile(const string filename, vector<int> &vec) {
    ifstream in(filename);
    int num;

    while (in >> num)
        vec.push_back(num);
}

double calcTime(const clock_t &start, const clock_t &finish) {
    return (finish - start) / (double) CLOCKS_PER_SEC;
}

int main() {
    string files[] = {"data/r100.txt", "data/r1000.txt",
       "data/r10000.txt", "data/r100000.txt", "data/r1000000.txt"};

    vector<int> elements;
    clock_t start, finish;
    cout << "number,quicksort,heapsort,bubble sort, insertion sort\n";
    for (int i = 0; i < 5; i++) {
        elements.clear();
        readFile(files[i], elements);
        const vector<int> orig(elements);
        
        cout << elements.size() << ",";

        // quicksort time
        start = clock();
        quicksort(&elements[0], elements.size());
        finish = clock();
        cout << setprecision(5) << fixed << calcTime(start,finish) << ",";

        elements = orig;

        // mergesort time
        start = clock();
        heapsort(&elements[0], elements.size());
        finish = clock(); 
        cout << setprecision(5) << fixed << calcTime(start,finish) << ",";

        elements = orig;

        // bubble sort
        start = clock();
        bubblesort(&elements[0], elements.size());
        finish = clock();
        cout << setprecision(5) << fixed << calcTime(start,finish) << ",";

        elements = orig;

        // insertion sort
        start = clock();
        insertionsort(&elements[0], elements.size());
        finish = clock();
        cout << setprecision(5) << fixed << calcTime(start,finish) << ",";

        cout << "\n";
    }
}
