//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_PREFAB_H
#define MYVERSE_PREFAB_H

#include "Client/Utils/Utils.h"
#include "Client/Utils/JsonUtils.h"

#ifdef _DEBUG
#include "Client/Common/Debug.h"
#endif

namespace Client
{

	class Entity;

	class Prefab
	{
	public:
		Prefab() = default;
		~Prefab() = default;

	public:
		static std::shared_ptr<Prefab> Load(const UUIDv4::UUID& p_uuid, const std::filesystem::path& p_path);

		std::shared_ptr<Entity> InstantiateNew();

	private:
		UUIDv4::UUID m_prefabUuid;

		JsonObject m_prefabStruct;
	};

} // Client

#endif // MYVERSE_PREFAB_H
