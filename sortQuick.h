/***********************************************************************
 * Module:
 *    Lesson 10, Sort Quick
 *    Brother Helfrich, CS 235
 * Author:
 *    <author>
 * Summary:
 *    This program will implement the Quick Sort
 ***********************************************************************/

#ifndef SORT_QUICK_H
#define SORT_QUICK_H

/*****************************************************
 * SWAP
 * Simple swap of two items by reference
 ****************************************************/
template <class T>
void swap(T* swapMe, T* andMe)
{
   T temp = swapMe;
   swapMe = andMe;
   andMe = swapMe;
   return;
}

/*****************************************************
 * SORT QUICK
 * Perform the quick sort
 ****************************************************/
template <class T>
void sortQuick(T array[], int num)
{
   //If the array is 1 or 2 elements long
   if (num <= 2)
   {
      if (num == 1)                 //If only a single item (sorted)
         return;
      else if (array[1] > array[0]) //If 2, (sorted)
         return;
      else                          //If 2, (unsorted) swap
      {
         swap(array[0], array[1]);
         return;
      }
   }

   //If more than 2 elements are in the array
   else      
   {
      int iStart = 0;
      int iEnd   = num - 1;
      T pivot = array[num / 2];     //Identify the pivot
      while (iStart <= iEnd)
      {
         //If two elements are misplaced on opposite sides, swap
         if (((array[iStart] > pivot || array[iStart] == pivot)
              && (pivot > array[iEnd] || pivot == array[iEnd])))
         {
            swap(array[iStart], array[iEnd]);
            iStart++;
            iEnd--;
         }

         //If both are less than pivot and UNSORTED
         else if (!(array[iStart] > pivot) && !(array[iEnd] > pivot)
                  && (array[iStart] > array[iEnd]))
         {
            swap(array[iStart], array[iEnd]);
            iStart++;
         }

         //If both are less than pivot and SORTED
         else if (!(array[iStart] > pivot) && !(array[iEnd] > pivot))
            iStart++;

         //If both are greater than pivot and UNSORTED
         else if ((array[iStart] > pivot) && (array[iEnd] > pivot)
                  && (array[iStart] > array[iEnd]))
         {
            swap(array[iStart], array[iEnd]);
            iEnd--;
         }

         //If both are greater than pivot and SORTED
         else if ((array[iStart] > pivot) && (array[iEnd] > pivot))
            iEnd--;

         //If both are on the correct side of the pivor
         else
         {
            iStart++;
            iEnd--;
         }
      }

      //If indicies landed on different elements
      if (iStart > iEnd)
      {
         sortQuick(array, iStart);
         sortQuick(array + iStart, num - iStart);
      }

      //If indicies landed on the same element
      else
      {
         sortQuick(array, iStart + 1);
         sortQuick(array + iStart + 1, num - iStart + 1);
      }
   }
}

#endif // SORT_QUICK_H
