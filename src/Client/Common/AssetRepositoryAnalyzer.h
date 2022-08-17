//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_ASSET_REPOSITORY_ANALYZER_H
#define MYVERSE_ASSET_REPOSITORY_ANALYZER_H

#include "Client/Utils/Utils.h"
#include "Client/Utils/JsonUtils.h"
#include "Client/Utils/SupportedFileType.h"

#ifdef _DEBUG
#include "Client/Common/Debug.h"
#endif

namespace Core
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

} // Core

#endif // MYVERSE_ASSET_REPOSITORY_ANALYZER_H
