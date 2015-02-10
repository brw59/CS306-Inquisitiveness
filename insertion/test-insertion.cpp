#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "insertionsort.h"
using namespace std;

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Please provide a filename as an argument.\n";
        return 0;
    }

    vector<int> vec;
    ifstream in(argv[1]);
    int num;
    while (in >> num)
        vec.push_back(num);

    insertionsort(&vec[0], vec.size());

    for (vector<int>::const_iterator i = vec.begin(); i != vec.end(); ++i)
        cout << *i << endl;

    return 0;
}
