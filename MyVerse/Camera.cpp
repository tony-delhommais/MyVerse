//
// Created by Tony on 29/06/2022.
//

#include "Camera.h"

#include "EntityFactory.h"

#include "ApplicationCore.h"

#include "Shader.h"

#include "ScriptFactory.h"

#ifdef _DEBUG
#include "Debug.h"
#endif

namespace Client
{

	Camera::Camera()
	{
		UpdateProjectionMatrix();
	}

	glm::mat4 Camera::GetViewMatrix()
	{
		return glm::inverse(GetModelMatrix());
	}

	glm::mat4 Camera::GetProjectionMatrix()
	{
		return m_projectionMatrix;
	}

	glm::mat4 Camera::GetViewProjectionMatrix()
	{
		return GetProjectionMatrix() * GetViewMatrix();
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

	bool Camera::s_isCameraMakerRegistered = EntityFactory::instance().Register("Camera", [](JsonObject& p_entityParameters) -> std::shared_ptr<Entity> {
		auto camera = std::make_shared<Camera>();

		camera->SetTag("MainCamera");

		camera->m_fov = GetParameterFromJsonObject(p_entityParameters, "Fov", camera->m_fov);
		camera->m_nearPlan = GetParameterFromJsonObject(p_entityParameters, "Near", camera->m_nearPlan);
		camera->m_farPlan = GetParameterFromJsonObject(p_entityParameters, "Far", camera->m_farPlan);

		camera->UpdateProjectionMatrix();

		auto& cameraControllerScriptData = GetParameterFromJsonObject(p_entityParameters, "CameraControllerScript", false, true);
		if (cameraControllerScriptData != p_entityParameters)
		{
			auto cameraControllerScript = ScriptFactory::instance().Make(cameraControllerScriptData);

			camera->SetScript(cameraControllerScript);
		}
#ifdef _DEBUG
		else
		{
			Debug::LogWarning("[Camera] No Camera Controller Script set!");
		}
#endif

		return camera;
	});

} // Client
