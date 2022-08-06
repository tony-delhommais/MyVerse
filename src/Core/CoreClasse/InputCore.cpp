//
// Created by Tony on 03/08/2022.
//

#include "Core/CoreClasse/InputCore.h"

#include "Core/Clock.h"

namespace Core
{

	InputCore& InputCore::instance()
	{
		static InputCore instance;
		return instance;
	}

	void InputCore::ParseAxisKey(JsonObject& p_newAxis)
	{
		static int default_alias = 0;

		KeyAxis new_axis;

		new_axis.name = GetParameterFromJsonObject(p_newAxis, "Alias", "Default_" + std::to_string(default_alias++));
		new_axis.positive = GetParameterFromJsonObject(p_newAxis, "PositiveKey", GLFW_KEY_UNKNOWN);
		new_axis.negative = GetParameterFromJsonObject(p_newAxis, "NegativeKey", GLFW_KEY_UNKNOWN);

		if (new_axis.positive == GLFW_KEY_UNKNOWN || new_axis.negative == GLFW_KEY_UNKNOWN)
			return;

		m_keyAxis.push_back(new_axis);
	}

	void InputCore::Initialize(GLFWwindow* p_window)
	{
		m_window = p_window;

		//////////////////////////////////////////////  Keyboard  //////////////////////////////////////////////
		auto keyCallback = [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			InputCore::instance().UpdateKeyAxis(key, action);
		};

		glfwSetKeyCallback(p_window, keyCallback);
		//////////////////////////////////////////////  Keyboard  //////////////////////////////////////////////

		//////////////////////////////////////////////  Mouse Position  //////////////////////////////////////////////
		auto cursorPositionCallback = [](GLFWwindow* window, double xpos, double ypos) {
			InputCore::instance().UpdateMousePosition(xpos, ypos);
		};

		glfwSetCursorPosCallback(p_window, cursorPositionCallback);
		//////////////////////////////////////////////  Mouse Position  //////////////////////////////////////////////

		//////////////////////////////////////////////  Mouse Button  //////////////////////////////////////////////
		auto mouseButtonCallback = [](GLFWwindow* window, int button, int action, int mods) {
			InputCore::instance().UpdateMouseButton(button, action);
		};
		
		glfwSetMouseButtonCallback(p_window, mouseButtonCallback);
		//////////////////////////////////////////////  Mouse Button  //////////////////////////////////////////////
	}

	void InputCore::ResetFrameState()
	{
		m_keysDown.clear();
		m_keysUp.clear();

		m_mouseButtonDown.clear();
		m_mouseButtonUp.clear();

		m_mouseMovement = m_mousePreviousPosition - m_mousePosition;
		m_mousePreviousPosition = m_mousePosition;
	}

	void InputCore::SetCursorMode(int p_cursorMode)
	{
		if(m_window) glfwSetInputMode(m_window, GLFW_CURSOR, p_cursorMode);
	}

	bool InputCore::IsKeyDown(int p_keyCode)
	{
		if (p_keyCode == GLFW_KEY_UNKNOWN) return false;

		for (int keyCode : m_keysDown)
		{
			if (keyCode == p_keyCode)
				return true;
		}

		return false;
	}

	bool InputCore::IsKeyUp(int p_keyCode)
	{
		if (p_keyCode == GLFW_KEY_UNKNOWN) return false;

		for (int keyCode : m_keysUp)
		{
			if (keyCode == p_keyCode)
				return true;
		}

		return false;
	}

	float InputCore::GetAxis(std::string p_axisName)
	{
		for (KeyAxis& keyAxis : m_keyAxis)
		{
			if (keyAxis.name == p_axisName)
				return keyAxis.value;
		}
#ifdef _DEBUG
		Debug::LogInfo("[Input] Failed to get Axis " + p_axisName);
#endif
		return 0.0f;
	}

	bool InputCore::IsMouseButtonDown(int p_mouseButton)
	{
		for (int mouseButton : m_mouseButtonDown)
		{
			if (mouseButton == p_mouseButton)
				return true;
		}

		return false;
	}

	bool InputCore::IsMouseButtonUp(int p_mouseButton)
	{
		for (int mouseButton : m_mouseButtonUp)
		{
			if (mouseButton == p_mouseButton)
				return true;
		}

		return false;
	}

	glm::vec2 InputCore::GetMousePosition()
	{
		return m_mousePosition;
	}

	glm::vec2 InputCore::GetMouseMovement()
	{
		return m_mouseMovement;
	}

	void InputCore::UpdateKeyAxis(int p_keyCode, int p_action)
	{
		if (p_action == GLFW_PRESS) m_keysDown.push_back(p_keyCode);
		else if (p_action == GLFW_RELEASE) m_keysUp.push_back(p_keyCode);

		for (KeyAxis& axis : m_keyAxis)
		{
			bool positiveChanged = false;
			bool negativeChanged = false;

			if (axis.positive == p_keyCode)
			{
				positiveChanged = p_action != axis.positivePressed;
				axis.positivePressed = p_action;
			}

			if (axis.negative == p_keyCode)
			{
				negativeChanged = p_action != axis.negativePressed;
				axis.negativePressed = p_action;
			}

			if (positiveChanged)
			{
				if (axis.positivePressed)
				{
					axis.value = 1.0f;
				}
				else if (axis.negativePressed)
				{
					axis.value = -1.0f;
				}
				else
				{
					axis.value = 0.0f;
				}
			}
			else if (negativeChanged)
			{
				if (axis.negativePressed)
				{
					axis.value = -1.0f;
				}
				else if (axis.positivePressed)
				{
					axis.value = 1.0f;
				}
				else
				{
					axis.value = 0.0f;
				}
			}
		}
	}

	void InputCore::UpdateMousePosition(double p_mouseX, double p_mouseY)
	{
		m_mousePosition = { p_mouseX, p_mouseY };
	}

	void InputCore::UpdateMouseButton(int p_mouseButton, int p_action)
	{
		if (p_action == GLFW_PRESS) m_mouseButtonDown.push_back(p_mouseButton);
		else if (p_action == GLFW_RELEASE) m_mouseButtonUp.push_back(p_mouseButton);
	}

} // Core