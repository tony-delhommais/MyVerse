//
// Created by Tony on 29/06/2022.
//

#include "Core/Ressource/Scene.h"

#include "Core/Entity/EntityQuadTree.h"

#include "Core/CoreClass/ApplicationCore.h"

#include "Core/Components/Camera.h"

#include "Core/Area/OrientationFixedRectangleArea.h"

#ifdef _DEBUG
#include "Core/Common/Debug.h"
#endif

namespace Core
{

	Scene::Scene()
	{
		m_renderCamera = std::make_shared<Camera>();
	}

	std::shared_ptr<Scene> Scene::Make(const std::filesystem::path& p_scenePath)
	{
		auto sceneJson = LoadJsonFile(p_scenePath);
		if (sceneJson.empty())
		{
#ifdef _DEBUG
			Debug::LogWarning("[SceneFactory] Unable to locate scene config file, trying at " + p_scenePath.string());
#endif
			return nullptr;
		}

		auto scene = std::make_shared<Scene>();

		auto sceneQuadTree = EntityQuadTree::Make(sceneJson);
		if (!sceneQuadTree)
		{
#ifdef _DEBUG
			Debug::LogWarning("[SceneFactory] Failed to parse EntityQuadTree settings on scene " + p_scenePath.string());
#endif
			return nullptr;
		}

		scene->m_entityQuadTree = sceneQuadTree;

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

				scene->AddLocalEntity(newLocalEntity);
			}
		}

		scene->BuildEntityQuadTree();

		std::shared_ptr<Camera> camera = nullptr;

		auto mainCameraEntity = scene->FindLocalEntityWithTag("MainCamera");
		if (mainCameraEntity) camera = mainCameraEntity->GetComponent<Camera>();

		if (!camera)
		{
#ifdef _DEBUG
			Debug::LogError("[SceneFactory] Failed to find the render Camera of the Player");
#endif
			return nullptr;
		}

		scene->m_renderCamera = camera;

		return scene;
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
		return m_entityQuadTree->FindEntityWithTag(p_tag);
	}

	std::vector<std::shared_ptr<Entity>> Scene::FindLocalEntitiesWithTag(const std::string& p_tag)
	{
		return m_entityQuadTree->FindEntitiesWithTag(p_tag);
	}

	void Scene::UpdateExecution(float p_deltaTime)
	{
		for(auto& entity : m_localEntities)
		{
			entity->UpdateExecution(p_deltaTime);
		}
	}

	void Scene::StopExecution()
	{
		for(auto& entity : m_localEntities)
		{
			entity->DestroyEntity();
		}
	}

	void Scene::RemoveDestroyedLocalEntities()
	{
		std::list<std::shared_ptr<Entity>> toRemove;

		for(auto& entity : m_localEntities)
		{
			if(entity->GetCurrentEntityExecutionState() == EntityExecutionState::PostDestroy)
			{
				toRemove.push_back(entity);
			}
		}

		for (auto& childToRemove : toRemove)
		{
			m_localEntities.remove(childToRemove);
		}
	}

	void Scene::Render()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		BuildEntityQuadTree();

		auto entitiesToRender = m_entityQuadTree->GetEntitiesOnCircleArea(m_renderCamera->GetDynamicEntityRenderingArea());

		glm::mat4 VueProjectionMatrix = m_renderCamera->GetViewProjectionMatrix();

		if (m_shaderVueProjectionMatrixUniformLocation == -1)
		{
			m_shaderVueProjectionMatrixUniformLocation = ApplicationCore::instance().GetActiveShader()->FindUniformLocation("VueProjectionMatrix");
		}

		ApplicationCore::instance().GetActiveShader()->SetUniformMat4(m_shaderVueProjectionMatrixUniformLocation, VueProjectionMatrix);

		for(auto& entity : entitiesToRender)
		{
			entity->Render();
		}
	}

	void Scene::BuildEntityQuadTree()
	{
		m_entityQuadTree->Clear();

		for (auto& entity : m_localEntities)
		{
			bool isAdded = m_entityQuadTree->AddEntity(entity);
#ifdef _DEBUG
			if (!isAdded)
				Debug::LogWarning("[Scene] a local Entity is out of QuadTree range");
#endif
		}
	}

	bool Scene::HasLocalEntities()
	{
		return !m_localEntities.empty();
	}

} // Core
