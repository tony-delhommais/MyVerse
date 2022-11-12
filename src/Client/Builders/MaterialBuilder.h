//
// Created by Tony on 09/11/2022.
//

#ifndef MYVERSE_MATERIAL_BUILDER_H
#define MYVERSE_MATERIAL_BUILDER_H

#include "Client/Ressource/Material.h"

namespace Client
{

	class MaterialBuilder
	{
	public:
		MaterialBuilder();
		~MaterialBuilder() = default;

	public:
		std::shared_ptr<Material> Build();

		MaterialBuilder& SetUseSolidColor(bool p_useSolidColor);
		MaterialBuilder& SetSolidColor(const glm::vec3& p_solidColor);
		MaterialBuilder& SetInvertTexture(bool p_invertTexture);
		MaterialBuilder& SetDiffuseTexture(std::shared_ptr<Texture> p_diffuseTexture);

	private:
		bool m_useSolidColor;
		glm::vec3 m_solidColor;

		bool m_invertTextures;

		std::shared_ptr<Texture> m_diffuseTexture;
	};

} // Client

#endif // MYVERSE_MATERIAL_BUILDER_H
