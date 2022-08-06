//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_CAMERA_H
#define MYVERSE_CAMERA_H

#include "Core/Utils/MathUtils.h"
#include "Core/Utils/JsonUtils.h"

#include "Core/Components/Component.h"

namespace Core
{

	class CircleArea;

	class Camera : public Component
	{
	public:
		Camera();
		Camera(std::shared_ptr<Camera> p_camera);
		~Camera() = default;

		static std::shared_ptr<Camera> Make(JsonObject& p_componentProprety);

	public:
		glm::mat4 GetViewMatrix();
		glm::mat4 GetProjectionMatrix();

		void UpdateProjectionMatrix();

	public:
		std::shared_ptr<CircleArea> GetDynamicEntityRenderingArea();

	private:

		float m_fov = 60.0f;
		float m_nearPlan = 0.01f;
		float m_farPlan = 100.0f;

		glm::mat4 m_projectionMatrix;

		float m_dynamicEntityRenderingAreaRadius = 5.0f;
	};

} // Core

#endif // MYVERSE_CAMERA_H
