//
// Created by Tony on 04/08/2022.
//

#ifndef MYVERSE_RESSOURCE_MANAGER_CORE_H
#define MYVERSE_RESSOURCE_MANAGER_CORE_H

#include "Core/Utils/GraphicsUtils.h"
#include "Core/Utils/Utils.h"
#include "Core/Utils/JsonUtils.h"
#include "Core/Utils/SupportedFileType.h"

#include "Core/Common/Clock.h"

namespace Core
{

	class Material;
	class Mesh;
	class Prefab;
	class Texture;

	struct RessourceMeta
	{
		SupportedFileType type = SupportedFileType::UNKNOWN;
		std::filesystem::path ressourcePath;
		bool alwaysLoaded = true;

		bool tryAllocate = false;
		bool isAllocated = false;

		std::vector<std::shared_ptr<Mesh>> meshes;
		std::shared_ptr<Texture> texture = nullptr;
		std::shared_ptr<Material> material = nullptr;
		std::shared_ptr<Prefab> prefab = nullptr;
	};

	typedef std::map<UUIDv4::UUID, RessourceMeta> RessourceMetaMap;

	class RessourceManagerCore
	{
	private:
		RessourceManagerCore() = default;
		~RessourceManagerCore() = default;

	public:
		static RessourceManagerCore& instance();

		void PreloadRessource(const std::filesystem::path& p_ressourceMetaPath);

		void ManagementLoop();

		std::vector<std::shared_ptr<Mesh>> FindMeshes(const UUIDv4::UUID& p_ressourceUuid);

		std::shared_ptr<Texture> FindTexture(const UUIDv4::UUID& p_ressourceUuid);

		std::shared_ptr<Material> FindMaterial(const UUIDv4::UUID& p_ressourceUuid);

		std::shared_ptr<Prefab> FindPrefab(const UUIDv4::UUID& p_ressourceUuid);

	private:
		RessourceMetaMap::iterator FindRessource(const UUIDv4::UUID& p_ressourceUuid, SupportedFileType p_wantedRessourceType);

		int GetReferenceCount(const RessourceMeta& p_ressourceMeta);

		void AllocRessource(const UUIDv4::UUID& p_ressourceUuid, RessourceMeta& p_ressourceMeta);
		void DeallocRessource(RessourceMeta& p_ressourceMeta);

	private:
		RessourceMetaMap m_ressources;
	};

} // Core

#endif // MYVERSE_RESSOURCE_MANAGER_CORE_H