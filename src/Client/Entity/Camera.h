//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_CAMERA_H
#define MYVERSE_CAMERA_H

#include "Client/Utils/Utils.h"
#include "Client/Utils/MathUtils.h"
#include "Client/Utils/JsonUtils.h"

#include "Client/Entity/Entity.h"

namespace Client
{

	class Camera : public Entity
	{
	public:
		Camera();
		~Camera() = default;

		static std::shared_ptr<Camera> Make(const std::filesystem::path& p_cameraSettingsPath);

	public:
		void UseCameraForRendering();

	private:
		glm::mat4 GetViewMatrix();
		glm::mat4 GetViewProjectionMatrix();

		void UpdateProjectionMatrix();

	private:
		GLint m_shaderVueProjectionMatrixUniformLocation = -1;

		float m_fov = 60.0f;
		float m_nearPlan = 0.01f;
		float m_farPlan = 100.0f;

		glm::mat4 m_projectionMatrix = glm::mat4(1.0);
	};

} // Client

#endif // MYVERSE_CAMERA_H
