#include "stdafx.h"
#include "cpb_CPPBridge.h"
#include "DataUnit.h"
#include "Utility.h"

#include <string>
#include <fstream>
#include <sstream>
#include <time.h>

using namespace std;

//Array that holds all plannerData loaded in the current week
DataUnit plannerData[168];

//Retrieves the data from ".txt" file and loads it into the array
JNIEXPORT void JNICALL Java_cpb_CPPBridge_dataRetrieval(JNIEnv *env, jobject, jstring dateStamp) {
	
	//Clear old data before loading
	for (int i = 0; i < 168; i++) {
		plannerData[i].title = "";
		plannerData[i].description = "";
	}
	
	//Determine what data to load based on its index in time postion
	//(Read more to find what that means...)
	jboolean isCopy;
	determineposition(env->GetStringUTFChars(dateStamp, &isCopy));

	//LOAD:
	//--------
	//Open datafile
	ifstream in;
	in.open("res/txt/plannerData.txt");

	//Read data
	string line;
	int index = -1;
	while (getline(in, line)) {
		//Find if theres a new entry
		char first = line.front();
		char second;
		if(line.size() >= 3)
			second = line.at(2);
		if (first != ' ') {
			//Init a new DataUnit at the specified index, only if the globalIndex
			//read from the entry is within the range of hour index we are looking at.
			int globalIndex;
			stringstream(line.substr(0, line.find(":"))) >> globalIndex;
			if (globalIndex < weekStart || globalIndex > weekEnd)
				continue;
			//Get that "localIndex", (index within the week), if indeed it belongs in the array
			index = globalIndex - weekStart;
			plannerData[index] = DataUnit();
			continue;
		}
		//Read the info of that index's event into the newly formed DataUnit
		else if (second == 't') {
			plannerData[index].title = line.substr(line.find(":") + 1, line.size() - 1);
			continue;
		}
		else if (second == 'd') {
			plannerData[index].description = line.substr(line.find(":") + 1, line.size() - 1);
			continue;
		}
		else continue;
	}
	in.close();
}

//Adds in an event to the storage by writing to file
JNIEXPORT void JNICALL Java_cpb_CPPBridge_encodeEvent(JNIEnv *env, jobject, jint inputIndex, jstring inputTitle, jstring inputDescription) {
	//Grab the parameters from their "Java Formats"
	string title, description;
	jboolean isCopy;
	title = env->GetStringUTFChars(inputTitle, &isCopy);
	description = env->GetStringUTFChars(inputDescription, &isCopy);
	int index = weekStart + (int)inputIndex;

	//Open a stream
	ofstream out;
	out.open("res/txt/plannerData.txt", out.app);

	//Write the data
	out << index << ":\n" << "  title:" << title << "\n  description:" << description << endl;
	out.close();
}

//Removes a certain indexed event from storage
JNIEXPORT void JNICALL Java_cpb_CPPBridge_removeEvent(JNIEnv *env, jobject, jint inputIndex) {
	//Open an ifstream first to read all the lines in the file before changing
	ifstream in;
	in.open("res/txt/plannerData.txt");

	//Control variables that mark where to stop changing
	bool shouldSkip = 0;
	int skippedLineCount = 3;

	//fileContents: Buffer variable for fileData
	string fileContents = "";
	string line;
	//READ:
	while (getline(in, line)) {
		//We inputted an index corresponding to an event to remove.
		//So, if the index is found, we "skip" , and, do not read the line.
		if (line.find(to_string(weekStart + (int)inputIndex)) != string::npos)
			shouldSkip = 1;
		if (shouldSkip && skippedLineCount > 0) {
			//skippedLineNum: Allows the lines after the index line to be skipped
			//twice, and then the function returns to reading the file
			skippedLineCount--;
			continue;
		}
		if (skippedLineCount == 0)
			shouldSkip = 0;
		fileContents.append(line + "\n");
	}
	in.close();

	//Now, open a ofstream
	ofstream out;
	out.open("res/txt/plannerData.txt");

	//And, the file is updated, without the event present before
	out << fileContents;
	out.close();
}

