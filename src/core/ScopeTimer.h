#ifndef __TIMER___H
#define __TIMER___H

#include <chrono>
#include <string>

namespace Tactics
{
	class ScopeTimer
	{
	public:
		ScopeTimer(const std::string& name);
		~ScopeTimer();
		std::string name;
		std::chrono::time_point<std::chrono::steady_clock> start;
		std::chrono::time_point<std::chrono::steady_clock> end;
	};
}

#endif