//
// Created by Tony on 17/08/2022.
//

#ifndef MYVERSE_CAMERA_CONTROLLER_H
#define MYVERSE_CAMERA_CONTROLLER_H

#include "Client/Common/Application.h"

using namespace Client;

class CameraController : public Script
{
public:
	CameraController() = default;
	~CameraController() override = default;

	void Update(float p_deltaTime) override;

private:
	static bool s_isRegistered;
};

#endif // MYVERSE_CAMERA_CONTROLLER_H
