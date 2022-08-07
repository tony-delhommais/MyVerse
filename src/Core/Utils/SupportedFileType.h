//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_SUPPORTED_FILE_TYPE_H
#define MYVERSE_SUPPORTED_FILE_TYPE_H

namespace Core
{

	enum SupportedFileType
	{
		UNKNOWN,
		DIRECTORY,
		SCENE,
		MESH,
		TEXTURE,
		MATERIAL,
		PREFAB,
		SHADER,
		VERTEX_SHADER,
		FRAGMENT_SHADER,
		DATA,
		CHUNK,
		TERRAIN,
		MAX_VALUE
	};

} // Core

#endif // MYVERSE_SUPPORTED_FILE_TYPE_H
