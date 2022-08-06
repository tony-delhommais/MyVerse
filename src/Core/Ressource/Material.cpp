//
// Created by Tony on 29/06/2022.
//

#include "Core/Ressource/Material.h"
#include "Core/Ressource/Shader.h"

#include "Core/Managers/RessourceManager.h"

namespace Core
{

	Material::Material(std::shared_ptr<Material> p_material)
	{
		m_diffuseTexture = p_material->m_diffuseTexture;
	}

	std::shared_ptr<Material> Material::Load(const std::string& p_path)
	{
		std::fstream materialFile;
		materialFile.open(p_path, std::ios::in);

		JsonObject materialStruct;
		materialFile >> materialStruct;

		if (GetParameterFromJsonObject(materialStruct, "Type", "Null") != "Material")
		{
			return nullptr;
		}

		auto material = std::make_shared<Material>();

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

	void Material::NotUse()
	{
		Texture::NotUse();
	}

} // Core
