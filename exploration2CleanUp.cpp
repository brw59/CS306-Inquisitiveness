/***********************************************************************
 * Program:
 *    Lesson 10, Sorting
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich and the Gang
 * Summary: 
 *    This is a driver program to exercise various Sort algorithsm. When you
 *    submit your program, this should not be changed in any way.  That being
 *    said, you may need to modify this once or twice to get it to work.
 ************************************************************************/

#include <iostream>                      // for CIN and COUT
#include <iomanip>                       // for SETW
#include <ctime>                         // for time(), part of the random process
#include <stdlib.h>                      // for rand() and srand()
#include <istream>                       // for input data read
#include <vector>                        // for buffer when reading data
#include "sortValue.h"                   // for SortValue to instrument the sort algorithms
#include "bubble/sortBubble.h"           // for sortBubble()
#include "selection/sortSelection.h"     // for sortSelection()
#include "insertionSort/sortInsertion.h" // for sortInsertion()
#include "binary/sortBinary.h"           // for sortBinary()
#include "heap/sortHeap.h"               // for sortHeap()
#include "merge/sortMerge.h"             // for sortMerge()
#include "quicksort/sortQuick.h"         // for sortQuick()
using namespace std;

// prototypes for our test functions
void compareSorts(string fileName, long fromSize, long toSize, int option, int skip);
void compareSortsAutomated(string filename);
void testIndividualSorts(int choice);

/******************************************
 * SORT NAME AND FUNCTION
 * This facilitates testing a number
 * of sorts
 *****************************************/
struct SortNameAndFunction
{
   const char * name;
   void (* sortInteger)(int       array[], int num);
   void (* sortValue  )(SortValue array[], int num);
};

/***************************************************************************
 * Get information from a file!
 *
 * NOTE: not used yet!
 ***************************************************************************/
const SortNameAndFunction SORTS[] =
{
   { NULL,             NULL,          NULL          },
   { "Bubble Sort",    sortBubble,    sortBubble    },
   { "Selection Sort", sortSelection, sortSelection },
   { "Insertion Sort", sortInsertion, sortInsertion },
   { "Binary Sort",    sortBinary,    sortBinary    },
   { "Heap Sort",      sortHeap,      sortHeap      },
   { "Merge Sort",     sortMerge,     sortMerge     },
   { "Quick Sort",     sortQuick,     sortQuick     }
};


void readTestArrays(
      SortValue * &arrayStart,
      SortValue * &arraySort,
      long & num,
      string filename = "Randomnm40000.txt")
{
   int temp;
   vector<int> buffer;

   ifstream fin(filename.c_str());

   if(!fin.is_open())
   {
      cerr << "File not found! Aborting application...\n";
      exit(0);
   }

   while(fin >> temp)
   {
      buffer.push_back(temp);
   }

   // copy to array to fit in with the other kids
   num = buffer.size();
   arrayStart = new(nothrow) SortValue[num];
   arraySort  = new(nothrow) SortValue[num]; // empty?

   for (int i = 0; i < num; i++)
      arrayStart[i] = buffer[i];

}

/*******************************************
 * CREATE TEST ARRAYS
 * Generate test arrays for the purpose of
 * comparing sorts.  This function has one
 * client: compareSort()
 * 
 * args:
 * option of which test to run
 *****************************************/
void createTestArrays(SortValue * & arrayStart,
      SortValue * & arraySort,
      long & num, int option)
{   
   // allocate the array
   arrayStart = new(nothrow) SortValue[num];
   arraySort  = new(nothrow) SortValue[num];
   if (arrayStart == NULL || arraySort == NULL)
   {
      cout << "Unable to allocate that much memory";
      return;
   }

   switch (option)
   {
      case 5:  // random but with a small number of possible values
         for (int i = 0; i < num; i++)
            arrayStart[i] = rand() % 10;
         break;
      case 4: // almost sorted in ascending order
         for (int i = 0; i < num; i++)
            arrayStart[i] = i + rand() % 10;
         break;
      case 3: // already sorted in decending order
         for (int i = 0; i < num; i++)
            arrayStart[i] = num - i;
         break;
      case 2: // already sorted in ascending order
         for (int i = 0; i < num; i++)
            arrayStart[i] = i;
         break;
      case 1: // random numbers
      default: 
         for (int i = 0; i < num; i++)
            arrayStart[i].random();
   }
}

void compareSortsAutomated(string filename)
{
   // allocate the array
   SortValue* arrayStart;
   SortValue* arraySort;
   long num;

   readTestArrays(arrayStart, arraySort, num, filename);

   // get ready with the header to the table
   srand(time(NULL));
   cout.setf(ios::fixed);
   cout.precision(2);
   system("clear");
   cout << "      Sort Name    Time       Assigns      Compares\n";
   cout << " ---------------+-------+-------------+-------------\n";

   for (int iSort = 4; iSort <= 7; iSort++)
   {
      // get ready by copying the un-sorted numbers to the array
      for (int iValue = 0; iValue < num; iValue++)
         arraySort[iValue] = arrayStart[iValue];
      arraySort[0].reset();

      // perform the sort
      int msBegin = clock();
      SORTS[iSort].sortValue(arraySort, num);
      int msEnd = clock();

      // report the results
      cout << setw(15) << SORTS[iSort].name                    << " |"
         << setw(6)  << (float)(msEnd - msBegin) / 1000000.0 << " |"
         << setw(12) << arraySort[0].getAssigns()            << " |"
         << setw(12) << arraySort[0].getCompares()           << endl;
   }

   // all done
   delete [] arrayStart;
   delete [] arraySort;
}

