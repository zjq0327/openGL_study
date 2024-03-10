#include"Shader.h"

static std::string ReadFile(const char* path)
{
    std::ifstream ifs(path);
    std::string shader;
    std::string line;
    while (std::getline(ifs, line))
    {
        shader += line;
        shader += '\n';
    }
    ifs.close();

    return shader;
}

static void CreateShader(GLuint shader, const char* path)
{

    std::string fragmentShaderCode = ReadFile(path);
    const char* fragmentShaderSource = fragmentShaderCode.c_str();

    glShaderSource(shader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(shader);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    m_shaderProgram = glCreateProgram();

    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    CreateShader(vertex, vertexPath);

    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    CreateShader(fragment, fragmentPath);

    glAttachShader(m_shaderProgram, vertex);
    glAttachShader(m_shaderProgram, fragment);
    glLinkProgram(m_shaderProgram);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader()
{
    glDeleteProgram(m_shaderProgram);
}

void Shader::Use() const
{
    glUseProgram(m_shaderProgram);
}

GLuint Shader::ShaderProgram()const
{
    return m_shaderProgram;
}

GLint Shader::GetUniformLoction(const std::string& name)
{
    if (m_LocationMap.find(name) != m_LocationMap.end())
    {
        return m_LocationMap[name];
    }
    GLint location = glGetUniformLocation(m_shaderProgram, name.c_str());

    m_LocationMap[name] = location;

    return location;
}


void Shader::SetUniform4f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
    GLint location = GetUniformLoction(name);

    glUniform4f(location, v0, v1, v2, v3);

}

void Shader::SetUniform3f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2)
{
    GLint location = GetUniformLoction(name);

    glUniform3f(location, v0, v1, v2);
}

void Shader::SetUniform1i(const std::string& name, GLint v0)
{
    GLint location = GetUniformLoction(name);

    glUniform1i(location, v0);
}

void Shader::SetUniform1f(const std::string& name, GLfloat v0)
{
    GLint location = GetUniformLoction(name);

    glUniform1f(location, v0);
}

void Shader::SetUniformMatrix4f(const std::string& name, const glm::mat4& trans)
{
    GLint location = GetUniformLoction(name);

    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(trans));
}



