//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_MATERIAL_H
#define MYVERSE_MATERIAL_H

#include "Core/Utils/JsonUtils.h"
#include "Core/Utils/MathUtils.h"

#include "Core/Ressource/Texture.h"

#ifdef _DEBUG
#include "Core/Common/Debug.h"
#endif

namespace Core
{

	class Shader;

	class Material
	{
	public:
		Material() = default;
		~Material() = default;

	public:
		static std::shared_ptr<Material> Load(const std::filesystem::path& p_path);

		void Use();
		void NotUse();

	private:
		bool m_useSolidColor = true;
		glm::vec3 m_solidColor = glm::vec3(1.0);

		bool m_invertTextures = true;

		bool m_isDiffuseTextureSet = false;
		UUIDv4::UUID m_diffuseTextureUuid;
		std::shared_ptr<Texture> m_diffuseTexture = nullptr;
	};

} // Core

#endif // MYVERSE_MATERIAL_H
