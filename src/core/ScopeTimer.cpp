#include "ScopeTimer.h"

namespace Tactics
{
	ScopeTimer::ScopeTimer(const std::string& name)
		:name(name)
	{
		start = std::chrono::steady_clock::now();
	}
	ScopeTimer::~ScopeTimer()
	{
		end = std::chrono::steady_clock::now();
		std::cout << name << ": " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
	}
}