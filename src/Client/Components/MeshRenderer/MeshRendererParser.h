//
// Created by Tony on 08/11/2022.
//

#ifndef MYVERSE_MESH_RENDER_PARSER_H
#define MYVERSE_MESH_RENDER_PARSER_H

#include "Client/Utils/JsonUtils.h"

#include "Client/Components/MeshRenderer/MeshRendererBuilder.h"

#ifdef _DEBUG
#include "Client/Common/Debug.h"
#endif

namespace Client
{

	class MeshRendererParser
	{
	public:
		MeshRendererParser() = default;
		~MeshRendererParser() = default;

	public:
		static JsonObject Serialize(std::shared_ptr<MeshRenderer> p_meshRenderer);

		static std::shared_ptr<MeshRenderer> Parse(JsonObject& p_data);
	};

} // Client

#endif // MYVERSE_MESH_RENDER_PARSER_H
