#version 430 core

layout(lines_adjacency) in;

layout(triangle_strip, max_vertices = 12) out; //输出三角形

uniform mat4 modelMatrix;

in vec4 VsGsColor[];


flat out vec4 GsColor;

void main()
{
	int n = 0;
	for(int i = 0; i < 4; ++i)//输出四个三角形 四个面
	{	
		for(int j = 0; j < 3; ++j)
		{
			gl_Position = modelMatrix*gl_in[(j+i)%gl_PatchVerticesIn].gl_Position;
			GsColor = VsGsColor[(j+i)%gl_PatchVerticesIn];
			EmitVertex();
		}
		EndPrimitive();
	}
}






