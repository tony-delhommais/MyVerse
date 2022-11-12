//
// Created by Tony on 09/11/2022.
//

#include "Client/Parser/MaterialParser.h"

#include "Client/Common/RessourceManager.h"

namespace Client
{

	bool MaterialParser::Serialize(const std::filesystem::path& p_path, std::shared_ptr<Material> p_material)
	{
		JsonObject data = MaterialParser::Serialize(p_material);

		return WriteJsonFile(p_path, data);
	}

	JsonObject MaterialParser::Serialize(std::shared_ptr<Material> p_material)
	{
		JsonObject materialData;

		materialData["Type"] = "Material";

		materialData["UseSolidColor"] = p_material->IsUsingSolidColor();
		glm::vec3 solidColor = p_material->GetSolidColor();
		materialData["SolidColor"] = JsonObject::array({solidColor[0], solidColor[1], solidColor[2]});
		materialData["InvertTextures"] = p_material->IsInvertingTextures();

		//todo serialize diffuse texture

		return materialData;
	}

	std::shared_ptr<Material> MaterialParser::Parse(const std::filesystem::path& p_path)
	{
		JsonObject data = LoadJsonFile(p_path);

		return MaterialParser::Parse(data);
	}

	std::shared_ptr<Material> MaterialParser::Parse(JsonObject& p_data)
	{
		// Test if object have a Type Material
		if (GetParameterFromJsonObject(p_data, "Type", "Null") != "Material")
		{
#ifdef _DEBUG
			Debug::LogWarning("[MaterialParser] Try to parse an Material, but type is invalid");
#endif
			return nullptr;
		}

		MaterialBuilder builder;

		builder.SetUseSolidColor(GetParameterFromJsonObject(p_data, "UseSolidColor", Material::DEFAULT_USE_SOLID_COLOR()));

		JsonObject& solidColorData = GetParameterFromJsonObject(p_data, "SolidColor", true, false);
		if(solidColorData != p_data && solidColorData.size() == 3)
			builder.SetSolidColor(glm::vec3(solidColorData[0], solidColorData[1], solidColorData[2]));

		builder.SetInvertTexture(GetParameterFromJsonObject(p_data, "InvertTexture", Material::DEFAULT_USE_SOLID_COLOR()));

		builder.SetDiffuseTexture(RessourceManager::FindTexture(UUIDv4::UUID::fromStrFactory(GetParameterFromJsonObject(p_data, "DiffuseTexture", "Null"))));

		return builder.Build();
	}

} // Client
