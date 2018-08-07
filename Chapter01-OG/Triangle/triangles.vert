#version 430 core
layout(location = 0) in vec4 vPosition;
void
main()
{
    vec4 p = vPosition;
    gl_Position = p;
}