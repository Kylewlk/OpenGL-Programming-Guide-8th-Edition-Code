#version 430 core 

uniform vec4 Ambient;

in vec4 color;

out vec4 FragColor;

void main()
{
    FragColor = color;
    FragColor = min(color*Ambient, vec4(1.0));
}
