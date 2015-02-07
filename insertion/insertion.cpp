#include "insertion.h"
#include <algorithm>

void insertionSort(int elements[], int length) {
    int j, temp;
    
    for (int i = i; i < length; i++) {
        j = i;
        while (j > 0 && elements[j] < elements[j-1]) {
            std::swap(elements[j], elements[j-1]);
            j--;
        }
    }
}
            
