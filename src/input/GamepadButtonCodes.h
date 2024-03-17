#ifndef GAMEPADBUTTONCODES_H
#define GAMEPADBUTTONCODES_H

namespace Tactics
{
	#define JOYSTICK_1             0
	#define JOYSTICK_2             1
	#define JOYSTICK_3             2
	#define JOYSTICK_4             3
	#define JOYSTICK_5             4
	#define JOYSTICK_6             5
	#define JOYSTICK_7             6
	#define JOYSTICK_8             7
	#define JOYSTICK_9             8
	#define JOYSTICK_10            9
	#define JOYSTICK_11            10
	#define JOYSTICK_12            11
	#define JOYSTICK_13            12
	#define JOYSTICK_14            13
	#define JOYSTICK_15            14
	#define JOYSTICK_16            15
	#define JOYSTICK_LAST          JOYSTICK_16
	/*! @} */

	/*! @defgroup gamepad_buttons Gamepad buttons
	 *  @brief Gamepad buttons.
	 *
	 *  See @ref gamepad for how these are used.
	 *
	 *  @ingroup input
	 *  @{ */
	#define GAMEPAD_BUTTON_A               0
	#define GAMEPAD_BUTTON_B               1
	#define GAMEPAD_BUTTON_X               2
	#define GAMEPAD_BUTTON_Y               3
	#define GAMEPAD_BUTTON_LEFT_BUMPER     4
	#define GAMEPAD_BUTTON_RIGHT_BUMPER    5
	#define GAMEPAD_BUTTON_BACK            6
	#define GAMEPAD_BUTTON_START           7
	#define GAMEPAD_BUTTON_GUIDE           8
	#define GAMEPAD_BUTTON_LEFT_THUMB      9
	#define GAMEPAD_BUTTON_RIGHT_THUMB     10
	#define GAMEPAD_BUTTON_DPAD_UP         11
	#define GAMEPAD_BUTTON_DPAD_RIGHT      12
	#define GAMEPAD_BUTTON_DPAD_DOWN       13
	#define GAMEPAD_BUTTON_DPAD_LEFT       14
	#define GAMEPAD_BUTTON_LAST            GAMEPAD_BUTTON_DPAD_LEFT

	#define GAMEPAD_BUTTON_CROSS       GAMEPAD_BUTTON_A
	#define GAMEPAD_BUTTON_CIRCLE      GAMEPAD_BUTTON_B
	#define GAMEPAD_BUTTON_SQUARE      GAMEPAD_BUTTON_X
	#define GAMEPAD_BUTTON_TRIANGLE    GAMEPAD_BUTTON_Y
	/*! @} */

	/*! @defgroup gamepad_axes Gamepad axes
	 *  @brief Gamepad axes.
	 *
	 *  See @ref gamepad for how these are used.
	 *
	 *  @ingroup input
	 *  @{ */
	#define GAMEPAD_AXIS_LEFT_X        0
	#define GAMEPAD_AXIS_LEFT_Y        1
	#define GAMEPAD_AXIS_RIGHT_X       2
	#define GAMEPAD_AXIS_RIGHT_Y       3
	#define GAMEPAD_AXIS_LEFT_TRIGGER  4
	#define GAMEPAD_AXIS_RIGHT_TRIGGER 5
	#define GAMEPAD_AXIS_LAST          GAMEPAD_AXIS_RIGHT_TRIGGER
}
#endif