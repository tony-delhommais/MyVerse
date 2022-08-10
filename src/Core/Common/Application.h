//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_APPLICATION_H
#define MYVERSE_APPLICATION_H

#include "Core/Utils/Utils.h"
#include "Core/Utils/JsonUtils.h"

#include "Core/Common/Clock.h"
#include "Core/Common/Input.h"

#include "Core/Entity/Entity.h"

#include "Core/Ressource/Scene.h"

#include "Core/Factories/ScriptFactory.h"

#include "Core/Common/Debug.h"

namespace Core
{

	class Application
	{
	private:
		Application() = default;
		~Application() = default;

	public:
		static void Quit();

		static bool LoadScene(const std::string& p_sceneAlias);
		static bool LoadScene(int p_sceneId);

	public:
		long long GetFrameCount();

		static std::shared_ptr<Scene> GetActiveScene();

		static bool IsApplicationPaused();
		static void SetApplicationPause(bool p_pauseState);
	};

} // Core

#endif // MYVERSE_APPLICATION_H