/*******************************************
 * COMPARE SORTS
 * Compare the relative speed of the various sorts
 ******************************************/
void compareSorts(string fileName, long fromSize, long toSize, int option, int skipSize = 5000)
{
   // allocate the array
   SortValue * arrayStart;
   SortValue * arraySort;

   if (option == 6)
      readTestArrays(arrayStart, arraySort, toSize);
   else
      createTestArrays(arrayStart, arraySort, toSize, option);

   srand(time(NULL));

   // get ready with the header to the table
   cout.setf(ios::fixed);
   cout.precision(2);
   system("clear");
   cout << "      Sort Name    Time       Assigns      Compares\n";

   ofstream fout;
   fout.open(fileName.c_str(), ios::app);

   for (long inputSize = fromSize; inputSize < toSize; inputSize += skipSize)
   {
      if (arrayStart == NULL || arraySort == NULL)
         return;

      cout << inputSize << "\n";
      cout << " ---------------+-------+-------------+-------------\n";


      fout << inputSize << ", ";

      for (int iSort = 1; iSort <= 7; iSort++)
      {
         // get ready by copying the un-sorted numbers to the array
         for (int iValue = 0; iValue < inputSize; iValue++)
            arraySort[iValue] = arrayStart[iValue];
         arraySort[0].reset();

         // perform the sort
         int msBegin = clock();
         SORTS[iSort].sortValue(arraySort, inputSize);
         int msEnd = clock();

         // report the results
         double timeResults = (double)(msEnd - msBegin) / 1000000.0;

         fout << timeResults << ", ";      

         cout << setw(15) << SORTS[iSort].name          << " |"
            << setw(6)  << timeResults                << " |"
            << setw(12) << arraySort[0].getAssigns()  << " |"
            << setw(12) << arraySort[0].getCompares() << endl;
      }


      fout << endl;

   }

   fout.close();

   // all done
   delete [] arrayStart;
   delete [] arraySort;
}

/*******************************************
 * TEST INDIVIDUAL SORTS
 * For a given sort selected by "choice",
 * feed it 100 random 3-digit integers and
 * display the results.
 *
 * To test with a smaller number of items,
 * for debugging purposes, just set the size variable
 * to a smaller value such as "size = 10;"
 *******************************************/
void testIndividualSorts(int choice)
{
   assert(choice >= 1 && choice <= 7);

   // prepare the array
   int array[] =
   {
      889, 192, 528, 675, 154, 746, 562, 482, 448, 842, 929, 330, 615, 225,
      785, 577, 606, 426, 311, 867, 773, 775, 190, 414, 155, 771, 499, 337,
      298, 242, 656, 188, 334, 184, 815, 388, 831, 429, 823, 331, 323, 752,
      613, 838, 877, 398, 415, 535, 776, 679, 455, 602, 454, 545, 916, 561,
      369, 467, 851, 567, 609, 507, 707, 844, 643, 522, 284, 526, 903, 107,
      809, 227, 759, 474, 965, 689, 825, 433, 224, 601, 112, 631, 255, 518,
      177, 224, 131, 446, 591, 882, 913, 201, 441, 673, 997, 137, 195, 281,
      563, 151
   };

   int size = sizeof(array) / sizeof(array[0]);

   // display the list before they are sorted
   cout << SORTS[choice].name << endl;
   cout << "\tBefore:\t" << array[0];
   for (int i = 1; i < size; i++)
      cout << (i % 10 == 0 ? ",\n\t\t" : ", ")
         << array[i];
   cout << endl << endl;

   // perform the sort
   SORTS[choice].sortInteger(array, size);

   // report the results
   bool sorted = true;
   cout << "\tAfter:\t" << array[0];

   for (int i = 1; i < size; i++)
   {
      cout << (i % 10 == 0 ? ",\n\t\t" : ", ")
         << array[i];
      if (array[i - 1] > array[i])
         sorted = false;
   }

   cout << endl;
   cout << "The array is "
      << (sorted ? "" : "NOT ")
      << "sorted\n";
}


/**********************************************************************
 * MAIN
 * This is just a simple menu to launch a collection of tests
 ***********************************************************************/
int main(const int argc, const char* argv[])
{

   if (argc < 4)
   {
      //                                     1       2         3             4
      cout << "Useage: $ " << argv[0] << "[typeOfInput] [fromSize] [toSize] [ResultsFileName]" << endl;
      cout << endl;
      cout << "NOTE: right now this will increment by 1,000 from fromSize to toSize";
      cout << endl;
      cout << "Types of input:";
      cout << "   1. random numbers\n";
      cout << "   2. already sorted in ascending order\n";
      cout << "   3. already sorted in decending order\n";
      cout << "   4. almost sorted in ascending order\n";
      cout << "   5. random but with a small number of possible values\n";
      cout << endl << endl;

   } else {
      compareSorts(argv[4], atol(argv[2]), atol(argv[3]), atoi(argv[1]));
   }

   return 0;
}
