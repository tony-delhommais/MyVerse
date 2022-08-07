//
// Created by Tony on 04/08/2022.
//

#include "Core/CoreClass/RessourceManagerCore.h"

#include "Core/CoreClass/ApplicationCore.h"

#include "Core/Ressource/Material.h"
#include "Core/Ressource/Mesh.h"
#include "Core/Ressource/Prefab.h"
#include "Core/Ressource/Shader.h"
#include "Core/Ressource/Texture.h"

#ifdef _DEBUG
#include "Core/Debug.h"
#endif

namespace Core
{

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

		auto readType = (SupportedFileType)GetParameterFromJsonObject(jsonStruct, "Type", (int)SupportedFileType::UNKNOWN);
		auto type = readType;
		if (type == SupportedFileType::UNKNOWN ||
			type == SupportedFileType::DIRECTORY ||
			type == SupportedFileType::SHADER ||
			type == SupportedFileType::DATA ||
			type == SupportedFileType::MAX_VALUE
			) return;

		if (type == SupportedFileType::SCENE)
		{
			ApplicationCore::instance().PreLoadScene(p_ressourceMetaPath.stem().string(), ressourcePath.string());
			return;
		}

		if (type == SupportedFileType::VERTEX_SHADER || type == SupportedFileType::FRAGMENT_SHADER)
		{
			type = SupportedFileType::SHADER;
		}

		std::string fileUuid = GetParameterFromJsonObject(jsonStruct, "Uuid", "None");
		if (fileUuid == "None") return;
		UUIDv4::UUID uuid = UUIDv4::UUID::fromStrFactory(fileUuid);

		auto alwaysLoaded = GetParameterFromJsonObject(jsonStruct, "AlwaysLoaded", true);

		auto settings = GetParameterFromJsonObject(jsonStruct, "Settings", false, true);
		if (settings != jsonStruct)
		{
			if (type == SupportedFileType::SHADER)
			{
				auto shaderLinkUuid = GetParameterFromJsonObject(settings, "ShaderUuid", "Null");
				if (shaderLinkUuid == "Null") return;

				uuid = UUIDv4::UUID::fromStrFactory(shaderLinkUuid);

				auto shader = FindShader(uuid);

				if (shader)
				{
					shader->SetShader(readType, ressourcePath);

					return;
				}
			}
		}
		else
		{
			if (type == SupportedFileType::SHADER) return;
		}

		RessourceMeta ressourceMeta;

		ressourceMeta.ressourcePath = ressourcePath;
		ressourceMeta.type = type;
		ressourceMeta.alwaysLoaded = alwaysLoaded;

		if (alwaysLoaded)
		{
			AllocRessource(uuid, ressourceMeta);
		}

		if (ressourceMeta.shader && type == SupportedFileType::SHADER)
		{
			ressourceMeta.shader->SetShader(readType, ressourcePath);
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
						Debug::LogInfo("[RessourceManager] Dealloc a ressource with uuid " + ressource.first.str());
#endif 
					}
				}
			}
		}
	}

	std::vector<std::shared_ptr<Mesh>> RessourceManagerCore::FindMeshes(const UUIDv4::UUID& p_ressourceUuid)
	{
		auto ressourceMetaIt = FindRessource(p_ressourceUuid, SupportedFileType::MESH);

		if (ressourceMetaIt == m_ressources.end()) return std::vector<std::shared_ptr<Mesh>>();

		return ressourceMetaIt->second.meshes;
	}

	std::shared_ptr<Texture> RessourceManagerCore::FindTexture(const UUIDv4::UUID& p_ressourceUuid)
	{
		auto ressourceMetaIt = FindRessource(p_ressourceUuid, SupportedFileType::TEXTURE);

		if (ressourceMetaIt == m_ressources.end()) return nullptr;

		return ressourceMetaIt->second.texture;
	}

	std::shared_ptr<Material> RessourceManagerCore::FindMaterial(const UUIDv4::UUID& p_ressourceUuid)
	{
		auto ressourceMetaIt = FindRessource(p_ressourceUuid, SupportedFileType::MATERIAL);

		if (ressourceMetaIt == m_ressources.end()) return nullptr;

		return ressourceMetaIt->second.material;
	}

	std::shared_ptr<Shader> RessourceManagerCore::FindShader(const UUIDv4::UUID& p_ressourceUuid)
	{
		auto ressourceMetaIt = FindRessource(p_ressourceUuid, SupportedFileType::SHADER);

		if (ressourceMetaIt == m_ressources.end()) return nullptr;

		return ressourceMetaIt->second.shader;
	}

	std::shared_ptr<Prefab> RessourceManagerCore::FindPrefab(const UUIDv4::UUID& p_ressourceUuid)
	{
		auto ressourceMetaIt = FindRessource(p_ressourceUuid, SupportedFileType::PREFAB);

		if (ressourceMetaIt == m_ressources.end()) return nullptr;

		return ressourceMetaIt->second.prefab;
	}

	RessourceMetaMap::iterator RessourceManagerCore::FindRessource(const UUIDv4::UUID& p_ressourceUuid, SupportedFileType p_wantedRessourceType)
	{
		auto ressourceMetaIt = m_ressources.find(p_ressourceUuid);

		if (ressourceMetaIt == m_ressources.end()) return m_ressources.end();

		auto& ressourceMeta = ressourceMetaIt->second;

		if (ressourceMeta.type != p_wantedRessourceType) return m_ressources.end();

		if (!ressourceMeta.isAllocated)
		{
			ressourceMeta.tryAllocate = true;

			return m_ressources.end();
		}

		return ressourceMetaIt;
	}

	int RessourceManagerCore::GetReferenceCount(const RessourceMeta& p_ressourceMeta)
	{
		if (!p_ressourceMeta.isAllocated) return 0;

		if (!p_ressourceMeta.meshes.empty()) return (int)p_ressourceMeta.meshes[0].use_count();

		if (p_ressourceMeta.texture) return (int)p_ressourceMeta.texture.use_count();

		if (p_ressourceMeta.material) return (int)p_ressourceMeta.material.use_count();

		if (p_ressourceMeta.shader) return (int)p_ressourceMeta.shader.use_count();

		if (p_ressourceMeta.prefab) return (int)p_ressourceMeta.prefab.use_count();

		return 0;
	}

	void RessourceManagerCore::AllocRessource(const UUIDv4::UUID& p_ressourceUuid, RessourceMeta& p_ressourceMeta)
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
			p_ressourceMeta.material = Material::Load(p_ressourceMeta.ressourcePath.string());

			if (p_ressourceMeta.material)
			{
				p_ressourceMeta.tryAllocate = false;
				p_ressourceMeta.isAllocated = true;
			}

			return;
		}

		if (p_ressourceMeta.type == SupportedFileType::SHADER)
		{
			p_ressourceMeta.shader = std::make_shared<Shader>();

			if (p_ressourceMeta.shader)
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
		if (!p_ressourceMeta.meshes.empty()) p_ressourceMeta.meshes.clear();

		if (p_ressourceMeta.texture) p_ressourceMeta.texture = nullptr;

		if (p_ressourceMeta.material) p_ressourceMeta.material = nullptr;

		if (p_ressourceMeta.shader) return;

		if (p_ressourceMeta.prefab) return;

		p_ressourceMeta.isAllocated = false;
	}

} // Core
