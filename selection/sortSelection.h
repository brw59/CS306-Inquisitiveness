/***********************************************************************
 * Module:
 *    Lesson 10, Sort Select
 *    Brother Helfrich, CS 235
 * Author:
 *    Justin Stucki <1 Hr>
 * Summary:
 *    This program will implement the Selection Sort
 ************************************************************************/

#ifndef SORT_SELECTION_H
#define SORT_SELECTION_H

/*****************************************************
 * SORT SELECTION
 * Perform the selection sort
 * Taken from 13.1 of the Textbook
 ****************************************************/
template <class T>
void sortSelection(T array[], int num)
{
   //Define the "sorted side"
   int iWall = 0;

   //Place each item in sorted position once
   while (iWall < num)
   {
      //Find teh smallest unsorted item
      int smallestPosition = iWall;
      for (int i = iWall; i < num; i++)
         if (array[smallestPosition] > array[i])
            smallestPosition = i;

      //Place it in next slot
      T tmp = array[iWall];
      array[iWall] = array[smallestPosition];
      array[smallestPosition] = tmp;
      iWall++;
   }
}


#endif // SORT_SELECTION_H
