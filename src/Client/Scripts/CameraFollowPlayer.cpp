//
// Created by Tony on 29/06/2022.
//

#include "Client/Scripts/CameraFollowPlayer.h"

void CameraFollowPlayer::Start()
{
	followingOffset = glm::vec3(0.0f, 1.5f, -2.5f);

	FindPlayerEntity();
}

void CameraFollowPlayer::Update(float p_deltaTime)
{
	UpdateCameraPosition(p_deltaTime);
}

void CameraFollowPlayer::FindPlayerEntity()
{
	//if (Application::instance().GetActiveScene()->FindEntityWithTag("Player"))
	//	playerRef = Application::instance().GetActiveScene()->FindEntityWithTag("Player");

	if (!playerRef)
		Debug::LogInfo("Can't find a Player");
}

void CameraFollowPlayer::UpdateCameraPosition(float p_deltaTime)
{
	if (playerRef)
	{
		if (prev_x_axis != Input::GetAxis("Right"))
		{
			prev_x_axis = Input::GetAxis("Right");
			x_axis_update = 0.0f;
		}
		x_axis_update += p_deltaTime * cameraAcceleration;
		followingDelay.x = Lerp(followingDelay.x, Input::GetAxis("Right") * -1.0f * maxCameraDelay, x_axis_update);

		if (prev_y_axis != Input::GetAxis("Forward"))
		{
			prev_y_axis = Input::GetAxis("Forward");
			y_axis_update = 0.0f;
		}
		y_axis_update += p_deltaTime * cameraAcceleration;
		followingDelay.z = Lerp(followingDelay.z, Input::GetAxis("Forward") * -1.0f * maxCameraDelay, y_axis_update);


		glm::vec3 targetPos = playerRef->GetWorldPosition() + followingOffset;

		GetEntity()->SetLocalPosition(targetPos + followingDelay);
	}
}

bool CameraFollowPlayer::s_isRegistered = ScriptFactory::instance().Register("CameraFollowPlayer", [](JsonObject& parameters)
	{
		auto script = std::make_shared<CameraFollowPlayer>();

		script->cameraAcceleration = GetParameterFromJsonObject(parameters, "CameraAcceleration", script->cameraAcceleration);
		script->maxCameraDelay = GetParameterFromJsonObject(parameters, "MaxCameraDelay", script->maxCameraDelay);

		return script;
	});
