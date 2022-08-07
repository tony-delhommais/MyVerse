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

#include "Core/Ressource/Scene.h"

#include "Core/Factories/ScriptFactory.h"

#ifdef _DEBUG
#include "Core/Debug.h"
#endif

namespace Core
{

	typedef std::map<std::string, std::filesystem::path> ScenePreloadMap;

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

		bool PreLoadScene(const std::string& p_sceneAlias, const std::filesystem::path& p_scenePath);

		bool LoadScene(const std::string& p_sceneAlias);
		bool LoadScene(int p_sceneId);

	public:
		__int64 GetFrameCount();

		std::shared_ptr<Scene> GetActiveScene();

		bool IsApplicationPaused();
		void SetApplicationPause(bool p_pauseState);

	private:
		bool ParseProjectSettings(const std::filesystem::path& p_projectSettingsFilePath);
		bool ParseGraphicsSettings(const std::filesystem::path& p_graphicsSettingsFilePath);

		int Init_Glfw();

		void SetupPipeline();

	private:
		std::string m_applicationName = "Default";

		bool m_fullScreenIsEnable = false;

		int m_windowWidth = 1600;
		int m_windowHeight = 900;

		bool m_superSamplingIsEnable = false;

		bool m_vSyncIsEnable = true;

		GLFWwindow* m_window = nullptr;

		__int64 m_frameCount = 0;

	private:
		ScenePreloadMap m_scenesPreload;
		int m_sceneToLoad = -1;

		std::shared_ptr<Scene> m_activeScene;

		bool m_applicationIsPaused = false;
	};

} // Core

#endif // MYVERSE_APPLICATION_CORE_H
