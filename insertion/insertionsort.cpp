#include <algorithm>

void insertionsort(int elements[], int size) {
    int j, temp;
    
    for (int i = i; i < size; i++) {
        j = i;
        while (j > 0 && elements[j] < elements[j-1]) {
            std::swap(elements[j], elements[j-1]);
            j--;
        }
    }
}
            
