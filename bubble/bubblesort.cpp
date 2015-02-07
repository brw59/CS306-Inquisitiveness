#include <algorithm>

void bubbleSort(int elements[], int size) {
    bool sorted = false;
    int j = 1;
    
    while (!sorted) {
        sorted = true;
        for (int i = 0; i <= size - j; i++) {
            if (elements[i] > elements[i+1]) {
                std::swap(elements[i], elements[i+1]);
                sorted = false;
            }
        }
    }
}
