//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_APPLICATION_H
#define MYVERSE_APPLICATION_H

#include "Core/Utils/Utils.h"
#include "Core/Utils/JsonUtils.h"

#include "Core/Clock.h"
#include "Core/Input.h"

#include "Core/Entity/Entity.h"

#include "Core/Rendering/Scene.h"
#include "Core/Factories/ScriptFactory.h"

#include "Core/Debug.h"

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
		static bool LoadScene(const int p_sceneId);

	public:
		static std::shared_ptr<Scene> GetActiveScene();
	};

} // Core

#endif // MYVERSE_APPLICATION_H
