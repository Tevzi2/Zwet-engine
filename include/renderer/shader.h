#pragma once

#include <core.h>
#include <utils.h>
#include <log.h>

namespace ZWET
{
    // ta struktura shranjuje podatke, kje se koda za shader nahaja v projektu razvijalca in tip shareja, ki je (vertex shader, fragment shader, geometry shader)
    struct ShaderData
    {
        std::string shaderDirectory;
	    unsigned int shaderType;
    };

    // klasa, ki skrbi za branje, preverjanje in kompilacijo shaderjov in shader programov, ki povezujejo razlicne tipe shaderjev
    class Shader
    {
        public: 
            Shader(std::vector<ShaderData> settings);

            ~Shader();

            void bind();

            void unbind();

            void remove();

            unsigned int& getProgram() { return program; };

            static SharedPtr<Shader> create(std::vector<ShaderData> settings);

        private: 
            //shader program
            unsigned int program;
            // lokacija shaderja
            unsigned int shaderLocation;
            // koda za shader
            std::string shader;
            // vektor, ki vsebuje vse tipe shaderjov, ki se povezejo v programu
            std::vector<ShaderData> settings;

            bool readShader(std::string directory);

            bool compileShader(unsigned int type);

            bool createShader();
    };
}