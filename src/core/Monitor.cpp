#include "Monitor.h"

namespace Tactics
{
	Monitor make_monitor()
	{
		Monitor monitor;
		monitor.glfw_monitor = glfwGetPrimaryMonitor();
		monitor.videoMode = glfwGetVideoMode(monitor.glfw_monitor);
		monitor.width = monitor.videoMode->width;
		monitor.height = monitor.videoMode->height;
		monitor.refreshRate = monitor.videoMode->refreshRate;
		return monitor;
	}
}
