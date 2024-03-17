#include "Log.h"

namespace Tactics
{	
	template<>
	void log(bool message)
	{
		std::string value;
		if (message == 0)
			value = "False";
		else
			value = "True";
		timeSeconds = time(NULL);
		localtime_s(&currentTime, &timeSeconds);
		std::cout << "[" << currentTime.tm_hour << ":" << std::setfill('0') << std::setw(2) << 
		currentTime.tm_min << ":" << std::setfill('0') << std::setw(2) << currentTime.tm_sec << "] " << value << std::endl;		
	}
	void log(char* fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		timeSeconds = time(NULL);
		localtime_s(&currentTime, &timeSeconds);
		printf("[%02d:%02d:%02d] ", currentTime.tm_hour, currentTime.tm_min, currentTime.tm_sec);
		vprintf(fmt, args);
	}
	void log(int color, char* fmt, ...)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    	SetConsoleTextAttribute(hConsole, (WORD)color);
		va_list args;
		va_start(args, fmt);
		timeSeconds = time(NULL);
		localtime_s(&currentTime, &timeSeconds);
		printf("[%02d:%02d:%02d] ", currentTime.tm_hour, currentTime.tm_min, currentTime.tm_sec);
		vprintf(fmt, args);
		SetConsoleTextAttribute(hConsole, 7);
	}
	// void log_interval(float seconds, char* fmt, ...)
	// {
	// 	va_list args;
	// 	va_start(args, fmt);
	// 	timeSeconds = time(NULL);
	// 	localtime_s(&currentTime, &timeSeconds);
	// 	printf("[%d:%d:%d]", currentTime.tm_hour, currentTime.tm_min, currentTime.tm_sec);
	// 	vprintf(fmt, args);		
	// }
	void log_error(char* fmt, ...)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    	SetConsoleTextAttribute(hConsole, 12);
		va_list args;
		va_start(args, fmt);
		timeSeconds = time(NULL);
		localtime_s(&currentTime, &timeSeconds);
		printf("[%02d:%02d:%02d] ", currentTime.tm_hour, currentTime.tm_min, currentTime.tm_sec);
		vprintf(fmt, args);
		SetConsoleTextAttribute(hConsole, 7);
	}
	template<>
	void log_error(bool message)
	{
		std::string value;
		if (message == 0)
			value = "False";
		else
			value = "True";
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    	SetConsoleTextAttribute(hConsole, 12);
		timeSeconds = time(NULL);
		localtime_s(&currentTime, &timeSeconds);
		std::cout << "[" << currentTime.tm_hour << ":" << std::setfill('0') << std::setw(2) << 
		currentTime.tm_min << ":" << std::setfill('0') << std::setw(2) << currentTime.tm_sec << "] " << value << std::endl;
		SetConsoleTextAttribute(hConsole, 7);			
	}
}