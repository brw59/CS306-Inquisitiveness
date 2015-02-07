#include <string>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iostream>
#include <iomanip>
#include <math.h>

#include "quicksort/quicksort-working.h"
#include "bubble/sortBubble.h"
#include "insertionSort/sortInsertion.h"

using namespace std;

void heapify(vector <int> & storage);
void heapsort(vector <int> storage);
void heapSort(vector <int> & storage);
void percolateDown(int position, int size, vector <int> & storage);

/***********************************************************************
* sorts by heap sort
***********************************************************************/
void heapsort(vector <int> storage)
{
   heapify(storage);
   heapSort(storage);
}

/***********************************************************************
* turns the vector storage into a heap
***********************************************************************/
void heapify(vector <int> & storage)
{
   //starting at the first non leaf, percolate down until to we hit root
   for (int i = floor((storage.size() - 1) / 2.0); i >= 0; i--)
      percolateDown(i, storage.size(), storage);
}

/***********************************************************************
* takes a heap and sorts it from least to greatest
***********************************************************************/
void heapSort(vector <int> & storage)
{
   //shifts all the sorted numbers to the right end of the vector 
   //while continually sorting
   for (int i = storage.size() - 1; i >= 0; i--)
   {
      swap(storage[0], storage[i]);
      percolateDown(0, i, storage);
   }
}

/***********************************************************************
* simple swap function
***********************************************************************/
void swap(int & num1, int & num2)
{
   int temp = num1;
   num1 = num2;
   num2 = temp;
}

/***********************************************************************
* Driver program
***********************************************************************/
void percolateDown(int position, int size, vector <int> & storage)
{
   //left and right child of the parent
   int leftChild = 2 * position + 1;
   int rightChild = 2 * position + 2;
   
   //checks the if the left or right child should be swapped with the parent
   while ((leftChild < size && storage[position] < storage[leftChild]) 
      || (rightChild < size && storage[position] < storage[rightChild]))
   {
      
      if (rightChild < size && storage[leftChild] < storage[rightChild])
      {   
         //swap right right child 
         swap(storage[rightChild], storage[position]);
         position = 2 * position + 2;
      }
      else
      {
         //swap left child
         swap(storage[leftChild], storage[position]);
         position = 2 * position + 1;         
      }
      
      //reinitialize the children
      leftChild = 2 * position + 1;
      rightChild = 2 * position + 2;
   }
}

void readFile(const string filename, vector<int> &vec) {
    ifstream in(filename);
    int num;

    while (in >> num)
        vec.push_back(num);
}

double calcTime(const clock_t &start, const clock_t &finish) {
    return (finish - start) / (double) CLOCKS_PER_SEC;
}

int main() {
    string files[] = {"in/Randomnm100.txt", "in/Randomnm1000.txt",
       "in/Randomnm10000.txt", "in/Randomnm100000.txt", 
       "in/Randomnm1000000.txt"};

    vector<int> elements;
    clock_t start, finish;
    cout << "number,quicksort,heapsort,bubble sort, insertion sort\n";
    for (int i = 0; i < 5; i++) {
        vector<int> temp;
        elements.clear();
        readFile(files[i], elements);
        temp = elements;
        
        cout << elements.size() << ",";

        // quicksort time
        start = clock();
        quickSort(&elements[0], 0, elements.size()-1);
        finish = clock();
        cout << setprecision(5) << fixed << calcTime(start,finish) << ",";

        elements = temp;

        // mergesort time
        start = clock();
        heapsort(elements);
        finish = clock(); 
        cout << setprecision(5) << fixed << calcTime(start,finish) << ",";

        elements = temp;

        // bubble sort
        start = clock();
        sortBubble(&elements[0], elements.size()-1);
        finish = clock();
        cout << setprecision(5) << fixed << calcTime(start,finish) << ",";

        elements = temp;

        // insertion sort
        start = clock();
        sortInsertion(&elements[0], elements.size()-1);
        finish = clock();
        cout << setprecision(5) << fixed << calcTime(start,finish) << ",";

        cout << "\n";
    }
}
