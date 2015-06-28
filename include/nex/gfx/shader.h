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

    GLuint getAttribute(const std::string& attribute) { return m_attributes[attribute]; }

    GLuint getUniform(const std::string& uniform) { return m_uniforms[uniform]; }

    /**
     * @brief Bind the shader program.
     */
    inline void bind() const { glUseProgram(m_shaderProgram); }

    /**
     * @brief Unbind the shader program.
     */
    inline void unbind() const { glUseProgram(0); }

    /**
     * @brief Get the id of the compiled shader program.
     * @return the id of the program.
     */
    inline GLuint getProgram() const { return m_shaderProgram; }

private:

    bool m_hasVertexShader;
    bool m_hasGeometryShader;
    bool m_hasFragmentShader;

    GLuint m_vertexShader;
    GLuint m_geometryShader;
    GLuint m_fragmentShader;

    GLuint m_shaderProgram;

    std::map<std::string, GLuint> m_attributes;
    std::map<std::string, GLuint> m_uniforms;
};

} //namespace nx

#endif // SHADER_H_INCLUDE
