//
// Created by Tony on 17/08/2022.
//

#ifndef MYVERSE_CAMERA_CONTROLLER_H
#define MYVERSE_CAMERA_CONTROLLER_H

#include "Client/Common/Application.h"

#include "Client/Entity/Player.h"

using namespace Client;

class CameraController : public Script
{
public:
	CameraController() = default;
	~CameraController() override = default;

	void Start() override;
	void Update(float p_deltaTime) override;

private:
	static bool s_isRegistered;

	glm::mat4 cameraOffsetTransform = glm::mat4(1.0f);

	glm::vec3 cameraOffsetPosition = glm::vec3(0.0f, 1.5f, 2.5f);
	glm::vec3 cameraOffsetRotation = glm::vec3(-20.0f, 0.0f, 0.0f);

	float cameraRotationAngle = 0.0f;
	float cameraRotationSpeed = 1.0f;
};

#endif // MYVERSE_CAMERA_CONTROLLER_H
