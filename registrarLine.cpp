
#include "IntNode.h"
#include "Student.h"
#include "DListQueue.h"
#include "DoubleLinkedList.h"
#include <iostream>
#include <fstream>
#include <string>



using namespace std;

int main(int argc, char** argv)
{
	int studCount(0);
	int shortWaitTime(0);

	//info variables
	int windowsOpen(0), timeArrived(0), studArriving(0), timeAtWindow(0);
	//measure variables
	float meanWT, medianWT;

	DListQueue<Student> *line;

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
		timeArrived = (stoi(fileLine))*60;

		getline(givenFile, fileLine);
		studArriving = stoi(fileLine);

		for(int i = 0; i < studArriving; ++i)
		{
			++studCount;
			Student *student = new Student();
			student->id = studCount;
			student->setTimeArrived(timeArrived);

			getline(givenFile, fileLine);
			timeAtWindow = stoi(fileLine);

			student->setTimeAtWindow(timeAtWindow);	

			if(timeAtWindow < shortWaitTime)
				shortWaitTime = timeAtWindow;

			if(i <= windowsOpen)
			{
				student->setTimeWaited(0);
			}
			else
			{
				if(shortWaitTime != 0)
				{
					float timeWaited= student->getTimeArrived() + shortWaitTime;
					student->setTimeWaited(timeWaited);
				}

			}
			line->insertBack(*student);
		
			shortWaitTime = 0;

		}
	}

	float waitTime[studCount];
	for(int i = 0; i < studCount; ++i)
	{
		Student *s = line->removeFront();
		waitTime[i] = s->getTimeWaited();
	}


	return 0;
}
