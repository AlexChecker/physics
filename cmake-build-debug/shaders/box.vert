#version 330 core
layout (location=0) in vec3 pos;

uniform vec2 posr;
uniform mat4 rot;
void main() {
    gl_Position =rot* vec4((pos.x/10.0f),(pos.y/10.0f),pos.z,1.0);
}