#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std;

/***************************************************************************
 * This will grab all the numbers from a single file and store it in "numbers" 
 ***************************************************************************/
void fileToVector(char filename[], vector<int> *numbers)
{

   int fData;
   ifstream fin(filename);

   while(fin >> fData)
   {
      numbers->push_back(fData);
   }
}

/***************************************************************************
 * This will concatinate all the files passed in into one vector
 ***************************************************************************/
vector<int>* argsToNumbers(int argc, char* argv[])
{
   vector<int>* numbers = new vector<int>;

   if(argc == 1)
   {
      cout << "To properly use the program, pass in a file names seperated by a space" << endl

           << "example: ./a.out filename1 filename2 ..." << endl;
      exit(0);
   }
    
   for (int i = 0; i < argc; ++i)
   {
      fileToVector(argv[i], numbers);
   }

   return numbers;
}



int main(int argc, char * argv[])
{
   vector<int> *numbers = argsToNumbers(argc, argv);

   // sort(numbers)

   cout << "[ ";
   
   for (int i = 0; i < numbers->size(); ++i)
   {
      cout << numbers->at(i) << ", ";
   }

   cout << "]" << endl;

   return 0;
}

