//
// Created by Tony on 23/09/2022.
//

#include "Client/Factories/EntityFactory.h"

namespace Client
{

	EntityFactory& EntityFactory::instance()
	{
		static EntityFactory instance;
		return instance;
	}

	bool EntityFactory::Register(const std::string& p_entityType, std::function<std::shared_ptr<Entity>(JsonObject& p_entityParameters)> p_entityBuilder)
	{
		if (m_entityBuilders.find(p_entityType) != std::end(m_entityBuilders))
		{
			return false;
		}
		m_entityBuilders[p_entityType] = p_entityBuilder;

		return true;
	}

} // Client
