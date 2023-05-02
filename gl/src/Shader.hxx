#ifndef _SHADER_HXX_
#define _SHADER_HXX_

#include <cstdlib>
#include <string>

class Shader
{
public:
    Shader(const std::string &vertextPath, const std::string &fragmentPath);

    void use();
    void setBool(const std::string &name, bool value);
    void setInt(const std::string &name, int value);
    void setFloat(const std::string &name, float value);

private:
    uint32_t ID;
};

#endif