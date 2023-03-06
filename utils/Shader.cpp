//
// Created by alex Cheker on 08.11.2022.
//

#include "Shader.h"

Shader::Shader()
= default;

Shader::Shader(const char *vpath, const char *fpath) {
    std::string vshader;
    std::string fshader;

    std::ifstream vshaderfile;
    std::ifstream fshaderfile;


    vshaderfile.exceptions(std::fstream::failbit | std::fstream::badbit);
    fshaderfile.exceptions(std::fstream::failbit | std::fstream::badbit);

    try
    {
        vshaderfile.open(vpath);
        fshaderfile.open(fpath);
        std::stringstream vshaderstream,fshaderstream;
        vshaderstream<<vshaderfile.rdbuf();
        fshaderstream<<fshaderfile.rdbuf();
        vshaderfile.close();
        fshaderfile.close();
        vshader =vshaderstream.str();
        fshader = fshaderstream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout<<"ERROR::SHADER::LOAD_ERROR"<<std::endl;
    }

    const char * vshadercode = vshader.c_str();
    const char * fshadercode = fshader.c_str();

    SHADER vertex,frag;
    int success;
    char log[512];
    vertex = glCreateShader(GL_VERTEX_SHADER);
    frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vertex,1,&vshadercode,nullptr);
    glShaderSource(frag,1,&fshadercode,nullptr);
    glCompileShader(vertex);
    glCompileShader(frag);
    glGetShaderiv(vertex,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        std::cout<<"ERROR::VERTEX_SHADER_ERROR"<<std::endl;
        glGetShaderInfoLog(vertex,512,nullptr,log);
        std::cout<<log<<std::endl;
    }
    glGetShaderiv(frag,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        std::cout<<"ERROR::FRAGMENT_SHADER_ERROR"<<std::endl;
        glGetShaderInfoLog(frag,512,nullptr,log);
        std::cout<<log<<std::endl;
    }

        std::cout<<"VERTEX SHADER SOURCE \""<<vpath<<"\":\n"<<vshadercode<<std::endl<<"FRAGMENT SHADER SOURCE\""<<fpath<<"\":\n"<<fshadercode<<std::endl;

    ID = glCreateProgram();
    glAttachShader(ID,vertex);
    glAttachShader(ID,frag);
    glLinkProgram(ID);
    glGetProgramiv(ID,GL_LINK_STATUS,&success);
    if(!success)
    {
        std::cout<<"ERROR::SHADER_PROGRAM_LINK_ERROR"<<std::endl;
        glGetProgramInfoLog(ID,512,nullptr,log);
        std::cout<<log<<std::endl;
    }
    glDeleteShader(vertex);
    glDeleteShader(frag);
    std::cout<<"Created shader with ID: "<<ID<<std::endl;
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string name, bool val)
{
    glUniform1i(glGetUniformLocation(ID,name.c_str()),(int)val);
}

void Shader::setFloat(const std::string name, float val)
{
    glUniform1f(glGetUniformLocation(ID,name.c_str()),val);
}

void Shader::setInt(const std::string name, int val)
{
    glUniform1i(glGetUniformLocation(ID,name.c_str()),val);
}

void Shader::setVec2f(const std::string name, float val1,float val2) {
    glUniform2f(glGetUniformLocation(ID,name.c_str()),val1,val2);
}

void Shader::setVec3f(const std::string name, float val1, float val2, float val3) {
    glUniform3f(glGetUniformLocation(ID,name.c_str()),val1,val2,val3);
}

void Shader::setFloat4x4(std::string name, glm::mat4 matrix) {
    glUniformMatrix4fv(glGetUniformLocation(ID,name.c_str()),1,GL_FALSE,glm::value_ptr(matrix));
}

void Shader::setVec4f(const std::string name, glm::vec4 vec) {
    glUniform4f(glGetUniformLocation(ID,name.c_str()),vec.x,vec.y,vec.z,vec.w);
}




