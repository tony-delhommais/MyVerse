//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_MATERIAL_H
#define MYVERSE_MATERIAL_H

#include "JsonUtils.h"
#include "MathUtils.h"
#include "GraphicsUtils.h"

#include "Texture.h"

#ifdef _DEBUG
#include "Debug.h"
#endif

namespace Client
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
		void Unuse();

	private:
		bool m_useSolidColor = true;
		glm::vec3 m_solidColor = glm::vec3(1.0);

		bool m_invertTextures = true;

		bool m_isDiffuseTextureSet = false;
		uuids::uuid m_diffuseTextureUuid;
		std::shared_ptr<Texture> m_diffuseTexture = nullptr;
	};

} // Client

#endif // MYVERSE_MATERIAL_H
