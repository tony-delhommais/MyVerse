//
// Created by Tony on 19/11/2022.
//

#ifndef MYVERSE_SCENE_MANAGER_H
#define MYVERSE_SCENE_MANAGER_H

#include "Client/Ressources/Scene/Scene.h"

namespace Client
{

	class SceneManager
	{
	private:
		SceneManager() = default;
		~SceneManager() = default;

	public:
		static void SwitchToScene(int p_sceneId);

		static std::shared_ptr<Scene> GetLoadedScene();
	};

} // Client

#endif // MYVERSE_SCENE_MANAGER_H
