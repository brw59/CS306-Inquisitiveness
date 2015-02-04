/***********************************************************************
 * Module:
 *    Lesson 10, Sort Merge
 *    Brother Helfrich, CS 235
 * Author:
 *    <Justin Stucki 3Hrs>
 * Summary:
 *    This program will implement the Merge Sort
 ************************************************************************/
#include <cassert>
#ifndef SORT_MERGE_H
#define SORT_MERGE_H

/*****************************************************
 * SORT MERGE
 * Perform the merge sort
 ****************************************************/
template <class T>
void sortMerge(T array[], int num)
{
  
   T* pSource = array;    //Pointer to source array
   T working[num];        //Array to receive sorted items
   T* pWorking = working; //Pointer to receiving array
   bool done = false;     //Whether sort is done or not
   //Indicies to track array progress
   int iWork, iStart1, iEnd1, iStart2, iEnd2;

   do // while (!done)
   {
      //Start all indicies at 0
      iWork = iStart1 = iEnd1 = iStart2 = iEnd2 = 0;

      //Merge until the working array is full
      while (iWork < num)
      {
         //Identify first sub array to merge by linear comparisons
         while (!(pSource[iEnd1] > pSource[iEnd1 + 1]) && iEnd1 < num - 1)
            iEnd1++;
         assert(iEnd1 < num && iEnd2 < num && iWork < num);

         //If the first sub array is the entire list (aka sorted list)
         if (iStart1 == 0 && iEnd1 == num - 1)
         {
            done = true; //Sort is done
            break;       //Discontinue loops
         }

         //Identify second sub array to merge by linear comparisons
         if (iEnd1 != num - 1)
         {
            //Position second indicies
            iStart2 = iEnd2 = iEnd1 + 1;
           
            //Identify second sub array to merge
            while (!(pSource[iEnd2] > pSource[iEnd2 + 1]) && iEnd2 < num - 1)
               iEnd2++;
            assert(iEnd1 < num && iEnd2 < num && iWork < num);
           
         }
         //Special case: no second sublist exists
         else
            iStart2 = iEnd2 = -1; //Mark the second sublist
                                    
         //With sublists identified, start sorting
         while (iStart1 <= iEnd1 || iStart2 <= iEnd2)
         {
            //While both sub lists exist (Second array not marked)
            if (iStart1 <= iEnd1 && iStart2 <= iEnd2 && iStart2 != -1)
            {
               //If sublist2 has the smaller item first
               if (pSource[iStart1] > pSource[iStart2])
               {
                  pWorking[iWork] = pSource[iStart2]; //Copy item
                  iStart2++;                          //Advance index
                  iWork++;                            //Inc working array
                  assert(iEnd1 < num && iEnd2 < num && iWork < num);
                  
               }
               //If sublist1 has the smaller item first
               else
               {
                  pWorking[iWork] = pSource[iStart1]; //Copy item
                  iStart1++;                          //Advance index
                  iWork++;                            //Inc working array
                  assert(iEnd1 < num && iEnd2 < num && iWork < num);
                  
               }
            }
            //If Sublist1 still exists and 2 does not
            else if (iStart1 <= iEnd1)
               //Copy until sublist1 is done
               while (iStart1 <= iEnd1)
               {
                  if (99 >= iEnd1)
                     pWorking[iWork] = pSource[iStart1]; //Copy item
                                    
                  iStart1++;                          //Advance index
                  if (iWork < num - 1)       //If not overstepping bounds
                     iWork++;                         //Inc working array
                  assert(iEnd1 < num && iEnd2 < num && iWork < num);
               }

            //If sublist 2 still exists
            else if (iStart2 <= iEnd2)
               //Copy until sublist2 is done
               while (iStart2 <= iEnd2)
               {
                  if (99 >= iEnd2 && iEnd2 >= 0) // (JC) added if statement
                  {
                     pWorking[iWork] = pSource[iStart2]; //Copy item
                  }
                  iStart2++;
                  //Advance index
                  if (iWork < num - 1)       //If not overstepping bounds
                     iWork++;                         //Inc working array
                  assert(iEnd1 < num && iEnd2 < num && iWork < num);
               }
         }
         
         //Move iWork to whichever ended farther along
         (iEnd1 > iEnd2) ? iWork = iEnd1 : iWork = iEnd2;

         //Reposition indicies if iEnd2 is farther
         if (iEnd1 < num && iEnd2 < num
             && iEnd1 < iEnd2 && iEnd2 != num - 1)
            iStart1 = iEnd1 = iStart2 = iEnd2 = iEnd2 + 1;

         //Reposition indicies if iEnd1 is farther
         else if (iEnd1 < num && iEnd2 < num
                  && iEnd1 > iEnd2 && iEnd1 != num - 1)
            iStart1 = iEnd1 = iStart2 = iEnd2 = iEnd1 + 1;

         iWork++; //Move iWork to next position in working array
                  //If iWork becomes move than num, loop exits
      }

      //Swap the source and working
      T* tmp = pSource;
      pSource = pWorking;
      pWorking = tmp;
   }
   while (!done);

   //Copy final working array into sorce to return
   for (int i = 0; i < num; i++)
      array[i] = pWorking[i];
}


#endif // SORT_MERGE_H
