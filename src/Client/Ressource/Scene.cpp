//
// Created by Tony on 29/06/2022.
//

#include "Client/Ressource/Scene.h"

#include "Client/Core/ApplicationCore.h"

#include "Client/Entity/Entity.h"

#ifdef _DEBUG
#include "Client/Common/Debug.h"
#endif

namespace Client
{

	Scene::Scene(std::string p_name, std::list<std::shared_ptr<Entity>> p_localEntities) :
		m_name(p_name),
		m_localEntities(p_localEntities)
	{
		std::list<std::shared_ptr<Camera>> cameras = FindAllCameras();

		if (!cameras.empty())
		{
			m_renderCamera = cameras.front();
			//todo improve with main camera
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
	}

	void Scene::StopExecution()
	{
		for(auto& entity : m_localEntities)
		{
			entity->DestroyEntity();
		}
	}

	void Scene::Render()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = m_renderCamera->GetProjectionMatrix();
		glm::mat4 view = m_renderCamera->GetViewMatrix();
		glm::mat4 viewProjection = projection * view;

		ApplicationCore::instance().GetActiveShader()->SetMatrixUniform(EnumMatrix::VIEW_MATRIX, view);
		ApplicationCore::instance().GetActiveShader()->SetMatrixUniform(EnumMatrix::PROJECTION_MATRIX, projection);
		ApplicationCore::instance().GetActiveShader()->SetMatrixUniform(EnumMatrix::VIEWPROJECTION_MATRIX, viewProjection);

		for(auto& entity : m_localEntities)
		{
			entity->Render(viewProjection);
		}
	}

	std::string Scene::GetName()
	{
		return m_name;
	}

	bool Scene::IsStopped()
	{
		for (auto& entity : m_localEntities)
		{
			if (entity->GetCurrentEntityExecutionState() != EntityExecutionState::PostDestroy) return false;
		}

		return true;
	}

	bool Scene::HasLocalEntities()
	{
		return !m_localEntities.empty();
	}

	bool Scene::HasRenderCamera()
	{
		return m_renderCamera != nullptr;
	}

	std::list<std::shared_ptr<Camera>> Scene::FindAllCameras()
	{
		return std::list<std::shared_ptr<Camera>>(); //todo
	}

} // Client
