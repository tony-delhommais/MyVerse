//
// Created by Tony on 23/07/2022.
//

#include "RessourceManager.h"

#include "RessourceManagerCore.h"

namespace Client
{

	std::vector<std::shared_ptr<Mesh>> RessourceManager::FindMeshes(const uuids::uuid& p_ressourceUuid)
	{
		return RessourceManagerCore::instance().FindMeshes(p_ressourceUuid);
	}

	std::shared_ptr<Texture> RessourceManager::FindTexture(const uuids::uuid& p_ressourceUuid)
	{
		return RessourceManagerCore::instance().FindTexture(p_ressourceUuid);
	}

	std::shared_ptr<Material> RessourceManager::FindMaterial(const uuids::uuid& p_ressourceUuid)
	{
		return RessourceManagerCore::instance().FindMaterial(p_ressourceUuid);
	}

	std::shared_ptr<Prefab> RessourceManager::FindPrefab(const uuids::uuid& p_ressourceUuid)
	{
		return RessourceManagerCore::instance().FindPrefab(p_ressourceUuid);
	}

} // Client