//
// Created by Tony on 29/06/2022.
//

#include "Core/Application.h"

#include "Core/CoreClass/ApplicationCore.h"

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

	bool Application::LoadScene(int p_sceneId)
	{
		return ApplicationCore::instance().LoadScene(p_sceneId);
	}

	long long Application::GetFrameCount()
	{
		return ApplicationCore::instance().GetFrameCount();
	}

	std::shared_ptr<Scene> Application::GetActiveScene()
	{
		return ApplicationCore::instance().GetActiveScene();
	}

	bool Application::IsApplicationPaused()
	{
		return ApplicationCore::instance().IsApplicationPaused();
	}

	void Application::SetApplicationPause(bool p_pauseState)
	{
		ApplicationCore::instance().SetApplicationPause(p_pauseState);
	}

} // Core
