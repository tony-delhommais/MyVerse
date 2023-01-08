//
// Created by Tony on 29/06/2022.
//

#include "Prefab.h"

#include "EntityFactory.h"

namespace Client
{

	std::shared_ptr<Prefab> Prefab::Load(const uuids::uuid& p_uuid, const std::filesystem::path& p_path)
	{
		auto data = LoadJsonFile(p_path);

		if (data.empty()) return nullptr;

		auto prefab = std::make_shared<Prefab>();

		prefab->m_prefabUuid = p_uuid;
		prefab->m_prefabStruct = data;

		return prefab;
	}

	std::shared_ptr<Entity> Prefab::InstantiateNew()
	{
		if (m_prefabStruct.empty()) return nullptr;

		auto newEntity = EntityFactory::instance().Make<Entity>(m_prefabStruct);

		newEntity->SetParent(nullptr);
		newEntity->SetPrefabReferenceUuid(m_prefabUuid);

		return newEntity;
	}

} // Client
