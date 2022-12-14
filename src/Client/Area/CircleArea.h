//
// Created by Tony on 30/06/2022.
//

#ifndef MYVERSE_CIRCLEAREA_H
#define MYVERSE_CIRCLEAREA_H

#include "Client/Area/Area.h"

namespace Client
{

	class OrientationFixedRectangleArea;

	class CircleArea : public Area
	{
	public:
		CircleArea() = default;
		CircleArea(const glm::vec3& p_position, float p_radius);
		~CircleArea() = default;

	public:
		bool IntersectWithEntity(std::shared_ptr<Entity> p_entity) override;
		bool IntersectWithCircleArea(std::shared_ptr<CircleArea> p_circleArea);
		bool IntersectWithOrientationFixedRectangleArea(std::shared_ptr<OrientationFixedRectangleArea> p_quadArea);

	public:
		float GetRadius();

	private:
		float m_radius = 1.0f;
	};

} // Client

#endif // MYVERSE_CIRCLEAREA_H
