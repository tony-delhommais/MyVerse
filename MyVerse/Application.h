//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_APPLICATION_H
#define MYVERSE_APPLICATION_H

#include "Utils.h"
#include "JsonUtils.h"

#include "Clock.h"
#include "Input.h"

#include "Entity.h"

#include "Scene.h"

#include "ScriptFactory.h"

#include "Debug.h"

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
