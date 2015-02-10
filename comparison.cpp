#include <string>
#include <chrono>
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
    ifstream in(filename.c_str());
    int num;

    while (in >> num)
        vec.push_back(num);
}

double calcTime(const chrono::high_resolution_clock::time_point &start, 
        const chrono::high_resolution_clock::time_point &finish) {
    auto time_span = chrono::duration_cast< chrono::duration<double> >(finish-start);
    return time_span.count();
}

int main() {
    string files[] = {"data/r100.txt", "data/r1000.txt",
       "data/r10000.txt", "data/r100000.txt", "data/r1000000.txt"};

    vector<int> elements;
    chrono::high_resolution_clock::time_point start, finish;
    cout << "number,quicksort,heapsort,bubble sort, insertion sort\n";
    for (int i = 0; i < 5; i++) {
        elements.clear();
        readFile(files[i], elements);
        const vector<int> orig(elements);
        
        cout << elements.size() << ",";

        // quicksort time
        start = chrono::high_resolution_clock::now();
        quicksort(&elements[0], elements.size());
        finish = chrono::high_resolution_clock::now();
        cout << setprecision(5) << fixed << calcTime(start,finish) << ",";

        elements = orig;

        // mergesort time
        start = chrono::high_resolution_clock::now();
        heapsort(&elements[0], elements.size());
        finish = chrono::high_resolution_clock::now(); 
        cout << setprecision(5) << fixed << calcTime(start,finish) << ",";

        elements = orig;

        // bubble sort
        start = chrono::high_resolution_clock::now();
        bubblesort(&elements[0], elements.size());
        finish = chrono::high_resolution_clock::now();
        cout << setprecision(5) << fixed << calcTime(start,finish) << ",";

        elements = orig;

        // insertion sort
        start = chrono::high_resolution_clock::now();
        insertionsort(&elements[0], elements.size());
        finish = chrono::high_resolution_clock::now();
        cout << setprecision(5) << fixed << calcTime(start,finish) << ",";

        cout << "\n";
    }
}
