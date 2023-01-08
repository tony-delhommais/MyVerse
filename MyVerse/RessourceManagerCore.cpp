//
// Created by Tony on 04/08/2022.
//

#include "RessourceManagerCore.h"

#include "ApplicationCore.h"

#include "MaterialParser.h"
#include "Mesh.h"
#include "Prefab.h"
#include "Texture.h"

#ifdef _DEBUG
#include "Debug.h"
#endif

namespace Client
{

	RessourceManagerCore::RessourceManagerCore()
	{
		std::random_device rd;
		auto seed_data = std::array<int, std::mt19937::state_size> {};
		std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
		std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
		std::mt19937 generator(seq);
		uuids::uuid_random_generator generateRandomUuid{ generator };

		RessourceMeta defaultMaterial;
		defaultMaterial.type = SupportedFileType::MATERIAL;
		defaultMaterial.isAllocated = true;
		defaultMaterial.material = MaterialBuilder().SetUseSolidColor(true).SetSolidColor(glm::vec3(1.0, 0.07843137254, 0.57647058823)).Build();

		m_ressources.insert(RessourceMetaMap::value_type(generateRandomUuid(), defaultMaterial));
	}

	RessourceManagerCore& RessourceManagerCore::instance()
	{
		static RessourceManagerCore instance;
		return instance;
	}

	void RessourceManagerCore::PreloadRessource(const std::filesystem::path& p_ressourceMetaPath)
	{
		if (!std::filesystem::exists(p_ressourceMetaPath)) return;

		if (p_ressourceMetaPath.extension() != ".meta") return;

		auto ressourcePath = std::filesystem::path(p_ressourceMetaPath.parent_path().string() + "/" + p_ressourceMetaPath.stem().string());

		if (!std::filesystem::exists(ressourcePath)) return;

		auto jsonStruct = LoadJsonFile(p_ressourceMetaPath.string());
		if (jsonStruct.empty()) return;

		auto type = (SupportedFileType)GetParameterFromJsonObject(jsonStruct, "Type", (int)SupportedFileType::UNKNOWN);
		if (type == SupportedFileType::UNKNOWN ||
			type == SupportedFileType::DIRECTORY ||
			type == SupportedFileType::DATA ||
			type == SupportedFileType::CHUNK ||
			type == SupportedFileType::MAX_VALUE
			) return;

		std::string fileUuid = GetParameterFromJsonObject(jsonStruct, "Uuid", "None");
		if (fileUuid == "None") return;
		uuids::uuid uuid = uuids::uuid::from_string(fileUuid).value();

		auto alwaysLoaded = GetParameterFromJsonObject(jsonStruct, "AlwaysLoaded", true);

		auto settings = GetParameterFromJsonObject(jsonStruct, "Settings", false, true);
		if (settings != jsonStruct)
		{
			
		}
		else
		{
			
		}

		RessourceMeta ressourceMeta;

		ressourceMeta.ressourcePath = ressourcePath;
		ressourceMeta.type = type;
		ressourceMeta.alwaysLoaded = alwaysLoaded;

		if (alwaysLoaded)
		{
			AllocRessource(uuid, ressourceMeta);
		}

		m_ressources.insert(RessourceMetaMap::value_type(uuid, ressourceMeta));
	}

	void RessourceManagerCore::ManagementLoop()
	{
		//todo can be optimized with an array of ressource to allocate
		for (auto& ressource : m_ressources)
		{
			if (ressource.second.tryAllocate && !ressource.second.isAllocated)
			{
				AllocRessource(ressource.first, ressource.second);
			}
		}

		if (Clock::instance().GetMillisecondStopWatchTime("RessourceManagerDeallocUpdate") > 3000)
		{
			Clock::instance().ResetStopWatch("RessourceManagerDeallocUpdate");

			Clock::instance().ResetStopWatch("RessourceManagerDeallocUpdateMaxTimer");

			for (auto& ressource : m_ressources)
			{
				if (Clock::instance().GetMillisecondStopWatchTime("RessourceManagerDeallocUpdateMaxTimer") > 15) break;

				if (!ressource.second.alwaysLoaded && ressource.second.isAllocated)
				{
					int useCount = GetReferenceCount(ressource.second);

					if (useCount == 1)
					{
						DeallocRessource(ressource.second);

#ifdef _DEBUG
						Debug::LogInfo("[RessourceManager] Dealloc a ressource with uuid " + uuids::to_string(ressource.first));
#endif 
					}
				}
			}
		}
	}

	std::vector<std::shared_ptr<Mesh>> RessourceManagerCore::FindMeshes(const uuids::uuid& p_ressourceUuid)
	{
		auto ressourceMetaIt = FindRessource(p_ressourceUuid, SupportedFileType::MESH);

		if (ressourceMetaIt == m_ressources.end())
			return std::vector<std::shared_ptr<Mesh>>();

		return ressourceMetaIt->second.meshes;
	}

