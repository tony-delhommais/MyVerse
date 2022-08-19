//
// Created by Tony on 29/06/2022.
//

#include "Client/GameScripts/Controllers/PlayerController.h"

void PlayerController::Update(float p_deltaTime)
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

	////////// Rotation //////////
	float targetRotationSpeed = current_x_axis * playerMaxRotationSpeedStatic;
	if(current_y_axis != 0) targetRotationSpeed = current_x_axis * playerMaxRotationSpeedInMovement;

	targetRotationSpeed *= -1.0f;

	if (previousTargetRotationSpeed != targetRotationSpeed)
	{
		previousTargetRotationSpeed = targetRotationSpeed;
		lerpUpdateRotationTime = 0.0f;
	}

	lerpUpdateRotationTime += p_deltaTime * playerRotationAcceleration;

	playerRotationVelocity = Math::Lerp(playerRotationVelocity, previousTargetRotationSpeed, lerpUpdateRotationTime);

	GetEntity()->RotateEuler(glm::vec3(0.0f, playerRotationVelocity, 0.0f) * p_deltaTime);
	////////// Rotation //////////

	////////// Translation //////////
	float targetDirectionalSpeed = current_y_axis * playerMaxSpeed;

	if (previousTargetDirectionalSpeed != targetDirectionalSpeed)
	{
		previousTargetDirectionalSpeed = targetDirectionalSpeed;
		lerpUpdateTime = 0.0f;
	}

	lerpUpdateTime += p_deltaTime * playerAcceleration;

	playerVelocity = Math::Lerp(playerVelocity, previousTargetDirectionalSpeed, lerpUpdateTime);

	GetEntity()->Translate(GetEntity()->Forward() * playerVelocity * p_deltaTime);
	////////// Translation //////////
}

bool PlayerController::s_isRegistered = ScriptFactory::instance().Register("PlayerController", [](JsonObject& parameters) {
	auto script = std::make_shared<PlayerController>();

	script->playerRotationAcceleration = GetParameterFromJsonObject(parameters, "PlayerRotationAcceleration", script->playerRotationAcceleration);
	script->playerMaxRotationSpeedStatic = GetParameterFromJsonObject(parameters, "PlayerMaxRotationSpeedStatic", script->playerMaxRotationSpeedStatic);
	script->playerMaxRotationSpeedInMovement = GetParameterFromJsonObject(parameters, "PlayerMaxRotationSpeedInMovement", script->playerMaxRotationSpeedInMovement);

	script->playerAcceleration = GetParameterFromJsonObject(parameters, "PlayerAcceleration", script->playerAcceleration);
	script->playerMaxSpeed = GetParameterFromJsonObject(parameters, "PlayerMaxSpeed", script->playerMaxSpeed);

	return script;
});
