#include "IntNode.h"
#include "Student.h"
#include "DListQueue.h"
#include "DoubleLinkedList.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int main(int argc, char** argv)
{
	bool doIntro = true;

	cout << "Hello Welcome to the Registrar Office Analyzer!!" << endl << endl;


	while(doIntro)
	{


		float studCount(0.0), shortWaitTime(0.0), longWaitTime(0.0), longIdleWaitTime(0.0), idleCount(0.0);
		float totalWaitTime(0.0), totStudWaitCount(0.0);
		int overTenCount(0);

		DoubleLinkedList<float> *waitTimes = new DoubleLinkedList<float>();
		DoubleLinkedList<float> *idleTimes = new DoubleLinkedList<float>();

		//info variables
		int numWindows(0), openWindows(0), timeArrived(0), studArriving(0), timeAtWindow(0);

		int overFiveIdleCount(0);


		DListQueue<Student> *line = new DListQueue<Student>();

		//get input file
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
		try
		{
			numWindows = stoi(fileLine);
			if(numWindows == 0)
			{
				cout << "Sorry: Registrar is closed. " << endl;
				return 0;
			}
			openWindows = numWindows;
		}
		catch (invalid_argument)
		{
			return 0;
		}
		

		int windowArray[numWindows];
		int idleWindowArray[numWindows];
		for(int i = 0; i < numWindows; ++i)
		{
			windowArray[i] = 0;
			idleWindowArray[i] = 0;
		}

		//temp holder variable
		int hourBefore = 0;
		//new hour
		while(!givenFile.eof())
		{
			getline(givenFile, fileLine);
			try
			{
				timeArrived = stoi(fileLine);
			}
			catch (invalid_argument)
			{
				return 0;
			}

			for(int i = 0; i < numWindows; ++i)
			{
				windowArray[i] = 0;
			}
			shortWaitTime = 0;

			if(!givenFile.eof())
			{
				//get student ariving
				getline(givenFile, fileLine);
				try
				{
					studArriving = stoi(fileLine);
				}
				catch (invalid_argument)
				{
					return 0;
				}

				//if an hour was skipped
				if((timeArrived - hourBefore) != 1)
				{
					//add idle time for all windows because no students came that hour skipped
					int time = (timeArrived - hourBefore)*60;
					for(int i = 0; i < numWindows; ++i)
					{
						idleWindowArray[i] += time;
					}
				}
				else //no hour was skipped
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

				//make all the students for the queue per hour
				for(int idx = 0; idx < studArriving; ++idx)
				{
					
					Student *student = new Student();
					++studCount;

					student->id = studCount;

					student->setTimeArrived(timeArrived);

					if(!givenFile.eof())
					{

						getline(givenFile, fileLine);
						try
						{
							timeAtWindow = stoi(fileLine);
						}
						catch (invalid_argument)
						{
							return 0;
						}

						student->setTimeAtWindow(timeAtWindow);	
						
						line->insertBack(*student); 
					}
				}
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

				//dequeue
				Student movingStud = line->removeFront();
				
				//refactor list of wait times 
				for(int k = 0; k < numWindows; ++k)
				{
					//get number of students waiting over 10
					if(windowArray[k] > 10)
						++overTenCount;

					//add the wait time to our analysis 
					waitTimes->insertBack(windowArray[k]);

					++totStudWaitCount;
					// +=  that with moving students time at window
					windowArray[k] += movingStud.getTimeAtWindow();
					shortWaitTime = 0;

					
					//get longest wait time
					if(windowArray[k] > longWaitTime)
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
				++idleCount;

				if(idleWindowArray[i] > longWaitTime)
				{
					longIdleWaitTime = idleWindowArray[i];
				}
				if(idleWindowArray[i] > 5)
				{
					++overFiveIdleCount;
				}
			}

		}

		//copy list to array
		IntNode<float> *current = waitTimes->front;

		float waitArray[waitTimes->getSize()];
		int count = 0;
		while(current->next != NULL)
		{
			waitArray[count++] = current->data;
			current = current->next;


		}
		current = idleTimes->front;
		float idleArray[idleTimes->getSize()];
		count  = 0;
		while(current->next != NULL)
		{
			idleArray[count++] = current->data;
			current = current->next;
		}

		delete waitTimes;
		delete idleTimes;

		int middle, middle2;

		float medianWaitTime(0.0), totalIdleTimes(0), totalWaitTimes(0);
		int sizeWait(0), sizeIdle(0);

		//account for sizeof function
		sizeWait = sizeof(waitArray)/4;
		sizeIdle = sizeof(idleArray)/4;



		//odd length
		if (sizeWait%2 != 0)
			middle = (sizeWait/2)+1;
		//even length
		else
		{
			middle2 = sizeWait/2;
		}
		//get data at that position
		for(int q = 0; q < sizeWait; ++q)
		{
			//calc mean wait time
			totalWaitTimes += waitArray[q];
			if(q == middle)
			{
				medianWaitTime = waitArray[q];

			}
				
			else if(q == middle2)
			{
				float d1,d2;

				d1 = waitArray[middle2];
				d2 = waitArray[middle2+1];

				medianWaitTime = (d1 + d2)/2;


			}
		}

		for(int p = 0; p < sizeIdle; ++p)
		{
				//calc mean wait time
				totalIdleTimes += idleArray[p];
		}

		cout << endl << endl << "--Here are your results --" << endl;

		cout << "Mean Student Wait Time: " << (totalWaitTimes/sizeWait) << " Mins " << endl;
		cout << "Median Student Wait Time: " << medianWaitTime << " Mins "  << endl;
		cout << "Longest Student Wait Time: " << longWaitTime << " Mins "  << endl;
		cout << "Number of Students Waiting Over 10 Mins: " << overTenCount << endl;
		cout << "Mean Window Idle Time: " << (totalIdleTimes/sizeIdle) << " Mins "  << endl;
		cout << "Longest Window Idle Time: " << longIdleWaitTime << " Mins "  << endl;
		cout << "Number of Windows Idle Over 5 Mins: " << overFiveIdleCount << endl;

		//check if they want to do another day
		int choice;
		cout << endl << endl  << "Would you like to analyze another day? (y = 1 | n = 0) :";
		cin >> choice;
		if(choice != 1)
		{
			if(choice == 100)
			{
				cout << "You've found the secret chamber..." << endl;
				cout << "... loading ..." << endl;
				cout << endl << endl << "@rene Here is a coffee from us:" << endl;
				cout << "(´・ω・)っ由"  << endl;
			}
			doIntro = false;
			cout << "Thank you come again! " << endl;
		}
	}
	return 0;
}
//end of main