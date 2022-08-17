//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_CAMERA_H
#define MYVERSE_CAMERA_H

#include "Client/Utils/MathUtils.h"
#include "Client/Utils/JsonUtils.h"

#include "Client/Components/Component.h"

namespace Client
{

	class CircleArea;

	class Camera : public Component
	{
	public:
		Camera();
		~Camera() = default;

		static std::shared_ptr<Camera> Make(JsonObject& p_componentProprety);

	public:
		glm::mat4 GetViewMatrix();
		glm::mat4 GetProjectionMatrix();
		glm::mat4 GetViewProjectionMatrix();

		void UpdateProjectionMatrix();

	public:
		std::shared_ptr<CircleArea> GetDynamicEntityRenderingArea();

	private:
		float m_fov = 60.0f;
		float m_nearPlan = 0.01f;
		float m_farPlan = 100.0f;

		glm::mat4 m_projectionMatrix = glm::mat4(1.0);

		float m_dynamicEntityRenderingAreaRadius = 5.0f;
	};

} // Client

#endif // MYVERSE_CAMERA_H
