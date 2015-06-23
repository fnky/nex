#include <nex/gfx/shader.h>

// Standard includes.
#include <fstream>
#include <sstream>
#include <iostream>

namespace nx
{

Shader::Shader() :
    mHasVertexShader(false),
    mHasGeometryShader(false),
    mHasFragmentShader(false),
    mShaderProgram(0),
    mVertexShader(0),
    mGeometryShader(0),
    mFragmentShader(0)
{ }

Shader::~Shader()
{
    if (mShaderProgram > 0) {
        glDeleteProgram(mShaderProgram);
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
        mVertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(mVertexShader, 1, &sourceCStr, NULL);
        glCompileShader(mVertexShader);
        mHasVertexShader = true;
        temp = mVertexShader;
    }
    else if (type == GeometryShader) {
        // Create and compile the geometry shader
        mGeometryShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(mGeometryShader, 1, &sourceCStr, NULL);
        glCompileShader(mGeometryShader);
        mHasGeometryShader = true;
        temp = mGeometryShader;
    }
    else if (type == FragmentShader) {
        // Create and compile the fragment shader.
        mFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(mFragmentShader, 1, &sourceCStr, NULL);
        glCompileShader(mFragmentShader);
        mHasFragmentShader = true;
        temp = mFragmentShader;
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
    mShaderProgram = glCreateProgram();

    if (mHasVertexShader)
        glAttachShader(mShaderProgram, mVertexShader);

    if (mHasGeometryShader)
        glAttachShader(mShaderProgram, mGeometryShader);

    if (mHasFragmentShader)
        glAttachShader(mShaderProgram, mFragmentShader);
    //glBindFragDataLocation(mShaderProgram, 0, "outColor");
    glLinkProgram(mShaderProgram);
}

void Shader::addAttribute(const std::string& attribute)
{
    mAttributes[attribute] = glGetAttribLocation(mShaderProgram, attribute.c_str());
}

void Shader::addUniform(const std::string& uniform)
{
    mUniforms[uniform] = glGetUniformLocation(mShaderProgram, uniform.c_str());
}

} //namespace nx
