//
// Created by Tony on 12/11/2022.
//

#include "Client/Builders/SceneBuilder.h"

namespace Client
{

	std::shared_ptr<Scene> Client::SceneBuilder::Build()
	{
		return std::make_shared<Scene>(m_name, m_localEntities);
	}

	SceneBuilder& SceneBuilder::SetName(const std::string p_name)
	{
		m_name = p_name;

		return *this;
	}

	SceneBuilder& SceneBuilder::SetLocalEntities(std::list<std::shared_ptr<Entity>> p_localEntities)
	{
		m_localEntities = p_localEntities;

		return *this;
	}

} // Client
