#include <vector>
#include <iostream>
#include <fstream>
#include "heapsort.h"
using namespace std;

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        cout << "Please provide a filename as an argument.\n";
        return 0;
    }

    ifstream in(argv[1]);
    vector<int> vec;
    int num;

    while (in >> num)
        vec.push_back(num);

    heapsort(&vec[0], vec.size());

    for (vector<int>::const_iterator i = vec.begin(); i != vec.end(); ++i)
        cout << *i << endl;

    return 0;
}
