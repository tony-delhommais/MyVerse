//
// Created by Tony on 05/08/2022.
//

#include "ApplicationCore.h"

#include "InputCore.h"
#include "RessourceManagerCore.h"

namespace Client
{

	ApplicationCore& ApplicationCore::instance()
	{
		static ApplicationCore instance;
		return instance;
	}

	int ApplicationCore::Initialize()
	{
		if (!ParseProjectSettings())
		{
			return 0;
		}

		if (!ParseGraphicsSettings())
		{
			return 0;
		}

		if (!InitGlfw())
		{
			return 0;
		}

		if (!SetupPipeline())
		{
			return 0;
		}

		if (!InitializeShader())
		{
			return 0;
		}

		InputCore::instance().Initialize(m_window);

		AssetRepositoryAnalyzer::GenerateMetaFilesOnAssetsFolder("./Assets");

		AssetRepositoryAnalyzer::PreloadAssetsFiles("./Assets");

		auto cameraSettings = LoadJsonFile(std::filesystem::path("./ProjectSettings" + std::string("./CameraSettings.json")));

		/*auto camera = EntityFactory::instance().Make<Camera>(cameraSettings);
		if (!camera)
		{
			return 0;
		}

		auto playerSettings = LoadJsonFile(std::filesystem::path("./ProjectSettings" + std::string("./PlayerSettings.json")));

		auto player = EntityFactory::instance().Make<Player>(playerSettings);
		if (!player)
		{
			return 0;
		}*/

		//Scene::instance().Initialize(std::filesystem::path(PROJECT_SETTINGS_PATH + std::string("./SceneSettings.json")));

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
#ifdef _DEBUG
		long long debugUpdateframeCount = 0;

		long long deltaMainLoop = 0;
		long long deltaRessourceManagementLoop = 0;
		long long deltaUpdateExecution = 0;
		long long deltaRender = 0;
#endif

		do
		{
			m_frameCount ++;
			long long deltaTime = Clock::instance().GetMicrosecondStopWatchTime("MainLoop");
			float secondDeltaTime = (float)(deltaTime / 1000000.0);
			Clock::instance().ResetStopWatch("MainLoop");

			InputCore::instance().ResetFrameState();
			glfwPollEvents();

			if (glfwWindowShouldClose(m_window))
				SceneManagerCore::instance().GetLoadedScene()->StopExecution();

#ifdef _DEBUG
			Clock::instance().ResetStopWatch("RessourceManagementLoop");
#endif
			RessourceManagerCore::instance().ManagementLoop();
#ifdef _DEBUG
			deltaRessourceManagementLoop += Clock::instance().GetMicrosecondStopWatchTime("RessourceManagementLoop");
#endif

#ifdef _DEBUG
			Clock::instance().ResetStopWatch("UpdateExecution");
#endif
			SceneManagerCore::instance().GetLoadedScene()->UpdateExecution(secondDeltaTime);
#ifdef _DEBUG
			deltaUpdateExecution += Clock::instance().GetMicrosecondStopWatchTime("UpdateExecution");
#endif

#ifdef _DEBUG
			Clock::instance().ResetStopWatch("Render");
#endif
			SceneManagerCore::instance().GetLoadedScene()->Render();
#ifdef _DEBUG
			deltaRender += Clock::instance().GetMicrosecondStopWatchTime("Render");
#endif

			glfwSwapBuffers(m_window);

#ifdef _DEBUG
			debugUpdateframeCount++;

			deltaMainLoop += deltaTime;

			if (Clock::instance().GetMillisecondStopWatchTime("MainLoopDebugUpdate") > 1000)
			{
				Clock::instance().ResetStopWatch("MainLoopDebugUpdate");

				if (debugUpdateframeCount != 0)
				{
					float l_deltaMainLoop = (int)(deltaMainLoop / (float)(debugUpdateframeCount)) / 1000.0f;
					float l_deltaRessourceManagementLoop = (int)(deltaRessourceManagementLoop / (float)(debugUpdateframeCount)) / 1000.0f;
					float l_deltaUpdateExecution = (int)(deltaUpdateExecution / (float)(debugUpdateframeCount)) / 1000.0f;
					float l_deltaRender = (int)(deltaRender / (float)(debugUpdateframeCount)) / 1000.0f;

					float l_total = (int)((deltaRessourceManagementLoop + deltaUpdateExecution + deltaRender) / (float)(debugUpdateframeCount)) / 1000.0f;

					std::cout << "\rFU: " << l_deltaMainLoop << "  ML: " << l_deltaRessourceManagementLoop << "  U: " << l_deltaUpdateExecution << "  R: " << l_deltaRender << "  TT: " << l_total << "                  ";
				}

				debugUpdateframeCount = 0;

				deltaMainLoop = 0;
				deltaRessourceManagementLoop = 0;
				deltaUpdateExecution = 0;
				deltaRender = 0;
			}
#endif

		} while (!glfwWindowShouldClose(m_window) || !SceneManagerCore::instance().GetLoadedScene()->IsStopped());

#ifdef _DEBUG
		std::cout << std::endl;
		Debug::LogInfo("Application End");
#endif
	}

