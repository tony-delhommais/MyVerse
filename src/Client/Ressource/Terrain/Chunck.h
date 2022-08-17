//
// Created by Tony on 07/08/2022.
//

#ifndef MYVERSE_CHUNCK_H
#define MYVERSE_CHUNCK_H

#include "Client/Utils/Utils.h"
#include "Client/Utils/JsonUtils.h"

namespace Core
{

	class Chunck
	{
	public:
		Chunck() = default;
		~Chunck() = default;

		static std::shared_ptr<Chunck> Load(const std::filesystem::path& p_chunckPath);
	};

} // Core

#endif // MYVERSE_CHUNCK_H
