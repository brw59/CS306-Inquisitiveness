#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void addData(int argc, char file[], vector<int> & storage)
{
	if(argc != 1)
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








	return 0;
}

