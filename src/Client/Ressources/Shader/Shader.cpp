//
// Created by Tony on 01/08/2022.
//

#include "Client/Ressources/Shader/Shader.h"

namespace Client
{

	Shader::~Shader()
	{
		if (m_programId) glDeleteProgram(m_programId);

		m_programId = 0;

		if(m_vertexId) glDeleteShader(m_vertexId);
		if(m_fragmentId) glDeleteShader(m_fragmentId);

		m_vertexId = 0;
		m_fragmentId = 0;
	}

	void Shader::Use()
	{
		if(m_programId) glUseProgram(m_programId);
	}

	GLint Shader::FindUniformLocation(const std::string& p_locationName)
	{
		if (!IsShaderValid()) return -1;

		GLint location = -1;

		auto findResult = m_uniformLink.find(p_locationName);
		if (findResult == m_uniformLink.end())
		{
			location = glGetUniformLocation(m_programId, p_locationName.c_str());

			if (location == -1) return -1;

			m_uniformLink.insert(std::map<std::string, GLint>::value_type(p_locationName, location));
		}
		else
		{
			location = findResult->second;
		}

		return location;
	}

	void Shader::SetShader(SupportedFileType p_shaderType, const std::filesystem::path& p_path)
	{
		if (IsShaderValid()) return;

		if (p_shaderType == SupportedFileType::VERTEX_SHADER)
		{
			m_vertexId = CompileShader(GL_VERTEX_SHADER, p_path);

			if (m_vertexId == 0)
				return;
		}

		if (p_shaderType == SupportedFileType::FRAGMENT_SHADER)
		{
			m_fragmentId = CompileShader(GL_FRAGMENT_SHADER, p_path);

			if (m_fragmentId == 0)
				return;
		}

		if (!m_vertexId || !m_fragmentId)
			return;

		int success;
		char infoLog[512];

		m_programId = glCreateProgram();
		glAttachShader(m_programId, m_vertexId);
		glAttachShader(m_programId, m_fragmentId);

		for (int i = 0; i < EnumAttrib::NB_ATTRIBUTES; i++)
		{
			glBindAttribLocation(m_programId, i, attribNames[i].c_str());
		}

		glLinkProgram(m_programId);
			
		glGetProgramiv(m_programId, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(m_programId, 512, NULL, infoLog);
#ifdef _DEBUG
			Debug::LogError("Linking of shaders to program failed :\n" + std::string(infoLog));
#endif
			glDeleteProgram(m_programId);
			m_programId = 0;
			return;
		}

		for (int i = 0; i < EnumUser::NB_UNIFORM_USER; i++)
		{
			m_userUniforms[i] = glGetUniformLocation(m_programId, uniformUserNames[i].c_str());
		}

		for (int i = 0; i < EnumMatrix::NB_UNIFORM_MATRIX; i++)
		{
			m_matrixUniforms[i] = glGetUniformLocation(m_programId, uniformMatrixNames[i].c_str());
		}

		for (int i = 0; i < EnumTexture::NB_UNIFORM_TEXTURE; i++)
		{
			m_textureUniforms[i] = glGetUniformLocation(m_programId, uniformTextureNames[i].c_str());

			if (m_textureUniforms[i] != -1)
				glUniform1i(m_textureUniforms[i], i);
		}
	}

	bool Shader::IsShaderValid()
	{
		return m_programId != 0;
	}

	bool Shader::HasUserUniform(EnumUser p_uniformID)
	{
		if (!IsShaderValid() || p_uniformID < 0 || p_uniformID >= EnumUser::NB_UNIFORM_USER)
			return false;

		if (m_userUniforms[p_uniformID] == -1)
			return false;

		return true;
	}

	void Shader::SetUserUniform(EnumUser p_uniformId, bool p_value)
	{
		if (!HasUserUniform(p_uniformId))
			return;

		glUniform1i(m_userUniforms[p_uniformId], p_value);
	}

	void Shader::SetUserUniform(EnumUser p_uniformId, int p_value)
	{
		if (!HasUserUniform(p_uniformId))
			return;

		glUniform1i(m_userUniforms[p_uniformId], p_value);
	}

	void Shader::SetUserUniform(EnumUser p_uniformId, glm::vec3 p_value)
	{
		if (!HasUserUniform(p_uniformId))
			return;

		glUniform3fv(m_userUniforms[p_uniformId], 1, glm::value_ptr(p_value));
	}

	bool Shader::HasMatrixUniform(EnumMatrix p_uniformID)
	{
		if (!IsShaderValid() || p_uniformID < 0 || p_uniformID >= EnumMatrix::NB_UNIFORM_MATRIX)
			return false;

		if (m_matrixUniforms[p_uniformID] == -1)
			return false;

		return true;
	}

	void Shader::SetMatrixUniform(EnumMatrix p_uniformID, glm::mat4 p_matrix)
	{
		if (!HasMatrixUniform(p_uniformID))
			return;

		glUniformMatrix4fv(m_matrixUniforms[p_uniformID], 1, GL_FALSE, &p_matrix[0][0]);
	}

	void Shader::SetMatrixUniform(EnumMatrix p_uniformID, glm::mat3 p_matrix)
	{
		if (!HasMatrixUniform(p_uniformID))
			return;

		glUniformMatrix3fv(m_matrixUniforms[p_uniformID], 1, GL_FALSE, &p_matrix[0][0]);
	}

	GLuint Shader::CompileShader(GLenum p_shaderType, const std::filesystem::path& p_path)
	{
		int success;
		char infoLog[512];

		std::string code;
		std::ifstream shaderFile;

		shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			shaderFile.open(p_path.string());
			std::stringstream shaderStream;

			shaderStream << shaderFile.rdbuf();

			shaderFile.close();

			code = shaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
#ifdef _DEBUG
			Debug::LogError("Failed to read a shader :\n" + std::string(infoLog));
#endif
			return 0;
		}

		const char* shaderCode = code.c_str();
		GLuint shaderId;
		shaderId = glCreateShader(p_shaderType);
		glShaderSource(shaderId, 1, &shaderCode, NULL);
		glCompileShader(shaderId);

		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
#ifdef _DEBUG
			Debug::LogError("Failed to compile a shader :\n" + std::string(infoLog));
#endif
			glDeleteShader(shaderId);
			return 0;
		}

		return shaderId;
	}

} // Client