	std::shared_ptr<Texture> RessourceManagerCore::FindTexture(const uuids::uuid& p_ressourceUuid)
	{
		auto ressourceMetaIt = FindRessource(p_ressourceUuid, SupportedFileType::TEXTURE);

		if (ressourceMetaIt == m_ressources.end())
			return nullptr;

		return ressourceMetaIt->second.texture;
	}

	std::shared_ptr<Material> RessourceManagerCore::FindMaterial(const uuids::uuid& p_ressourceUuid)
	{
		auto ressourceMetaIt = FindRessource(p_ressourceUuid, SupportedFileType::MATERIAL);

		if (ressourceMetaIt == m_ressources.end())
			return m_ressources.begin()->second.material;

		return ressourceMetaIt->second.material;
	}

	std::shared_ptr<Prefab> RessourceManagerCore::FindPrefab(const uuids::uuid& p_ressourceUuid)
	{
		auto ressourceMetaIt = FindRessource(p_ressourceUuid, SupportedFileType::PREFAB);

		if (ressourceMetaIt == m_ressources.end())
			return nullptr;

		return ressourceMetaIt->second.prefab;
	}

	RessourceMetaMap::iterator RessourceManagerCore::FindRessource(const uuids::uuid& p_ressourceUuid, SupportedFileType p_wantedRessourceType)
	{
		auto ressourceMetaIt = m_ressources.find(p_ressourceUuid);

		if (ressourceMetaIt == m_ressources.end())
			return m_ressources.end();

		auto& ressourceMeta = ressourceMetaIt->second;

		if (ressourceMeta.type != p_wantedRessourceType)
			return m_ressources.end();

		if (!ressourceMeta.isAllocated)
		{
			ressourceMeta.tryAllocate = true;

			return m_ressources.end();
		}

		return ressourceMetaIt;
	}

	int RessourceManagerCore::GetReferenceCount(const RessourceMeta& p_ressourceMeta)
	{
		if (!p_ressourceMeta.isAllocated)
			return 0;

		if (!p_ressourceMeta.meshes.empty())
			return (int)p_ressourceMeta.meshes[0].use_count();

		if (p_ressourceMeta.texture)
			return (int)p_ressourceMeta.texture.use_count();

		if (p_ressourceMeta.material)
			return (int)p_ressourceMeta.material.use_count();

		if (p_ressourceMeta.prefab)
			return (int)p_ressourceMeta.prefab.use_count();

		return 0;
	}

	void RessourceManagerCore::AllocRessource(const uuids::uuid& p_ressourceUuid, RessourceMeta& p_ressourceMeta)
	{
		if (p_ressourceMeta.type == SupportedFileType::MESH)
		{
			p_ressourceMeta.meshes = Mesh::LoadFromOBJ(p_ressourceMeta.ressourcePath.string());

			if (!p_ressourceMeta.meshes.empty())
			{
				p_ressourceMeta.tryAllocate = false;
				p_ressourceMeta.isAllocated = true;
			}

			return;
		}

		if (p_ressourceMeta.type == SupportedFileType::TEXTURE)
		{
			p_ressourceMeta.texture = Texture::Load(p_ressourceMeta.ressourcePath.string());

			if (p_ressourceMeta.texture)
			{
				p_ressourceMeta.tryAllocate = false;
				p_ressourceMeta.isAllocated = true;
			}

			return;
		}

		if (p_ressourceMeta.type == SupportedFileType::MATERIAL)
		{
			p_ressourceMeta.material = MaterialParser::Parse(p_ressourceMeta.ressourcePath);

			if (p_ressourceMeta.material)
			{
				p_ressourceMeta.tryAllocate = false;
				p_ressourceMeta.isAllocated = true;
			}

			return;
		}

		if (p_ressourceMeta.type == SupportedFileType::PREFAB)
		{
			p_ressourceMeta.prefab = Prefab::Load(p_ressourceUuid, p_ressourceMeta.ressourcePath.string());

			if (p_ressourceMeta.prefab)
			{
				p_ressourceMeta.tryAllocate = false;
				p_ressourceMeta.isAllocated = true;
			}

			return;
		}
	}

	void RessourceManagerCore::DeallocRessource(RessourceMeta& p_ressourceMeta)
	{
		if (!p_ressourceMeta.meshes.empty())
			p_ressourceMeta.meshes.clear();

		if (p_ressourceMeta.texture)
			p_ressourceMeta.texture = nullptr;

		if (p_ressourceMeta.material)
			p_ressourceMeta.material = nullptr;

		if (p_ressourceMeta.prefab)
			return;

		p_ressourceMeta.isAllocated = false;
	}

} // Client
