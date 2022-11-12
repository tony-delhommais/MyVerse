//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_MESH_RENDERER_H
#define MYVERSE_MESH_RENDERER_H

#include "Client/Components/Component.h"

namespace Client
{

	class Mesh;
	class Material;

	class MeshRenderer : public Component
	{
	public:
		MeshRenderer(std::shared_ptr<Entity> p_entity, std::vector<std::shared_ptr<Mesh>> p_subMeshes, std::vector<std::shared_ptr<Material>> p_materials);
		~MeshRenderer() = default;

	public:
		void Render();

	private:

		std::vector<std::shared_ptr<Mesh>> m_subMeshes;
		std::vector<std::shared_ptr<Material>> m_materials;
	};

} // Client

#endif // MYVERSE_MESH_RENDERER_H
