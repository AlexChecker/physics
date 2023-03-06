//
// Created by alex Cheker on 03.03.2023.
//

#ifndef PHYSICS_BASEOBJECT_H
#define PHYSICS_BASEOBJECT_H
#include "../utils/Shader.h"
#include "../utils/Color.h"
#include <box2d/box2d.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glfw3.h>

typedef unsigned int uint;

 class BaseObject {

 public:
     Color color;
     b2Body* body;
     bool debug;
     bool isDynamic;
     float initX;
     float initY;
     Shader objectShader;
     b2BodyDef physics;
     b2World* world;
     uint VAO;
     uint VBO;
     uint EBO;

 };


#endif //PHYSICS_BASEOBJECT_H
