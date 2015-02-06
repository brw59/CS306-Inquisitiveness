#include <string>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iostream>
#include <iomanip>

#include "quicksort/quicksort-working.h"
#include "bubble/sortBubble.h"
#include "insertionSort/sortInsertion.h"

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
    string files[] = {"in/Randomnm100.txt", "in/Randomnm1000.txt",
       "in/Randomnm10000.txt", "in/Randomnm100000.txt", 
       "in/Randomnm1000000.txt"};

    vector<int> elements;
    clock_t start, finish;
    cout << "number,quicksort,mergesort,bubble sort, insertion sort\n";
    for (int i = 0; i < 5; i++) {
        elements.clear();
        readFile(files[i], elements);
        
        cout << elements.size() << ",";

        // quicksort time
        start = clock();
        quickSort(&elements[0], 0, elements.size()-1);
        finish = clock();
        cout << setprecision(5) << fixed << calcTime(start,finish) << ",";

        // mergesort time
        start = clock();
        // mergesort
        finish = clock(); 
        cout << setprecision(5) << fixed << calcTime(start,finish) << ",";

        // bubble sort
        start = clock();
        sortBubble(&elements[0], elements.size()-1);
        finish = clock();
        cout << setprecision(5) << fixed << calcTime(start,finish) << ",";

        // insertion sort
        start = clock();
        sortInsertion(&elements[0], elements.size()-1);
        finish = clock();
        cout << setprecision(5) << fixed << calcTime(start,finish) << ",";

        cout << "\n";
    }
}
