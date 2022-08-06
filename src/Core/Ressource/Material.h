//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_MATERIAL_H
#define MYVERSE_MATERIAL_H

#include "Core/Utils/JsonUtils.h"

#include "Core/Ressource/Texture.h"

#ifdef _DEBUG
#include "Core/Debug.h"
#endif

namespace Core
{

	class Shader;

	class Material
	{
	public:
		Material() = default;
		Material(std::shared_ptr<Material> p_material);
		~Material() = default;

	public:
		static std::shared_ptr<Material> Load(const std::string& p_path);

		void Use(std::shared_ptr<Shader> p_shader = nullptr);
		void NotUse();

	private:
		bool m_invertTextures = true;

		bool m_isDiffuseTextureSet = false;
		UUIDv4::UUID m_diffuseTextureUuid;
		std::shared_ptr<Texture> m_diffuseTexture = nullptr;
	};

} // Core

#endif // MYVERSE_MATERIAL_H
