//
// Created by Tony on 19/11/2022.
//

#include "SceneManagerCore.h"

namespace Client
{

	SceneManagerCore& SceneManagerCore::instance()
	{
		static SceneManagerCore instance;

		return instance;
	}

	void SceneManagerCore::AddScene(std::shared_ptr<Scene> p_scene)
	{
		m_scenes.push_back(p_scene);
	}

	void SceneManagerCore::SwitchToScene(int p_sceneId)
	{

	}

	std::shared_ptr<Scene> SceneManagerCore::GetLoadedScene()
	{
		return m_loadedScene;
	}

} // Client
