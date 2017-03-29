
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

	DListQueue<Student> *line;

	string filePath, fileLine;
	ifstream givenFile;

	cout << "Enter file path: ";
	cin >> filePath;

	givenFile.open(filePath);
	cout << "Opened file" << endl;

	if(givenFile.fail())
	{
		cout << "Error: File doesn't exist." << endl;
		return 1;
	}

	getline(givenFile, fileLine);
	cout << "Got line " << endl;
	windowsOpen = stoi(fileLine);

	while(!givenFile.eof())
	{

		getline(givenFile, fileLine);
		cout << "line = " << fileLine << endl;
		timeArrived = stoi(fileLine);
		timeArrived*=60;

		if(!givenFile.eof())
		{
			cout << "about to get line again" << endl;
			getline(givenFile, fileLine);
			studArriving = stoi(fileLine);

			for(int idx = 0; idx < studArriving; ++idx)
			{
				cout << "index: " << idx << "Stud arriving = " << studArriving << endl;
				++studCount;
				cout << "Added one to stud count" << endl;
				Student *student = new Student();
				cout << "made a new student" << endl;
				cout << "about to set id" << endl;
				student->id = studCount;
				cout << "hi" << endl;
				cout << "about to set time arrived" << endl;
				student->setTimeArrived(timeArrived);
				cout << "set time arrived " << endl;

				cout << "INDEX " << idx  << endl;

				if(!givenFile.eof())
				{
					cout << "about to get another line" << endl;
					getline(givenFile, fileLine);
					timeAtWindow = stoi(fileLine);
					cout << "got another line" << endl;
					cout << "index is " << idx << endl;

					cout << "time at window: " << timeAtWindow << endl;
					student->setTimeAtWindow(timeAtWindow);	
					cout << "Set time at window to " << timeAtWindow <<endl ;

					cout << "short wait time: " << shortWaitTime << endl;
					cout << "timeAtWindow: " << timeAtWindow << endl;

					
					if(idx <= windowsOpen-1)
					{
						cout << "in if statement" << endl;
						student->setTimeWaited(0.0);

						if(idx == 0)
						{
							shortWaitTime = student->getTimeAtWindow();
						}
						else
						{
							if(student->getTimeAtWindow() < shortWaitTime)
							{
								shortWaitTime = student->getTimeAtWindow();
							}
						}
						
					}

					//might be +1
					else if(idx > (windowsOpen-1))
					{
						
					}
					else
					{
						
						if(shortWaitTime != 0)
						{
							float timeWaited= student->getTimeArrived() + shortWaitTime;
							student->setTimeWaited(timeWaited);
							cout << cout << "Student " << idx << " time waited is " << timeWaited;
						}
					}
					line->insertBack(*student);
					cout << "Put student on queue" << endl;
				
					shortWaitTime = 0;
				}
			}

			//reset count of students arriving per hour
		}
	}

	float waitTime[studCount];
	for(int i = 0; i < studCount; ++i)
	{
		Student s = line->removeFront();
		cout << "Removed student" << endl;
		waitTime[i] = s.getTimeWaited();
		cout << "put wait time in array" << endl;
	}


	return 0;
}
