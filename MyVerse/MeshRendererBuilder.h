//
// Created by Tony on 08/11/2022.
//

#ifndef MYVERSE_MESH_RENDERER_BUILDER_H
#define MYVERSE_MESH_RENDERER_BUILDER_H

#include "MeshRenderer.h"

namespace Client
{

	class MeshRendererBuilder
	{
	public:
		MeshRendererBuilder() = default;
		~MeshRendererBuilder() = default;

	public:
		std::shared_ptr<MeshRenderer> Build();

		MeshRendererBuilder& SetSubMeshes(std::vector<std::shared_ptr<Mesh>> p_subMeshes);
		MeshRendererBuilder& SetMaterials(std::vector<std::shared_ptr<Material>> p_materials);

	private:
		std::shared_ptr<Entity> m_entity = nullptr;

		std::vector<std::shared_ptr<Mesh>> m_subMeshes;
		std::vector<std::shared_ptr<Material>> m_materials;
	};

} // Client

#endif // MYVERSE_MESH_RENDERER_BUILDER_H
