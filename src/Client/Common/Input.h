//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_INPUT_H
#define MYVERSE_INPUT_H

#include "Client/Utils/MathUtils.h"
#include "Client/Utils/Utils.h"

namespace Core
{

	class Input
	{
	public:
		static void SetCursorMode(int p_cursorMode);

		static bool IsKeyDown(int p_keyCode);
		static bool IsKeyUp(int p_keyCode);
		static float GetAxis(const std::string& p_axisName);

		static bool IsMouseButtonDown(int p_mouseButton);
		static bool IsMouseButtonUp(int p_mouseButton);

		static glm::vec2 GetMousePosition();
		static glm::vec2 GetMouseMovement();
	};

} // Core

#endif // MYVERSE_INPUT_H
