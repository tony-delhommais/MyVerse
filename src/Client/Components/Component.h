//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_COMPONENT_H
#define MYVERSE_COMPONENT_H

#include <memory>
#include <vector>

namespace Client
{

	class Entity;

	class Component
	{
	public:
		Component() = default;
		virtual ~Component() = default;

	public:
		void SetEntity(std::shared_ptr<Entity> p_entity);
		std::shared_ptr<Entity> GetEntity();

	private:
		std::shared_ptr<Entity> m_entity = nullptr;
	};

} // Client

#endif // MYVERSE_COMPONENT_H
