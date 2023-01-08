//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_SPAWN_TEST_H
#define MYVERSE_SPAWN_TEST_H

#include "Application.h"

using namespace Client;

class SpawnTest : public Script
{
public:
	void Start() override;

private:
	static bool s_isRegistered;

	std::string testPrefabUuid = "Null";

	int x = 5;
	int y = 5;
};

#endif // MYVERSE_SPAWN_TEST_H
