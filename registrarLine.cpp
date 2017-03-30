
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
	int longWaitTime(0);
	float totalWaitTime(0.0);
	int overTenCount(0);

	DoubleLinkedList<float> *waitTimes;
	DoubleLinkedList<float> *idleTimes;

	//info variables
	int numWindows(0), openWindows(0), timeArrived(0), studArriving(0), timeAtWindow(0);

	int overFiveIdleCount(0);


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
	numWindows = stoi(fileLine);
	openWindows = numWindows;

	int windowArray[numWindows];
	int idleWindowArray[numWindows];
	for(int i = 0; i < numWindows; ++i)
	{
		windowArray[i] = 0;
		idleWindowArray[i] = 0;
	}

	//temp holder variable
	int hourBefore(0);

	//new hour
	while(!givenFile.eof())
	{
		getline(givenFile, fileLine);
		timeArrived = stoi(fileLine);


		if(!givenFile.eof())
		{
			getline(givenFile, fileLine);
			studArriving = stoi(fileLine);

			if((timeArrived - hourBefore) != 1)
			{
				//add idle time for all windows because no students came that hour skipped
				int time = (timeArrived - hourBefore)*60;
				for(int i = 0; i < numWindows; ++i)
				{
					idleWindowArray[i] += time;
				}

			}
			else //is = 1
			{
				//clear idle times
				//check if students arriving is less than windows
				//window does not get student during this hour
				if(studArriving < numWindows)
				{
					int num = (numWindows - studArriving);
					for(int j = 0; j < num; ++j)
					{
						idleWindowArray[j] += 60;
					}

					//clear the rest
					for(int j = (num-1); j < numWindows; ++j)
					{
						idleWindowArray[j] = 0;
					}
				}
				else //students are greater than or equal to windows
				{
					//clear everything
					for(int j = 0; j < numWindows; ++j)
					{
						idleWindowArray[j] = 0;
					}
				}
			}
			hourBefore = timeArrived;



			for(int idx = 0; idx < studArriving; ++idx)
			{
				++studCount;

				Student *student = new Student();

				student->id = studCount;

				student->setTimeArrived(timeArrived);

				if(!givenFile.eof())
				{

					getline(givenFile, fileLine);
					timeAtWindow = stoi(fileLine);

					student->setTimeAtWindow(timeAtWindow);	
					
					line->insertBack(*student);

					cout << "finished inserting in main" << endl;

				}
			}

			//reset count of students arriving per hour
		}

		//still in the hour
		//people with no wait time
		//fill up all windows
		for(int h = 0; h < numWindows; ++h)
		{
			if(line->getSize()!=0)
			{
				--openWindows;
				Student movingStud = line->removeFront();
				waitTimes->insertBack(0);
				
				//getting wait times
				//first person to go to window
				if(numWindows-1 == openWindows)
				{
					shortWaitTime = movingStud.getTimeAtWindow();
				}

				//everyone else filling up open windows
				else
				{
					if(movingStud.getTimeAtWindow() < shortWaitTime)
					{
						shortWaitTime = movingStud.getTimeAtWindow();
					}
				}

				windowArray[h] += movingStud.getTimeAtWindow();
				
			}
			
		}

		//open windows == 0
		while(line->getSize() != 0)
		{
			//means there are more people left in line
		
			//get next guy and give him that shortest wait time (ie. add it to list and total )	

			//deque
			Student movingStud = line->removeFront();
			
			//refactor list of wait times 
			for(int k = 0; k < numWindows; ++k)
			{
				//get number of students waiting over 10
				if(windowArray[k] > 10)
					++overTenCount;

				if(windowArray[k] == shortWaitTime)
				{
					//add the wait time to our analysis 
					waitTimes->insertBack(windowArray[k]);
					// +=  that with moving students time at window
					windowArray[k] += movingStud.getTimeAtWindow();
					shortWaitTime = 0;
				}
				//get longest wait time
				else if(windowArray[k] > longWaitTime)
				{
					longWaitTime = windowArray[k];
				}
			}
			//reset short wait time
			for(int k = 0; k < numWindows; ++k)
			{
				if(k == 0)
				{
					shortWaitTime = windowArray[k];
				}
				else
				{
					if(windowArray[k] < shortWaitTime)
					{
						shortWaitTime = windowArray[k];
					}
				}
			}
		}


		//set into idle wait time list
		for(int i = 0; i < numWindows; ++i)
		{
			idleWindowArray[i] += (60 - windowArray[i]);
			idleTimes->insertBack(idleWindowArray[i]);
		}

	}



	//calc mean wait time
	//calc median wait time
	float totalTimes = 0.0;
	IntNode<float> *curr = waitTimes->front;
	while(curr->next != NULL)
	{
		totalTimes += curr->data;
		curr = curr->next;
	}
	cout << "Mean Student Wait Time: " << totalTimes/studCount << endl;
	cout << "Longest Student Wait Time: " << longWaitTime << endl;
	cout << "Number of Students Waiting Over 10 Mins: " << overTenCount << endl;



	return 0;
}
