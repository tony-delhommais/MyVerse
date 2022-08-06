//
// Created by Tony on 29/06/2022.
//

#include "Core/Input.h"

#include "Core/CoreClass/InputCore.h"

namespace Core
{

	void Input::SetCursorMode(int p_cursorMode)
	{
		InputCore::instance().SetCursorMode(p_cursorMode);
	}

	bool Input::IsKeyDown(int p_keyCode)
	{
		return InputCore::instance().IsKeyDown(p_keyCode);
	}

	bool Input::IsKeyUp(int p_keyCode)
	{
		return InputCore::instance().IsKeyUp(p_keyCode);
	}

	float Input::GetAxis(std::string p_axisName)
	{
		return InputCore::instance().GetAxis(p_axisName);
	}

	bool Input::IsMouseButtonDown(int p_mouseButton)
	{
		return InputCore::instance().IsMouseButtonDown(p_mouseButton);
	}

	bool Input::IsMouseButtonUp(int p_mouseButton)
	{
		return InputCore::instance().IsMouseButtonUp(p_mouseButton);
	}

    glm::vec2 Input::GetMousePosition()
	{
		return InputCore::instance().GetMousePosition();
    }

    glm::vec2 Input::GetMouseMovement()
	{
		return InputCore::instance().GetMouseMovement();
    }

} // Core
