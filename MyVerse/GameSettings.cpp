//
// Created by Tony on 06/08/2022.
//

#include "GameSettings.h"

void GameSettings::Start()
{
	Input::SetCursorMode(GLFW_CURSOR_DISABLED);
}

void GameSettings::Update(float p_deltaTime)
{
	if (Input::IsKeyDown(GLFW_KEY_ESCAPE))
	{
		if (Application::IsApplicationPaused())
		{
			Input::SetCursorMode(GLFW_CURSOR_DISABLED);
			Application::SetApplicationPause(false);
		}
		else
		{
			Input::SetCursorMode(GLFW_CURSOR_NORMAL);
			Application::SetApplicationPause(true);
		}
	}
}

bool GameSettings::s_isRegistered = ScriptFactory::instance().Register("GameSettings", [](JsonObject& parameters) {
	auto script = std::make_shared<GameSettings>();

	return script;
});
