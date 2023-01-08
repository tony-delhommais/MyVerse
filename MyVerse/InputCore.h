//
// Created by Tony on 03/08/2022.
//

#ifndef MYVERSE_INPUT_CORE_H
#define MYVERSE_INPUT_CORE_H

#include "GraphicsUtils.h"
#include "JsonUtils.h"
#include "MathUtils.h"
#include "Utils.h"

#ifdef _DEBUG
#include "Debug.h"
#endif

namespace Client
{

	struct KeyBindingData
	{
		int keyPressed = GLFW_RELEASE;

		float value = 0.0f;
	};

	struct Action
	{
		int id = -1;
		std::string alias = "";

		float transitionTime = 0.0f;

		std::map<int, KeyBindingData> keyBindingList;

		float targetValue = 0.0f;
		float value = 0.0f;
	};

	class InputCore
	{
	private:
		InputCore() = default;
		~InputCore() = default;

	public:
		static InputCore& instance();

		void ParseActions(JsonObject& p_actionList);

		void Initialize(GLFWwindow* p_window);

		void ResetFrameState();

		void SetCursorMode(int p_cursorMode);

		bool IsKeyDown(int p_keyCode);
		bool IsKeyUp(int p_keyCode);
		float GetAction(int p_actionId);

		int GetActionId(const std::string& p_actionAlias);

		bool IsMouseButtonDown(int p_mouseButton);
		bool IsMouseButtonUp(int p_mouseButton);

		const glm::vec2& GetMousePosition();
		const glm::vec2& GetMouseMovement();

		void UpdateKeyAxis(int p_keyCode, int p_action);
		void UpdateMousePosition(double p_mouseX, double p_mouseY);
		void UpdateMouseButton(int p_mouseButton, int p_action);

	private:
		GLFWwindow* m_window = nullptr;

		std::vector<int> m_keysDown;
		std::vector<int> m_keysUp;
		std::list<Action> m_actions;

		std::vector<int> m_mouseButtonDown;
		std::vector<int> m_mouseButtonUp;

		glm::vec2 m_mousePreviousPosition = { 0, 0 };
		glm::vec2 m_mousePosition = { 0, 0 };

		glm::vec2 m_mouseMovement = { 0, 0 };
	};

} // Client

#endif // MYVERSE_INPUT_CORE_H
