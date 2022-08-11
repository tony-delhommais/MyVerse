//
// Created by Tony on 01/08/2022.
//

#include "Core/Ressource/Shader.h"

namespace Core
{

	Shader::~Shader()
	{
		if (m_programId) glDeleteProgram(m_programId);

		if(m_vertexId) glDeleteShader(m_vertexId);
		if(m_fragmentId) glDeleteShader(m_fragmentId);
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

		if (p_shaderType == SupportedFileType::VERTEX_SHADER && !SetVertexShader(p_path)) return;

		if (p_shaderType == SupportedFileType::FRAGMENT_SHADER && !SetFragmentShader(p_path)) return;

		int success;
		char infoLog[512];

		if (m_vertexId && m_fragmentId)
		{
			m_programId = glCreateProgram();
			glAttachShader(m_programId, m_vertexId);
			glAttachShader(m_programId, m_fragmentId);
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

			glDeleteShader(m_vertexId);
			glDeleteShader(m_fragmentId);

			m_vertexId = 0;
			m_fragmentId = 0;
		}
	}

	bool Shader::IsShaderValid()
	{
		return m_programId;
	}

	void Shader::SetUniformInt(const std::string& p_locationName, int p_value)
	{
		GLint location = FindUniformLocation(p_locationName);

		SetUniformInt(location, p_value);
	}

	void Shader::SetUniformInt(const GLint p_locationId, int p_value)
	{
		if (!IsShaderValid()) return;

		if (p_locationId == -1) return;

		glUniform1i(p_locationId, p_value);
	}

	void Shader::SetUniformVec3(const std::string& p_locationName, const glm::vec3& p_value)
	{
		GLint location = FindUniformLocation(p_locationName);

		SetUniformVec3(location, p_value);
	}

	void Shader::SetUniformVec3(const GLint p_locationId, const glm::vec3& p_value)
	{
		if (!IsShaderValid()) return;

		if (p_locationId == -1) return;

		glUniform3fv(p_locationId, 1, glm::value_ptr(p_value));
	}

	void Shader::SetUniformMat4(const std::string& p_locationName, const glm::mat4& p_value)
	{
		GLint location = FindUniformLocation(p_locationName);

		SetUniformMat4(location, p_value);
	}

	void Shader::SetUniformMat4(const GLint p_locationId, const glm::mat4& p_value)
	{
		if (!IsShaderValid()) return;

		if (p_locationId == -1) return;

		glUniformMatrix4fv(p_locationId, 1, GL_FALSE, glm::value_ptr(p_value));
	}

	bool Shader::SetVertexShader(const std::filesystem::path& p_path)
	{
		int success;
		char infoLog[512];

		std::string vertexCode;
		std::ifstream vShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			vShaderFile.open(p_path.string());
			std::stringstream vShaderStream;

			vShaderStream << vShaderFile.rdbuf();

			vShaderFile.close();

			vertexCode = vShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
#ifdef _DEBUG
			Debug::LogError("Failed to read a vertex shader :\n" + std::string(infoLog));
#endif
			return false;
		}

		const char* vShaderCode = vertexCode.c_str();

		m_vertexId = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(m_vertexId, 1, &vShaderCode, NULL);
		glCompileShader(m_vertexId);

		glGetShaderiv(m_vertexId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(m_vertexId, 512, NULL, infoLog);
#ifdef _DEBUG
			Debug::LogError("Failed to compile a vertex shader :\n" + std::string(infoLog));
#endif
			glDeleteShader(m_vertexId);
			m_vertexId = 0;
			return false;
		}

		return true;
	}

	bool Shader::SetFragmentShader(const std::filesystem::path& p_path)
	{
		int success;
		char infoLog[512];

		std::string fragmentCode;
		std::ifstream fShaderFile;

		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			fShaderFile.open(p_path.string());
			std::stringstream fShaderStream;

			fShaderStream << fShaderFile.rdbuf();

			fShaderFile.close();

			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
#ifdef _DEBUG
			Debug::LogError("Failed to read a fragment shader :\n" + std::string(infoLog));
#endif
			return false;
		}

		const char* fShaderCode = fragmentCode.c_str();

		m_fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(m_fragmentId, 1, &fShaderCode, NULL);
		glCompileShader(m_fragmentId);

		glGetShaderiv(m_fragmentId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(m_fragmentId, 512, NULL, infoLog);
#ifdef _DEBUG
			Debug::LogError("Failed to compile a fragment shader :\n" + std::string(infoLog));
#endif
			glDeleteShader(m_fragmentId);
			m_fragmentId = 0;
			return false;
		}

		return true;
	}

} // Core
