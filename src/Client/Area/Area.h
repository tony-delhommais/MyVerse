//
// Created by Tony on 30/06/2022.
//

#ifndef MYVERSE_AREA_H
#define MYVERSE_AREA_H

#include "Client/Utils/MathUtils.h"

#include "Client/Entity/Entity.h"

namespace Client
{

	class CircleArea;
	class QuadArea;

	class Area : public std::enable_shared_from_this<Area>
	{
	public:
		Area() = default;
		Area(const glm::vec3& p_position);
		~Area() = default;

	public:
		virtual bool IntersectWithEntity(std::shared_ptr<Entity> p_entity) = 0;

	public:
		const glm::vec3& GetPosition();

	protected:
		glm::vec3 m_position;
	};

} // Client

#endif // MYVERSE_AREA_H
