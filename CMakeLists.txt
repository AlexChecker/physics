cmake_minimum_required(VERSION 3.24)
project(physics)

set(CMAKE_CXX_STANDARD 17)

set(GLEW_H /usr/local/Cellar/glew/2.2.0_1/include/GL)
set(GLFW_H /usr/local/Cellar/glfw/3.3.8/include/GLFW)
set(GLM_H /usr/local/Cellar/glm/0.9.9.8/include/glm)
set(GLAD_H /usr/local/include/glad)
set(KHR_H /usr/local/include/KHR)
set(BOX2D_H /usr/local/Cellar/box2d/2.4.1/include)
set(IMGUI_H /usr/local/include/imgui)
include_directories(${GLEW_H} ${GLFW_H} ${GLM_H} ${GLAD_H} ${KHR_H} ${BOX2D_H} ${IMGUI_H})

# Add target link
set(GLEW_LINK /usr/local/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.3.8/lib/libglfw.3.dylib)
link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK})

add_executable(physics main.cpp glad.c utils/Shader.cpp objects/BaseObject.cpp objects/BaseObject.h objects/BoxObject.cpp objects/BoxObject.h utils/Color.h
        ${IMGUI_H}/imgui.cpp ${IMGUI_H}/imgui_demo.cpp ${IMGUI_H}/imgui_draw.cpp ${IMGUI_H}/imgui_tables.cpp ${IMGUI_H}/imgui_widgets.cpp ${IMGUI_H}/backends/imgui_impl_glfw.cpp ${IMGUI_H}/backends/imgui_impl_opengl3.cpp)
target_link_libraries(physics /usr/local/Cellar/box2d/2.4.1/lib/libbox2d.a)

if (APPLE)
    target_link_libraries(physics "-framework OpenGL")
    target_link_libraries(physics "-framework GLUT")
endif()