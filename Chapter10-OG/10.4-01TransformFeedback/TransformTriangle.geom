#version 430 core

layout(lines_adjacency) in;
layout(points, max_vertices = 30) out;

uniform mat4 modelMatrix;
uniform mat4 dMatrix;

in vec4 VsGsColor[];


layout(stream=0) out vec4 lColor;
layout(stream=0) out vec4 lPos;

layout(stream=1) out rVert
{
	vec4 rColor;
	vec4 rPos;
};
// layout(stream=1) out vec4 rColor;
// layout(stream=1) out vec4 rPos;


void main()
{
	int n = 0;
	int VertCount = gl_in.length();
	for(int i = 0; i < 4; ++i)
	{	
		for(int j = 0; j < 3; ++j)
		{
			lPos = modelMatrix*gl_in[(j+i)%VertCount].gl_Position;
			lColor = VsGsColor[(j+i)%VertCount];
			gl_Position = lPos;
			EmitStreamVertex(0);
			//EmitVertex();
		}
		EndStreamPrimitive(0);
		//EndPrimitive();
	}
	
	for(int i = 0; i < 4; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			rPos = dMatrix * modelMatrix*gl_in[(j+i)%VertCount].gl_Position;
			rColor = VsGsColor[(j+i)%VertCount] * 0.4;
			gl_Position = rPos;
			EmitStreamVertex(1);
		}
		EndStreamPrimitive(1);
	}	
}






