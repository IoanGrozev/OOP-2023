#include "Event.h"



Event::Event()
{
	strcpy(eventName, "EventName");
}

Event::Event(const char* Name, Date date, Time sTime, Time eTime)
{
	strcpy(eventName, Name);
	dateOfEvent = date;
	startTime = sTime;
	endTime = eTime;
}

void Event::setNameOfEvent(const char* name)
{
	strcpy(eventName, name);
}

void Event::setdateOfEvent(unsigned int year, unsigned int month, unsigned int day)
{
	dateOfEvent.setDay(day);
	dateOfEvent.setMonth(month);
	dateOfEvent.setYear(year);
}

void Event::setStartTime(unsigned int hour, unsigned int minutes)
{
	startTime.setHours(hour);
	startTime.setMinutes(minutes);
}

void Event::setEndTime(unsigned int hour, unsigned int minutes)
{
	endTime.setHours(hour);
	endTime.setMinutes(minutes);
}



const char* Event::geteventName() const
{
	return eventName;
}

Date Event::getdateOfEvent() const
{
	return dateOfEvent ;
}

Time Event::getstartTime() const
{
	return startTime;
}

Time Event::getendTime() const
{
	return endTime;
}



const char* Event::getDayOfW(Date dateOfEvent) const
{

	int dayOfE = 0;
	dayOfE = dateOfEvent.getDayOfWeek();
	switch (dayOfE)
	{
	case 0:return "Monday";
	case 1:return"Tuesday"; 
	case 2:return "Wednesday"; 
	case 3:return  "Thursday"; 
	case 4:return "Friday"; 
	case 5:return"Saturday"; 
	case 6:return "Sunday"; 
	}
}

void Event::printEvent() const
{
	char dayOfWeak[20];

	std::cout << "Name of event: "<< geteventName();
	std::cout << std::endl;
	std::cout << "Date: " <<dateOfEvent.getDay()<<"."<<dateOfEvent.getMonth()<<"."<<dateOfEvent.getYear();
	std::cout << std::endl;
	std::cout << "Start time: " << startTime.getHours() << ":" << startTime.getMinutes();
	std::cout << std::endl;
	std::cout << "End time: " << endTime.getHours() << ":" << endTime.getMinutes();
	std::cout << std::endl;
	/*std::cout << getDayOfW(dateOfEvent);*/

}
