//
// Created by Tony on 29/06/2022.
//

#include "Client/Entity/EntityQuadTree.h"

namespace Core
{

	EntityQuadTree::EntityQuadTree(std::shared_ptr<OrientationFixedRectangleArea> p_area, int p_maxDepth, int p_maxEntity)
	{
		m_area = p_area;

		m_maxDepth = p_maxDepth;
		m_maxEntity = p_maxEntity;

		if (m_maxDepth != 0)
		{
			auto NWArea = std::make_shared<OrientationFixedRectangleArea>(glm::vec3(m_area->GetPosition().x - m_area->GetWidth() / 4, 0.0, m_area->GetPosition().z + m_area->GetHeight() / 4), m_area->GetWidth() / 2, m_area->GetHeight() / 2);
			m_cardinalPoints[0] = std::make_unique<EntityQuadTree>(NWArea, m_maxDepth - 1, m_maxEntity);

			auto NEArea = std::make_shared<OrientationFixedRectangleArea>(glm::vec3(m_area->GetPosition().x + m_area->GetWidth() / 4, 0.0, m_area->GetPosition().z + m_area->GetHeight() / 4), m_area->GetWidth() / 2, m_area->GetHeight() / 2);
			m_cardinalPoints[1] = std::make_unique<EntityQuadTree>(NEArea, m_maxDepth - 1, m_maxEntity);

			auto SWArea = std::make_shared<OrientationFixedRectangleArea>(glm::vec3(m_area->GetPosition().x - m_area->GetWidth() / 4, 0.0, m_area->GetPosition().z - m_area->GetHeight() / 4), m_area->GetWidth() / 2, m_area->GetHeight() / 2);
			m_cardinalPoints[2] = std::make_unique<EntityQuadTree>(SWArea, m_maxDepth - 1, m_maxEntity);

			auto SEArea = std::make_shared<OrientationFixedRectangleArea>(glm::vec3(m_area->GetPosition().x + m_area->GetWidth() / 4, 0.0, m_area->GetPosition().z - m_area->GetHeight() / 4), m_area->GetWidth() / 2, m_area->GetHeight() / 2);
			m_cardinalPoints[3] = std::make_unique<EntityQuadTree>(SEArea, m_maxDepth - 1, m_maxEntity);
		}
	}

	std::shared_ptr<EntityQuadTree> EntityQuadTree::Make(JsonObject& psceneData)
	{
		auto quadTreeSettings = GetParameterFromJsonObject(psceneData, "QuadTreeSettings", false, true);
		if (quadTreeSettings == psceneData) return nullptr;

		auto quadTreeAreaSettings = GetParameterFromJsonObject(quadTreeSettings, "Area", false, true);
		if (quadTreeAreaSettings == quadTreeSettings) return nullptr;

		auto quadTreeAreaLocationData = GetParameterFromJsonObject(quadTreeAreaSettings, "Location", true, false);
		if (quadTreeAreaLocationData == quadTreeAreaSettings || quadTreeAreaLocationData.size() != 3 || !quadTreeAreaLocationData[0].is_number_float()) return nullptr;

		glm::vec3 quadTreeAreaLocation = { quadTreeAreaLocationData[0] , quadTreeAreaLocationData[1] , quadTreeAreaLocationData[2] };
		auto quadTreeAreaWidth = GetParameterFromJsonObject(quadTreeAreaSettings, "Width", 50.0f);
		auto quadTreeAreaHeight = GetParameterFromJsonObject(quadTreeAreaSettings, "Height", 50.0f);

		auto quadTreeArea = std::make_shared<OrientationFixedRectangleArea>(quadTreeAreaLocation, quadTreeAreaWidth, quadTreeAreaHeight);
		auto quadTreeMaxDepth = GetParameterFromJsonObject(quadTreeSettings, "MaxDepth", 0);
		auto quadTreeMaxEntity = GetParameterFromJsonObject(quadTreeSettings, "MaxEntity", 100);

		return std::make_shared<EntityQuadTree>(quadTreeArea, quadTreeMaxDepth, quadTreeMaxEntity);
	}

