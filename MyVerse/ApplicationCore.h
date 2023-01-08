//
// Created by Tony on 05/08/2022.
//

#ifndef MYVERSE_APPLICATION_CORE_H
#define MYVERSE_APPLICATION_CORE_H

#define OPENGL_VERSION_MAJOR	3
#define OPENGL_VERSION_MINOR	2

#include "GraphicsUtils.h"
#include "JsonUtils.h"
#include "MathUtils.h"
#include "Utils.h"

#include "AssetRepositoryAnalyzer.h"

#include "Clock.h"
#include "Input.h"

#include "SceneManagerCore.h"

#include "Shader.h"

#include "ScriptFactory.h"

#ifdef _DEBUG
#include "Debug.h"
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
