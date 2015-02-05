/***********************************************************************
 * Module:
 *    Lesson 10, Sort Bubble
 *    Brother Helfrich, CS 235
 * Author:
 *    <Jacob Casperson>
 * Summary:
 *    This program will implement the Bubble Sort
 ************************************************************************/

#ifndef SORT_BUBBLE_H
#define SORT_BUBBLE_H

/*****************************************************
 * SORT BUBBLE
 * Perform the bubble sort
 * Code taken from CS124 textbook
 ****************************************************/
template <class T>
void sortBubble(T array[], int num)
{
   // did we switch two values?
   bool switched = true;

   // The outer loop checks each spot in the array and looks for the
   // item to go there.
   for (int iSpot = num - 1; iSpot >= 1 && switched; iSpot--)

      // The inner loop brings the correct item to the spot.  This is done
      // by "bubbling" the item to the correct location.
      for (int iCheck = 0, switched = false; iCheck <= iSpot - 1; iCheck++)
      {
         if (array[iCheck] > array[iCheck + 1])
         {
            T temp = array[iCheck]; // swap 2 items if out of order
            array[iCheck] = array[iCheck + 1];
            array[iCheck + 1] = temp;
            switched = true; 
         }
      }
}


#endif // SORT_BUBBLE_H
