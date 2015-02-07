/***********************************************************************
 * Module:
 *    Lesson 10, Sort Insertion
 *    Brother Helfrich, CS 235
 * Author
 *    Justin Stucki <0.5 hr> *Taken from lesson05
 * Summary:
 *    This program will implement the Insertion Sort
 ************************************************************************/

#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H
#include "../node.h"

using namespace std;

/***********************************************
 * INSERTION SORT
 * Perform the insertion sort
 **********************************************/
template <class T>
void sortInsertion(T array[], int num)
{
   Node<T>* iHead = NULL;
   bool inserted = false;
   headInsert(array[0], iHead);
  
   for (int i = 1; i < num; i++)
   {
      inserted = false;
      for (Node<T>* p = iHead; p; p = p->pNext)
      {
         //Vaule is put on the head
         if (!(array[i] > iHead->data) && inserted == false)
         {
            headInsert(array[i], iHead);
            inserted = true;
         }
         // value goes in the middle of the list
         else if (!(array[i] > p->data) && inserted == false)
         {
            insert(array[i], p->pPrev);
            inserted = true;
         }
         // value goes to the back of the list
         else if (p->pNext == NULL && inserted == false) 
         {
            insert(array[i], p);
            inserted = true;
         }
      }

   }
   int i = 0;
   //Recreates the array from linked list
   for (Node<T> * p = iHead; p; p = p->pNext)
   {
      array[i] = p->data;
      i++;
   }

}

#endif // INSERTION_SORT_H
