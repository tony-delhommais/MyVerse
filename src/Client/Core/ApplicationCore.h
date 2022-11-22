//
// Created by Tony on 05/08/2022.
//

#ifndef MYVERSE_APPLICATION_CORE_H
#define MYVERSE_APPLICATION_CORE_H

#define OPENGL_VERSION_MAJOR	3
#define OPENGL_VERSION_MINOR	2

#include "Client/Utils/GraphicsUtils.h"
#include "Client/Utils/JsonUtils.h"
#include "Client/Utils/MathUtils.h"
#include "Client/Utils/Utils.h"

#include "Client/Common/AssetRepositoryAnalyzer.h"

#include "Client/Common/Clock.h"
#include "Client/Common/Input.h"

#include "Client/Core/SceneManagerCore.h"

#include "Client/Ressources/Shader/Shader.h"

#include "Client/Components/Script/ScriptFactory.h"

#ifdef _DEBUG
#include "Client/Common/Debug.h"
#endif

namespace Client
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

	public:
		long long GetFrameCount();

		std::shared_ptr<Shader> GetActiveShader();

		bool IsApplicationPaused();
		void SetApplicationPause(bool p_pauseState);

	private:
		bool ParseProjectSettings();
		bool ParseGraphicsSettings();

		bool InitGlfw();

		bool SetupPipeline();

		bool InitializeShader();

	private:
		std::string m_applicationName = "Default";

		bool m_fullScreenIsEnable = false;

		int m_windowWidth = 1600;
		int m_windowHeight = 900;

		bool m_superSamplingIsEnable = false;

		bool m_vSyncIsEnable = true;

		GLFWwindow* m_window = nullptr;

		long long m_frameCount = 0;

	private:
		std::filesystem::path m_vertexShaderPath;
		std::filesystem::path m_fragmentShaderPath;
		std::shared_ptr<Shader> m_activeShader = nullptr;

		bool m_applicationIsPaused = false;
	};

} // Client

#endif // MYVERSE_APPLICATION_CORE_H
