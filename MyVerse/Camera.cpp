//
// Created by Tony on 29/06/2022.
//

#include "Camera.h"

#include "Entity.h"

#ifdef _DEBUG
#include "Debug.h"
#endif

namespace Client
{

	Camera::Camera(std::shared_ptr<Entity> p_entity, float p_fov, const glm::vec2& p_nearFar) :
		Component(ComponentType::CAMERA, p_entity),
		m_fov(p_fov),
		m_nearFar(p_nearFar)
	{
		UpdateProjectionMatrix();
	}

	float Camera::GetFov()
	{
		return m_fov;
	}

	glm::vec2 Camera::GetNearFar()
	{
		return m_nearFar;
	}

	glm::mat4 Camera::GetViewMatrix()
	{
		return glm::inverse(GetEntity()->GetTransform()->GetModelMatrix());
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
			m_nearFar[0],
			m_nearFar[1]
		);
	}

	float Camera::DEFAULT_FOV()
	{
		return 60.0f;
	}

	glm::vec2 Camera::DEFAULT_NEAR_FAR()
	{
		return glm::vec2(0.01f, 100.0f);
	}

} // Client
