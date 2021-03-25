#pragma once

#include <string>
#include <glad/glad.h>

class GLSLProgram
{
private:
	GLuint programID;
	GLuint vertexShaderID;
	GLuint geometryShaderID;
	GLuint fragmentShaderID;
	int numAttributes;

public:
	GLSLProgram();
	~GLSLProgram();

	void CompileShaders(
		const std::string& vertexShaderFilePath,
		const std::string& geometryShaderFilePath,
		const std::string& fragmentShaderFilePath
	);

	void LinkShaders();

	void AddAttribute(const std::string& attributeName);

	void Use();

	void UnUse();

	GLint GetUniformLocation(const std::string& name);

private:
	void compileShader(const std::string& filePath, GLuint shaderID);
};