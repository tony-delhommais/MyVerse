//
// Created by Tony on 29/06/2022.
//

#include "Input.h"

#include "InputCore.h"

namespace Client
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

	float Input::GetAction(int p_actionId)
	{
		return InputCore::instance().GetAction(p_actionId);
	}

	bool Input::IsMouseButtonDown(int p_mouseButton)
	{
		return InputCore::instance().IsMouseButtonDown(p_mouseButton);
	}

	bool Input::IsMouseButtonUp(int p_mouseButton)
	{
		return InputCore::instance().IsMouseButtonUp(p_mouseButton);
	}

	const glm::vec2& Input::GetMousePosition()
	{
		return InputCore::instance().GetMousePosition();
	}

	const glm::vec2& Input::GetMouseMovement()
	{
		return InputCore::instance().GetMouseMovement();
	}

} // Client
