#include "Shader.hxx"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath) {
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vertexShaderFile;
    std::ofstream fragmentShaderFile;

    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        fragmentShaderFile.open(fragmentPath);
        vertexShaderFile.open(vertexPath);
        std::stringstream vertexShader, fragmentShader;

        vertexShader << vertexShaderFile.rdbuf();
        fragmentShader << fragmentShaderFile.rdbuf();

        vertexShaderFile.close();
        fragmentShaderFile.close();

        vertexCode = vertexShader.str();
        fragmentCode = fragmentShader.str();
    } catch(std::ifstream::failure e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
}