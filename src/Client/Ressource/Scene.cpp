//
// Created by Tony on 29/06/2022.
//

#include "Client/Ressource/Scene.h"

#include "Client/Entity/EntityQuadTree.h"
#include "Client/Entity/Camera.h"
#include "Client/Entity/Player.h"

#include "Client/Area/OrientationFixedRectangleArea.h"

#ifdef _DEBUG
#include "Client/Common/Debug.h"
#endif

namespace Client
{

	Scene& Scene::instance()
	{
		static Scene instance;
		return instance;
	}

	void Scene::Initialize(const std::filesystem::path& p_scenePath, std::shared_ptr<Camera> p_camera, std::shared_ptr<Player> p_player)
	{
		m_camera = p_camera;
		m_player = p_player;

		auto sceneJson = LoadJsonFile(p_scenePath);
		if (sceneJson.empty())
		{
#ifdef _DEBUG
			Debug::LogWarning("[SceneFactory] Unable to locate scene config file, trying at " + p_scenePath.string());
#endif
			return;
		}

		auto localEntitiesArray = GetParameterFromJsonObject(sceneJson, "LocalEntities", true, false);
		if (localEntitiesArray != sceneJson)
		{
			for (auto& localEntityData : localEntitiesArray)
			{
				auto newLocalEntity = Entity::Make(localEntityData);

				if (!newLocalEntity)
				{
#ifdef _DEBUG
					Debug::LogWarning("[SceneFactory] Failed to parse a local Entity");
#endif
					continue;
				}

				AddLocalEntity(newLocalEntity);
			}
		}
	}

	void Scene::AddLocalEntity(std::shared_ptr<Entity> p_entity)
	{
		m_localEntities.push_back(p_entity);
	}

	void Scene::RemoveLocalEntity(std::shared_ptr<Entity> p_entity)
	{
		m_localEntities.erase(std::remove(m_localEntities.begin(), m_localEntities.end(), p_entity), m_localEntities.end());
	}

	std::shared_ptr<Entity> Scene::FindLocalEntityWithTag(const std::string& p_tag)
	{
		for (auto& entity : m_localEntities)
		{
			auto foundEntity = entity->FindChildWithTag(p_tag);
			if (foundEntity)
				return foundEntity;
		}

		return nullptr;
	}

	std::list<std::shared_ptr<Entity>> Scene::FindLocalEntitiesWithTag(const std::string& p_tag)
	{
		std::list<std::shared_ptr<Entity>> returnList;

		for (auto& entity : m_localEntities)
		{
			auto entities = entity->FindChildsWithTag(p_tag);

			returnList.insert(returnList.end(), entities.begin(), entities.end());
		}

		return returnList;
	}

	void Scene::UpdateExecution(float p_deltaTime)
	{
		m_player->UpdateExecution(p_deltaTime);

		std::list<std::shared_ptr<Entity>>::iterator it = m_localEntities.begin();
		while (it != m_localEntities.end())
		{
			std::list<std::shared_ptr<Entity>>::iterator entity = it;

			entity->get()->UpdateExecution(p_deltaTime);

			it++;

			if (entity->get()->GetCurrentEntityExecutionState() == EntityExecutionState::PostDestroy)
			{
				m_localEntities.erase(entity);
			}
		}

		m_camera->UpdateExecution(p_deltaTime);
	}

	void Scene::StopExecution()
	{
		m_player->DestroyEntity();

		for(auto& entity : m_localEntities)
		{
			entity->DestroyEntity();
		}

		m_camera->DestroyEntity();
	}

	void Scene::Render()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_camera->UseCameraForRendering();

		m_player->Render();

		for(auto& entity : m_localEntities)
		{
			entity->Render();
		}
	}

	bool Scene::IsStopped()
	{
		if (m_camera->GetCurrentEntityExecutionState() != EntityExecutionState::PostDestroy) return false;

		if (m_player->GetCurrentEntityExecutionState() != EntityExecutionState::PostDestroy) return false;

		for (auto& entity : m_localEntities)
		{
			if (entity->GetCurrentEntityExecutionState() != EntityExecutionState::PostDestroy) return false;
		}

		return true;
	}

	std::shared_ptr<Camera> Scene::GetCamera()
	{
		return m_camera;
	}

	std::shared_ptr<Player> Scene::GetPlayer()
	{
		return m_player;
	}

	bool Scene::HasLocalEntities()
	{
		return !m_localEntities.empty();
	}

} // Client
