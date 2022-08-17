//
// Created by Tony on 01/08/2022.
//

#ifndef MYVERSE_SHADER_H
#define MYVERSE_SHADER_H

#include "Client/Utils/Utils.h"
#include "Client/Utils/MathUtils.h"
#include "Client/Utils/GraphicsUtils.h"
#include "Client/Utils/SupportedFileType.h"

#ifdef _DEBUG
#include "Client/Common/Debug.h"
#endif

namespace Client
{

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

		void SetUniformInt(const std::string& p_locationName, int p_value);
		void SetUniformInt(const GLint p_locationId, int p_value);

		void SetUniformVec3(const std::string& p_locationName, const glm::vec3& p_value);
		void SetUniformVec3(const GLint p_locationId, const glm::vec3& p_value);

		void SetUniformMat4(const std::string& p_locationName, const glm::mat4& p_value);
		void SetUniformMat4(const GLint p_locationId, const glm::mat4& p_value);

	private:
		bool SetVertexShader(const std::filesystem::path& p_path);
		bool SetFragmentShader(const std::filesystem::path& p_path);

	private:
		GLuint m_programId = 0;

		GLuint m_vertexId = 0;
		GLuint m_fragmentId = 0;

		std::map<std::string, GLint> m_uniformLink;
	};

} // Client

#endif // MYVERSE_SHADER_H
