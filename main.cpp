#include <iostream>
#include "utils/Shader.h"
#include <glfw3.h>
#include "objects/BaseObject.h"
#include "objects/BoxObject.h"
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

void resize_callback(GLFWwindow* win,int w,int h);
void initSecondFBO(uint *fbo,uint *texture);
void removeSecondFBO(uint *fbo);

int main() {

    //glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    //glm::mat4 trans(1.0f);
    //trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    //vec = trans * vec;
    //printf("%4.2f %4.2f\n",vec.x,vec.y);
    //std::cout << vec.x << vec.y << vec.z << std::endl;
    //return 0;


    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(600,600,"Physics",NULL,NULL);
    if(window==NULL)
    {
        std::cout<<"Error while creating window!"<<std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout<<"Error while initializing GLAD"<<std::endl;
        glfwTerminate();
        return -1;
    }

    ImGui_ImplGlfw_InitForOpenGL(window,true);
    ImGui_ImplOpenGL3_Init("#version 150");

    int attributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, & attributes);
    std::cout<<"Supported "<<attributes<<" of vertex attributes"<<std::endl;
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    std::cout<<"Framebuffer width: "<<width<<" | Framebuffer height: "<<height<<std::endl;
    glViewport(0,0,width,height);
    b2World world(b2Vec2(.0f,-10.0f));
    BoxObject ground=BoxObject(10.0f,1.0f,10.0f,1.0f,.0f,&world,CYAN,false);
    BoxObject wall=BoxObject(1.0f,10.0f,1.0f,10.0f,.0f,&world,CYAN);
    BoxObject wall2=BoxObject(1.0f,10.0f,19.0f,10.0f,.0f,&world,CYAN);
    BoxObject wall3=BoxObject(10.0f,1.0f,10.0f,19.0f,.0,&world,CYAN);
    BoxObject mixer=BoxObject(5.0f,1.0f,10.0f,10.0f,.0,&world,GREEN,true);
    BoxObject box1=BoxObject(1.0f,1.0f,10.0f,5.0f,.0f,&world,RED,true );
    BoxObject box2=BoxObject(1.0f,1.0f,10.9f,10.0f,.0f,&world,MAGENTA, true);
    //BoxObject plane=BoxObject(5.0f,1.0f,5.0f,5.0f,-45.0f,&world,WHITE);
    float const step =1.0f/60.0f;
    int velocityIterations = 6;
    int positionIterations = 2;
    bool pause=false;
    float x=10.0f;
    float y=10.0f;

    int w,h;

    glfwSetFramebufferSizeCallback(window,resize_callback);
    float angle=.0f;
    uint fbo;
    unsigned int texture;
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(.0,.0,.0,1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Hello");
        //ImGui::Text("Hui");
        ImGui::DragFloat("Angle velocity", &angle,1.0f,.0f,100.0f);
        ImGui::DragFloat("X position", &x,.1f,.0,20.0f);
        ImGui::DragFloat("Y position",&y,.1f,.0,20.0f);
        ImGui::End();

        initSecondFBO(&fbo,&texture);



        ground.Draw();
        wall.Draw();
        wall2.Draw();
        wall3.Draw();
        mixer.body->SetTransform(b2Vec2(x,y),angle);
        //mixer.body->SetAngularVelocity(angle);
        mixer.Draw();
        box1.body->SetAwake(true);
        box1.Draw();
        box2.Draw();
        //box2.body->SetAngularVelocity(10.0f);
        //plane.body->SetTransform(b2Vec2(x,y),angle);
        //plane.Draw();
        if(!pause)
        {
            world.Step(step,velocityIterations,positionIterations);
            world.DebugDraw();
        }

        removeSecondFBO(&fbo);

        glfwGetWindowSize(window,&w,&h);
        resize_callback(window,w,h);

        ImGui::SetNextWindowSize(ImVec2(300,400.0f*(300.0f/400.0f)));
        ImGui::Begin("Render",nullptr,ImGuiWindowFlags_NoResize);

        ImGui::BeginChild("Render");
        ImVec2 size=ImGui::GetWindowSize();
        ImGui::Image((ImTextureID)texture,size,ImVec2(0,1),ImVec2(1,0));

        ImGui::EndChild();

        ImGui::End();


        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}

void resize_callback(GLFWwindow* win,int w,int h)
{
    //glfwSetWindowSize(win,600,600);
    float aspect =(float)w/(float)h;
    if(w>h) glViewport(0,0,w,h*aspect);
    else glViewport(0,0,w*aspect,h);
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    ////gluPerspective(60.0*aspect,aspect,0.01f,100.0f);
    //glOrtho(-1.0f,600*aspect,-1.0f,600*aspect,-1,1);
    //glMatrixMode(GL_MODELVIEW);

}

void initSecondFBO(uint *fbo,uint *texture)
{
    glGenFramebuffers(1,fbo);
    glBindFramebuffer(GL_FRAMEBUFFER,*fbo);
    resize_callback(nullptr,300,400);

    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 300*(300.0f/400.0f), 400, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *texture, 0);

    glClear(GL_COLOR_BUFFER_BIT);
}

void removeSecondFBO(uint *fbo)
{
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteFramebuffers(1,fbo);
}