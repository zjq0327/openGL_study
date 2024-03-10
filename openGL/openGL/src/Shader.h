#include"glad/glad.h"
#include"glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();
	void Use() const;
	GLuint ShaderProgram()const;

	void SetUniform4f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
	void SetUniform3f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2);
	void SetUniform1i(const std::string& name, GLint v0);
	void SetUniform1f(const std::string& name, GLfloat v0);
	void SetUniformMatrix4f(const std::string& name, const glm::mat4& trans);
	//void SetMVP(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);


private:
	GLint GetUniformLoction(const std::string& name);


private:
	GLuint m_shaderProgram;
	std::unordered_map<std::string, GLint> m_LocationMap;
};