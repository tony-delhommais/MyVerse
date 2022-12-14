//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_TEXTURE_H
#define MYVERSE_TEXTURE_H

#include "Client/Utils/Utils.h"
#include "Client/Utils/GraphicsUtils.h"

namespace Client
{

	class Texture
	{
	public:
		Texture() = default;
		~Texture();

	public:
		void Use(unsigned int p_channel = 0);
		static void NotUse(unsigned int p_channel = 0);

		static std::shared_ptr<Texture> Load(const std::filesystem::path& p_path);

	private:
		GLuint m_openGL_id = 0;
	};

} // Client

#endif // MYVERSE_TEXTURE_H
