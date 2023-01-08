//
// Created by Tony on 17/08/2022.
//

#include "Player.h"

#include "EntityFactory.h"

namespace Client
{

	bool Player::s_isPlayerMakerRegistered = EntityFactory::instance().Register("Player", [](JsonObject& p_entityParameters) -> std::shared_ptr<Entity> {
		auto player = std::make_shared<Player>();

		player->SetTag("Player");

		auto& playerMeshRendererData = GetParameterFromJsonObject(p_entityParameters, "PlayerMeshRenderer", false, true);
		if (playerMeshRendererData != p_entityParameters)
		{
			auto playerMeshRenderer = MeshRenderer::Make(playerMeshRendererData);

			player->SetMeshRenderer(playerMeshRenderer);
		}
#ifdef _DEBUG
		else
		{
			Debug::LogWarning("[Player] No Player MeshRenderer set!");
		}
#endif

		auto& playerControllerScriptData = GetParameterFromJsonObject(p_entityParameters, "PlayerControllerScript", false, true);
		if (playerControllerScriptData != p_entityParameters)
		{
			auto playerControllerScript = ScriptFactory::instance().Make(playerControllerScriptData);

			player->SetScript(playerControllerScript);
		}
#ifdef _DEBUG
		else
		{
			Debug::LogWarning("[Player] No Player Controller Script set!");
		}
#endif

		return player;
	});

} // Client
