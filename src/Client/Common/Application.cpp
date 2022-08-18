//
// Created by Tony on 29/06/2022.
//

#include "Client/Common/Application.h"

#include "Client/Core/ApplicationCore.h"

namespace Client
{

	void Application::Quit()
	{
		ApplicationCore::instance().Quit();
	}

	long long Application::GetFrameCount()
	{
		return ApplicationCore::instance().GetFrameCount();
	}

	bool Application::IsApplicationPaused()
	{
		return ApplicationCore::instance().IsApplicationPaused();
	}

	void Application::SetApplicationPause(bool p_pauseState)
	{
		ApplicationCore::instance().SetApplicationPause(p_pauseState);
	}

} // Client
