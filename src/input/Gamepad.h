#ifndef GAMEPAD_H
#define GAMEPAD_H

#define MAX_GAMEPAD_STATES 5
#define GAMEPAD_BUTTON_STATE_SIZE 15

namespace Tactics
{
	struct Gamepad
	{
		GLFWgamepadstate state;
		int joyStick1 = JOYSTICK_1;
		int current_state_number = 0;
		bool button_state[GAMEPAD_BUTTON_STATE_SIZE];
		bool button_states[MAX_GAMEPAD_STATES][GAMEPAD_BUTTON_STATE_SIZE];
	};

	void update_gamepad(Window* window, Gamepad* gamepad);
	void update_gamepad_states(Gamepad* gamepad);
	int get_previous_gamepad_state_number(Gamepad* gamepad);
}
#endif