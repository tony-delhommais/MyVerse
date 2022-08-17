//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_SCRIPT_H
#define MYVERSE_SCRIPT_H

#include "Client/Components/Component.h"

#include "Client/Utils/JsonUtils.h"

namespace Client
{
	
	class Script : public Component
	{
	public:
		Script() = default;
		virtual ~Script() = default;

		virtual void Awake();
		virtual void OnEnable();
		virtual void Start();
		//virtual void FixedUpdate(float p_fixedDeltaTime);
		virtual void Update(float p_deltaTime);
		virtual void OnDisable();
		virtual void Destroy();
	};

} // Client

#endif // MYVERSE_SCRIPT_H
