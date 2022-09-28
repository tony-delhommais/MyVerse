//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_PLAYER_MOVEMENT_CONTROLLER_H
#define MYVERSE_PLAYER_MOVEMENT_CONTROLLER_H

#include "Client/Common/Application.h"

using namespace Client;

class PlayerController : public Script
{
public:
	PlayerController() = default;
	~PlayerController() override = default;

	void Start() override;
	void Update(float p_deltaTime) override;

private:
	static bool s_isRegistered;

	float playerRotationAcceleration = 5.0f;
	float playerMaxRotationSpeedStatic = 250.0f;
	float playerMaxRotationSpeedInMovement = 100.0f;

	float previousTargetRotationSpeed = 0.0f;

	float lerpUpdateRotationTime = 0.0f;

	float playerRotationVelocity = 0.0f;


	float playerAcceleration = 1.0f;
	float playerMaxSpeed = 2.0f;

	float previousTargetDirectionalSpeed = 0.0f;

	float lerpUpdateTime = 0.0f;

	float playerVelocity = 0.0f;
};

#endif // MYVERSE_PLAYER_MOVEMENT_CONTROLLER_H
