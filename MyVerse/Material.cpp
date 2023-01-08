//
// Created by Tony on 29/06/2022.
//

#include "Material.h"
#include "Shader.h"

#include "RessourceManager.h"

#include "ApplicationCore.h"

namespace Client
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
			material->m_diffuseTextureUuid = uuids::uuid::from_string(diffuseTextureUuid).value();
			material->m_isDiffuseTextureSet = true;
		}

		return material;
	}

	void Material::Use()
	{
		ApplicationCore::instance().GetActiveShader()->SetUserUniform(EnumUser::USE_SOLID_COLOR, m_useSolidColor);

		if (m_useSolidColor)
		{
			ApplicationCore::instance().GetActiveShader()->SetUserUniform(EnumUser::SOLID_COLOR, m_solidColor);
		}
		else
		{
			ApplicationCore::instance().GetActiveShader()->SetUserUniform(EnumUser::TEXTURE_INVERSION_VALUE, (!m_invertTextures ? 1 : -1));

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

	void Material::Unuse()
	{
		ApplicationCore::instance().GetActiveShader()->SetUserUniform(EnumUser::USE_SOLID_COLOR, true);

		ApplicationCore::instance().GetActiveShader()->SetUserUniform(EnumUser::SOLID_COLOR, glm::vec3(0.95f));
	}

} // Client
