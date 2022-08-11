//
// Created by Tony on 30/06/2022.
//

#include "Core/Area/Area.h"

namespace Core
{

	Area::Area(const glm::vec3& p_position)
	{
		m_position = p_position * glm::vec3(1.0, 0.0, 1.0);
	}

	const glm::vec3& Area::GetPosition()
	{
		return m_position;
	}

} // Core
