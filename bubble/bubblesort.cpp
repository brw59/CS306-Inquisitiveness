#include <algorithm>

void bubblesort(int elements[], int size) {
    bool sorted = false;
    
    while (!sorted) {
        sorted = true;
        for (int i = 0; i < size - 1; i++) {
            if (elements[i] > elements[i+1]) {
                std::swap(elements[i], elements[i+1]);
                sorted = false;
            }
        }
    }
}
