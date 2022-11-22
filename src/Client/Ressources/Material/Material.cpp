//
// Created by Tony on 29/06/2022.
//

#include "Client/Ressources/Material/Material.h"
#include "Client/Ressources/Shader/Shader.h"

#include "Client/Core/ApplicationCore.h"

namespace Client
{

	Material::Material(bool p_useSolidColor, const glm::vec3& p_solidColor, bool p_invertTexture, std::shared_ptr<Texture> p_diffuseTexture) :
		m_useSolidColor(p_useSolidColor),
		m_solidColor(p_solidColor),
		m_invertTextures(p_invertTexture),
		m_diffuseTexture(p_diffuseTexture)
	{

	}

	bool Material::IsUsingSolidColor()
	{
		return m_useSolidColor;
	}

	glm::vec3 Material::GetSolidColor()
	{
		return m_solidColor;
	}

	bool Material::IsInvertingTextures()
	{
		return m_invertTextures;
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
		}
	}

	void Material::Unuse()
	{
		ApplicationCore::instance().GetActiveShader()->SetUserUniform(EnumUser::USE_SOLID_COLOR, true);

		ApplicationCore::instance().GetActiveShader()->SetUserUniform(EnumUser::SOLID_COLOR, Material::DEFAULT_SOLID_COLOR());
	}

	bool Material::DEFAULT_USE_SOLID_COLOR()
	{
		return true;
	}

	glm::vec3 Material::DEFAULT_SOLID_COLOR()
	{
		return glm::vec3(0.95f);
	}

	bool Material::DEFAULT_INVERT_TEXTURE()
	{
		return true;
	}

	std::shared_ptr<Texture> Material::DEFAULT_DIFFUSE_TEXTURE()
	{
		return nullptr;
	}

} // Client
