//
// Created by Tony on 05/08/2022.
//

#ifndef MYVERSE_APPLICATION_CORE_H
#define MYVERSE_APPLICATION_CORE_H

#define OPENGL_VERSION_MAJOR	3
#define OPENGL_VERSION_MINOR	2

#include "Core/Utils/GraphicsUtils.h"
#include "Core/Utils/JsonUtils.h"
#include "Core/Utils/MathUtils.h"
#include "Core/Utils/Utils.h"

#include "Core/AssetRepositoryAnalyzer.h"

#include "Core/Clock.h"
#include "Core/Input.h"

#include "Core/Rendering/Scene.h"
#include "Core/Factories/ScriptFactory.h"

#ifdef _DEBUG
#include "Core/Debug.h"
#endif

namespace Core
{

	typedef std::map<std::string, std::string> ScenePreloadMap;

	class ApplicationCore
	{
	private:
		ApplicationCore() = default;
		~ApplicationCore() = default;

	public:
		static ApplicationCore& instance();

		int Initialize();
		void Clear();

		void RenderLoop();

		void Quit();

		bool PreLoadScene(const std::string& p_sceneAlias, const std::string& p_scenePath);

		bool LoadScene(const std::string& p_sceneAlias);
		bool LoadScene(const int p_sceneId);

	public:
		std::shared_ptr<Scene> GetActiveScene();

	private:
		bool ParseProjectSettings(const std::string& p_projectSettingsFilePath);
		bool ParseGraphicsSettings(const std::string& p_graphicsSettingsFilePath);

		int Init_Glfw();

		void SetupPipeline();

	private:
		std::string m_assetsFolder = RESOURCES_PATH;
		std::string m_projectSettingsFolder = RESOURCES_PATH;

		std::string m_applicationName = "Default";

		bool m_fullScreenIsEnable = false;

		int m_windowWidth = 1600;
		int m_windowHeight = 900;

		bool m_superSamplingIsEnable = false;

		bool m_vSyncIsEnable = true;

		GLFWwindow* m_window = nullptr;

		ScenePreloadMap m_scenesPreload;
		int m_sceneToLoad = -1;

		std::shared_ptr<Scene> m_activeScene;
	};

} // Core

#endif // MYVERSE_APPLICATION_CORE_H
