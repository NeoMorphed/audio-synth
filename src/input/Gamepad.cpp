#include "Gamepad.h"
#include "core/Window.h"

namespace Tactics
{
	void update_gamepad()
	{

	}
	// @Cleanup we need to check if a gamepad exists before using any of this. We also need to be polling 
	// for gamepads being plugged in and also multiple joysticks.
	void update_gamepad_states(Gamepad* gamepad, Window* window)
	{
		//if (!glfwGetGamepadState(joyStick1, &state))
			//log_error("Failed to get joy_stick1 gamepad state");
		gamepad->button_state[GAMEPAD_BUTTON_A]	 			= gamepad->state.buttons[GAMEPAD_BUTTON_A]; 
		gamepad->button_state[GAMEPAD_BUTTON_B]				= gamepad->state.buttons[GAMEPAD_BUTTON_B]; 
		gamepad->button_state[GAMEPAD_BUTTON_X] 				= gamepad->state.buttons[GAMEPAD_BUTTON_X]; 
		gamepad->button_state[GAMEPAD_BUTTON_Y] 				= gamepad->state.buttons[GAMEPAD_BUTTON_Y]; 
		gamepad->button_state[GAMEPAD_BUTTON_LEFT_BUMPER] 	= gamepad->state.buttons[GAMEPAD_BUTTON_LEFT_BUMPER]; 
		gamepad->button_state[GAMEPAD_BUTTON_RIGHT_BUMPER] 	= gamepad->state.buttons[GAMEPAD_BUTTON_RIGHT_BUMPER]; 
		gamepad->button_state[GAMEPAD_BUTTON_BACK] 			= gamepad->state.buttons[GAMEPAD_BUTTON_BACK]; 
		gamepad->button_state[GAMEPAD_BUTTON_START] 			= gamepad->state.buttons[GAMEPAD_BUTTON_START]; 
		gamepad->button_state[GAMEPAD_BUTTON_GUIDE] 			= gamepad->state.buttons[GAMEPAD_BUTTON_GUIDE]; 
		gamepad->button_state[GAMEPAD_BUTTON_LEFT_THUMB] 	= gamepad->state.buttons[GAMEPAD_BUTTON_LEFT_THUMB]; 
		gamepad->button_state[GAMEPAD_BUTTON_RIGHT_THUMB] 	= gamepad->state.buttons[GAMEPAD_BUTTON_RIGHT_THUMB]; 
		gamepad->button_state[GAMEPAD_BUTTON_DPAD_UP] 		= gamepad->state.buttons[GAMEPAD_BUTTON_DPAD_UP]; 
		gamepad->button_state[GAMEPAD_BUTTON_DPAD_RIGHT] 	= gamepad->state.buttons[GAMEPAD_BUTTON_DPAD_RIGHT]; 
		gamepad->button_state[GAMEPAD_BUTTON_DPAD_DOWN] 		= gamepad->state.buttons[GAMEPAD_BUTTON_DPAD_DOWN]; 
		gamepad->button_state[GAMEPAD_BUTTON_DPAD_LEFT] 		= gamepad->state.buttons[GAMEPAD_BUTTON_DPAD_LEFT]; 

		if (gamepad->current_state_number == MAX_GAMEPAD_STATES - 1)
		{
			gamepad->current_state_number = 0;
		}
		else gamepad->current_state_number++;
		memcpy(gamepad->button_states[gamepad->current_state_number], gamepad->button_state, sizeof(bool) * GAMEPAD_BUTTON_STATE_SIZE);
	}
	int get_previous_gamepad_state_number(Gamepad* gamepad)
	{
		if (gamepad->current_state_number == 0)
			return MAX_GAMEPAD_STATES - 1;
		else return gamepad->current_state_number - 1;
	}
}