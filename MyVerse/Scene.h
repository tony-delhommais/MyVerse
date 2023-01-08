//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_SCENE_H
#define MYVERSE_SCENE_H

#include "Utils.h"
#include "GraphicsUtils.h"

namespace Client
{

	class EntityQuadTree;
	class Entity;
	class Camera;
	class Player;

	class Scene
	{
	private:
		Scene() = default;
		virtual ~Scene() = default;

	public:
		static Scene& instance();

		void Initialize(const std::filesystem::path& p_scenePath, std::shared_ptr<Camera> p_camera, std::shared_ptr<Player> p_player);

	public:
		void AddLocalEntity(std::shared_ptr<Entity> p_entity);
		void RemoveLocalEntity(std::shared_ptr<Entity> p_entity);

		std::shared_ptr<Entity> FindLocalEntityWithTag(const std::string& p_tag);
		std::list<std::shared_ptr<Entity>> FindLocalEntitiesWithTag(const std::string& p_tag);

		void UpdateExecution(float p_deltaTime);
		void StopExecution();

		void Render();

	public:
		bool IsStopped();

		std::shared_ptr<Camera> GetCamera();

		std::shared_ptr<Player> GetPlayer();

		bool HasLocalEntities();

	private:
		std::shared_ptr<Camera> m_camera = nullptr;

		std::shared_ptr<Player> m_player = nullptr;

		std::list<std::shared_ptr<Entity>> m_localEntities;
	};

} // Client

#endif // MYVERSE_SCENE_H
