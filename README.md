# **GrandPlan-JavaFX**

A JavaFX application, precursor to the Android app, [GrandPlan](https://github.com/npweber/GrandPlan), capable of planning daily events only in the year 2018.

![](https://github.com/npweber/GrandPlan-JavaFX/raw/main/screenshots/Shot4.png)

## Features

**Designed as a prototype to [GrandPlan](https://github.com/npweber/GrandPlan), it has the same features implemented in a desktop application.**

Plan your day by the hour, by placing events into any hour slot of the day.

![](https://github.com/npweber/GrandPlan-JavaFX/raw/main/screenshots/Shot6.png)

![](https://github.com/npweber/GrandPlan-JavaFX/raw/main/screenshots/Shot7.png)

Get a heads up from the single week display. It shows a preview of the entire week's plans, letting you know of what's ahead.

![](https://github.com/npweber/GrandPlan-JavaFX/raw/main/screenshots/Shot1.png)

Take advantage of the smart weekly navigation controls. By selecting a month in a year and any 1st-4th week in the month, it will be hard to lose track of what week is being viewed.

![](https://github.com/npweber/GrandPlan-JavaFX/raw/main/screenshots/Shot2.png)

## Specifications

GrandPlan-JavaFX is written in, namely, JavaFX and consists of a front and backend implementation. The backend however, does not utilize `java.util.calendar` because this project was a college final for *Intro to OOP with C++* and needed to be written in C++. So, I made a personal decision to write a custom C++ backend to implement the calendar functionality. A C++ API that can load and edit the contents of a week from 2018 from cache was the result of the effort. This was then JNI compiled to be called by a Java reference, and then a backend could be used in turn to give the calendar functionality.


 ## **Author**
Nathan Weber

**GitHub** [@npweber](https://github.com/npweber/)

***Many thanks!***

