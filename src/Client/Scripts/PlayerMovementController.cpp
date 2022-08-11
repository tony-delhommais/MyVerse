//
// Created by Tony on 29/06/2022.
//

#include "Client/Scripts/PlayerMovementController.h"

void PlayerMovementController::Update(float p_deltaTime)
{
	UpdatePlayerPosition(p_deltaTime);
	UpdateCameraRotation(p_deltaTime);
}

void PlayerMovementController::UpdatePlayerPosition(float p_deltaTime)
{
	// Z: (W) 87
	// S: (S) 83
	// D: (D) 68
	// Q: (A) 65

	float current_x_axis = 0;
	float current_y_axis = 0;

	if (!Application::IsApplicationPaused())
	{
		current_x_axis = Input::GetAxis("Right");
		current_y_axis = Input::GetAxis("Forward");
	}

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

	playerVelocity = Math::Lerp(playerVelocity, previousTargetDirectionalSpeed, lerpUpdateTime);

	GetEntity()->Translate(playerVelocity * p_deltaTime);
}

void PlayerMovementController::UpdateCameraRotation(float p_deltaTime)
{
	glm::vec2 mouseMovement = glm::vec2(0.0);

	if (!Application::IsApplicationPaused())
	{
		mouseMovement = Input::GetMouseMovement();
	}

	GetEntity()->RotateEuler(glm::vec3(0.0, mouseMovement.x, 0.0) * (cameraRotationSpeed * 2) / 100.0f);
}

bool PlayerMovementController::s_isRegistered = ScriptFactory::instance().Register("PlayerMovementController", [](JsonObject& parameters) {
	auto script = std::make_shared<PlayerMovementController>();

	script->playerAcceleration = GetParameterFromJsonObject(parameters, "PlayerAcceleration", script->playerAcceleration);
	script->playerMaxSpeed = GetParameterFromJsonObject(parameters, "PlayerMaxSpeed", script->playerMaxSpeed);

	script->cameraRotationSpeed = GetParameterFromJsonObject(parameters, "CameraRotationSpeed", script->cameraRotationSpeed);

	return script;
});
