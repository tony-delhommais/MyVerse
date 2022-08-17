//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_MATERIAL_H
#define MYVERSE_MATERIAL_H

#include "Client/Utils/JsonUtils.h"
#include "Client/Utils/MathUtils.h"
#include "Client/Utils/GraphicsUtils.h"

#include "Client/Ressource/Texture.h"

#ifdef _DEBUG
#include "Client/Common/Debug.h"
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

	private:
		bool m_useSolidColor = true;
		GLint m_shaderSolidColorUniformLocation = -1;
		glm::vec3 m_solidColor = glm::vec3(1.0);

		GLint m_shaderInvertTextureUniformLocation = -1;
		bool m_invertTextures = true;

		bool m_isDiffuseTextureSet = false;
		UUIDv4::UUID m_diffuseTextureUuid;
		std::shared_ptr<Texture> m_diffuseTexture = nullptr;
	};

} // Client

#endif // MYVERSE_MATERIAL_H
