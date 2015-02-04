/***********************************************************************
 * Module:
 *    Lesson 10, Sort Heap
 *    Brother Helfrich, CS 235
 * Author:
 *    <Jacob Casperson 4 hours>
 * Summary:
 *    This program will implement the Heap Sort
 ************************************************************************/

#ifndef SORT_HEAP_H
#define SORT_HEAP_H

/*****************************************************
 * Heap class
 ****************************************************/
template <class T>
class Heap
{
  public:
   // Default Constructor
   Heap<T>() : array(NULL), num(0){}
   // non default constructor
   Heap<T>(T theArray[], int theNum) : array(theArray), num(theNum){array--;}

   T getMax();
   void deleteMax();
   void heapify();
   void sort();
   void percolateDown(int i);
   bool notHeap();

  private:
   T * array;
   int num;
   int iRight;
   int iLeft;
   int iParent;
};

/*****************************************************
 * HEAPIFY
 ****************************************************/
template <class T>
void Heap<T> :: heapify()
{
   //  array--;
   bool notHeap;
   for (int i = num / 2; i > 0; --i) // i = iParent
   {
      iRight = 2 * i + 1;
      iLeft = 2 * i;

      if (array[iRight] > array[i] || array[iLeft] > array[i])
      {
         percolateDown(i);   //Recusrive
      }
   }

}

/*****************************************************
 * PERCOLATE DOWN
 ****************************************************/
template <class T>
void Heap<T> :: percolateDown(int i)
{
   iRight = 2 * i + 1;
   iLeft = 2 * i;

   if (array[iLeft] >  array[i] && array[iLeft] > array[iRight])
   {
      if (iLeft > num)
         return;
      //  swap me and left
      T temp = array[i];
      array[i] = array[iLeft];
      array[iLeft] = temp;
      percolateDown(iLeft);
   }

   if (array[iRight] > array[i])
   {
      if (iRight > num)
         return;
      //  swap me and right
      T temp = array[i];
      array[i] = array[iRight];
      array[iRight] = temp;
      percolateDown(iRight);
   }

   else
      return;
}

/*****************************************************
 * SORT
 ****************************************************/
template <class T>
void Heap<T> :: sort()
{
   while (num)
   {
      T temp = array[num];
      array[num] = array[1];
      array[1] = temp;
      num--;
      percolateDown(1);
   }
}

/*****************************************************
 * SORT HEAP
 * Perform the heap sort
 ****************************************************/
template <class T>
void sortHeap(T array[], int num)
{
   //Declare a heap
   Heap<T> theHeap(array,num);
   //Make it a valid heap
   theHeap.heapify();
   //Sort the heap
   theHeap.sort();
}

#endif // SORT_HEAP_H
