//
// Created by Tony on 30/06/2022.
//

#include "CircleArea.h"

#include "OrientationFixedRectangleArea.h"

namespace Client
{

	CircleArea::CircleArea(const glm::vec3& p_position, float p_radius) : Area(p_position)
	{
		m_radius = p_radius;
	}

	bool CircleArea::IntersectWithEntity(std::shared_ptr<Entity> p_entity)
	{
		return glm::distance(m_position, (p_entity->GetModelPosition() * glm::vec3(1.0, 0.0, 1.0))) <= m_radius;
		return false;
	}

	bool CircleArea::IntersectWithCircleArea(std::shared_ptr<CircleArea> p_circleArea)
	{
		return glm::distance(m_position, p_circleArea->m_position) <= m_radius + p_circleArea->m_radius;
	}

	bool CircleArea::IntersectWithOrientationFixedRectangleArea(std::shared_ptr<OrientationFixedRectangleArea> p_quadArea)
	{
		return p_quadArea->IntersectWithCircleArea(std::static_pointer_cast<CircleArea>(shared_from_this()));
	}

	float CircleArea::GetRadius()
	{
		return m_radius;
	}

} // Client
