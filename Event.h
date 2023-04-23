#pragma once
#include "Date.h"
#include "Time.h"

#pragma warning(disable:4996)

class Event
{
private:
	char eventName[100];
	Date dateOfEvent;
	Time startTime;
	Time endTime;
public:
	Event();
	Event(const char* eventName,Date dateOfEvent,Time sTime,Time eTime);


	void setNameOfEvent(const char* name);
	void setdateOfEvent(unsigned int year,unsigned int month,unsigned int day);
	void setStartTime(unsigned int hour, unsigned int minutes);
	void setEndTime(unsigned int hour, unsigned int minutes);
	
	const char* geteventName() const;
	Date getdateOfEvent() const;
	Time getstartTime() const;
	Time getendTime() const;

	const char* getDayOfW(Date dateOfEvent) const;

    void printEvent() const;


};

