//
// Created by Tony on 29/06/2022.
//

#include "Script.h"

namespace Client
{

	Script::Script() :
		Component(ComponentType::SCRIPT, nullptr)
	{

	}

	void Script::Awake() {}

	void Script::OnEnable() {}

	void Script::Start() {}

	//void Script::FixedUpdate(float p_fixedDeltaTime) {}

	void Script::Update(float p_deltaTime) {}

	void Script::OnDisable() {}

	void Script::Destroy() {}

} // Client
