//
// Created by Tony on 29/06/2022.
//

#include "Client/Components/Component.h"

namespace Core
{

	void Component::SetEntity(std::shared_ptr<Entity> p_entity)
	{
		m_entity = p_entity;
	}

	std::shared_ptr<Entity> Component::GetEntity()
	{
		return m_entity;
	}

} // Core
