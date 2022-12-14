//
// Created by Tony on 29/06/2022.
//

#include "AssetRepositoryAnalyzer.h"

#include "RessourceManagerCore.h"

namespace Client
{

	void AssetRepositoryAnalyzer::GenerateMetaFilesOnAssetsFolder(const std::filesystem::path& p_assetsFolder)
	{
		std::map<std::string, SupportedFileType> supportedFiles = {
			{".scene", SupportedFileType::SCENE},
			{".obj", SupportedFileType::MESH},
			{".bmp", SupportedFileType::TEXTURE},
			{".BMP", SupportedFileType::TEXTURE},
			{".mat", SupportedFileType::MATERIAL},
			{".prefab", SupportedFileType::PREFAB},
			{".vert", SupportedFileType::VERTEX_SHADER},
			{".frag", SupportedFileType::FRAGMENT_SHADER},
			{".json", SupportedFileType::DATA},
			{".xml", SupportedFileType::DATA},
			{".chunk", SupportedFileType::CHUNK},
			{".terrain", SupportedFileType::TERRAIN},
		};

		std::random_device rd;
		auto seed_data = std::array<int, std::mt19937::state_size> {};
		std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
		std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
		std::mt19937 generator(seq);
		uuids::uuid_random_generator generateRandomUuid{ generator };

		std::string test = uuids::to_string(generateRandomUuid());

		int newFiles = 0;
		for (const auto& entry : std::filesystem::recursive_directory_iterator(p_assetsFolder))
		{
			if (entry.path().extension() == ".meta") continue;

			std::string metaFile = entry.path().string() + ".meta";

			if (std::filesystem::exists(metaFile)) continue;

			JsonObject metaJson;

			////////////////////////////////////  FILE TYPE  ////////////////////////////////////
			metaJson["Type"] = (int)SupportedFileType::DIRECTORY;
			if (!entry.is_directory())
			{
				SupportedFileType fileType = supportedFiles[entry.path().extension().string()];

				metaJson["Type"] = (
				fileType >= SupportedFileType::UNKNOWN && fileType < SupportedFileType::MAX_VALUE ?
				(int)fileType : (int)SupportedFileType::UNKNOWN);
			}
			////////////////////////////////////  FILE TYPE  ////////////////////////////////////


			////////////////////////////////////  FILE IS ALWAYS LOADED  ////////////////////////////////////
			metaJson["AlwaysLoaded"] = false;

			if (metaJson["Type"] == (int)SupportedFileType::PREFAB ||
				metaJson["Type"] == (int)SupportedFileType::VERTEX_SHADER ||
				metaJson["Type"] == (int)SupportedFileType::FRAGMENT_SHADER ||
				metaJson["Type"] == (int)SupportedFileType::TERRAIN
				) metaJson["AlwaysLoaded"] = true;
			////////////////////////////////////  FILE IS ALWAYS LOADED  ////////////////////////////////////


			////////////////////////////////////  FILE UUID  ////////////////////////////////////
			metaJson["Uuid"] = uuids::to_string(generateRandomUuid());
			////////////////////////////////////  FILE UUID  ////////////////////////////////////


			////////////////////////////////////  FILE IS OF TYPE VERTEX_SHADER OR FRAGMENT_SHADER  ////////////////////////////////////
			if (metaJson["Type"] == (int)SupportedFileType::VERTEX_SHADER || metaJson["Type"] == (int)SupportedFileType::FRAGMENT_SHADER)
			{
				std::string co_shader_meta_extention = (metaJson["Type"] == (int)SupportedFileType::VERTEX_SHADER ? ".frag.meta" : ".vert.meta");
				std::string co_shader_meta_path = entry.path().parent_path().string() + "/" + entry.path().stem().string() + co_shader_meta_extention;

				std::filesystem::path co_shader(co_shader_meta_path);

				JsonObject co_shader_meta = LoadJsonFile(co_shader);
				if (co_shader_meta.empty())
				{
					metaJson["Settings"]["ShaderUuid"] = uuids::to_string(generateRandomUuid());
				}
				else
				{
					metaJson["Settings"]["ShaderUuid"] = co_shader_meta["Settings"]["ShaderUuid"];
				}
			}
			////////////////////////////////////  FILE IS OF TYPE VERTEX_SHADER OR FRAGMENT_SHADER  ////////////////////////////////////

			std::fstream newMetaFile;
			newMetaFile.open(metaFile, std::ios::out);

			newMetaFile << metaJson.dump(2);

			newMetaFile.close();

			newFiles++;
		}

#ifdef _DEBUG
		Debug::LogInfo("[AssetRepositoryAnalyzer] " + std::to_string(newFiles) + " new files can be readed by the engine");
#endif
	}

	void AssetRepositoryAnalyzer::PreloadAssetsFiles(const std::filesystem::path& p_assetsFolder)
	{
		for (const auto& entry : std::filesystem::recursive_directory_iterator(p_assetsFolder))
		{
			RessourceManagerCore::instance().PreloadRessource(entry.path());
		}
	}

} // Client
