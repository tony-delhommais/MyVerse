//
// Created by Tony on 17/08/2022.
//

#include "CameraController.h"

void CameraController::Start()
{
	glm::mat4 position = glm::translate(glm::mat4(1.0f), cameraOffsetPosition);
	glm::mat4 rotation = glm::toMat4(glm::quat(glm::radians(cameraOffsetRotation)));

	cameraOffsetTransform = position * rotation;
}

void CameraController::Update(float p_deltaTime)
{
	if (!Application::IsApplicationPaused())
	{
		cameraRotationAngle += Input::GetMouseMovement().x * (cameraRotationSpeed * 2) / 100.0f;
	}

	/*glm::mat4 position = glm::translate(glm::mat4(1.0f), Scene::instance().GetPlayer()->GetTransform()->GetPosition());

	glm::mat4 newTransform = glm::rotate(position, glm::radians(cameraRotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));

	GetEntity()->GetTransform()->SetLocalTransform(newTransform * cameraOffsetTransform);*/
}

bool CameraController::s_isRegistered = ScriptFactory::instance().Register("CameraController", [](JsonObject& parameters) {
	auto script = std::make_shared<CameraController>();

	script->cameraRotationSpeed = GetParameterFromJsonObject(parameters, "CameraRotationSpeed", script->cameraRotationSpeed);

	return script;
});