//From the specified index, these functions grab the title or description corresponding to an event in
//the array and returns it for the interface
JNIEXPORT jstring JNICALL Java_cpb_CPPBridge_titles(JNIEnv *env, jobject, jint index) {
	return (*env).NewStringUTF(plannerData[index].title.c_str());
}

JNIEXPORT jstring JNICALL Java_cpb_CPPBridge_descriptions(JNIEnv *env, jobject, jint index) {
	return (*env).NewStringUTF(plannerData[index].description.c_str());
}

//Retrieves the current date from a C++ library
JNIEXPORT jstring JNICALL Java_cpb_CPPBridge_currentDate(JNIEnv *env) {
	//Get the C++ TimeObject, initialized to "NULL" or the current time
	time_t timeObject = time(NULL);

	//Read into char array
	char timeStamp[26];
	ctime_s(timeStamp, 26, &timeObject);

	//Return a re-formatted timestamp that the interface or api can use
	char time[26] = "";
	string dateStamp = "M:" + getMM(timeStamp) + "/" + getMM(timeStamp) + ";D:" + getDD(timeStamp) + ";H:" + getHH(timeStamp);
	stringstream(dateStamp) >> time;
	
	return (*env).NewStringUTF(time);
}

//Gets the same value that the supporting function "getStartOffset()" gets,
//except it does it based on parameters specified by the interface, so
//the interface can access the return value.
JNIEXPORT jstring JNICALL Java_cpb_CPPBridge_weekStartOffset(JNIEnv *env, jobject, jstring inputDay, jstring inputMonth) {
	//Input Java Formatted Parameters
	jboolean isCopy;
	int day;
	int month;
	stringstream(env->GetStringUTFChars(inputDay, &isCopy)) >> day;
	stringstream(env->GetStringUTFChars(inputMonth, &isCopy)) >> month;

	//Output a string format of the supporting function's output
	return (*env).NewStringUTF(to_string(getStartOffset(month, day)).c_str());
}

//"Fabricates" a dateStamp based on the parameters of "month" & "numWeek" (currentWeekNumber)
JNIEXPORT jstring JNICALL Java_cpb_CPPBridge_fabricateStamp(JNIEnv *env, jobject, jint inputMonth, jint numWeek) {
	//Start at the day of 1
	days = 1;
	//Same as "determinePostion()", count up to the month that is specified
	const int monthWeeks[12] = { 4, 4, 5, 4, 4, 5, 4, 5, 4, 4, 5, 4 };
	for (int m = 1; m < inputMonth; m++)
		days += monthWeeks[m - 1] * 7;

	//And, since the weekNumber is specified, count up to that too.
	days += (numWeek - 1) * 7;

	//Now, we are in the right day of the year,
	//just without the day being within a month and correct week in that month.

	//So, find the resulting day of the month the amount of days in the year resembles the amount of days progressed
	int month = -1;
	int monthDaysPassed = 0;
	int monthDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	//This evaluates if the current amout of days "passed" 
	//will be more than the days we are converting, if another month is counted.
	//(Meaning the next month is beyond the amount of days we have and is not correct)
	for (int i = 0; i < 12; i++) 
		//If not, count another month
		if ((monthDaysPassed + monthDays[i]) < days)
			monthDaysPassed += monthDays[i];
		//If so, we have found our month and the amount of days up to that month
		else {
			month = i + 1;
			break;
		}
	
	//Now, subtracting the days up to the current month from amount of days will yield
	//the day in the month the parameters want.
	int day = days - monthDaysPassed;

	//Lastly, output the values found in a formatted stamp
	//(Month, "M", has two values next to each other because the interface needs to
	//see the month of the date formatted AND the month with the week requested)
	string stamp = "M:" + convertStringDigits(month) + "/" + convertStringDigits((int)inputMonth) + ";D:" + convertStringDigits(day) + ";H:00";
	
	return (*env).NewStringUTF(stamp.c_str());
}