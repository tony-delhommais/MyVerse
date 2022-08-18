//
// Created by Tony on 17/08/2022.
//

#include "Client/GameScripts/Controllers/CameraController.h"

void CameraController::Update(float p_deltaTime)
{
	
}

bool CameraController::s_isRegistered = ScriptFactory::instance().Register("CameraController", [](JsonObject& parameters) {
	auto script = std::make_shared<CameraController>();

	return script;
	});
