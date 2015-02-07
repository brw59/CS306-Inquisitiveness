/***********************************************************************
* Program:
*    Assignment 17, Heap Sort
*    Brother Ercanbrack, CS 235
* Author: 
*    Justin Hurley
* Summary: 
*   Takes a file from the command line, stores every number in a vector,
*   then it uses a heap sort to sort the items.
* Notes
***********************************************************************/

// #include <iostream>
// #include <fstream>
// #include <vector>
#include <math.h>

using namespace std;

//prototypes
void heapify(vector <int> & storage);
void heapsort(vector <int> storage);
void heapSort(vector <int> & storage);
void percolateDown(int position, int size, vector <int> & storage);

/***********************************************************************
* Driver program
***********************************************************************/
// int main(int argc, char * argv[])
// {
//    ifstream fin(argv[1]);
   
//    //error check
//    if (fin.fail())
//    {
//       cout << "Unable to open file.\n";
//       return 0;
//    }
   
//    vector <int> storage;
//    int data;
   
//    //read in data
//    while (fin >> data)
//       storage.push_back(data);

//    sort(storage);

//    //display
//    for (int i = 0; i < storage.size(); i++)
//       cout << storage[i] << " ";
//    cout << endl;
   
//    return 0;
// }

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
void heapify(vector <int> storage)
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
