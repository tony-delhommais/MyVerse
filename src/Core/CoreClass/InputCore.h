//
// Created by Tony on 03/08/2022.
//

#ifndef MYVERSE_INPUT_CORE_H
#define MYVERSE_INPUT_CORE_H

#include "Core/Utils/GraphicsUtils.h"
#include "Core/Utils/JsonUtils.h"
#include "Core/Utils/MathUtils.h"
#include "Core/Utils/Utils.h"

#ifdef _DEBUG
#include "Core/Debug.h"
#endif

namespace Core
{

	struct KeyAxis
	{
		std::string	name = "";

		int	positive = GLFW_KEY_UNKNOWN;
		int positivePressed = GLFW_RELEASE;

		int negative = GLFW_KEY_UNKNOWN;
		int negativePressed = GLFW_RELEASE;

		float value = 0.0f;
	};

	class InputCore
	{
	private:
		InputCore() = default;
		~InputCore() = default;

	public:
		static InputCore& instance();

		void ParseAxisKey(JsonObject& p_newAxis);

		void Initialize(GLFWwindow* p_window);

		void ResetFrameState();

		void SetCursorMode(int p_cursorMode);

		bool IsKeyDown(int p_keyCode);
		bool IsKeyUp(int p_keyCode);
		float GetAxis(const std::string& p_axisName);

		bool IsMouseButtonDown(int p_mouseButton);
		bool IsMouseButtonUp(int p_mouseButton);

		glm::vec2 GetMousePosition();
		glm::vec2 GetMouseMovement();

		void UpdateKeyAxis(int p_keyCode, int p_action);
		void UpdateMousePosition(double p_mouseX, double p_mouseY);
		void UpdateMouseButton(int p_mouseButton, int p_action);

	private:
		GLFWwindow* m_window = nullptr;

		std::vector<int> m_keysDown;
		std::vector<int> m_keysUp;
		std::vector<KeyAxis> m_keyAxis;

		std::vector<int> m_mouseButtonDown;
		std::vector<int> m_mouseButtonUp;

		glm::vec2 m_mousePreviousPosition = { 0, 0 };
		glm::vec2 m_mousePosition = { 0, 0 };

		glm::vec2 m_mouseMovement = { 0, 0 };
	};

} // Core

#endif // MYVERSE_INPUT_CORE_H
