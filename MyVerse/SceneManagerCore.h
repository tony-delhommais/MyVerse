//
// Created by Tony on 19/11/2022.
//

#ifndef MYVERSE_SCENE_MANAGER_CORE_H
#define MYVERSE_SCENE_MANAGER_CORE_H

#include "Utils.h"

#include "Scene.h"

namespace Client
{

	class SceneManagerCore
	{
	private:
		SceneManagerCore() = default;
		~SceneManagerCore() = default;

	public:
		static SceneManagerCore& instance();

	public:
		void AddScene(std::shared_ptr<Scene> p_scene);

	public:
		void SwitchToScene(int p_sceneId);

		std::shared_ptr<Scene> GetLoadedScene();

	private:
		std::list<std::shared_ptr<Scene>> m_scenes;

		std::shared_ptr<Scene> m_loadedScene = nullptr;
	};

} // Client

#endif // MYVERSE_SCENE_MANAGER_CORE_H