	bool EntityQuadTree::AddEntity(const std::shared_ptr<Entity>& p_newEntity)
	{
		if(m_area->IntersectWithEntity(p_newEntity))
		{
			if (!m_isSubdivided)
			{
				m_entities.push_back(p_newEntity);

				if (m_maxDepth > 0 && m_entities.size() > m_maxEntity)
				{
					SubDivide();
				}
			}
			else
			{
				AddEntityToCardinal(p_newEntity);
			}

			return true;
		}

		return false;
	}

	void EntityQuadTree::Clear()
	{
		m_entities.clear();

		m_isSubdivided = false;

		if (m_maxDepth != 0) for(auto& m_cardinalPoint : m_cardinalPoints) m_cardinalPoint->Clear();
	}

	int EntityQuadTree::GetEntitiesCount()
	{
		int entitiesCount = (int)(m_entities.size());

		if(m_isSubdivided)
		{
			for(auto& m_cardinalPoint : m_cardinalPoints) entitiesCount += m_cardinalPoint->GetEntitiesCount();
		}

		return entitiesCount;
	}

	std::vector<std::shared_ptr<Entity>> EntityQuadTree::GetEntitiesOnCircleArea(std::shared_ptr<CircleArea> p_circleArea)
	{
		std::vector<std::shared_ptr<Entity>> entitiesOnArea;

		if(!m_area->IntersectWithCircleArea(p_circleArea))
			return entitiesOnArea;

		if(!m_isSubdivided)
		{
			for(auto& entity : m_entities)
			{
				if(p_circleArea->IntersectWithEntity(entity))
					entitiesOnArea.push_back(entity);
			}
		}
		else
		{
			for(auto& m_cardinalPoint : m_cardinalPoints)
			{
				auto newEntitiesOnArea = m_cardinalPoint->GetEntitiesOnCircleArea(p_circleArea);

				entitiesOnArea.insert(entitiesOnArea.end(), newEntitiesOnArea.begin(), newEntitiesOnArea.end());
			}
		}

		return entitiesOnArea;
	}

	std::shared_ptr<Entity> EntityQuadTree::FindEntityWithTag(const std::string& p_tag)
	{
		if(m_isSubdivided)
		{
			for(auto& m_cardinalPoint : m_cardinalPoints)
			{
				auto entity = m_cardinalPoint->FindEntityWithTag(p_tag);
				if(entity)
					return entity;
			}
		}
		else
		{
			for(auto& entity : m_entities)
			{
				auto foundEntity = entity->FindChildWithTag(p_tag);
				if(foundEntity)
					return foundEntity;
			}
		}

		return nullptr;
	}

	std::vector<std::shared_ptr<Entity>> EntityQuadTree::FindEntitiesWithTag(const std::string& p_tag)
	{
		std::vector<std::shared_ptr<Entity>> returnVector;

		if(m_isSubdivided)
		{
			for(auto& m_cardinalPoint : m_cardinalPoints)
			{
				auto entities = m_cardinalPoint->FindEntitiesWithTag(p_tag);
				
				returnVector.insert(returnVector.end(), entities.begin(), entities.end());
			}
		}
		else
		{
			for (auto& entity : m_entities)
			{
				auto entities = entity->FindChildsWithTag(p_tag);
				
				returnVector.insert(returnVector.end(), entities.begin(), entities.end());
			}
		}

		return returnVector;
	}

	void EntityQuadTree::SubDivide()
	{
		for (auto& entity : m_entities)
		{
			AddEntityToCardinal(entity);
		}

		m_entities.clear();

		m_isSubdivided = true;
	}

	void EntityQuadTree::AddEntityToCardinal(std::shared_ptr<Entity> p_entity)
	{
		auto& entityLocalPosition = p_entity->GetLocalPosition();
		auto& areaPosition = m_area->GetPosition();

		bool entityIsOnNorth = entityLocalPosition.z > areaPosition.z;
		bool entityIsOnWest = entityLocalPosition.x < areaPosition.x;

		if (entityIsOnWest && entityIsOnNorth)
			m_cardinalPoints[0]->AddEntity(p_entity);

		if (!entityIsOnWest && entityIsOnNorth)
			m_cardinalPoints[1]->AddEntity(p_entity);

		if (entityIsOnWest && !entityIsOnNorth)
			m_cardinalPoints[2]->AddEntity(p_entity);

		if (!entityIsOnWest && !entityIsOnNorth)
			m_cardinalPoints[3]->AddEntity(p_entity);
	}

} // Core
