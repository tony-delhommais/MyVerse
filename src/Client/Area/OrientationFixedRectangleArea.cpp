//
// Created by Tony on 30/06/2022.
//

#include "Client/Area/OrientationFixedRectangleArea.h"

#include "Client/Area/CircleArea.h"

namespace Core
{

	OrientationFixedRectangleArea::OrientationFixedRectangleArea(const glm::vec3& p_position, float p_width, float p_height) : Area(p_position)
	{
		m_width = p_width;
		m_height = p_height;

		m_topLeftX = m_position.x - (p_width / 2.0f);
		m_topLeftY = m_position.z + (p_width / 2.0f);

		m_topRightX = m_position.x + (p_height / 2.0f);
		m_topRightY = m_position.z + (p_width / 2.0f);

		m_bottomLeftX = m_position.x - (p_width / 2.0f);
		m_bottomLeftY = m_position.z - (p_height / 2.0f);

		m_bottomRightX = m_position.x + (p_height / 2.0f);
		m_bottomRightY = m_position.z - (p_height / 2.0f);
	}

	bool OrientationFixedRectangleArea::IntersectWithEntity(std::shared_ptr<Entity> p_entity)
	{
		auto& entityPosition = p_entity->GetLocalPosition();

		return entityPosition.x >= m_topLeftX &&
			entityPosition.x <= m_bottomRightX &&
			entityPosition.z >= m_bottomRightY &&
			entityPosition.z <= m_topLeftY;
	}

	bool OrientationFixedRectangleArea::IntersectWithCircleArea(std::shared_ptr<CircleArea> p_circleArea)
	{
		float deltaX = p_circleArea->GetPosition().x - fmax(m_bottomLeftX, fmin(p_circleArea->GetPosition().x, m_topRightX));
		float deltaY = p_circleArea->GetPosition().z - fmax(m_bottomLeftY, fmin(p_circleArea->GetPosition().z, m_topRightY));

		return (deltaX * deltaX + deltaY * deltaY) < (p_circleArea->GetRadius() * p_circleArea->GetRadius());
	}

	bool OrientationFixedRectangleArea::IntersectWithOrientationFixedRectangleArea(std::shared_ptr<OrientationFixedRectangleArea> p_quadArea)
	{
		if (m_topLeftX == m_topLeftY || m_bottomRightX == m_bottomRightY || p_quadArea->m_topLeftX == p_quadArea->m_topLeftY || p_quadArea->m_bottomRightX == p_quadArea->m_bottomRightY)
			return false;

		if (m_topLeftX > p_quadArea->m_bottomRightX || p_quadArea->m_topLeftX > m_bottomRightX)
			return false;

		if (m_topLeftY > p_quadArea->m_bottomRightY || p_quadArea->m_topLeftY > m_bottomRightY)
			return false;

		return true;
	}

	float OrientationFixedRectangleArea::GetWidth()
	{
		return m_width;
	}

	float OrientationFixedRectangleArea::GetHeight()
	{
		return m_height;
	}

} // Core
