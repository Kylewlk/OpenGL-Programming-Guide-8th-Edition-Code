#version 430 core

layout(triangles, invocations = 2) in;
layout(triangle_strip, max_vertices=3) out;

in vec3 vs_gs_normal[];

out vec3 gs_fs_normal;

void main()
{
	float f = gl_InvocationID > 0 ?  -1 : 1;//Õý·´Ãæ
	for(int i = 0; i < gl_in.length(); ++i)
	{
		gl_Layer = gl_InvocationID;
		gl_Position = gl_in[i].gl_Position;
		gl_Position.z = f*gl_Position.z;
		gs_fs_normal = vs_gs_normal[i];
		gs_fs_normal.z = gs_fs_normal.z *f;
		EmitVertex();
	}
	EndPrimitive();
}
