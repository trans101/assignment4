#include <iostream>
#include <fstream>
#ifndef DLISTQUEUE_H
#ifndef STUDENT_H
#ifndef DOUBLELINKEDLIST_H

using namespace std;

int main(int argc, char** argv)
{
	//info variables
	int windowsOpen(0), timeArrived(0), studArriving(0), timeAtWindow(0);
	//measure variables
	float meanWT, medianWT

	string filePath, fileLine;
	ifstream givenFile;

	cout << "Enter file path: ";
	cin >> filePath;

	givenFile.open(filePath);

	if(givenFile.fail())
	{
		cout << "Error: File doesn't exist." << endl;
		return 1;
	}

	getline(givenFile, fileLine);
	windowsOpen = stoi(fileLine);

	while(!givenFile.eof())
	{
		getline(givenFile, fileLine);
		timeArrived = stoi(fileLine);
		getline(givenFile, fileLine);
		studArriving = stoi(fileLine);

		for(int i = 0; i < studArriving; ++i)
		{
			getline(givenFile, fileLine);
			timeAtWindow = stoi(fileLine);
		}



	}







	DListQueue line = new DListQueue();
}

#endif
#endif