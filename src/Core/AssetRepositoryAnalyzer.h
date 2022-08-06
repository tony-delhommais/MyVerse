//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_ASSET_REPOSITORY_ANALYZER_H
#define MYVERSE_ASSET_REPOSITORY_ANALYZER_H

#include "Core/Utils/Utils.h"
#include "Core/Utils/JsonUtils.h"
#include "Core/Utils/SupportedFileType.h"

#ifdef _DEBUG
#include "Core/Debug.h"
#endif

namespace Core
{

	class AssetRepositoryAnalyzer
	{
	private:
		AssetRepositoryAnalyzer() = default;
		~AssetRepositoryAnalyzer() = default;

	public:
		static void GenerateMetaFilesOnAssetsFolder(const std::string& p_assetsFolder);

		static void PreloadAssetsFiles(const std::string& p_assetsFolder);
	};

} // Core

#endif // MYVERSE_ASSET_REPOSITORY_ANALYZER_H