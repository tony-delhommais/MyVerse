//
// Created by Tony on 09/11/2022.
//

#ifndef MYVERSE_MATERIAL_PARSER_H
#define MYVERSE_MATERIAL_PARSER_H

#include "Client/Utils/JsonUtils.h"

#include "Client/Builders/MaterialBuilder.h"

namespace Client
{

	class MaterialParser
	{
	public:
		MaterialParser() = default;
		~MaterialParser() = default;

	public:
		static bool Serialize(const std::filesystem::path& p_path, std::shared_ptr<Material> p_material);
		static JsonObject Serialize(std::shared_ptr<Material> p_material);

		static std::shared_ptr<Material> Parse(const std::filesystem::path& p_path);
		static std::shared_ptr<Material> Parse(JsonObject& p_data);
	};

} // Client

#endif // MYVERSE_MATERIAL_PARSER_H
