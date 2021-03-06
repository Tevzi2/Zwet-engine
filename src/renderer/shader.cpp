#include <shader.h>

namespace ZWET
{
    Shader::Shader(std::vector<ShaderData> settings)
        : settings(settings)
    {
        if(!createShader())
            ZWET_ERROR("Shader didn't properly compile");
    }

    Shader::~Shader()
    {
        glDeleteProgram(program);
    }

    void Shader::bind()
    {
        glUseProgram(program);
    }

    void Shader::unbind()
    {
        glUseProgram(0);
    }

    SharedPtr<Shader> Shader::create(std::vector<ShaderData> settings)
    {
        return CreateShared<Shader>(settings);
    }

    bool Shader::readShader(std::string directory)
    {
        std::string line, shaderScriptAcumulator;
        std::ifstream shaderFile(directory);

        if (shaderFile.is_open())
        {
            while (std::getline(shaderFile, line))
            {
                //std::cout << line << std::endl;
                shaderScriptAcumulator += line + "\n";
            }
        }
        else
            return false;

        shader = shaderScriptAcumulator;
        return true;
    }

    bool Shader::compileShader(unsigned int type)
    {
        const char* src = shader.c_str();
        shaderLocation = glCreateShader(type);
        glShaderSource(shaderLocation, 1, &src, nullptr);
        glCompileShader(shaderLocation);

        int result;
        glGetShaderiv(shaderLocation, GL_COMPILE_STATUS, &result);

        if (result == GL_FALSE)
        {
            int length;
            glGetShaderiv(shaderLocation, GL_INFO_LOG_LENGTH, &length);

            char* message = (char*)malloc(length * sizeof(char));
            glGetShaderInfoLog(shaderLocation, length, &length, message);

            std::cout << "Shader failed to compile" << (type == GL_VERTEX_SHADER ? "vertex: " : "fragment: ") << std::endl;
            std::cout << message << std::endl;

            glDeleteShader(shaderLocation);

            return false;
        }

        return true;
    }

    bool Shader::createShader()
    {
        program = glCreateProgram();

        std::vector<unsigned int> deleteQueue;

        for(std::vector<ShaderData>::iterator it = settings.begin(); it != settings.end(); it++)
        {
            readShader(it.base()->shaderDirectory);
            compileShader(it.base()->shaderType);

            glAttachShader(program, shaderLocation);
            deleteQueue.push_back(shaderLocation);
        }

        glLinkProgram(program);
        glValidateProgram(program);

        int result;
        glGetProgramiv(program, GL_VALIDATE_STATUS, &result);
        if(result == GL_FALSE)
        {
            int length;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

            char* message = (char*)malloc(length * sizeof(char));
            glGetProgramInfoLog(program, length, &length, message);

            std::cout << "Program failed to validate:" << std::endl;
            std::cout << message << std::endl;

            return false;
        }

        for(const unsigned int& shaderLoc : deleteQueue)
        {   
            glDeleteShader(shaderLoc);
        }

        glUseProgram(0);

        return true;
    }
}
