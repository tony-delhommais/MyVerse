//
// Created by Tony on 29/06/2022.
//

#include "Client/Scripts/PlayerMovementController.h"

void PlayerMovementController::Update(float p_deltaTime)
{
	if (!Application::IsApplicationPaused())
	{
		UpdatePlayerPosition(p_deltaTime);
		UpdateCameraRotation(p_deltaTime);
	}
}

void PlayerMovementController::UpdatePlayerPosition(float p_deltaTime)
{
	// Z: (W) 87
	// S: (S) 83
	// D: (D) 68
	// Q: (A) 65

	float current_x_axis = Input::GetAxis("Right");
	float current_y_axis = Input::GetAxis("Forward");

	glm::vec3 direction = glm::vec3(0.0);

	if (current_x_axis != 0 || current_y_axis != 0)
	{
		direction = glm::normalize(GetEntity()->Forward() * current_y_axis + GetEntity()->Right() * current_x_axis);
	}

	glm::vec3 targetDirectionalSpeed = direction * playerMaxSpeed;

	if (previousTargetDirectionalSpeed != targetDirectionalSpeed)
	{
		previousTargetDirectionalSpeed = targetDirectionalSpeed;
		lerpUpdateTime = 0.0f;
	}

	lerpUpdateTime += p_deltaTime * playerAcceleration;

	playerVelocity = Lerp(playerVelocity, previousTargetDirectionalSpeed, lerpUpdateTime);

	GetEntity()->Translate(playerVelocity * p_deltaTime);
}

void PlayerMovementController::UpdateCameraRotation(float p_deltaTime)
{
	GetEntity()->RotateEuler(glm::vec3(0.0, Input::GetMouseMovement().x, 0.0) * (cameraRotationSpeed * 2) / 100.0f);
}

bool PlayerMovementController::s_isRegistered = ScriptFactory::instance().Register("PlayerMovementController", [](JsonObject& parameters)
	{
		auto script = std::make_shared<PlayerMovementController>();

		script->playerAcceleration = GetParameterFromJsonObject(parameters, "PlayerAcceleration", script->playerAcceleration);
		script->playerMaxSpeed = GetParameterFromJsonObject(parameters, "PlayerMaxSpeed", script->playerMaxSpeed);

		script->cameraRotationSpeed = GetParameterFromJsonObject(parameters, "CameraRotationSpeed", script->cameraRotationSpeed);

		return script;
	});