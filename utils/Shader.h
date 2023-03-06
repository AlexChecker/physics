//
// Created by alex Cheker on 08.11.2022.
//

#ifndef GLORTHOVIEW_SHADER_H
#define GLORTHOVIEW_SHADER_H
#include <glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm.hpp>

typedef unsigned  int SHADER;
#define DEBUG 1

class Shader {
public:
    u_int  ID;
    Shader(const char* vpath,const char* fpath);
    Shader();
    void use();
    void setBool(const std::string name,bool val);
    void setInt(const std::string name,int val);
    void setFloat(const std::string name,float val);
    void setVec2f(const std::string name, float val1,float val2);
    void setVec3f(const std::string name,float val1,float val2,float val3);
    void setFloat4x4(std::string name, glm::mat4 matrix);
    void setVec4f(const std::string name,glm::vec4 vec);

};


#endif //GLORTHOVIEW_SHADER_H
