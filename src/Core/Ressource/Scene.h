//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_SCENE_H
#define MYVERSE_SCENE_H

#include "Core/Utils/Utils.h"
#include "Core/Utils/GraphicsUtils.h"

namespace Core
{

	class EntityQuadTree;
	class Entity;
	class Camera;

	class Scene
	{
	public:
		Scene();
		virtual ~Scene() = default;

		static std::shared_ptr<Scene> Make(const std::filesystem::path& p_scenePath);

	public:
		void AddLocalEntity(std::shared_ptr<Entity> p_entity);
		void RemoveLocalEntity(std::shared_ptr<Entity> p_entity);

		std::shared_ptr<Entity> FindLocalEntityWithTag(const std::string& p_tag);
		std::vector<std::shared_ptr<Entity>> FindLocalEntitiesWithTag(const std::string& p_tag);

		void UpdateExecution(float p_deltaTime);
		void StopExecution();

		void RemoveDestroyedLocalEntities();

		void Render();

	private:
		void BuildEntityQuadTree();

	public:
		bool HasLocalEntities();

	private:
		GLint m_shaderVueProjectionMatrixUniformLocation = -1;

		std::shared_ptr<EntityQuadTree> m_entityQuadTree = nullptr;

		std::list<std::shared_ptr<Entity>> m_localEntities;

		std::shared_ptr<Entity> m_player = nullptr;

		std::shared_ptr<Camera> m_renderCamera = nullptr;
	};

} // Core

#endif // MYVERSE_SCENE_H
