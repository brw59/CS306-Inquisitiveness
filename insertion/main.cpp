#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "insertion.h"
using namespace std;

int main(int argc, char** argv) {
    vector<int> elements;
    ifstream in(argv[1]);
    int num;
    while (in >> num)
        elements.push_back(num);

    insertionSort(&elements[0], elements.size()-1);
}
