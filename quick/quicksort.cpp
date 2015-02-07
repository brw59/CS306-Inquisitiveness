#include <algorithm>
using namespace std;

void quicksort(int numbers[], int beginning, int end) 
{
    int left = beginning, right = end;
    int pivot = numbers[(beginning + end) / 2];
 	int temp;

    while (left <= right) 
    {
          while (numbers[left] < pivot)
                left++;
          while (numbers[right] > pivot)
                right--;
          if (left <= right) 
          {
                swap(numbers[left], numbers[right]);
                left++;
                right--;
          }
    };
 
    if (beginning < right)
          quicksort(numbers, beginning, right);
    if (left < end)
          quicksort(numbers, left, end);
}

void quicksort(int elements[], int size) {
    quicksort(elements, 0, size-1);
}
