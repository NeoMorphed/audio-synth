
#ifndef MONITOR_H
#define	MONITOR_H

#include "GLFW/glfw3.h"

namespace Tactics
{
	struct Monitor
	{
		GLFWmonitor* glfw_monitor;
		const GLFWvidmode* videoMode;
		int width;
		int height;
		int refreshRate;
	};
	Monitor make_monitor();
}
#endif