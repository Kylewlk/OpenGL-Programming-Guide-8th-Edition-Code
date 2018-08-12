#version 430 core

layout(vertices = 3) out;

in vec4 color[];

out vec4 TCcolor[];

void main()
{
	gl_TessLevelInner[0] = 4.0;

	gl_TessLevelOuter[0] = 2.0;
	gl_TessLevelOuter[1] = 2.0;
	gl_TessLevelOuter[2] = 2.0;


	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
	TCcolor[gl_InvocationID] = color[gl_InvocationID];
	
	if(gl_InvocationID == 2)
	{ 
		gl_out[gl_InvocationID].gl_Position.x = 0.0;
	}
}



