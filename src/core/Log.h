#ifndef LOG_H
#define LOG_H

#include <iomanip>
#include <iostream>
#include <string>
#include <stdarg.h>

namespace Tactics
{	
	static time_t timeSeconds = time(NULL);
	static tm currentTime;
	template<class T>
	void log(T message)
	{
		timeSeconds = time(NULL);
		localtime_s(&currentTime, &timeSeconds);
		std::cout << "[" << currentTime.tm_hour << ":" << std::setfill('0') << std::setw(2) << 
		currentTime.tm_min << ":" << std::setfill('0') << std::setw(2) << currentTime.tm_sec << "] " << message << std::endl;
	}
	template<>
	void log(bool message);
	void log(char* fmt, ...);
	void log(int color, char* fmt, ...);
	void log_error(char* fmt, ...);
	template<class T>
	void log_error(T message)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    	SetConsoleTextAttribute(hConsole, 12);
		timeSeconds = time(NULL);
		localtime_s(&currentTime, &timeSeconds);
		std::cout << "[" << currentTime.tm_hour << ":" << std::setfill('0') << std::setw(2) << 
		currentTime.tm_min << ":" << std::setfill('0') << std::setw(2) << currentTime.tm_sec << "] " << message << std::endl;
		SetConsoleTextAttribute(hConsole, 7);		
	}
	template<>
	void log_error(bool message);
}

#endif