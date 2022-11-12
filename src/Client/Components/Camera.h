//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_CAMERA_H
#define MYVERSE_CAMERA_H

#include "Client/Utils/Utils.h"
#include "Client/Utils/MathUtils.h"

#include "Client/Components/Component.h"

namespace Client
{

	class Entity;

	class Camera : public Component
	{
	public:
		Camera(std::shared_ptr<Entity> p_entity, float p_fov, const glm::vec2& p_nearFar);
		~Camera() = default;

	public:
		float GetFov();
		glm::vec2 GetNearFar();

		glm::mat4 GetViewMatrix();
		glm::mat4 GetProjectionMatrix();
		glm::mat4 GetViewProjectionMatrix();

	private:
		void UpdateProjectionMatrix();

	public:
		static float DEFAULT_FOV();
		static glm::vec2 DEFAULT_NEAR_FAR();

	private:
		float m_fov = 60.0f;
		glm::vec2 m_nearFar = glm::vec2(0.01f, 100.0f);

		glm::mat4 m_projectionMatrix = glm::mat4(1.0);
	};

} // Client

#endif // MYVERSE_CAMERA_H
