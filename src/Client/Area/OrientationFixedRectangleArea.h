//
// Created by Tony on 30/06/2022.
//

#ifndef MYVERSE_ORIENTATION_FIXED_RECTANGLE_AREA_H
#define MYVERSE_ORIENTATION_FIXED_RECTANGLE_AREA_H

#include "Client/Area/Area.h"

namespace Client
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

		float m_topLeftX = 0.0f;
		float m_topLeftY = 0.0f;

		float m_topRightX = 0.0f;
		float m_topRightY = 0.0f;

		float m_bottomLeftX = 0.0f;
		float m_bottomLeftY = 0.0f;

		float m_bottomRightX = 0.0f;
		float m_bottomRightY = 0.0f;
	};

} // Client

#endif // MYVERSE_ORIENTATION_FIXED_RECTANGLE_AREA_H
