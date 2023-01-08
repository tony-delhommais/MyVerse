//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_COMPONENT_H
#define MYVERSE_COMPONENT_H

#include <memory>
#include <vector>

namespace Client
{

	enum ComponentType
	{
		TRANSFORM,
		CAMERA,
		MESH_RENDERER,
		SCRIPT
	};

	class Entity;

	class Component
	{
	public:
		Component(ComponentType p_componentType, std::shared_ptr<Entity> p_entity);
		virtual ~Component() = default;

	public:
		ComponentType GetComponentType();

		void SetEntity(std::shared_ptr<Entity> p_entity);
		std::shared_ptr<Entity> GetEntity();

	private:
		ComponentType m_componentType;

		std::shared_ptr<Entity> m_entity;
	};

} // Client

#endif // MYVERSE_COMPONENT_H
