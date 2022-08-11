//
// Created by Tony on 30/06/2022.
//

#include "Core/Area/OrientationFixedRectangleArea.h"

#include "Core/Area/CircleArea.h"

namespace Core
{

	OrientationFixedRectangleArea::OrientationFixedRectangleArea(const glm::vec3& p_position, float p_width, float p_height) : Area(p_position)
	{
		m_width = p_width;
		m_height = p_height;

		m_halfWidth = p_width / 2.0f;
		m_halfHeight = p_height / 2.0f;
	}

	bool OrientationFixedRectangleArea::IntersectWithEntity(std::shared_ptr<Entity> p_entity)
	{
		auto entityPosition = p_entity->GetLocalPosition();

		return entityPosition.x >= m_position.x - m_halfWidth &&
			entityPosition.x <= m_position.x + m_halfWidth &&
			entityPosition.z >= m_position.z - m_halfHeight &&
			entityPosition.z <= m_position.z + m_halfHeight;
	}

	bool OrientationFixedRectangleArea::IntersectWithCircleArea(std::shared_ptr<CircleArea> p_circleArea)
	{
		float bottomLeftX = m_position.x - m_halfWidth;
		float bottomLeftY = m_position.z - m_halfHeight;

		float deltaX = p_circleArea->GetPosition().x - fmax(bottomLeftX, fmin(p_circleArea->GetPosition().x, bottomLeftX + m_width));
		float deltaY = p_circleArea->GetPosition().z - fmax(bottomLeftY, fmin(p_circleArea->GetPosition().z, bottomLeftY + m_height));

		return (deltaX * deltaX + deltaY * deltaY) < (p_circleArea->GetRadius() * p_circleArea->GetRadius());
	}

	bool OrientationFixedRectangleArea::IntersectWithOrientationFixedRectangleArea(std::shared_ptr<OrientationFixedRectangleArea> p_quadArea)
	{
		float thisTopLeftX = m_position.x - m_halfWidth;
		float thisTopLeftY = m_position.z + m_halfWidth;
		float thisBottomRightX = m_position.x + m_halfHeight;
		float thisBottomRightY = m_position.z - m_halfHeight;

		float otherTopLeftX = p_quadArea->m_position.x - p_quadArea->m_halfWidth;
		float otherTopLeftY = p_quadArea->m_position.z + p_quadArea->m_halfHeight;
		float otherBottomRightX = p_quadArea->m_position.x + p_quadArea->m_halfWidth;
		float otherBottomRightY = p_quadArea->m_position.z - p_quadArea->m_halfHeight;

		if(thisTopLeftX == thisTopLeftY || thisBottomRightX == thisBottomRightY || otherTopLeftX == otherTopLeftY || otherBottomRightX == otherBottomRightY)
			return false;

		if(thisTopLeftX > otherBottomRightX || otherTopLeftX > thisBottomRightX)
			return false;

		if(thisTopLeftY > otherBottomRightY || otherTopLeftY > thisBottomRightY)
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
