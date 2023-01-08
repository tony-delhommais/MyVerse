//
// Created by Tony on 19/11/2022.
//

#include "SceneManager.h"

#include "SceneManagerCore.h"

namespace Client
{

	void SceneManager::SwitchToScene(int p_sceneId)
	{
		SceneManagerCore::instance().SwitchToScene(p_sceneId);
	}

	std::shared_ptr<Scene> SceneManager::GetLoadedScene()
	{
		return SceneManagerCore::instance().GetLoadedScene();
	}

} // Client
