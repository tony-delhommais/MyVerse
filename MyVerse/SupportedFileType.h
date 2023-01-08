//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_SUPPORTED_FILE_TYPE_H
#define MYVERSE_SUPPORTED_FILE_TYPE_H

namespace Client
{

	enum SupportedFileType
	{
		UNKNOWN,
		DIRECTORY,
		SCENE, //todo remove
		MESH,
		TEXTURE,
		MATERIAL,
		PREFAB,
		VERTEX_SHADER,
		FRAGMENT_SHADER,
		DATA,
		CHUNK,
		TERRAIN,
		MAX_VALUE
	};

} // Client

#endif // MYVERSE_SUPPORTED_FILE_TYPE_H
