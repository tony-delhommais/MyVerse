//
// Created by Tony on 29/06/2022.
//

#include "Client/Ressource/Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Client
{

	Texture::~Texture()
	{
		if (m_openGL_id) glDeleteTextures(1, &m_openGL_id);
	}

	void Texture::Use(unsigned int p_channel)
	{
		glEnable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0 + p_channel);
		glBindTexture(GL_TEXTURE_2D, m_openGL_id);
	}

	void Texture::NotUse(unsigned int p_channel)
	{
		glDisable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0 + p_channel);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	std::shared_ptr<Texture> Texture::Load(const std::filesystem::path& p_path)
	{
		int width, height, nrChannels;
		unsigned char* data = stbi_load(p_path.string().c_str(), &width, &height, &nrChannels, 0);
		if (!data)
		{
			return nullptr;
		}

		auto texture = std::make_shared<Texture>();
		
		glGenTextures(1, &texture->m_openGL_id);
		if (texture->m_openGL_id == 0)
		{
			return nullptr;
		}

		// glBinTexture
		glBindTexture(GL_TEXTURE_2D, texture->m_openGL_id);
		// glTexParameteri (pour les filtres)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// glTexImage2D
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		// glGenerateMipmap
		glGenerateMipmap(GL_TEXTURE_2D);
		Texture::NotUse();
		stbi_image_free(data);

		return texture;
	}

} // Client
