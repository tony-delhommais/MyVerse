//
// Created by Tony on 29/06/2022.
//

#include "Component.h"

namespace Client
{

	Component::Component(ComponentType p_componentType, std::shared_ptr<Entity> p_entity) :
		m_componentType(p_componentType),
		m_entity(p_entity)
	{

	}

	ComponentType Component::GetComponentType()
	{
		return m_componentType;
	}

	void Component::SetEntity(std::shared_ptr<Entity> p_entity)
	{
		m_entity = p_entity;
	}

	std::shared_ptr<Entity> Component::GetEntity()
	{
		return m_entity;
	}

} // Client
