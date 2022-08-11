//
// Created by Tony on 30/06/2022.
//

#ifndef MYVERSE_ORIENTATION_FIXED_RECTANGLE_AREA_H
#define MYVERSE_ORIENTATION_FIXED_RECTANGLE_AREA_H

#include "Core/Area/Area.h"

namespace Core
{

	class CircleArea;

	class OrientationFixedRectangleArea : public Area
	{
	public:
		OrientationFixedRectangleArea() = default;
		OrientationFixedRectangleArea(const glm::vec3& p_position, float p_width, float p_height);
		~OrientationFixedRectangleArea() = default;

	public:
		bool IntersectWithEntity(std::shared_ptr<Entity> p_entity) override;
		bool IntersectWithCircleArea(std::shared_ptr<CircleArea> p_circleArea);
		bool IntersectWithOrientationFixedRectangleArea(std::shared_ptr<OrientationFixedRectangleArea> p_quadArea);

	public:
		float GetWidth();
		float GetHeight();

	private:
		float m_width = 1.0f;
		float m_height = 1.0f;

		float m_halfWidth = 0.5f;
		float m_halfHeight = 0.5f;
	};

} // Core

#endif // MYVERSE_ORIENTATION_FIXED_RECTANGLE_AREA_H
