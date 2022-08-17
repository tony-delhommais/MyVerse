//
// Created by Tony on 23/07/2022.
//

#include "Client/Common/RessourceManager.h"

#include "Client/Core/RessourceManagerCore.h"

namespace Core
{

	std::vector<std::shared_ptr<Mesh>> RessourceManager::FindMeshes(const UUIDv4::UUID& p_ressourceUuid)
	{
		return RessourceManagerCore::instance().FindMeshes(p_ressourceUuid);
	}

	std::shared_ptr<Texture> RessourceManager::FindTexture(const UUIDv4::UUID& p_ressourceUuid)
	{
		return RessourceManagerCore::instance().FindTexture(p_ressourceUuid);
	}

	std::shared_ptr<Material> RessourceManager::FindMaterial(const UUIDv4::UUID& p_ressourceUuid)
	{
		return RessourceManagerCore::instance().FindMaterial(p_ressourceUuid);
	}

	std::shared_ptr<Prefab> RessourceManager::FindPrefab(const UUIDv4::UUID& p_ressourceUuid)
	{
		return RessourceManagerCore::instance().FindPrefab(p_ressourceUuid);
	}

} // Core