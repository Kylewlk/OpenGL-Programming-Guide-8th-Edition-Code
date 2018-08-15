#version 430 core

layout(location = 0) uniform int slice;
layout(location = 1) uniform sampler2DArray tex;

out vec4 FragColor;

in vec2 fsTex;


void main()
{		
	FragColor = texture(tex, vec3(fsTex, slice)); 
	//FragColor = vec4(fsTex, 1.0, 1.0); 
}






