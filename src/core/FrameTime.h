#ifndef FRAME_TIME_H
#define FRAME_TIME_H

namespace Tactics
{
	struct FrameTime
	{
		float delta_time = 0;
		float fps_delta_time = 0;
		float last_fps_frame_time = 0;
		float last_frame_time = 0;
		float fps = 1 / 60.0f;
		float total_frame_time = 0;
		bool paused = false;
		bool one_frame = false;
		FrameTime()
		{

		}
	};
	static float time_as_milliseconds(FrameTime& frame_time) { return frame_time.delta_time * 1000.0f; }
}

#endif