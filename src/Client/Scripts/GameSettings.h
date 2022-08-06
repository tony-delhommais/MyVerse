//
// Created by Tony on 06/08/2022.
//

#ifndef MYVERSE_GAME_SETTINGS_H
#define MYVERSE_GAME_SETTINGS_H

#include "Core/Application.h"

using namespace Core;

class GameSettings : public Script
{
public:
	GameSettings() = default;
	~GameSettings() override = default;

	void Start() override;
	void Update(float p_deltaTime) override;

private:
	static bool s_isRegistered;
};

#endif // MYVERSE_GAME_SETTINGS_H