	void ApplicationCore::Quit()
	{
		glfwSetWindowShouldClose(m_window, GLFW_TRUE);
	}

	long long ApplicationCore::GetFrameCount()
	{
		return m_frameCount;
	}

	std::shared_ptr<Shader> ApplicationCore::GetActiveShader()
	{
		return m_activeShader;
	}

	bool ApplicationCore::IsApplicationPaused()
	{
		return m_applicationIsPaused;
	}

	void ApplicationCore::SetApplicationPause(bool p_pauseState)
	{
		m_applicationIsPaused = p_pauseState;
	}

	bool ApplicationCore::ParseProjectSettings()
	{
		auto projectSettings = LoadJsonFile(std::filesystem::path("./ProjectSettings" + std::string("./ProjectSettings.json")));
		if (projectSettings.empty())
		{
#ifdef _DEBUG
			Debug::LogError("[Application] Unable to locate project settings file");
#endif
			return false;
		}

		m_applicationName = GetParameterFromJsonObject(projectSettings, "ApplicationName", m_applicationName);

		JsonObject& actionList = GetParameterFromJsonObject(projectSettings, "Actions", true, false);
		if (actionList != projectSettings)
		{
			InputCore::instance().ParseActions(actionList);
		}

		return true;
	}

	bool ApplicationCore::ParseGraphicsSettings()
	{
		auto graphicsSettings = LoadJsonFile(std::filesystem::path("./ProjectSettings" + std::string("./GraphicsSettings.json")));
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

		auto vertexShaderStr = GetParameterFromJsonObject(graphicsSettings, "VertexShader", "Null");
		auto fragmentShaderStr = GetParameterFromJsonObject(graphicsSettings, "FragmentShader", "Null");

		if (vertexShaderStr == "Null" || fragmentShaderStr == "Null")
		{
#ifdef _DEBUG
			Debug::LogError("[Application] Unable to locate shaders settings");
#endif
			return false;
		}

		m_vertexShaderPath = std::filesystem::path("./ProjectSettings" + vertexShaderStr);
		m_fragmentShaderPath = std::filesystem::path("./ProjectSettings" + fragmentShaderStr);

		if (!std::filesystem::exists(m_vertexShaderPath) || !std::filesystem::exists(m_fragmentShaderPath))
		{
#ifdef _DEBUG
			Debug::LogError("[Application] Shaders path are invalid");
#endif
			return false;
		}

		return true;
	}

	bool ApplicationCore::InitGlfw()
	{
		GLenum res = glfwInit();

		if (res != GLFW_TRUE)
		{
#ifdef _DEBUG
			Debug::LogError("[Application] Cannot initialize GLFW");
#endif
			return false;
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
			return false;
		}

		return true;
	}

	bool ApplicationCore::SetupPipeline()
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

		return true;
	}

	bool ApplicationCore::InitializeShader()
	{
		m_activeShader = std::make_shared<Shader>();

		m_activeShader->SetShader(SupportedFileType::VERTEX_SHADER, m_vertexShaderPath);
		m_activeShader->SetShader(SupportedFileType::FRAGMENT_SHADER, m_fragmentShaderPath);

		if (!m_activeShader->IsShaderValid())
		{
#ifdef _DEBUG
			Debug::LogError("[Application] Failed to create shader program");
#endif
			return false;
		}

		m_activeShader->Use();

		return true;
	}

} // Client
