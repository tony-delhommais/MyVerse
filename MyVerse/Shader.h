//
// Created by Tony on 01/08/2022.
//

#ifndef MYVERSE_SHADER_H
#define MYVERSE_SHADER_H

#include "Utils.h"
#include "MathUtils.h"
#include "GraphicsUtils.h"
#include "SupportedFileType.h"

#ifdef _DEBUG
#include "Debug.h"
#endif

namespace Client
{

	typedef enum {
		POSITION,
		NORMAL,
		TANGENT,
		BITANGENT,
		COLOR,
		TEXCOORD0,
		TEXCOORD1,
		TEXCOORD2,
		TEXCOORD3,
		NB_ATTRIBUTES
	} EnumAttrib;

	const std::string attribNames[EnumAttrib::NB_ATTRIBUTES] = {
		"in_position",
		"in_normal",
		"in_tangent",
		"in_bitangent",
		"in_color",
		"in_texcoord0",
		"in_texcoord1",
		"in_texcoord2",
		"in_texcoord3"
	};

	typedef enum {
		TEXTURE_INVERSION_VALUE,
		USE_SOLID_COLOR,
		SOLID_COLOR,
		NB_UNIFORM_USER
	} EnumUser;

	const std::string uniformUserNames[EnumUser::NB_UNIFORM_USER] = {
		"textureInversionValue",
		"useSolidColor",
		"solidColor"
	};

	typedef enum {
		PROJECTION_MATRIX,
		VIEW_MATRIX,
		MODEL_MATRIX,
		NORMAL_MATRIX,
		VIEWPROJECTION_MATRIX,
		MODELVIEW_MATRIX,
		MODELVIEWPROJECTION_MATRIX,
		NB_UNIFORM_MATRIX
	} EnumMatrix;

	const std::string uniformMatrixNames[EnumMatrix::NB_UNIFORM_MATRIX] = {
		"projectionMatrix",
		"viewMatrix",
		"modelMatrix",
		"normalMatrix",
		"viewProjectionMatrix",
		"modelViewMatrix",
		"modelViewProjectionMatrix"
	};

	typedef enum {
		TEXTURE0,
		TEXTURE1,
		TEXTURE2,
		TEXTURE3,
		TEXTURE4,
		TEXTURE5,
		TEXTURE6,
		TEXTURE7,
		TEXTURE8,
		TEXTURE9,
		TEXTURE10,
		TEXTURE11,
		NB_UNIFORM_TEXTURE
	} EnumTexture;

	const std::string uniformTextureNames[EnumTexture::NB_UNIFORM_TEXTURE] = {
		"texture0",
		"texture1",
		"texture2",
		"texture3",
		"texture4",
		"texture5",
		"texture6",
		"texture7",
		"texture8",
		"texture9",
		"texture10",
		"texture11"
	};

	class Shader
	{
	public:
		Shader() = default;
		~Shader();

	public:
		void Use();

		GLint FindUniformLocation(const std::string& p_locationName);

	public:
		void SetShader(SupportedFileType p_shaderType, const std::filesystem::path& p_path);

		bool IsShaderValid();

		bool HasUserUniform(EnumUser p_uniformID);
		void SetUserUniform(EnumUser p_uniformId, bool p_value);
		void SetUserUniform(EnumUser p_uniformId, int p_value);
		void SetUserUniform(EnumUser p_uniformId, glm::vec3 p_value);

		bool HasMatrixUniform(EnumMatrix p_uniformID);
		void SetMatrixUniform(EnumMatrix p_uniformID, glm::mat4 p_matrix);
		void SetMatrixUniform(EnumMatrix p_uniformID, glm::mat3 p_matrix);

	private:
		GLuint CompileShader(GLenum p_shaderType, const std::filesystem::path& p_path);

	private:
		GLuint m_programId = 0;

		GLuint m_vertexId = 0;
		GLuint m_fragmentId = 0;

		std::map<std::string, GLint> m_uniformLink;

		GLint m_userUniforms[EnumUser::NB_UNIFORM_USER];
		GLint m_matrixUniforms[EnumMatrix::NB_UNIFORM_MATRIX];
		GLint m_textureUniforms[EnumTexture::NB_UNIFORM_TEXTURE];
	};

} // Client

#endif // MYVERSE_SHADER_H
