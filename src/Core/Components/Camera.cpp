//
// Created by Tony on 29/06/2022.
//

#include "Core/Components/Camera.h"

#include "Core/Entity/Entity.h"

#include "Core/Area/CircleArea.h"

#ifdef _DEBUG
#include "Core/Debug.h"
#endif

namespace Core
{

	Camera::Camera() : Component()
	{
		UpdateProjectionMatrix();
	}

	Camera::Camera(std::shared_ptr<Camera> p_camera) : Component(p_camera)
	{
		m_fov = p_camera->m_fov;
		m_nearPlan = p_camera->m_nearPlan;
		m_farPlan = p_camera->m_farPlan;

		m_projectionMatrix = p_camera->m_projectionMatrix;
	}

	std::shared_ptr<Camera> Camera::Make(JsonObject& p_componentProprety)
	{
		bool cameraIsValid = true;

		if (GetParameterFromJsonObject(p_componentProprety, "Type", "Null") != "Camera")
			cameraIsValid = false;

		if (!cameraIsValid)
		{
			return nullptr;
		}

		auto camera = std::make_shared<Camera>();

		camera->m_fov = GetParameterFromJsonObject(p_componentProprety, "Fov", camera->m_fov);
		camera->m_nearPlan = GetParameterFromJsonObject(p_componentProprety, "Near", camera->m_nearPlan);
		camera->m_farPlan = GetParameterFromJsonObject(p_componentProprety, "Far", camera->m_farPlan);

		camera->m_dynamicEntityRenderingAreaRadius = GetParameterFromJsonObject(p_componentProprety, "DynamicEntityRenderingAreaRadius", camera->m_dynamicEntityRenderingAreaRadius);

		camera->UpdateProjectionMatrix();

		return camera;
	}

	glm::mat4 Camera::GetViewMatrix()
	{
		if (GetEntity())
		{
			glm::vec3 position = GetEntity()->GetWorldPosition();

			glm::vec3 direction = GetEntity()->Forward();

			glm::vec3 up = GetEntity()->Up();

			return glm::lookAt(
				position,
				position + direction,
				up
			);
		}

#ifdef _DEBUG
    Debug::LogWarning("[Camera] Not assigned to an Entity");
#endif

		return glm::mat4(1.0);
	}

	glm::mat4 Camera::GetProjectionMatrix()
	{
		return m_projectionMatrix;
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

	std::shared_ptr<CircleArea> Camera::GetDynamicEntityRenderingArea()
	{
		return std::make_shared<CircleArea>(GetEntity()->GetWorldPosition(), m_dynamicEntityRenderingAreaRadius);
	}

} // Core
