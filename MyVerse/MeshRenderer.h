//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_MESH_RENDERER_H
#define MYVERSE_MESH_RENDERER_H

#include "MathUtils.h"
#include "JsonUtils.h"

#include "Component.h"

#include "RessourceManager.h"

#include "Shader.h"

namespace Client
{

	class Mesh;
	class Material;

	typedef struct
	{
		std::shared_ptr<Mesh> mesh;
		std::shared_ptr<Material> material;
		//todo animator
	} LinkMeshMaterial;

	class MeshRenderer : public Component
	{
	public:
		MeshRenderer() = default;
		~MeshRenderer() = default;

	public:
		static std::shared_ptr<MeshRenderer> Make(JsonObject& p_componentProprety);

	private:
		void FindMeshRef();
		void FindMaterialRef(int p_meshId);

	public:
		void Render();

	private:
		void SetMeshes(std::vector<std::shared_ptr<Mesh>> p_meshes);
		void SetRenderMaterial(std::shared_ptr<Material> p_material, int p_assignedMeshPos = 0);

	public:
		int GetMeshesCount();

	private:
		uuids::uuid m_meshesUuid;
		std::vector<LinkMeshMaterial> m_meshesMaterials;

		std::map<int, uuids::uuid> m_usedMaterialsUuid;
	};

} // Client

#endif // MYVERSE_MESH_RENDERER_H
