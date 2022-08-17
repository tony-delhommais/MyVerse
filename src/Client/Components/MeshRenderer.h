//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_MESH_RENDERER_H
#define MYVERSE_MESH_RENDERER_H

#include "Client/Utils/MathUtils.h"
#include "Client/Utils/JsonUtils.h"

#include "Client/Components/Component.h"

#include "Client/Common/RessourceManager.h"

#include "Client/Ressource/Shader.h"

namespace Core
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
		UUIDv4::UUID m_meshesUuid;
		std::vector<LinkMeshMaterial> m_meshesMaterials;

		std::map<int, UUIDv4::UUID> m_usedMaterialsUuid;
	};

} // Core

#endif // MYVERSE_MESH_RENDERER_H
