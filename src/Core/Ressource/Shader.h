//
// Created by Tony on 01/08/2022.
//

#ifndef MYVERSE_SHADER_H
#define MYVERSE_SHADER_H

#include "Core/Utils/Utils.h"
#include "Core/Utils/MathUtils.h"
#include "Core/Utils/GraphicsUtils.h"
#include "Core/Utils/SupportedFileType.h"

#ifdef _DEBUG
#include "Core/Common/Debug.h"
#endif

namespace Core
{

	class Shader
	{
	public:
		Shader() = default;
		~Shader();

	public:
		void Use();

	private:
		GLint FindUniformLinkId(const std::string& p_locationName);

	public:
		void SetShader(SupportedFileType p_shaderType, const std::filesystem::path& p_path);

		bool IsShaderValid();

		void SetUniformInt(const std::string& p_locationName, int p_value);
		void SetUniformVec3(const std::string& p_locationName, const glm::vec3& p_value);
		void SetUniformMat4(const std::string& p_locationName, const glm::mat4& p_value);

	private:
		bool SetVertexShader(const std::filesystem::path& p_path);
		bool SetFragmentShader(const std::filesystem::path& p_path);

	private:
		GLuint m_programId = 0;

		GLuint m_vertexId = 0;
		GLuint m_fragmentId = 0;

		std::map<std::string, GLint> m_uniformLink;
	};

} // Core

#endif // MYVERSE_SHADER_H
