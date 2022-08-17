//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_RESSOURCE_MANAGER_H
#define MYVERSE_RESSOURCE_MANAGER_H

#include "Client/Utils/Utils.h"
#include "Client/Utils/JsonUtils.h"

namespace Core
{

	class Material;
	class Mesh;
	class Prefab;
	class Texture;

	class RessourceManager
	{
	public:
		static std::vector<std::shared_ptr<Mesh>> FindMeshes(const UUIDv4::UUID& p_ressourceUuid);

		static std::shared_ptr<Texture> FindTexture(const UUIDv4::UUID& p_ressourceUuid);

		static std::shared_ptr<Material> FindMaterial(const UUIDv4::UUID& p_ressourceUuid);

		static std::shared_ptr<Prefab> FindPrefab(const UUIDv4::UUID& p_ressourceUuid);
	};

} // Core

#endif // MYVERSE_RESSOURCE_MANAGER_H
