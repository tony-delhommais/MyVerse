//
// Created by Tony on 29/06/2022.
//

#include "Client/Entity/Camera.h"

#include "Client/Core/ApplicationCore.h"

#include "Client/Ressource/Shader.h"

#include "Client/Factories/ScriptFactory.h"

#ifdef _DEBUG
#include "Client/Common/Debug.h"
#endif

namespace Client
{

	Camera::Camera()
	{
		UpdateProjectionMatrix();
	}

	std::shared_ptr<Camera> Camera::Make(const std::filesystem::path& p_cameraSettingsPath)
	{
		JsonObject cameraSettings = LoadJsonFile(p_cameraSettingsPath);
		if (cameraSettings.empty())
		{
#ifdef _DEBUG
			Debug::LogError("[Camera] Camera Settings Path not valid!");
#endif
			return nullptr;
		}

		auto camera = std::make_shared<Camera>();

		camera->SetTag("MainCamera");

		camera->m_fov = GetParameterFromJsonObject(cameraSettings, "Fov", camera->m_fov);
		camera->m_nearPlan = GetParameterFromJsonObject(cameraSettings, "Near", camera->m_nearPlan);
		camera->m_farPlan = GetParameterFromJsonObject(cameraSettings, "Far", camera->m_farPlan);

		camera->UpdateProjectionMatrix();

		auto& cameraControllerScriptData = GetParameterFromJsonObject(cameraSettings, "CameraControllerScript", false, true);
		if (cameraControllerScriptData == cameraSettings)
		{
#ifdef _DEBUG
			Debug::LogWarning("[Camera] No Camera Controller Script set!");
#endif
		}
		else
		{
			auto cameraControllerScript = ScriptFactory::instance().Make(cameraControllerScriptData);
			
			camera->AddComponent(cameraControllerScript);
		}

		return camera;
	}

	void Camera::UseCameraForRendering()
	{
		if (m_shaderVueProjectionMatrixUniformLocation == -1)
		{
			m_shaderVueProjectionMatrixUniformLocation = ApplicationCore::instance().GetActiveShader()->FindUniformLocation("VueProjectionMatrix");
		}

		ApplicationCore::instance().GetActiveShader()->SetUniformMat4(m_shaderVueProjectionMatrixUniformLocation, m_projectionMatrix * GetViewMatrix());
	}

	glm::mat4 Camera::GetViewMatrix()
	{
		glm::vec3 position = GetWorldPosition();

		glm::vec3 direction = Forward();

		glm::vec3 up = Up();

		return glm::lookAt(
			position,
			position + direction,
			up
		);
	}

	glm::mat4 Camera::GetViewProjectionMatrix()
	{
		return m_projectionMatrix * GetViewMatrix();
	}

	void Camera::UpdateProjectionMatrix()
	{
		m_projectionMatrix = glm::perspective(
			glm::radians(m_fov),
			16.0f / 9.0f,
			m_nearPlan,
			m_farPlan
		);
	}

} // Client
