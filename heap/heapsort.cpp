#include <algorithm>

void percDown(int elements[], const int start, const int end) {
    int root = start;

    while (root*2+1 < end) {
        int child = 2*root + 1;
        if ((child + 1 < end) && elements[child] < elements[child+1])
            child++;

        if (elements[root] < elements[child]) {
            std::swap(elements[child], elements[root]);
            root = child;
        }
        else 
            return;
    }
}

void heapsort(int elements[], const int size) {
    int end;

    for (int i = (size-2)/2; i >= 0; i--)
        percDown(elements, i, size);

    for (int i = size-1; i > 0; i--) {
        std::swap(elements[i], elements[0]);
        percDown(elements, 0, i);
    }
}
