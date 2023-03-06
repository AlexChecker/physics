#version 330 core

out vec4 fragColor;
uniform vec3 col;
uniform vec2 aspect;
void main() {
    float ration = aspect.x/aspect.y;
    fragColor=vec4(col.r,col.g,col.b,1.0);
}