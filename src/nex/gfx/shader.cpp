#include <nex/gfx/shader.h>

// Standard includes.
#include <fstream>
#include <sstream>
#include <iostream>

namespace nx
{

Shader::Shader() :
    m_hasVertexShader(false),
    m_hasGeometryShader(false),
    m_hasFragmentShader(false),
    m_shaderProgram(0),
    m_vertexShader(0),
    m_geometryShader(0),
    m_fragmentShader(0)
{ }

Shader::~Shader()
{
    if (m_shaderProgram > 0) {
        glDeleteProgram(m_shaderProgram);
    }
}

bool Shader::compileShaderFile(const std::string filePath, ShaderType type)
{
    std::ifstream fileStream(filePath);
    std::stringstream buffer;

    if (!fileStream.is_open())
        return false;

    buffer << fileStream.rdbuf();

    return compileShader(buffer.str(), type);
}

bool Shader::compileShader(const std::string& source, ShaderType type)
{
    // Only holds the id of the current shader.
    GLuint temp = 0;

    const char *sourceCStr = source.c_str();

    if (type == VertexShader) {
        // Create and compile the vertex shader
        m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(m_vertexShader, 1, &sourceCStr, NULL);
        glCompileShader(m_vertexShader);
        m_hasVertexShader = true;
        temp = m_vertexShader;
    }
    else if (type == GeometryShader) {
        // Create and compile the geometry shader
        m_geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(m_geometryShader, 1, &sourceCStr, NULL);
        glCompileShader(m_geometryShader);
        m_hasGeometryShader = true;
        temp = m_geometryShader;
    }
    else if (type == FragmentShader) {
        // Create and compile the fragment shader.
        m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(m_fragmentShader, 1, &sourceCStr, NULL);
        glCompileShader(m_fragmentShader);
        m_hasFragmentShader = true;
        temp = m_fragmentShader;
    }

    // Check the compile results.
    GLint status;
    glGetShaderiv(temp, GL_COMPILE_STATUS, &status);

    if (status == GL_FALSE) {

        char buffer[512];
        glGetShaderInfoLog(temp, 512, NULL, buffer);
        std::cout << (std::string("Failed to compile shader: ").append(std::string(buffer)));
    }

    return status == GL_TRUE;
}

void Shader::linkProgram()
{
    // Link the vertex and fragment shader into a shader program
    m_shaderProgram = glCreateProgram();

    if (m_hasVertexShader)
        glAttachShader(m_shaderProgram, m_vertexShader);

    if (m_hasGeometryShader)
        glAttachShader(m_shaderProgram, m_geometryShader);

    if (m_hasFragmentShader)
        glAttachShader(m_shaderProgram, m_fragmentShader);
    //glBindFragDataLocation(mShaderProgram, 0, "outColor");
    glLinkProgram(m_shaderProgram);
}

void Shader::addAttribute(const std::string& attribute)
{
    m_attributes[attribute] = glGetAttribLocation(m_shaderProgram, attribute.c_str());
}

void Shader::addUniform(const std::string& uniform)
{
    m_uniforms[uniform] = glGetUniformLocation(m_shaderProgram, uniform.c_str());
}

} //namespace nx
