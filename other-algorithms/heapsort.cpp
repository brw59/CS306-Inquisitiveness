#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
/**********************************************************************
 * PERCDOWN
 *    Percelates the numbers down
 ***********************************************************************/
void percDown(vector<int> & heap, int i, int wall = -1)
{
   int swap;

   //stop condition
   if (i * 2 + 1 > heap.size())
      return;

   //check to see if it is the right or left child that needs swapping
   else if(heap[i] < heap[i * 2] && heap[i * 2] >= heap[i * 2 + 1])
   {
      //other stop condition... the wall
      if(i * 2 >= wall && wall != -1)
         return;
      swap = heap[i];
      heap[i] = heap[i * 2];
      heap[i * 2] = swap;
      //recursivle calls itself
      percDown(heap, i * 2, wall);
   }
   //same as above
   else if(heap[i] < heap[i * 2 + 1])
   {
      if(i * 2 + 1 >= wall && wall != -1)
         return;
      swap = heap[i];
      heap[i] = heap[i * 2 + 1];
      heap[i * 2 + 1] = swap;
      percDown(heap, i * 2 + 1, wall);
   }
}

/**********************************************************************
 * PERCUP
 *    Percelates the numbers up
 ***********************************************************************/
void percUp(vector<int> & heap, int i)
{
   int swap;
   //swaps if necessary
   if(i != 1 && heap[i] >= heap[i / 2])
   {
      swap = heap[i];
      heap[i] = heap[i / 2];
      heap[i / 2] = swap; 
   }
   //calls percdown to finish the swapage
   percDown(heap, i);
}

/**********************************************************************
 * SORT
 *    Sorts the heap using a heap sort
 ***********************************************************************/
void sort(vector<int> & heap)
{
   int swap;

   //sorts everything that needs sorting
   for (int wall = heap.size() - 1; wall > 1; wall--)
   {
      swap = heap[1];
      heap[1] = heap[wall];
      heap[wall] = swap;
      percDown(heap, 1, wall);
   }
}

void addData(int argc, char file[], vector<int> & storage)
{
   if(argc != 2)
   {
      cout << "To properly use the program, pass in a file name as a command"
           << "line argument" << endl
           << "example: ./a.out filename" << endl;
      exit(0);
   }

   int fData;
   ifstream fin(file);

   while(fin >> fData)
   {
      storage.push_back(fData);
   }
}


int main(int argc, char * argv[])
{
   vector<int> data;

   addData(argc, argv[1], data);

   //heapifies the vector
   for (int i = data.size(); i > 0; i--)
      percUp(data, i);

   //applies the heap sort
   sort(data);

   for (int i = 0; i <= data.size(); i++) {
       cout << data[i] << endl;
   }

   return 0;
}

