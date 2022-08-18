//
// Created by Tony on 17/08/2022.
//

#include "Client/Entity/Player.h"

namespace Client
{

	std::shared_ptr<Player> Player::Make(const std::filesystem::path& p_playerSettingsPath)
	{
		JsonObject playerSettings = LoadJsonFile(p_playerSettingsPath);
		if (playerSettings.empty())
		{
#ifdef _DEBUG
			Debug::LogError("[Player] Player Settings Path not valid!");
#endif
			return nullptr;
		}

		auto player = std::make_shared<Player>();

		player->SetTag("Player");

		auto& playerMeshRendererData = GetParameterFromJsonObject(playerSettings, "PlayerMeshRenderer", false, true);
		if (playerMeshRendererData == playerSettings)
		{
#ifdef _DEBUG
			Debug::LogWarning("[Player] No Player MeshRenderer set!");
#endif
		}
		else
		{
			auto playerMeshRenderer = MeshRenderer::Make(playerMeshRendererData);

			player->AddComponent(playerMeshRenderer);
		}

		auto& playerControllerScriptData = GetParameterFromJsonObject(playerSettings, "PlayerControllerScript", false, true);
		if (playerControllerScriptData == playerSettings)
		{
#ifdef _DEBUG
			Debug::LogWarning("[Player] No Player Controller Script set!");
#endif
		}
		else
		{
			auto playerControllerScript = ScriptFactory::instance().Make(playerControllerScriptData);

			player->AddComponent(playerControllerScript);
		}

		return player;
	}

} // Client
