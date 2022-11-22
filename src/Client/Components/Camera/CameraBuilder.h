//
// Created by Tony on 08/11/2022.
//

#ifndef MYVERSE_CAMERA_BUILDER_H
#define MYVERSE_CAMERA_BUILDER_H

#include "Client/Components/Camera/Camera.h"

namespace Client
{

	class CameraBuilder
	{
	public:
		CameraBuilder();
		~CameraBuilder() = default;

	public:
		std::shared_ptr<Camera> Build();

		CameraBuilder& SetFov(float p_fov);
		CameraBuilder& SetNearFar(const glm::vec2& p_nearFar);
		CameraBuilder& SetNear(float p_near);
		CameraBuilder& SetFar(float p_far);

	private:
		std::shared_ptr<Entity> m_entity = nullptr;

		float m_fov;
		glm::vec2 m_nearFar;
	};

} // Client

#endif // MYVERSE_CAMERA_BUILDER_H
