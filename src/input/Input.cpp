#include "Input.h"
#include "math/common_math.h"
#include "core/Window.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Gamepad.h"

#include "Mouse.cpp"
#include "Keyboard.cpp"
#include "Gamepad.cpp"

namespace Tactics
{

	Keyboard keyboard = Keyboard();
	Mouse mouse = Mouse();
	Gamepad gamepad = Gamepad();
	std::unordered_map<std::string, int> input_actions;
	std::unordered_map<std::string, int> key_to_value_map;

	void init_input()
	{
		key_to_value_map.emplace("space", KEY_SPACE);
		key_to_value_map.emplace("'", KEY_APOSTROPHE);
		key_to_value_map.emplace(",", KEY_COMMA);
		key_to_value_map.emplace("-", KEY_MINUS);
		key_to_value_map.emplace(".", KEY_PERIOD);
		key_to_value_map.emplace("/", KEY_SLASH);
		key_to_value_map.emplace("0", KEY_0);
		key_to_value_map.emplace("1", KEY_1);
		key_to_value_map.emplace("2", KEY_2);
		key_to_value_map.emplace("3", KEY_3);
		key_to_value_map.emplace("4", KEY_4);
		key_to_value_map.emplace("5", KEY_5);
		key_to_value_map.emplace("6", KEY_6);
		key_to_value_map.emplace("7", KEY_7);
		key_to_value_map.emplace("8", KEY_8);
		key_to_value_map.emplace("9", KEY_9);
		key_to_value_map.emplace(";", KEY_SEMICOLON);
		key_to_value_map.emplace("=", KEY_EQUAL);
		key_to_value_map.emplace("A", KEY_A);
		key_to_value_map.emplace("B", KEY_B);
		key_to_value_map.emplace("C", KEY_C);
		key_to_value_map.emplace("D", KEY_D);
		key_to_value_map.emplace("E", KEY_E);
		key_to_value_map.emplace("F", KEY_F);
		key_to_value_map.emplace("G", KEY_G);
		key_to_value_map.emplace("H", KEY_H);
		key_to_value_map.emplace("I", KEY_I);
		key_to_value_map.emplace("J", KEY_J);
		key_to_value_map.emplace("K", KEY_K);
		key_to_value_map.emplace("L", KEY_L);
		key_to_value_map.emplace("M", KEY_M);
		key_to_value_map.emplace("N", KEY_N);
		key_to_value_map.emplace("O", KEY_O);
		key_to_value_map.emplace("P", KEY_P);
		key_to_value_map.emplace("Q", KEY_Q);
		key_to_value_map.emplace("R", KEY_R);
		key_to_value_map.emplace("S", KEY_S);
		key_to_value_map.emplace("T", KEY_T);
		key_to_value_map.emplace("U", KEY_U);
		key_to_value_map.emplace("V", KEY_V);
		key_to_value_map.emplace("W", KEY_W);
		key_to_value_map.emplace("X", KEY_X);
		key_to_value_map.emplace("Y", KEY_Y);
		key_to_value_map.emplace("Z", KEY_Z);
		key_to_value_map.emplace("escape", KEY_ESCAPE);
		key_to_value_map.emplace("enter", KEY_ENTER);
		key_to_value_map.emplace("tab", KEY_TAB);
		key_to_value_map.emplace("backspace", KEY_BACKSPACE);
		key_to_value_map.emplace("insert", KEY_INSERT);
		key_to_value_map.emplace("delete", KEY_DELETE);
		key_to_value_map.emplace("right", KEY_RIGHT);
		key_to_value_map.emplace("left", KEY_LEFT);
		key_to_value_map.emplace("down", KEY_DOWN);
		key_to_value_map.emplace("up", KEY_UP);
		key_to_value_map.emplace("page_up", KEY_PAGE_UP);
		key_to_value_map.emplace("page_down", KEY_PAGE_DOWN);
		key_to_value_map.emplace("home", KEY_HOME);
		key_to_value_map.emplace("end", KEY_END);
		key_to_value_map.emplace("caps_lock", KEY_CAPS_LOCK);
		key_to_value_map.emplace("scroll_lock", KEY_SCROLL_LOCK);
		key_to_value_map.emplace("num_lock", KEY_NUM_LOCK);
		key_to_value_map.emplace("print_screen", KEY_PRINT_SCREEN);
		key_to_value_map.emplace("pause", KEY_PAUSE);
		key_to_value_map.emplace("F1", KEY_F1);
		key_to_value_map.emplace("F2", KEY_F2);
		key_to_value_map.emplace("F3", KEY_F3);
		key_to_value_map.emplace("F4", KEY_F4);
		key_to_value_map.emplace("F5", KEY_F5);
		key_to_value_map.emplace("F6", KEY_F6);
		key_to_value_map.emplace("F7", KEY_F7);
		key_to_value_map.emplace("F8", KEY_F8);
		key_to_value_map.emplace("F9", KEY_F9);
		key_to_value_map.emplace("F10", KEY_F10);
		key_to_value_map.emplace("F11", KEY_F11);
		key_to_value_map.emplace("F12", KEY_F12);
	}
	int key_bind(const std::string& action_name)
	{
		assert(input_actions.find(action_name) != input_actions.end());
		return input_actions[action_name];
	}
	void add_input_action(const std::string& action_name, int key_value)
	{
		if (input_actions.find(action_name) == input_actions.end())
			input_actions.emplace(action_name, key_value);
		else std::cout << "Input action " << action_name << " already added." << std::endl;
	}
	void add_input_action(const std::string& action_name, std::string key_value)
	{
		if (input_actions.find(action_name) == input_actions.end())
		{
			assert(key_to_value_map.find(key_value) != key_to_value_map.end());
 			input_actions.emplace(action_name, key_to_value_map[key_value]);
		}
		else log_error("Input action already added. Action: %s\n", action_name.c_str());
	}
	void update_input_states(Window* window)
	{
		update_mouse(&mouse, window);
		update_keyboard_states(&keyboard, window);
		update_gamepad_states(&gamepad, window);
	}
	void set_mouse_pos(int x, int y)
	{
		mouse.position = vec2((float)x, (float)y);
	}
	Vector2 get_mouse_pos()
	{
		return mouse.position;
	}
	Vector2 get_mouse_world_pos()
	{
		return mouse.worldPosition;
	}
	bool key_down(int key)
	{
		return keyboard.state[key];
	}
	// TODO: Does not work when the framerate is limited. Must figure out a way for that to work.
	// 	     The same goes for mouse_button_just_down and gamepad_button_just_down.
	bool key_just_down(int key)
	{
		int key_states_index = get_previous_keyboard_state_number(&keyboard);
		if (keyboard.state[key] && !keyboard.states[key_states_index][key])
		{
			//printf("Space: ");
			return true;
		}
		else
			return false;
	}
	bool key_up(int key)
	{
		if (!keyboard.state[key])
			return true;
		else
			return false;
	}
	bool mouse_button_down(int mouseButton)
	{
		return mouse.state[mouseButton];
	}
	bool mouse_button_just_down(int mouseButton)
	{
		int mouse_states_index = get_previous_mouse_state_number(&mouse);
		if (mouse.state[mouseButton] && !mouse.states[mouse_states_index][mouseButton])
			return true;
		else
			return false;
	}
	bool mouse_button_up(int mouseButton)
	{
		if (!mouse.state[mouseButton])
			return true;
		else
			return false;
	}
	bool gamepad_button_down(int gamepad_button)
	{
		if (gamepad.button_state[gamepad_button])
		{
			return true;
		}
		return false;
	}
	bool gamepad_button_just_down(int gamepad_button)
	{
		int gamepad_states_index = get_previous_gamepad_state_number(&gamepad);
		if (gamepad.button_state[gamepad_button] && !gamepad.button_states[gamepad_states_index][gamepad_button])
			return true;
		else
			return false;
	}
	bool gamepad_button_up(int gamepad_button)
	{
		if (!gamepad.button_state[gamepad_button])
		{
			return true;
		}
		return false;
	}
	void transform_mouse_pos(const Matrix4 &matrix)
	{
		mouse.worldPosition = transform_vec2(mouse.scaledPosition, inverse_matrix(matrix));
	} 
    void scale_mouse_pos(int viewportWidth, int viewportHeight, int renderTargetWidth, int renderTargetHeight)
    {
        float xScale = (float)viewportWidth / (float)renderTargetWidth;
        float yScale = (float)viewportHeight / (float)renderTargetHeight;
        mouse.scaledPosition = mouse.position = vec2(mouse.position.x / xScale, mouse.position.y / yScale);
    }


}