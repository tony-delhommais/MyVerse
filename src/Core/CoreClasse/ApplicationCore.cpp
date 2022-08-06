//
// Created by Tony on 05/08/2022.
//

#include "Core/CoreClasse/ApplicationCore.h"

#include "Core/CoreClasse/InputCore.h"
#include "Core/CoreClasse/RessourceManagerCore.h"

namespace Core
{

	ApplicationCore& ApplicationCore::instance()
	{
		static ApplicationCore instance;
		return instance;
	}

	int ApplicationCore::Initialize()
	{
		m_assetsFolder = RESOURCES_PATH + std::string("./Assets/");
		m_projectSettingsFolder = RESOURCES_PATH + std::string("./ProjectSettings/");

		std::string projectSettingsPath = m_projectSettingsFolder + std::string("./ProjectSettings.json");
		if (!ParseProjectSettings(projectSettingsPath))
		{
			return 0;
		}

		std::string graphicsSettingsPath = m_projectSettingsFolder + std::string("./GraphicsSettings.json");
		if (!ParseGraphicsSettings(graphicsSettingsPath))
		{
			return 0;
		}

		if (!Init_Glfw())
		{
			return 0;
		}

		SetupPipeline();

		InputCore::instance().Initialize(m_window);

		AssetRepositoryAnalyzer::GenerateMetaFilesOnAssetsFolder(RESOURCES_PATH);

		AssetRepositoryAnalyzer::PreloadAssetsFiles(RESOURCES_PATH);

		return 1;
	}

	void ApplicationCore::Clear()
	{
		if (m_window)
		{
			glfwDestroyWindow(m_window);
			m_window = nullptr;
		}

		glfwTerminate();
	}

	void ApplicationCore::RenderLoop()
	{
		if (m_sceneToLoad == -1)
		{
#ifdef _DEBUG
			Debug::LogError("[Application] No one scene was preloaded");
#endif
			return;
		}

		do
		{
			ScenePreloadMap::iterator sceneToLoad = m_scenesPreload.begin();
			for (int i = 0; i < m_sceneToLoad; i++) sceneToLoad++;

			m_sceneToLoad = -1;
			m_activeScene = Scene::Make(sceneToLoad->second);

			if (!m_activeScene)
			{
#ifdef _DEBUG
				Debug::LogError("[Application] Unable to load scene");
#endif
				return;
			}

#ifdef _DEBUG
			__int64 frameCount = 0;

			__int64 deltaMainLoop = 0;
			__int64 deltaRessourceManagementLoop = 0;
			__int64 deltaUpdateExecution = 0;
			__int64 deltaRender = 0;
#endif

			do
			{
				__int64 deltaTime = Clock::instance().GetNanosecondStopWatchTime("MainLoop");
				float secondDeltaTime = (float)(deltaTime / 1000000.0);
				Clock::instance().ResetStopWatch("MainLoop");

				InputCore::instance().ResetFrameState();
				glfwPollEvents();

				if (glfwWindowShouldClose(m_window) || m_sceneToLoad != -1)
					m_activeScene->StopExecution();

#ifdef _DEBUG
				Clock::instance().ResetStopWatch("RessourceManagementLoop");
#endif
				RessourceManagerCore::instance().ManagementLoop();
#ifdef _DEBUG
				deltaRessourceManagementLoop += Clock::instance().GetNanosecondStopWatchTime("RessourceManagementLoop");
#endif

#ifdef _DEBUG
				Clock::instance().ResetStopWatch("UpdateExecution");
#endif
				m_activeScene->UpdateExecution(secondDeltaTime);
#ifdef _DEBUG
				deltaUpdateExecution += Clock::instance().GetNanosecondStopWatchTime("UpdateExecution");
#endif

				m_activeScene->RemoveDestroyedLocalEntities();

#ifdef _DEBUG
				Clock::instance().ResetStopWatch("Render");
#endif
				m_activeScene->Render();
#ifdef _DEBUG
				deltaRender += Clock::instance().GetNanosecondStopWatchTime("Render");
#endif

				glfwSwapBuffers(m_window);

#ifdef _DEBUG
				frameCount++;

				deltaMainLoop += deltaTime;

				if (Clock::instance().GetMillisecondStopWatchTime("MainLoopDebugUpdate") > 1000)
				{
					Clock::instance().ResetStopWatch("MainLoopDebugUpdate");

					float d = frameCount;

					if (frameCount != 0)
					{
						float l_deltaMainLoop = (int)(deltaMainLoop / d) / 1000.0f;
						float l_deltaRessourceManagementLoop = (int)(deltaRessourceManagementLoop / d) / 1000.0f;
						float l_deltaUpdateExecution = (int)(deltaUpdateExecution / d) / 1000.0f;
						float l_deltaRender = (int)(deltaRender / d) / 1000.0f;

						float l_total = (int)((deltaRessourceManagementLoop + deltaUpdateExecution + deltaRender) / d) / 1000.0f;

						std::cout << "\rFU: " << l_deltaMainLoop << "  ML: " << l_deltaRessourceManagementLoop << "  U: " << l_deltaUpdateExecution << "  R: " << l_deltaRender << "  TT: " << l_total << "                  ";
					}

					frameCount = 0;

					deltaMainLoop = 0;
					deltaRessourceManagementLoop = 0;
					deltaUpdateExecution = 0;
					deltaRender = 0;
				}
#endif

			} while ((!glfwWindowShouldClose(m_window) && m_sceneToLoad == -1) || m_activeScene->HasLocalEntities());

			m_activeScene = nullptr;

		} while (!glfwWindowShouldClose(m_window));

#ifdef _DEBUG
		std::cout << std::endl;
		Debug::LogInfo("Application End");
#endif

		return;
	}

