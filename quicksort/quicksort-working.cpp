#include "quicksort-working.h"
#include <algorithm>
using namespace std;

void quickSort(int numbers[], int beginning, int end) 
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
          quickSort(numbers, beginning, right);
    if (left < end)
          quickSort(numbers, left, end);
}
