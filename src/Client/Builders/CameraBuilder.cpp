//
// Created by Tony on 08/11/2022.
//

#include "Client/Builders/CameraBuilder.h"

namespace Client
{

	CameraBuilder::CameraBuilder()
	{
		m_fov = Camera::DEFAULT_FOV();
		m_nearFar = Camera::DEFAULT_NEAR_FAR();
	}

	std::shared_ptr<Camera> CameraBuilder::Build()
	{
		return std::make_shared<Camera>(m_entity, m_fov, m_nearFar);
	}

	CameraBuilder& Client::CameraBuilder::SetFov(float p_fov)
	{
		m_fov = p_fov;

		return *this;
	}

	CameraBuilder& Client::CameraBuilder::SetNearFar(const glm::vec2& p_nearFar)
	{
		m_nearFar = p_nearFar;

		return *this;
	}

	CameraBuilder& Client::CameraBuilder::SetNear(float p_near)
	{
		m_nearFar[0] = p_near;

		return *this;
	}

	CameraBuilder& Client::CameraBuilder::SetFar(float p_far)
	{
		m_nearFar[1] = p_far;

		return *this;
	}

} // Client
