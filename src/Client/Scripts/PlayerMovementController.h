//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_PLAYER_MOVEMENT_CONTROLLER_H
#define MYVERSE_PLAYER_MOVEMENT_CONTROLLER_H

#include "Core/Common/Application.h"

using namespace Core;

class PlayerMovementController : public Script
{
public:
	PlayerMovementController() = default;
	~PlayerMovementController() override = default;

	void Update(float p_deltaTime) override;

private:
	void UpdatePlayerPosition(float p_deltaTime);
	void UpdateCameraRotation(float p_deltaTime);

private:
	static bool s_isRegistered;

	float playerAcceleration = 1.0f;
	float playerMaxSpeed = 2.0f;

	glm::vec3 previousTargetDirectionalSpeed = glm::vec3(0.0f);

	float lerpUpdateTime = 0.0f;

	glm::vec3 playerVelocity = glm::vec3(0.0f);

	float cameraRotationSpeed = 1.0f;
};

#endif // MYVERSE_PLAYER_MOVEMENT_CONTROLLER_H
