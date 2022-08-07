//
// Created by Tony on 29/06/2022.
//

#include "Core/Ressource/Material.h"
#include "Core/Ressource/Shader.h"

#include "Core/Managers/RessourceManager.h"

namespace Core
{

	std::shared_ptr<Material> Material::Load(const std::filesystem::path& p_path)
	{
		JsonObject materialStruct = LoadJsonFile(p_path);

		if (materialStruct.empty()) return nullptr;

		if (GetParameterFromJsonObject(materialStruct, "Type", "Null") != "Material") return nullptr;

		auto material = std::make_shared<Material>();

		material->m_useSolidColor = GetParameterFromJsonObject(materialStruct, "UseSolidColor", material->m_useSolidColor);

		auto solidColor = GetParameterFromJsonObject(materialStruct, "SolidColor", true, false);

		if (solidColor != materialStruct && solidColor.size() == 3 && solidColor[0].is_number_float()) material->m_solidColor = glm::vec3(solidColor[0], solidColor[1], solidColor[2]);

		material->m_invertTextures = GetParameterFromJsonObject(materialStruct, "InvertTextures", material->m_invertTextures);

		std::string diffuseTextureUuid = GetParameterFromJsonObject(materialStruct, "DiffuseTexture", "Null");
		if (diffuseTextureUuid != "Null")
		{
			material->m_diffuseTextureUuid = UUIDv4::UUID::fromStrFactory(diffuseTextureUuid);
			material->m_isDiffuseTextureSet = true;
		}

		return material;
	}

	void Material::Use(std::shared_ptr<Shader> p_shader)
	{
		if (m_useSolidColor)
		{
			if (p_shader) p_shader->SetUniformVec3("solidColor", m_solidColor);
		}
		else
		{
			if (p_shader && !m_invertTextures) p_shader->SetUniformInt("textureInversion", 1);

			if (m_diffuseTexture)
			{
				m_diffuseTexture->Use();
			}
			else if (m_isDiffuseTextureSet)
			{
				m_diffuseTexture = RessourceManager::FindTexture(m_diffuseTextureUuid);
			}
		}
	}

	void Material::NotUse()
	{
		Texture::NotUse();
	}

} // Core
