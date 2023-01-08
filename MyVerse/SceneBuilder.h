//
// Created by Tony on 12/11/2022.
//

#ifndef MYVERSE_SCENE_BUILDER_H
#define MYVERSE_SCENE_BUILDER_H

#include "Scene.h"

namespace Client
{

	class SceneBuilder
	{
	public:
		SceneBuilder() = default;
		~SceneBuilder() = default;

	public:
		std::shared_ptr<Scene> Build();

		SceneBuilder& SetName(const std::string p_name);
		SceneBuilder& SetLocalEntities(std::list<std::shared_ptr<Entity>> p_localEntities);

	private:
		std::string m_name;

		std::list<std::shared_ptr<Entity>> m_localEntities;
	};

} // Client

#endif // MYVERSE_SCENE_BUILDER_H
