//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_ASSET_REPOSITORY_ANALYZER_H
#define MYVERSE_ASSET_REPOSITORY_ANALYZER_H

#include "Utils.h"
#include "JsonUtils.h"
#include "SupportedFileType.h"

#ifdef _DEBUG
#include "Debug.h"
#endif

namespace Client
{

	class AssetRepositoryAnalyzer
	{
	private:
		AssetRepositoryAnalyzer() = default;
		~AssetRepositoryAnalyzer() = default;

	public:
		static void GenerateMetaFilesOnAssetsFolder(const std::filesystem::path& p_assetsFolder);

		static void PreloadAssetsFiles(const std::filesystem::path& p_assetsFolder);
	};

} // Client

#endif // MYVERSE_ASSET_REPOSITORY_ANALYZER_H
