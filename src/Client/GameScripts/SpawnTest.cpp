//
// Created by Tony on 29/06/2022.
//

#include "Client/GameScripts/SpawnTest.h"

#include "Client/GameScripts/Rotation.h"

void SpawnTest::Start()
{
	UUIDv4::UUID prefabUuid = UUIDv4::UUID::fromStrFactory(testPrefabUuid);

	auto prefab = RessourceManager::FindPrefab(prefabUuid);

	if (prefab)
	{
		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < y; j++)
			{
				auto newTest = prefab->InstantiateNew();

				newTest->SetPosition(glm::vec3(-((x - 1) / 2) + i * 1, 0.0, -((y - 1) / 2) + j * 1));

				auto rotation = newTest->GetScript<Rotation>();

				if (rotation)
				{
					if((i + j) % 2 == 0) rotation->SetIndice(1.0f);
					else rotation->SetIndice(-1.0f);
				}
			}
		}
	}
}

bool SpawnTest::s_isRegistered = ScriptFactory::instance().Register("SpawnTest", [](JsonObject& parameters) {
	auto script = std::make_shared<SpawnTest>();

	script->testPrefabUuid = GetParameterFromJsonObject(parameters, "TestPrefabUuid", script->testPrefabUuid);

	script->x = GetParameterFromJsonObject(parameters, "X", script->x);
	script->y = GetParameterFromJsonObject(parameters, "Y", script->y);

	return script;
});
