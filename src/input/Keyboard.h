#ifndef KEYBOARD_H
#define KEYBOARD_H

#define MAX_KEY_STATES 5 
#define KEYBOARD_STATE_SIZE 348

namespace Tactics
{
	struct Keyboard
	{
		int current_state_number = 0;
		bool state[KEYBOARD_STATE_SIZE];
		bool states[MAX_KEY_STATES][KEYBOARD_STATE_SIZE];
	};

	void update_keyboard_states(Keyboard* keyboard, Window* window);
	int get_previous_keyboard_state_number(Keyboard* keyboard);
}
#endif
