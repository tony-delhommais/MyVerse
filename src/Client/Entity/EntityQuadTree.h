//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_ENTITY_QUAD_TREE_H
#define MYVERSE_ENTITY_QUAD_TREE_H

#include "Client/Utils/Utils.h"
#include "Client/Utils/MathUtils.h"

#include "Client/Entity/Entity.h"

#include "Client/Area/CircleArea.h"
#include "Client/Area/OrientationFixedRectangleArea.h"

namespace Core
{

	class EntityQuadTree
	{
	public:
		EntityQuadTree(std::shared_ptr<OrientationFixedRectangleArea> p_area, int p_maxDepth, int p_maxEntity);
		~EntityQuadTree() = default;

		static std::shared_ptr<EntityQuadTree> Make(JsonObject& psceneData);

	public:
		bool AddEntity(const std::shared_ptr<Entity>& p_newEntity);
		void Clear();

		int GetEntitiesCount();
		std::vector<std::shared_ptr<Entity>> GetEntitiesOnCircleArea(std::shared_ptr<CircleArea> p_circleArea);

		std::shared_ptr<Entity> FindEntityWithTag(const std::string& p_tag);
		std::vector<std::shared_ptr<Entity>> FindEntitiesWithTag(const std::string& p_tag);

	private:
		void SubDivide();

		void AddEntityToCardinal(std::shared_ptr<Entity> p_entity);

	private:
		std::shared_ptr<OrientationFixedRectangleArea> m_area = nullptr;

		int m_maxDepth = 0;
		int m_maxEntity = 50;

		std::list<std::shared_ptr<Entity>> m_entities;

		bool m_isSubdivided = false;

		std::unique_ptr<EntityQuadTree> m_cardinalPoints[4] = {
				nullptr,
				nullptr,
				nullptr,
				nullptr
		};
	};

} // Core

#endif // MYVERSE_ENTITY_QUAD_TREE_H
