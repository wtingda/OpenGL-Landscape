#ifndef SHADER_H
#define SHADER_H
#endif

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtc/type_ptr.hpp"
#include <GL/glew.h>

class Shader {
public:
	Shader();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

	std::string ReadFile(const char* fileLocation);

	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
    GLuint GetViewLocation();

	void UseShader();
    
    void setInt(const std::string &name, int value) const;

    void setMat4(const std::string &name, const glm::mat4 &mat) const;

	void ClearShader();

	~Shader();

private:
	GLuint shaderID, uniformProjection, uniformModel, uniformView;

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};
