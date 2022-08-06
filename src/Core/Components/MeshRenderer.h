//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_MESH_RENDERER_H
#define MYVERSE_MESH_RENDERER_H

#include "Core/Utils/MathUtils.h"
#include "Core/Utils/JsonUtils.h"

#include "Core/Components/Component.h"

#include "Core/Managers/RessourceManager.h"

#include "Core/Ressource/Shader.h"

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
		MeshRenderer(std::shared_ptr<MeshRenderer> p_meshRenderer);
		~MeshRenderer() = default;

	public:
		static std::shared_ptr<MeshRenderer> Make(JsonObject& p_componentProprety);

	private:
		void FindMeshRef();
		void FindMaterialRef(int p_meshId);

	public:
		void Render(const glm::mat4& p_MVP);

	private:
		void SetMeshes(std::vector<std::shared_ptr<Mesh>> p_meshes);
		void SetRenderMaterial(std::shared_ptr<Material> p_material, int p_assignedMeshPos = 0);

	public:
		int GetMeshesCount();

	private:
		UUIDv4::UUID m_meshesUuid;
		std::vector<LinkMeshMaterial> m_meshesMaterials;

		std::map<int, UUIDv4::UUID> m_usedMaterialsUuid;

		UUIDv4::UUID m_shaderUuid;
		std::shared_ptr<Shader> m_shader = nullptr;
	};

} // Core

#endif // MYVERSE_MESH_RENDERER_H
