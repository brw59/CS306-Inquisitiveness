/***********************************************************************
* Program:
*    Assignment 18, Merge Sort
*    Brother Ercanbrack, CS235
* Author:
*    Benjamin Ray Walker
* Summary:
*    Sort a bunch of data using a Merge Sort by writing to two files
*    and reading them back again
************************************************************************/

#include <iostream>
#include <fstream>
#include <stdio.h>
using namespace std;

/**********************************************************************
 * use three files to sort data.
 * files "writeFile2" and "writeFile3" are the files with temporary
 * data stored in them. Data is read from "writeFile1" and separated into
 * one of the other two files according to decending rank
 * File 2 and 3 are then combined following the merge sort process
 * and put back into file 1
 *
 * Note: all variables ending in "1" "2" or "3" corresponds to all of
 * the other variables with the same ending of "1" "2" or "3", including
 * the three file names. This was done to make it easier to follow.
 ***********************************************************************/
int main(int argc, char *argv[])
{
   // read in file name
   char * fileName;
   if (argc > 1)
   {
      fileName = argv[1];
   }
   // otherwise prompt for user input of filename
   else
   {
      cout << "Enter input filename: ";
      fileName = new char[80];
      cin >> fileName;
   }

   // for code reading purposes, every file has "1" "2" or "3" postscripts
   ifstream input1;
   ifstream input2;
   ifstream input3;

   // validate file
   input1.open(fileName);
   if (input1.fail())
   {
      cout << "ERROR: Filename Invalid" << endl;
      return 0;
   }

   // this variable counts the groups of increasing numbers
   // in the "writeFile1.data" only
   // i.e.
   // 1,2,3,4, 3,5,7,8,9,10, 13,17,24, 4,58,60,90, 50,51
   // is five groups separated by spaces for read-ability
   int orderedGroups = -1; // anything but zero

   // one output for each file for readability
   ofstream output1;
   ofstream output2;
   ofstream output3;
         
   int num;
   int dataCount = 0;

   int count = 0;

   // take all data in given file and transfer to the new file
   output1.open("writeFile1.data");
   while (input1 >> num)
   {
      output1 << num << " ";
      count++;
   }

   input1.close();
   output1.close();

   // when there is no increment in "orderedGroups" it means there
   // is only one group and the set is organized
   while (orderedGroups != 0)
   {
      orderedGroups = 0;

      // from the 1st file, separate into two separate files according
      // to increasing values (using merge sort technique)
      input1.open("writeFile1.data");
      output2.open("writeFile2.data");
      output3.open("writeFile3.data");

      // place the first value in the first File by default
      int prevNum;
      input1 >> prevNum;
      output2 << prevNum << " ";

      
      bool swapFile = false;
      while (input1 >> num)
      {
         // compare the values in file1 to those before it
         // if the previous number is smaller than the current
         // number, then the merge sort technique calls to
         // switch which file it's placed it
         if (num < prevNum)
         {
            // if it ever makes it into this "if-statement"
            // then "writeFile1.data" is not sorted yet
            orderedGroups += 1;
            // whichever file data is inputted into, swap the file
            if (swapFile)
               swapFile = false;
            else
               swapFile = true;
         }

         // input to file2
         if (!swapFile)
         {
            output2 << num << " ";  
         }
         // input to file3
         else
         {
            output3 << num << " ";
         }
         // keep track of last inputted number to compare
         prevNum = num;
      }

      input1.close();
      output2.close();
      output3.close();

      // this is what determines if all has been sorted, if this is still zero
      if (orderedGroups == 0)
         break;

      // use the data from file 2 and 3 and recombine them, sorted groups
      // at a time back into the main file
      output1.open("writeFile1.data");
      input2.open("writeFile2.data");
      input3.open("writeFile3.data");

      // current read file values are kept track of for later comparison with
      // the previous file inputs
      int secondFile;
      int thirdFile;

      input2 >> secondFile;
      input3 >> thirdFile;

      // previous file inputs are kept track of for comparison with the last
      // read corresponding file value
      int secondFilePrev = secondFile;
      int thirdFilePrev = thirdFile;

      input2 >> secondFile;
      input3 >> thirdFile;

      // if any time these become true, then the a file has been emptied
      // so the opposing file will empty the rest of it's contents into file1
      bool inputFile2 = false;
      bool inputFile3 = false;

      bool swapInput;

      // if any time one of these becomes true, then a file has reached the end
      // of one of the groups within the file, so the opposing file will empty
      // the rest of the current group it contains
      bool emptySecond = false;
      bool emptyThird = false;
      
      for (;;)
      {
         // this will be called if the third file reached the end of it's group
         if (emptySecond)
         {
            // check for multiple values within the same group that
            // need to be inserted in
            while (secondFilePrev <= secondFile && !inputFile3)
            {
               output1 << secondFilePrev << " ";
               secondFilePrev = secondFile;
               // just in case this causes the end of the file
               if (!(input2 >> secondFile))
                  inputFile3 = true;
            }
            // insert value and read in next value one more time
            output1 << secondFilePrev << " ";
            secondFilePrev = secondFile;
            if (!(input2 >> secondFile))
               inputFile3 = true;
            emptySecond = false;
         }
         // this will be called if the second file reached the end of a group
         else if (emptyThird)
         {
            // check for multiple values to be read in
            while (thirdFilePrev <= thirdFile && !inputFile2)
            {
               output1 << thirdFilePrev << " ";
               thirdFilePrev = thirdFile;
               // check for end of file
               if (!(input3 >> thirdFile))
                  inputFile2 = true;
            }
            // insert one more time
            output1 << thirdFilePrev << " ";
            thirdFilePrev = thirdFile;
            if (!(input3 >> thirdFile))
               inputFile2 = true;
            emptyThird = false;
         }

         // compare between the two values between files for which
         // one is smaller
         if (secondFilePrev <= thirdFilePrev)
            // input file2 data
            swapInput = true;
         else
            // input file3 data
            swapInput = false;

         // this is the file2 input process
         if (swapInput)
         {
            // check to see if it's the last item in the group
            if (secondFilePrev <= secondFile)
            {
               output1 << secondFilePrev << " ";
            }
            // if it is the last item in the group, then read it in
            // then set the variable to read in the rest of the other
            // file's current group
            else
            {
               output1 << secondFilePrev << " ";
               emptyThird = true;
            }

            // increment corresponding values to the new values to compare
            // for this file
            secondFilePrev = secondFile;    
            if (!(input2 >> secondFile))
               inputFile3 = true;
         }
         // file3 gets to input
         else
         {
            // check for end of group
            if (thirdFilePrev <= thirdFile)
            {
               output1 << thirdFilePrev << " ";
            }
            // if it is the end of the group, then set the variable
            // to read in all the values of the other group
            else
            {
               output1 << thirdFilePrev << " ";
               emptySecond = true;
            }

            // set file3 data to the data it should be
            thirdFilePrev = thirdFile;
            if (!(input3 >> thirdFile))
               inputFile2 = true;
         }

         // this means file3 has reached an end, so read in the rest
         // of file2
         if (inputFile2)
         {
            output1 << secondFilePrev << " ";
            output1 << secondFile << " ";
            while (input2 >> secondFile)
               output1 << secondFile << " ";
            break;
         }

         // file2 reached an end, so read in the rest of file3
         if (inputFile3)
         {
            output1 << thirdFilePrev << " ";
            output1 << thirdFile << " ";
            while (input3 >> thirdFile)
               output1 << thirdFile << " ";
            break;
         }
      }

      output1.close();
      input2.close();
      input3.close();
   }  

   // display the sorted data contained in "writeFile1.data"
   int temp = 0;
   input1.open("writeFile1.data");
   while (input1 >> temp)
//      cout << temp << " ";
      ;
   cout << endl;
   input1.close();

   remove("writeFile2.data");
   remove("writeFile3.data");

   return 0;
}
