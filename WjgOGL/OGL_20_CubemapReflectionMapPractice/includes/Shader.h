#ifndef SHADER_H
#define SHADER_H

#include "glad\glad.h"
#include "glm\glm.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	//����ID
	unsigned int ID;

	//������ɫ��
	Shader(const GLchar* vertexPath,const GLchar* fragmentPath);

	//������ɫ������
	void use();

	//uniform���ߺ���
	void setBool(const std::string &name,bool value) const;
	void setInt(const std::string &name,int value) const;
	void setFloat(const std::string &name,float value) const;
	void setVec2(const std::string &name, const glm::vec2 &value) const;
	void setVec2(const std::string &name, float x, float y) const;
	void setVec3(const std::string &name, const glm::vec3 &value) const;
	void setVec3(const std::string &name, float x, float y, float z) const;
	void setVec4(const std::string &name, const glm::vec4 &value) const;
	void setVec4(const std::string &name, float x, float y, float z, float w) const;
	void setMat2(const std::string &name, const glm::mat2 &mat) const;
	void setMat3(const std::string &name, const glm::mat3 &mat) const;
	void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
	void checkCompileErrors(unsigned int shader, std::string type);

};

inline Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	// 1. ���ļ�·���л�ȡ����/Ƭ����ɫ��
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ��֤ifstream��������׳��쳣��
	vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	try 
	{
		// ���ļ�
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		// ��ȡ�ļ��Ļ������ݵ���������
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		// �ر��ļ�������
		vShaderFile.close();
		fShaderFile.close();

		// ת����������string
		vertexCode   = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char * fShaderCode = fragmentCode.c_str();

	// 2. ����shader
	unsigned int vertex, fragment;
	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");
	// fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");
	// shader Program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	// ��ӡ���Ӵ�������еĻ���
	checkCompileErrors(ID, "PROGRAM");

	// ɾ����ɫ���������Ѿ����ӵ����ǵĳ������ˣ��Ѿ�������Ҫ��
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

inline void Shader::use()
{
	glUseProgram(ID);
}

inline void Shader::setBool(const std::string & name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}

inline void Shader::setInt(const std::string & name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}

inline void Shader::setFloat(const std::string & name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
}

inline void Shader::setVec2(const std::string & name, const glm::vec2 & value) const
{
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
}

inline void Shader::setVec2(const std::string & name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y); 
}

inline void Shader::setVec3(const std::string & name, const glm::vec3 & value) const
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
}

inline void Shader::setVec3(const std::string & name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); 
}

inline void Shader::setVec4(const std::string & name, const glm::vec4 & value) const
{
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
}

inline void Shader::setVec4(const std::string & name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w); 
}

inline void Shader::setMat2(const std::string & name, const glm::mat2 & mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

inline void Shader::setMat3(const std::string & name, const glm::mat3 & mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

inline void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}


#endif // !SHADER_H