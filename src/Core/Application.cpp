//
// Created by Tony on 29/06/2022.
//

#include "Core/Application.h"

#include "Core/CoreClasse/ApplicationCore.h"

namespace Core
{

	void Application::Quit()
	{
		ApplicationCore::instance().Quit();
	}

	bool Application::LoadScene(const std::string& p_sceneAlias)
	{
		return ApplicationCore::instance().LoadScene(p_sceneAlias);
	}

	bool Application::LoadScene(const int p_sceneId)
	{
		return ApplicationCore::instance().LoadScene(p_sceneId);
	}

	std::shared_ptr<Scene> Application::GetActiveScene()
	{
		return ApplicationCore::instance().GetActiveScene();
	}

} // Core
