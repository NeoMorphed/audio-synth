#ifndef INPUT______H
#define INPUT______H

namespace Tactics
{
	struct Vector2;
	struct Matrix4;
	struct Window;
	struct Mouse;
	struct Keyboard;
	struct Gamepad;

	void init_input();
	void update_input_states(Window* window);
	void set_mouse_pos(int x, int y);
	Vector2 get_mouse_pos();
	Vector2 get_mouse_world_pos();
	bool key_down(int key);
	bool key_just_down(int key);
	bool key_up(int key);
	bool mouse_button_down(int mouseButton);
	bool mouse_button_just_down(int mouseButton);
	bool mouse_button_up(int mouseButton);
	bool gamepad_button_down(int gamepadButton);
	bool gamepad_button_just_down(int gamepad_button);
	bool gamepad_button_up(int gamepad_button);
	void transform_mouse_pos(const Matrix4 &matrix);
	void scale_mouse_pos(int viewportWidth, int viewportHeight, int renderTargetWidth, int renderTargetHeight);
	int key_bind(const std::string& action_name);
	void add_input_action(const std::string& action_name, int key_value);
	void add_input_action(const std::string& action_name, std::string key_value);
	
}

#endif
