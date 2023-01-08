//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_CAMERA_H
#define MYVERSE_CAMERA_H

#include "Utils.h"
#include "MathUtils.h"
#include "JsonUtils.h"

#include "Entity.h"

namespace Client
{

	class Camera : public Entity
	{
	public:
		Camera();
		~Camera() = default;

	public:
		glm::mat4 GetViewMatrix();
		glm::mat4 GetProjectionMatrix();
		glm::mat4 GetViewProjectionMatrix();

	private:
		void UpdateProjectionMatrix();

	private:
		static bool s_isCameraMakerRegistered;

		float m_fov = 60.0f;
		float m_nearPlan = 0.01f;
		float m_farPlan = 100.0f;

		glm::mat4 m_projectionMatrix = glm::mat4(1.0);
	};

} // Client

#endif // MYVERSE_CAMERA_H
