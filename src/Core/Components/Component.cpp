//
// Created by Tony on 29/06/2022.
//

#include "Core/Components/Component.h"

namespace Core
{

	Component::Component(std::shared_ptr<Component> p_component)
	{
		m_entity = p_component->m_entity;
	}

	void Component::SetEntity(std::shared_ptr<Entity> p_entity)
	{
		m_entity = p_entity;
	}

	std::shared_ptr<Entity> Component::GetEntity()
	{
		return m_entity;
	}

} // Core