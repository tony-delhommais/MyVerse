//
// Created by Tony on 03/08/2022.
//

#include "Client/Core/InputCore.h"

#include "Client/Common/Clock.h"

namespace Client
{

	InputCore& InputCore::instance()
	{
		static InputCore instance;
		return instance;
	}

	void InputCore::ParseActions(JsonObject& p_actionList)
	{
		if (p_actionList.is_array())
		{
			for (JsonObject& actionData : p_actionList)
			{
				Action action;

				action.id = GetParameterFromJsonObject(actionData, "Id", action.id);
				if (action.id == -1) continue;

				action.alias = GetParameterFromJsonObject(actionData, "Alias", "Null");
				if (action.alias == "Null") continue;

				action.transitionTime = GetParameterFromJsonObject(actionData, "TransitionTime", action.transitionTime);

				JsonObject& keyBindingList = GetParameterFromJsonObject(actionData, "KeysBinding", true, false);
				if (keyBindingList != actionData)
				{
					for (JsonObject& keyBindingJsonData : keyBindingList)
					{
						JsonObject& keys = GetParameterFromJsonObject(keyBindingJsonData, "Keys", true, false);
						//todo manage multiple keys
						int key = keys[0];

						KeyBindingData keyBindingData;

						keyBindingData.value = GetParameterFromJsonObject(keyBindingJsonData, "Value", 1.0f);

						action.keyBindingList.insert(std::map<int, KeyBindingData>::value_type(key, keyBindingData));
					}
				}

				m_actions.push_back(action);
			}
		}
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

		//todo use transition speed
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
			if (keyCode == p_keyCode) return true;
		}

		return false;
	}

	bool InputCore::IsKeyUp(int p_keyCode)
	{
		if (p_keyCode == GLFW_KEY_UNKNOWN) return false;

		for (int keyCode : m_keysUp)
		{
			if (keyCode == p_keyCode) return true;
		}

		return false;
	}

	float InputCore::GetAction(int p_actionId)
	{
		for (Action& action : m_actions)
		{
			if (action.id == p_actionId) return action.value;
		}
#ifdef _DEBUG
		Debug::LogInfo("[Input] Failed to get Axis " + p_actionId);
#endif
		return 0.0f;
	}

	int InputCore::GetActionId(const std::string& p_actionAlias)
	{
		for (Action& action : m_actions)
		{
			if (action.alias == p_actionAlias) return action.id;
		}
#ifdef _DEBUG
		Debug::LogWarning("[Input] Axis " + p_actionAlias + " don't exist");
#endif
		return -1;
	}

	bool InputCore::IsMouseButtonDown(int p_mouseButton)
	{
		for (int mouseButton : m_mouseButtonDown)
		{
			if (mouseButton == p_mouseButton) return true;
		}

		return false;
	}

	bool InputCore::IsMouseButtonUp(int p_mouseButton)
	{
		for (int mouseButton : m_mouseButtonUp)
		{
			if (mouseButton == p_mouseButton) return true;
		}

		return false;
	}

	const glm::vec2& InputCore::GetMousePosition()
	{
		return m_mousePosition;
	}

	const glm::vec2& InputCore::GetMouseMovement()
	{
		return m_mouseMovement;
	}

	void InputCore::UpdateKeyAxis(int p_keyCode, int p_action)
	{
		if (p_action == GLFW_PRESS) m_keysDown.push_back(p_keyCode);
		else if (p_action == GLFW_RELEASE) m_keysUp.push_back(p_keyCode);

		for (Action& action : m_actions)
		{
			bool actionChanged = false;

			bool noKeyForActionIsPressed = true;

			for (auto& keyBindingData : action.keyBindingList)
			{
				bool keyBindingDataChanged = false;

				if (keyBindingData.first == p_keyCode)
				{
					keyBindingDataChanged = p_action != keyBindingData.second.keyPressed;
					keyBindingData.second.keyPressed = p_action;
				}

				if (!actionChanged && keyBindingDataChanged)
				{
					if (keyBindingData.second.keyPressed)
					{
						action.value = keyBindingData.second.value; //todo chnge to target value

						actionChanged = true;
					}
				}

				noKeyForActionIsPressed = noKeyForActionIsPressed && keyBindingData.second.keyPressed == GLFW_RELEASE;
			}

			if (noKeyForActionIsPressed)
			{
				action.value = 0.0f; //todo chnge to target value
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

} // Client
