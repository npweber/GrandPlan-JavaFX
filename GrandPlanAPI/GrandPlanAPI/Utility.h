#pragma once
//Header for Utility.cpp
#ifndef Utility_h
#define Utility_h

#include <string>

using namespace std;

//Position Variables
extern int position;
extern int weekStart;
extern int weekEnd;
extern int days;

//Source functions
void determineposition(string dateStamp);
int getStartOffset(int month, int day);

string convertStringDigits(int num);
string getHH(string timeStamp);
string getDD(string timeStamp);
string getMM(string timeStamp);

#endif
