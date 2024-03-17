#include "KeyBoard.h"
#include "core/Window.h"
#include "KeyCodes.h"

namespace Tactics
{
	void update_keyboard_states(Keyboard* keyboard, Window* window)
	{
		keyboard->state[KEY_SPACE] 			=  glfwGetKey(window->glfw_window, KEY_SPACE);
		keyboard->state[KEY_APOSTROPHE] 		=  glfwGetKey(window->glfw_window, KEY_APOSTROPHE);
		keyboard->state[KEY_COMMA] 			=  glfwGetKey(window->glfw_window, KEY_COMMA);
		keyboard->state[KEY_MINUS] 			=  glfwGetKey(window->glfw_window, KEY_MINUS);
		keyboard->state[KEY_PERIOD] 			=  glfwGetKey(window->glfw_window, KEY_PERIOD);
		keyboard->state[KEY_SLASH] 			=  glfwGetKey(window->glfw_window, KEY_SLASH);
		keyboard->state[KEY_0] 				=  glfwGetKey(window->glfw_window, KEY_0);
		keyboard->state[KEY_1] 				=  glfwGetKey(window->glfw_window, KEY_1);
		keyboard->state[KEY_2] 				=  glfwGetKey(window->glfw_window, KEY_2);
		keyboard->state[KEY_3] 				=  glfwGetKey(window->glfw_window, KEY_3);
		keyboard->state[KEY_4] 				=  glfwGetKey(window->glfw_window, KEY_4);
		keyboard->state[KEY_5] 				=  glfwGetKey(window->glfw_window, KEY_5);
		keyboard->state[KEY_6] 				=  glfwGetKey(window->glfw_window, KEY_6);
		keyboard->state[KEY_7] 				=  glfwGetKey(window->glfw_window, KEY_7);
		keyboard->state[KEY_8] 				=  glfwGetKey(window->glfw_window, KEY_8);
		keyboard->state[KEY_9] 				=  glfwGetKey(window->glfw_window, KEY_9);
		keyboard->state[KEY_SEMICOLON] 		=  glfwGetKey(window->glfw_window, KEY_SEMICOLON);
		keyboard->state[KEY_EQUAL] 			=  glfwGetKey(window->glfw_window, KEY_EQUAL);
		keyboard->state[KEY_A] 				=  glfwGetKey(window->glfw_window, KEY_A);
		keyboard->state[KEY_B] 				=  glfwGetKey(window->glfw_window, KEY_B);
		keyboard->state[KEY_C] 				=  glfwGetKey(window->glfw_window, KEY_C);
		keyboard->state[KEY_D] 				=  glfwGetKey(window->glfw_window, KEY_D);
		keyboard->state[KEY_E] 				=  glfwGetKey(window->glfw_window, KEY_E);
		keyboard->state[KEY_F] 				=  glfwGetKey(window->glfw_window, KEY_F);
		keyboard->state[KEY_G] 				=  glfwGetKey(window->glfw_window, KEY_G);
		keyboard->state[KEY_H] 				=  glfwGetKey(window->glfw_window, KEY_H);
		keyboard->state[KEY_I] 				=  glfwGetKey(window->glfw_window, KEY_I);
		keyboard->state[KEY_J] 				=  glfwGetKey(window->glfw_window, KEY_J);
		keyboard->state[KEY_K] 				=  glfwGetKey(window->glfw_window, KEY_K);
		keyboard->state[KEY_L] 				=  glfwGetKey(window->glfw_window, KEY_L);
		keyboard->state[KEY_M] 				=  glfwGetKey(window->glfw_window, KEY_M);
		keyboard->state[KEY_N] 				=  glfwGetKey(window->glfw_window, KEY_N);
		keyboard->state[KEY_O] 				=  glfwGetKey(window->glfw_window, KEY_O);
		keyboard->state[KEY_P] 				=  glfwGetKey(window->glfw_window, KEY_P);
		keyboard->state[KEY_Q] 				=  glfwGetKey(window->glfw_window, KEY_Q);
		keyboard->state[KEY_R] 				=  glfwGetKey(window->glfw_window, KEY_R);
		keyboard->state[KEY_S] 				=  glfwGetKey(window->glfw_window, KEY_S);
		keyboard->state[KEY_T] 				=  glfwGetKey(window->glfw_window, KEY_T);
		keyboard->state[KEY_U] 				=  glfwGetKey(window->glfw_window, KEY_U);
		keyboard->state[KEY_V] 				=  glfwGetKey(window->glfw_window, KEY_V);
		keyboard->state[KEY_W] 				=  glfwGetKey(window->glfw_window, KEY_W);
		keyboard->state[KEY_X] 				=  glfwGetKey(window->glfw_window, KEY_X);
		keyboard->state[KEY_Y] 				=  glfwGetKey(window->glfw_window, KEY_Y);
		keyboard->state[KEY_Z] 				=  glfwGetKey(window->glfw_window, KEY_Z);
		keyboard->state[KEY_LEFT_BRACKET] 	=  glfwGetKey(window->glfw_window, KEY_LEFT_BRACKET);
		keyboard->state[KEY_BACKSLASH] 		=  glfwGetKey(window->glfw_window, KEY_BACKSLASH);
		keyboard->state[KEY_RIGHT_BRACKET]	=  glfwGetKey(window->glfw_window, KEY_RIGHT_BRACKET);
		keyboard->state[KEY_GRAVE_ACCENT] 	=  glfwGetKey(window->glfw_window, KEY_GRAVE_ACCENT);
		keyboard->state[KEY_WORLD_1] 			=  glfwGetKey(window->glfw_window, KEY_WORLD_1);
		keyboard->state[KEY_WORLD_2] 			=  glfwGetKey(window->glfw_window, KEY_WORLD_2);
		keyboard->state[KEY_ESCAPE] 			=  glfwGetKey(window->glfw_window, KEY_ESCAPE);
		keyboard->state[KEY_ENTER] 			=  glfwGetKey(window->glfw_window, KEY_ENTER);
		keyboard->state[KEY_TAB] 				=  glfwGetKey(window->glfw_window, KEY_TAB);
		keyboard->state[KEY_BACKSPACE] 		=  glfwGetKey(window->glfw_window, KEY_BACKSPACE);
		keyboard->state[KEY_INSERT] 			=  glfwGetKey(window->glfw_window, KEY_INSERT);
		keyboard->state[KEY_DELETE] 			=  glfwGetKey(window->glfw_window, KEY_DELETE);
		keyboard->state[KEY_RIGHT] 			=  glfwGetKey(window->glfw_window, KEY_RIGHT);
		keyboard->state[KEY_LEFT] 			=  glfwGetKey(window->glfw_window, KEY_LEFT);
		keyboard->state[KEY_DOWN] 			=  glfwGetKey(window->glfw_window, KEY_DOWN);
		keyboard->state[KEY_UP] 				=  glfwGetKey(window->glfw_window, KEY_UP);
		keyboard->state[KEY_PAGE_UP] 			=  glfwGetKey(window->glfw_window, KEY_PAGE_UP);
		keyboard->state[KEY_PAGE_DOWN] 		=  glfwGetKey(window->glfw_window, KEY_PAGE_DOWN);
		keyboard->state[KEY_HOME] 			=  glfwGetKey(window->glfw_window, KEY_HOME);
		keyboard->state[KEY_END] 				=  glfwGetKey(window->glfw_window, KEY_END);
		keyboard->state[KEY_CAPS_LOCK] 		=  glfwGetKey(window->glfw_window, KEY_CAPS_LOCK);
		keyboard->state[KEY_SCROLL_LOCK] 		=  glfwGetKey(window->glfw_window, KEY_SCROLL_LOCK);
		keyboard->state[KEY_NUM_LOCK] 		=  glfwGetKey(window->glfw_window, KEY_NUM_LOCK);
		keyboard->state[KEY_PRINT_SCREEN] 	=  glfwGetKey(window->glfw_window, KEY_PRINT_SCREEN);
		keyboard->state[KEY_PAUSE] 			=  glfwGetKey(window->glfw_window, KEY_PAUSE);
		keyboard->state[KEY_F1] 				=  glfwGetKey(window->glfw_window, KEY_F1);
		keyboard->state[KEY_F2] 				=  glfwGetKey(window->glfw_window, KEY_F2);
		keyboard->state[KEY_F3] 				=  glfwGetKey(window->glfw_window, KEY_F3);
		keyboard->state[KEY_F4] 				=  glfwGetKey(window->glfw_window, KEY_F4);
		keyboard->state[KEY_F5] 				=  glfwGetKey(window->glfw_window, KEY_F5);
		keyboard->state[KEY_F6] 				=  glfwGetKey(window->glfw_window, KEY_F6);
		keyboard->state[KEY_F7] 				=  glfwGetKey(window->glfw_window, KEY_F7);
		keyboard->state[KEY_F8] 				=  glfwGetKey(window->glfw_window, KEY_F8);
		keyboard->state[KEY_F9] 				=  glfwGetKey(window->glfw_window, KEY_F9);
		keyboard->state[KEY_F10] 				=  glfwGetKey(window->glfw_window, KEY_F10);
		keyboard->state[KEY_F11] 				=  glfwGetKey(window->glfw_window, KEY_F11);
		keyboard->state[KEY_F12] 				=  glfwGetKey(window->glfw_window, KEY_F12);
		keyboard->state[KEY_KP_0] 			=  glfwGetKey(window->glfw_window, KEY_KP_0);
		keyboard->state[KEY_KP_1] 			=  glfwGetKey(window->glfw_window, KEY_KP_1);
		keyboard->state[KEY_KP_2] 			=  glfwGetKey(window->glfw_window, KEY_KP_2);
		keyboard->state[KEY_KP_3] 			=  glfwGetKey(window->glfw_window, KEY_KP_3);
		keyboard->state[KEY_KP_4] 			=  glfwGetKey(window->glfw_window, KEY_KP_4);
		keyboard->state[KEY_KP_5] 			=  glfwGetKey(window->glfw_window, KEY_KP_5);
		keyboard->state[KEY_KP_6] 			=  glfwGetKey(window->glfw_window, KEY_KP_6);
		keyboard->state[KEY_KP_7] 			=  glfwGetKey(window->glfw_window, KEY_KP_7);
		keyboard->state[KEY_KP_8] 			=  glfwGetKey(window->glfw_window, KEY_KP_8);
		keyboard->state[KEY_KP_9] 			=  glfwGetKey(window->glfw_window, KEY_KP_9);
		keyboard->state[KEY_KP_DECIMAL] 		=  glfwGetKey(window->glfw_window, KEY_KP_DECIMAL);
		keyboard->state[KEY_KP_DIVIDE] 		=  glfwGetKey(window->glfw_window, KEY_KP_DIVIDE);
		keyboard->state[KEY_KP_MULTIPLY] 		=  glfwGetKey(window->glfw_window, KEY_KP_MULTIPLY);
		keyboard->state[KEY_KP_SUBTRACT] 		=  glfwGetKey(window->glfw_window, KEY_KP_SUBTRACT);
		keyboard->state[KEY_KP_ADD] 			=  glfwGetKey(window->glfw_window, KEY_KP_ADD);
		keyboard->state[KEY_KP_ENTER] 		=  glfwGetKey(window->glfw_window, KEY_KP_ENTER);
		keyboard->state[KEY_KP_EQUAL] 		=  glfwGetKey(window->glfw_window, KEY_KP_EQUAL);
		keyboard->state[KEY_LEFT_SHIFT] 		=  glfwGetKey(window->glfw_window, KEY_LEFT_SHIFT);
		keyboard->state[KEY_LEFT_CONTROL] 	=  glfwGetKey(window->glfw_window, KEY_LEFT_CONTROL);
		keyboard->state[KEY_LEFT_ALT] 		=  glfwGetKey(window->glfw_window, KEY_LEFT_ALT);
		keyboard->state[KEY_LEFT_SUPER] 		=  glfwGetKey(window->glfw_window, KEY_LEFT_SUPER);
		keyboard->state[KEY_RIGHT_SHIFT] 		=  glfwGetKey(window->glfw_window, KEY_RIGHT_SHIFT);
		keyboard->state[KEY_RIGHT_CONTROL]	=  glfwGetKey(window->glfw_window, KEY_RIGHT_CONTROL);
		keyboard->state[KEY_RIGHT_ALT] 		= glfwGetKey(window->glfw_window, KEY_RIGHT_ALT);
		keyboard->state[KEY_RIGHT_SUPER] 		= glfwGetKey(window->glfw_window, KEY_RIGHT_SUPER);
		keyboard->state[KEY_MENU] 			= glfwGetKey(window->glfw_window, KEY_MENU);

		if (keyboard->current_state_number == MAX_KEY_STATES - 1)
		{
			keyboard->current_state_number = 0;
		}
		else keyboard->current_state_number++;

		memcpy(keyboard->states[keyboard->current_state_number], keyboard->state, sizeof(bool) * 348);
	}
	int get_previous_keyboard_state_number(Keyboard* keyboard)
	{
		if (keyboard->current_state_number == 0)
			return MAX_KEY_STATES - 1;
		else return keyboard->current_state_number - 1;
	}
}
