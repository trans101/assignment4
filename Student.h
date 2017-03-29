#include <iostream>
using namespace std;
class Student
{

private:
	float timeArrived;
	float timeWaited;
	float timeAtWindow;

public: 

	int id;

	Student();
	Student(float tArrived, float tWindow);
	~Student();

	void setTimeArrived(float arrived);
	void setTimeWaited(float waited);
	void setTimeAtWindow(float windowTime);

	float getTimeArrived();
	float getTimeWaited();
	float getTimeAtWindow();

};

Student:: Student()
{
	timeArrived = 0;
	timeWaited = 0;
	timeAtWindow = 0;

}
Student:: Student(float tArrived, float tWindow)
{
	timeArrived = tArrived;
	timeAtWindow = tWindow;
	timeWaited = 0;
}
Student:: ~Student()
{

}
void Student:: setTimeArrived(float arrived)
{
	timeArrived = arrived;
}
void Student:: setTimeWaited(float waited)
{
	timeWaited = waited;
}
void Student:: setTimeAtWindow(float windowTime)
{
	timeAtWindow = windowTime;
}
float Student:: getTimeArrived()
{
	return timeArrived;
}
float Student:: getTimeWaited()
{
	return timeWaited;
}
float Student:: getTimeAtWindow()
{	
	return timeAtWindow;
}
