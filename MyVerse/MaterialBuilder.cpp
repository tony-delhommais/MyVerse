//
// Created by Tony on 09/11/2022.
//

#include "MaterialBuilder.h"

namespace Client
{

	Client::MaterialBuilder::MaterialBuilder()
	{
		m_useSolidColor = Material::DEFAULT_USE_SOLID_COLOR();
		m_solidColor = Material::DEFAULT_SOLID_COLOR();
		m_invertTextures = Material::DEFAULT_INVERT_TEXTURE();
		m_diffuseTexture = Material::DEFAULT_DIFFUSE_TEXTURE();
	}

	std::shared_ptr<Material> MaterialBuilder::Build()
	{
		//if (!m_diffuseTexture)
			//todo use default pink texture

		return std::make_shared<Material>(m_useSolidColor, m_solidColor, m_invertTextures, m_diffuseTexture);
	}

	MaterialBuilder& MaterialBuilder::SetUseSolidColor(bool p_useSolidColor)
	{
		m_useSolidColor = p_useSolidColor;

		return *this;
	}

	MaterialBuilder& MaterialBuilder::SetSolidColor(const glm::vec3& p_solidColor)
	{
		m_solidColor = p_solidColor;

		return *this;
	}

	MaterialBuilder& MaterialBuilder::SetInvertTexture(bool p_invertTexture)
	{
		m_invertTextures = p_invertTexture;

		return *this;
	}

	MaterialBuilder& MaterialBuilder::SetDiffuseTexture(std::shared_ptr<Texture> p_diffuseTexture)
	{
		m_diffuseTexture = p_diffuseTexture;

		return *this;
	}

} // Client
