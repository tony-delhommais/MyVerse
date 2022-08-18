//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_APPLICATION_H
#define MYVERSE_APPLICATION_H

#include "Client/Utils/Utils.h"
#include "Client/Utils/JsonUtils.h"

#include "Client/Common/Clock.h"
#include "Client/Common/Input.h"

#include "Client/Entity/Entity.h"

#include "Client/Ressource/Scene.h"

#include "Client/Factories/ScriptFactory.h"

#include "Client/Common/Debug.h"

namespace Client
{

	class Application
	{
	private:
		Application() = default;
		~Application() = default;

	public:
		static void Quit();

	public:
		long long GetFrameCount();

		static bool IsApplicationPaused();
		static void SetApplicationPause(bool p_pauseState);
	};

} // Client

#endif // MYVERSE_APPLICATION_H
