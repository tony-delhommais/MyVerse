//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_RESSOURCE_MANAGER_H
#define MYVERSE_RESSOURCE_MANAGER_H

#include "Utils.h"
#include "JsonUtils.h"

namespace Client
{

	class Material;
	class Mesh;
	class Prefab;
	class Texture;

	class RessourceManager
	{
	public:
		static std::vector<std::shared_ptr<Mesh>> FindMeshes(const uuids::uuid& p_ressourceUuid);

		static std::shared_ptr<Texture> FindTexture(const uuids::uuid& p_ressourceUuid);

		static std::shared_ptr<Material> FindMaterial(const uuids::uuid& p_ressourceUuid);

		static std::shared_ptr<Prefab> FindPrefab(const uuids::uuid& p_ressourceUuid);
	};

} // Client

#endif // MYVERSE_RESSOURCE_MANAGER_H
