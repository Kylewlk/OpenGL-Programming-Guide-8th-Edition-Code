#version 430 core

layout(vertices = 4) out;

in vec4 color[];

out vec4 TCcolor[];

void main()
{
	gl_TessLevelInner[0] = 4.0;
	gl_TessLevelInner[1] = 3.0;

	gl_TessLevelOuter[0] = 2.0;
	gl_TessLevelOuter[1] = 3.0;
	gl_TessLevelOuter[2] = 3.0;
	gl_TessLevelOuter[3] = 2.0;


	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
	TCcolor[gl_InvocationID] = color[gl_InvocationID];
}