	void ApplicationCore::Quit()
	{
		glfwSetWindowShouldClose(m_window, GLFW_TRUE);
	}

	bool ApplicationCore::PreLoadScene(const std::string& p_sceneAlias, const std::string& p_scenePath)
	{
		std::fstream file;
		file.open(p_scenePath, std::ios::in);

		if (!file.is_open())
		{
#ifdef _DEBUG
			Debug::LogWarning("[Application] Unable to preload scene, config file not found");
#endif
			return false;
		}

		file.close();

		auto ret = m_scenesPreload.insert(ScenePreloadMap::value_type(p_sceneAlias, p_scenePath));
		if (ret.second == false)
		{
#ifdef _DEBUG
			Debug::LogWarning("[Application] Tried to preload a scene with a multiple used alias");
#endif
			return false;
		}

		m_sceneToLoad = 0;

		return true;
	}

	bool ApplicationCore::LoadScene(const std::string& p_sceneAlias)
	{
		ScenePreloadMap::iterator it = m_scenesPreload.find(p_sceneAlias);

		if (it == m_scenesPreload.end())
		{
			return false;
		}

		m_sceneToLoad = int(std::distance(m_scenesPreload.begin(), it));

		return true;
	}

	bool ApplicationCore::LoadScene(const int p_sceneId)
	{
		if (p_sceneId < 0 || p_sceneId >= m_scenesPreload.size())
			return false;

		m_sceneToLoad = p_sceneId;

		return true;
	}

	std::shared_ptr<Scene> ApplicationCore::GetActiveScene()
	{
		return m_activeScene;
	}

	bool ApplicationCore::IsApplicationPaused()
	{
		return m_applicationIsPaused;
	}

	void ApplicationCore::SetApplicationPause(bool p_pauseState)
	{
		m_applicationIsPaused = p_pauseState;
	}

	bool ApplicationCore::ParseProjectSettings(const std::string& p_projectSettingsFilePath)
	{
		auto projectSettings = LoadJsonFile(p_projectSettingsFilePath);
		if (projectSettings.empty())
		{
#ifdef _DEBUG
			Debug::LogError("[Application] Unable to locate project settings file");
#endif
			return false;
		}

		m_applicationName = GetParameterFromJsonObject(projectSettings, "ApplicationName", m_applicationName);

		JsonObject& axisList = GetParameterFromJsonObject(projectSettings, "Axis", true, false);
		if (axisList != projectSettings)
		{
			for (auto& axis : axisList)
			{
				InputCore::instance().ParseAxisKey(axis);
			}
		}

		return true;
	}

	bool ApplicationCore::ParseGraphicsSettings(const std::string& p_graphicsSettingsFilePath)
	{
		auto graphicsSettings = LoadJsonFile(p_graphicsSettingsFilePath);
		if (graphicsSettings.empty())
		{
#ifdef _DEBUG
			Debug::LogError("[Application] Unable to locate graphics settings file");
#endif
			return false;
		}

		m_fullScreenIsEnable = GetParameterFromJsonObject(graphicsSettings, "EnableFullScreen", m_fullScreenIsEnable);

		m_windowWidth = GetParameterFromJsonObject(graphicsSettings, "Width", m_windowWidth);
		m_windowHeight = GetParameterFromJsonObject(graphicsSettings, "Height", m_windowHeight);

		m_superSamplingIsEnable = GetParameterFromJsonObject(graphicsSettings, "EnableSuperSampling", m_superSamplingIsEnable);

		m_vSyncIsEnable = GetParameterFromJsonObject(graphicsSettings, "EnableVSync", m_vSyncIsEnable);

		return true;
	}

	int ApplicationCore::Init_Glfw()
	{
		GLenum res = glfwInit();

		if (res != GLFW_TRUE)
		{
#ifdef _DEBUG
			Debug::LogError("[Application] Cannot initialize GLFW");
#endif
			return 0;
		}

		if (m_superSamplingIsEnable) glfwWindowHint(GLFW_SAMPLES, 4);

		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		if (m_fullScreenIsEnable)
		{
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* mode = glfwGetVideoMode(monitor);

			m_window = glfwCreateWindow(mode->width, mode->height, m_applicationName.c_str(), monitor, NULL);
		}
		else m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, m_applicationName.c_str(), NULL, NULL);

		if (!m_window)
		{
#ifdef _DEBUG
			Debug::LogError("[Application] glfwCreateWindow failed!");
#endif
			return 0;
		}

		return 1;
	}

	void ApplicationCore::SetupPipeline()
	{
		glfwMakeContextCurrent(m_window);

		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		if (m_vSyncIsEnable) glfwSwapInterval(1);
		else glfwSwapInterval(0);

		glDrawBuffer(GL_BACK);
		glClearColor(0.25, 0.25f, 0.25f, 1.0f);
		glClearDepth(1.0f);
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_DEPTH_TEST);

		// pour activer la prise en charge des textures bitmaps
		glEnable(GL_TEXTURE_2D);
		// pour masquer les faces dont les normales ne sont pas en direction de la camera
		glEnable(GL_CULL_FACE);

		if (m_superSamplingIsEnable) glEnable(GL_MULTISAMPLE);
	}

} // Core
