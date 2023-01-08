//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_SCENE_H
#define MYVERSE_SCENE_H

#include "Utils.h"
#include "GraphicsUtils.h"

namespace Client
{

	class Entity;
	class Camera;

	class Scene
	{
	public:
		Scene(std::string p_name, std::list<std::shared_ptr<Entity>> p_localEntities);
		virtual ~Scene() = default;

	public:
		void AddLocalEntity(std::shared_ptr<Entity> p_entity);
		void RemoveLocalEntity(std::shared_ptr<Entity> p_entity);

		std::shared_ptr<Entity> FindLocalEntityWithTag(const std::string& p_tag);
		std::list<std::shared_ptr<Entity>> FindLocalEntitiesWithTag(const std::string& p_tag);

		void UpdateExecution(float p_deltaTime);
		void StopExecution();

		void Render();

	public:
		std::string GetName();

	public:
		bool IsStopped();

		bool HasLocalEntities();

		bool HasRenderCamera();

	private:
		std::list<std::shared_ptr<Camera>> FindAllCameras();

	private:
		std::string m_name;

		std::list<std::shared_ptr<Entity>> m_localEntities;

		std::shared_ptr<Camera> m_renderCamera;
	};

} // Client

#endif // MYVERSE_SCENE_H
