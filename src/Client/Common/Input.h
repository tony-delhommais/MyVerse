//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_INPUT_H
#define MYVERSE_INPUT_H

#include "Client/Utils/MathUtils.h"
#include "Client/Utils/Utils.h"

namespace Client
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

		static const glm::vec2& GetMousePosition();
		static const glm::vec2& GetMouseMovement();
	};

} // Client

#endif // MYVERSE_INPUT_H
