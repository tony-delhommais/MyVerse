//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_MATERIAL_H
#define MYVERSE_MATERIAL_H

#include "Client/Utils/MathUtils.h"

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
		Material(bool p_useSolidColor, const glm::vec3& p_solidColor, bool p_invertTexture, std::shared_ptr<Texture> p_diffuseTexture);
		~Material() = default;

	public:
		bool IsUsingSolidColor();
		glm::vec3 GetSolidColor();
		bool IsInvertingTextures();
		//todo get diffuse texture

	public:
		void Use();
		void Unuse();

	public:
		static bool DEFAULT_USE_SOLID_COLOR();
		static glm::vec3 DEFAULT_SOLID_COLOR();

		static bool DEFAULT_INVERT_TEXTURE();

		static std::shared_ptr<Texture> DEFAULT_DIFFUSE_TEXTURE();

	private:
		bool m_useSolidColor = true;
		glm::vec3 m_solidColor = glm::vec3(1.0);

		bool m_invertTextures = true;

		std::shared_ptr<Texture> m_diffuseTexture = nullptr;
	};

} // Client

#endif // MYVERSE_MATERIAL_H
