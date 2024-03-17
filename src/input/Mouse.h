#ifndef MOUSE_H
#define MOUSE_H

#include "math/Vectors.h"

#define MAX_MOUSE_STATES 5 
#define MOUSE_STATE_SIZE 8

namespace Tactics
{
	struct Mouse
	{
		bool isVisible;
		// @Cleanup maybe use iVector2 for this since it always be int
		Vector2 position;
		Vector2 worldPosition;
		Vector2 scaledPosition;
		Vector2 oldPosition;
		Vector2 oldWorldPosition;
		bool justMoved;

		int current_state_number = 0;
		bool state[MOUSE_STATE_SIZE];
		bool states[MAX_MOUSE_STATES][MOUSE_STATE_SIZE];
	};
	
	void update_mouse(Mouse* mouse, Window* window);
	void update_mouse_states(Mouse* mouse, Window* window);
	int get_previous_mouse_state_number(Mouse* mouse);

	// struct Entity
	// {
	// 	Vector2 position;
	// };
	// struct Plant
	// {
	// 	Entity* entity;
	// 	float growth_percent;
	// 	Vector2 wind_movement_position;
	// 	float temperature;
	// 	RootSystem root_system;
	// };
	// struct RootSystem
	// {
	// 	Bacteria* coexisting_bacterium;
	// 	int coexisting_bacterium_count;
	// 	float growth_percent;
	// 	float water_absorbtion;
	// 	float sugar_excretion;
	// };
	// struct Soil
	// {
	// 	Bacteria* bacterium;
	// 	int bacterium_count;
	// 	float sand_percent;
	// 	float silt_percent;
	// 	float clay_percent;
	// 	float airation_percent;
	// 	float water_amount;
	// };
	// struct Cloud
	// {
	// 	Vector2 span;
	// 	float vapor_density;
	// 	float speed;
	// 	Vector2 direction_of_travel;
	// 	float height;
	// };
	// struct Atmosphere
	// {
	// 	Cloud* clouds;
	// 	int cloud_count;
	// 	float pressure;
	// };
}
#endif
