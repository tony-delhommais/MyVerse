//
// Created by Tony on 06/11/2022.
//

#include "Client/Components/MeshRenderer/MeshRendererParser.h"

#include "Client/Common/RessourceManager.h"

namespace Client
{

	JsonObject MeshRendererParser::Serialize(std::shared_ptr<MeshRenderer> p_camera)
	{
		JsonObject transformData;

		transformData["Type"] = "MeshRenderer";

		//todo

		return transformData;
	}

	std::shared_ptr<MeshRenderer> MeshRendererParser::Parse(JsonObject& p_data)
	{
		// Test if object is a MeshRenderer
		if (GetParameterFromJsonObject(p_data, "Type", "Null") != "MeshRenderer")
		{
#ifdef _DEBUG
			Debug::LogWarning("[MeshRendererParser] Try to parse an MeshRenderer, but type is invalid");
#endif
			return nullptr;
		}

		MeshRendererBuilder builder;

		std::string meshUuid = GetParameterFromJsonObject(p_data, "Mesh", "Null");
		if (meshUuid == "Null")
		{
#ifdef _DEBUG
			Debug::LogWarning("[MeshRendererParser] Mesh UUID is invalid");
#endif
			return nullptr;
		}

		builder.SetSubMeshes(RessourceManager::FindMeshes(UUIDv4::UUID::fromStrFactory(meshUuid)));

		std::vector<std::shared_ptr<Material>> materials;

		JsonObject& materialsUuidList = GetParameterFromJsonObject(p_data, "Materials", true, false);

		if (materialsUuidList != p_data)
		{
			for (auto& materialUuid : materialsUuidList)
			{
				if (!materialUuid.is_string())
					continue;

				materials.push_back(RessourceManager::FindMaterial(UUIDv4::UUID::fromStrFactory(materialUuid)));
			}
		}

		builder.SetMaterials(materials);

		return builder.Build();
	}

} // Client
