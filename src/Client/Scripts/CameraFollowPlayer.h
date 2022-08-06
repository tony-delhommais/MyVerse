//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_CAMERA_FOLLOW_PLAYER_H
#define MYVERSE_CAMERA_FOLLOW_PLAYER_H

#include "Core/Application.h"

using namespace Core;

class CameraFollowPlayer : public Script
{
public:
	void Start() override;
	void Update(float p_deltaTime) override;

	void FindPlayerEntity();

private:
	void UpdateCameraPosition(float p_deltaTime);

private:
	static bool s_isRegistered;

	std::shared_ptr<Entity> playerRef;

	glm::vec3 followingOffset;
	glm::vec3 followingDelay = glm::vec3(0.0f);

	float cameraAcceleration = 0.6f;
	float maxCameraDelay = 0.07f;

	float prev_x_axis = 0.0f;
	float x_axis_update = 0.0f;

	float prev_y_axis = 0.0f;
	float y_axis_update = 0.0f;
};

#endif // MYVERSE_CAMERA_FOLLOW_PLAYER_H
