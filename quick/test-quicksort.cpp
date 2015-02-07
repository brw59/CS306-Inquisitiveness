#include <vector>
#include <iostream>
#include <fstream>
#include "quicksort-working.h"
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

    quickSort(&vec[0], 0, vec.size()-1);

    for (vector<int>::const_iterator i = vec.begin(); i != vec.end(); ++i)
        cout << *i << endl;

    return 0;
}
