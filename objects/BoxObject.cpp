//
// Created by alex Cheker on 03.03.2023.
//

#include "BoxObject.h"


BoxObject::BoxObject(float w, float h, float x, float y,float angle, b2World *world,Color col, bool isDynamic, bool debug) {
    this->debug=debug;
    this->isDynamic=isDynamic;
    initX=x;
    initY=y;
    color=col;
    objectShader=Shader("./shaders/box.vert","./shaders/box.frag");
    this->world=world;
    physics.position.Set(x,y);
    physics.angle=glm::radians(angle);
    b2FixtureDef fixture;
    b2PolygonShape shape;
    shape.SetAsBox(w,h);
    if (isDynamic)physics.type = b2_dynamicBody;
    fixture.shape = &shape;
    fixture.friction=.3f;
    fixture.density=.5f;
    //printf("INTERNAL VERTICES\n");
    //for(auto i : shape.m_vertices)
    //{
    //    printf("%4.2f %4.2f\n",i.x,i.y);
    //}
    //printf("INTERNAL VERTICES END\n");
    body = world->CreateBody(&physics);
    body->CreateFixture(&fixture);
    printf("%4.2f\n",(y+h)/10.0f-1);
    uint indices[]=
            {
                    0,1,2,
                    2,3,0
            };

        float vertices[] =
                {(w), (h), .0f,  //right top
                 (w), (-h), .0f,  //right bottom
                 (-w), (-h), .0f,  //left bottom
                 (-w), (h), .0f  //left top
                };

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glBindVertexArray(0);

}

void BoxObject::Draw() {
    glBindVertexArray(VAO);
    objectShader.use();
        //objectShader.setVec2f("posr", body->GetPosition().x, body->GetPosition().y);
    objectShader.setVec3f("col",color.red,color.green,color.blue);
    glm::vec4 vec(1.0f);
    glm::mat4 trans(1.0f);

    trans=glm::translate(trans,glm::vec3(body->GetPosition().x/10.0f-1.0f,body->GetPosition().y/10.0f-1.0f,.0f));
    //vec=vec*trans;

    trans=glm::rotate(trans,body->GetAngle(),glm::vec3(.0,.0,1.0));
    if(debug)
    {
        printf("POS:   %4.2f %4.2f\n",body->GetPosition().x/10.0f-1.0f,body->GetPosition().y/10.0f-1.0f);
        //printf("INIT:  %4.2f %4.2f\n",initX/10.0f-1.0f,initY/10.0f-1.0f);
        //printf("AFTER: %4.2f %4.2f\n",vec.x,vec.y);
        //std::cout<<"BOX X: "<<body->GetPosition().x<<std::endl;
        //std::cout<<"BOX Y: "<<body->GetPosition().y<<std::endl;
    }
    objectShader.setFloat4x4("rot",trans);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
}
