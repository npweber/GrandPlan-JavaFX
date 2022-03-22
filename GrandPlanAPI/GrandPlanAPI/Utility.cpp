#include "stdafx.h"
#include "Utility.h"

#include <string>
#include <sstream>
#include <time.h>

using namespace std;

//Utility.cpp: Source of supporting functions NOT being used by the interface.
//------------------------------------------------------------------------------


//Variables used in positioning of time:
//-------------------------------------------
//Position: The current hour of the year
int position;
//WeekStart: The hour index of the day that starts the week 
//that the time provided presides in.
int weekStart;
//WeekEnd: A week (in hours) after WeekStart
int weekEnd;
//Days: The amount of days leading up to the week
int days;

//"Utiliy" Functions that help sorting out string's and int's with time info
//---------------------------------------------------------------------------

//Retrieve a substr of a "ctime" timestamp containing only 
//the current hour.
string getHH(string timeStamp) {
	return timeStamp.substr(11, 2);
}

//Get an integer using "sstream.h" from a substr of a timestamp
//containing only the day in the month.
//Then, use a method below to convert that integer to a "two digit string".
string getDD(string timeStamp) {
	int dayDigit;
	stringstream(timeStamp.substr(9, 2)) >> dayDigit;
	return convertStringDigits(dayDigit);
}

//Used to get the month number from a timestamp
string getMM(string timeStamp) {
	//Retrieve month from timestamp
	string month = timeStamp.substr(4, 3);
	//Find the right number of month
	if (month == "Jan")
		return "01";
	else if (month == "Feb")
		return "02";
	else if (month == "Mar")
		return "03";
	else if (month == "Apr")
		return "04";
	else if (month == "May")
		return "05";
	else if (month == "Jun")
		return "06";
	else if (month == "Jul")
		return "07";
	else if (month == "Aug")
		return "08";
	else if (month == "Sep")
		return "09";
	else if (month == "Oct")
		return "10";
	else if (month == "Nov")
		return "11";
	else if (month == "Dec")
		return "12";
	return "-1";
}

//Convert an integer to a string and dertermine its size.
//Then, if the size only allows for 1 digit, substitute a '0'
//before that digit.
string convertStringDigits(int i) {
	string stringDigit = to_string(i);
	if (stringDigit.size() < 2)
		stringDigit = "0" + stringDigit;
	return stringDigit;
}

//Positioning Functions: Finding the current week from a given DateStamp:
//-----------------------------------------------------------------------

//MOST IMPORTANT FUNCTION IN FILE!
//Determines the week the datestamp is pointing to, 
//so the week can be setup, in app.
void determineposition(string dateStamp) {
	//Re-Declare header time variables for input
	int month;
	int day;
	int hour;

	//From the datestamp provided, input the datestamp's properties to the variables. 
	stringstream(dateStamp.substr(5, 2)) >> month;
	stringstream(dateStamp.substr(10, 2)) >> day;
	stringstream(dateStamp.substr(15, 2)) >> hour;

	//Count the number of days leading up to the week we are trying to find:
	//----------------------------------------------------------------------
	
	//We are on the first day to begin with
	days = 1;
	//In each month that is before the current month, add that month's amount
	//of weeks (converted to days) to the "days" variable.
	const int monthWeeks[12] = { 4, 4, 5, 4, 4, 5, 4, 5, 4, 4, 5, 4 };
	for (int m = 1; m < month; m++)
		days += monthWeeks[m - 1] * 7;

	//Now, we find the current week:
	int week = -1;
	//Iterate thru the amount of weeks in the month
	for (int i = 1; i <= monthWeeks[month - 1]; i++)
		//If the day provided (day) is before - or - at the amount of days progressed (days)
		// + The current iteration of possible week number
		//-AND-
		//It is greater than the amount of days leading to the last week:
		//The current iteration IS the right week number
		if ((day + days) <= (days + (i * 7)) && (day + days) > (days + ((i - 1) * 7))) {
			week = i;
			break;
		}

	//Now, this expression will add how many days 
	//that amount of days of weeks adds to the total days.
	days += (week - 1) * 7;
	
	//If we know how many days leads up to the current week,
	//"X24" will give us the "global index" that the week starts on.
	//(Thay way, we can know what entries to pull data from...)
	position = ((days + day) * 24) + hour;
	weekStart = days * 24;
	weekEnd = weekStart + 168;

	//**This readies the API to pull all events in the planner that corresponds
	//to the week's range of hourIndexes...
}

//Gets the days from the beginning of the week (Monday)
int getStartOffset(int month, int day) {
	//Create a "time.h" object that resembles the day and month provided
	tm timeInfo = {};
	timeInfo.tm_year = 2018 - 1900;
	timeInfo.tm_mon = month - 1;
	timeInfo.tm_mday = day;
	mktime(&timeInfo);
	//Grab the days from Sunday (tm_wday)
	//If it is 0, it's actually six; because, we are counting from Monday.
	if (timeInfo.tm_wday == 0)
		return 6;
	//Which is what substracting by one will do for that variable:
	return timeInfo.tm_wday - 1;
}