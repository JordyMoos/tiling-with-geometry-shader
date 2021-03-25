#include "GLSLProgram.h"
#include "Error.h"
#include <fstream>
#include <vector>

GLSLProgram::GLSLProgram()
	: programID(0), vertexShaderID(0), fragmentShaderID(0)
	, numAttributes(0)
{
}

GLSLProgram::~GLSLProgram()
{
	if (programID != 0)
	{
		glDeleteProgram(programID);
	}

	if (vertexShaderID != 0)
	{
		glDeleteShader(vertexShaderID);
	}

	if (fragmentShaderID != 0)
	{
		glDeleteShader(fragmentShaderID);
	}
}

void GLSLProgram::CompileShaders(const std::string& vertexShaderFilePath, const std::string& geometryShaderFilePath, const std::string& fragmentShaderFilePath)
{
	programID = glCreateProgram();

	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (vertexShaderID == 0)
	{
		Fatal("could not create Vertex shader");
	}

	geometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);
	if (geometryShaderID == 0)
	{
		Fatal("could not create Geometry shader");
	}

	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (fragmentShaderID == 0)
	{
		Fatal("could not create Fragment shader");
	}

	compileShader(vertexShaderFilePath, vertexShaderID);
	compileShader(geometryShaderFilePath, geometryShaderID);
	compileShader(fragmentShaderFilePath, fragmentShaderID);
}

void GLSLProgram::LinkShaders()
{
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	GLint isLinked = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> errorLog(maxLength);
		glGetProgramInfoLog(programID, maxLength, &maxLength, &errorLog[0]);

		glDeleteProgram(programID);
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);

		std::printf("%s\n", &(errorLog[0]));
		Fatal("Shader program failed to link");
	}

	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);

	glDeleteShader(vertexShaderID);
	vertexShaderID = 0;
	glDeleteShader(fragmentShaderID);
	fragmentShaderID = 0;
}

void GLSLProgram::AddAttribute(const std::string& attributeName)
{
	glBindAttribLocation(programID, numAttributes, attributeName.c_str());
	numAttributes++;
}

void GLSLProgram::Use()
{
	glUseProgram(programID);
	for (int i = 0; i < numAttributes; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void GLSLProgram::UnUse()
{
	for (int i = 0; i < numAttributes; i++)
	{
		glDisableVertexAttribArray(i);
	}
	glUseProgram(0);
}

GLint GLSLProgram::GetUniformLocation(const std::string& name)
{
	GLint location = glGetUniformLocation(programID, name.c_str());
	if (location == GL_INVALID_INDEX)
	{
		Fatal("Uniform " + name + " not found in shader");
	}

	return location;
}

void GLSLProgram::compileShader(const std::string& filePath, GLuint shaderID)
{
	std::ifstream shaderFile(filePath);
	if (shaderFile.fail())
	{
		perror(filePath.c_str());
		Fatal("Failed to open " + filePath);
	}

	std::string fileContents = "";
	std::string line;
	while (std::getline(shaderFile, line))
	{
		fileContents += line + "\n";
	}
	shaderFile.close();

	const char* contentsPtr = fileContents.c_str();
	glShaderSource(shaderID, 1, &contentsPtr, nullptr);
	glCompileShader(shaderID);

	GLint isCompiled = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);

		glDeleteShader(shaderID);

		std::printf("%s\n", &(errorLog[0]));
		Fatal("Shader " + filePath + " failed to compile");
	}
}