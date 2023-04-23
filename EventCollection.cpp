#include "EventCollection.h"

EventCollection::EventCollection()
{
	currentSize = 1;
	maxSize = 8;
	events = new Event[maxSize];
}

EventCollection::~EventCollection()
{
	delete[] events;
	events = nullptr;
	currentSize = 0;
	maxSize = 0;
}

EventCollection::EventCollection(unsigned int cSize, unsigned int mSize)
{
	currentSize = cSize;
	events = new Event[currentSize];
	maxSize = mSize;
}

EventCollection::EventCollection(const EventCollection& other)
{
	currentSize = other.currentSize;
	maxSize = other.maxSize;
	events = new Event[currentSize];
	for (int i = 0; i < currentSize; i++)
	{
		events[i] = other.events[i];
	}
}

EventCollection& EventCollection::operator=(const EventCollection& other)
{
	if (this != &other)
	{
		delete[] events;
		currentSize = other.currentSize;
		maxSize = other.maxSize;
		events = new Event[currentSize];
		for (int i = 0; i < currentSize; i++)
		{
			events[i] = other.events[i];
		}

	}
	return *this;
}
void EventCollection::resize(unsigned int newSize)
{
	maxSize = newSize;

	Event* temp = new Event[maxSize];
	for (size_t i = 0; i < currentSize; i++)
	{
		temp[i] = events[i];
	}

	delete[] events;
	events = temp;
}

void EventCollection::deleteEvent(const char* name)
{

	for (int i = 0; i < currentSize-1; i++)
	{
		if (strcmp(events[i].geteventName(), name) == 0)
		{
			currentSize -= 1;
			events[i] = events[currentSize-1];
			break;
		}

	}
	Event* temp = new Event[maxSize];
	for (int i = 0; i < currentSize-1; i++)
	{
		temp[i] = events[i];
	}
	delete[] events;
	events = temp;
}

char* EventCollection::longestEvent() const
{
	unsigned int indexOfLongestEvent;
	unsigned int timeOfLongestEventInMin=0;
	unsigned int startTimeInMin;
	unsigned int endTimeInMin;
	char nameOe[100];
	for (int i = 0; i < currentSize-1; i++)
	{
		startTimeInMin = (events[i].getstartTime().getHours() * 60) + events[i].getstartTime().getMinutes();
		endTimeInMin = (events[i].getendTime().getHours() * 60) + events[i].getendTime().getMinutes();
		if (timeOfLongestEventInMin < endTimeInMin - startTimeInMin)
		{
			timeOfLongestEventInMin = endTimeInMin - startTimeInMin;
			indexOfLongestEvent = i;
		}
	}

	strcpy(nameOe, events[indexOfLongestEvent].geteventName());
	return nameOe;


}

unsigned int EventCollection::countOfMaxEventsForDate(unsigned int year, unsigned int month, unsigned int day) const
{
	unsigned int counter = 0;
	unsigned int counterEventsWeCanGo = 1;
	unsigned int minIndex = 0;
	unsigned int maxIndex = 0;
	
	for (int i = 0; i < currentSize - 1; i++)
	{
		if (events[i].getdateOfEvent().getYear() == year && events[i].getdateOfEvent().getMonth() == month && events[i].getdateOfEvent().getDay() == day)
		{
			++counter;
		}
	}

	Event* temp = new Event[counter];

	for (int i = 0; i < counter; i++)
	{
		if (events[i].getdateOfEvent().getYear() == year && events[i].getdateOfEvent().getMonth() == month && events[i].getdateOfEvent().getDay() == day)
		{
			temp[i] = events[i];
		}
	}

	for (int i = 0; i < counter-1; i++)
	{
		for (int j = i + 1; j < counter; j++)
		{
			if (temp[j].getstartTime().getHours() < temp[i].getstartTime().getHours() || temp[maxIndex].getendTime().getHours() <= temp[i].getstartTime().getHours() && temp[maxIndex].getendTime().getMinutes() < temp[i].getstartTime().getMinutes())
			{
				std::swap(temp[i], temp[j]);
			}
		}

	}

	

	for (int i = 1; i < counter; i++)
	{
		if (temp[maxIndex].getendTime().getHours() < temp[i].getstartTime().getHours() || temp[maxIndex].getendTime().getHours() <= temp[i].getstartTime().getHours() && temp[maxIndex].getendTime().getMinutes() < temp[i].getstartTime().getMinutes())
		{
			maxIndex = i;
			++counterEventsWeCanGo;
		}

	}
	delete[] temp;
	return counterEventsWeCanGo;
}

void EventCollection::printColection() const
{
	for (int i = 0; i < currentSize-1; i++)
	{
		events[i].printEvent();
	}
}


void EventCollection::addEvent(const char* name, unsigned int year, unsigned int month, unsigned int day, unsigned int startHour, unsigned int startMinutes, unsigned int endHour, unsigned int endMinutes)
{
	if (currentSize == maxSize)
	{
		resize(maxSize * 2);
	}

	events[currentSize - 1].setNameOfEvent(name);
	events[currentSize - 1].setdateOfEvent(year,month,day);
	events[currentSize - 1].setStartTime(startHour, startMinutes);
	events[currentSize - 1].setEndTime(endHour, endMinutes);

	currentSize++;
}

