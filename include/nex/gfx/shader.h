#ifndef SHADER_H_INCLUDE
#define SHADER_H_INCLUDE

#include <GL/glew.h>

#include <string>
#include <map>

namespace nx
{

enum ShaderType
{
    None = 0,
    FragmentShader = 1,
    VertexShader = 2,
    GeometryShader = 3
};

class Shader
{
public:
    Shader();
    ~Shader();

    /**
     * @brief Compile a shader program from the given source.
     * @param source = The shader program source.
     * @param type = The type of shader to compiler.
     * @return the results of the compilation.
     */
    bool compileShader(const std::string& source, ShaderType type);

    /**
     * @brief Compile a shader program from the given file.
     * @param filePath = The path to the shader program.
     * @param type = The type of shader to compile.
     * @return the results of the compilation.
     */
    bool compileShaderFile(const std::string filePath, ShaderType type);

    /**
     * @brief Link all of the compiled shaders into a program.
     */
    void linkProgram();

    /**
     * @brief Add an attribute to the shader program.
     * @param attribute = The attribute to add.
     */
    void addAttribute(const std::string& attribute);

    /**
     * @brief Add a uniform to the shader program.
     * @param uniform = The unform to add.
     */
    void addUniform(const std::string& uniform);

    GLuint getAttribute(const std::string& attribute) { return mAttributes[attribute]; }

    GLuint getUniform(const std::string& uniform) { return mUniforms[uniform]; }

    /**
     * @brief Bind the shader program.
     */
    inline void bind() const { glUseProgram(mShaderProgram); }

    /**
     * @brief Unbind the shader program.
     */
    inline void unbind() const { glUseProgram(0); }

    /**
     * @brief Get the id of the compiled shader program.
     * @return the id of the program.
     */
    inline GLuint getProgram() const { return mShaderProgram; }

private:

    bool mHasVertexShader;
    bool mHasGeometryShader;
    bool mHasFragmentShader;

    GLuint mVertexShader;
    GLuint mGeometryShader;
    GLuint mFragmentShader;

    GLuint mShaderProgram;

    std::map<std::string, GLuint> mAttributes;
    std::map<std::string, GLuint> mUniforms;
};

} //namespace nx

#endif // SHADER_H_INCLUDE
