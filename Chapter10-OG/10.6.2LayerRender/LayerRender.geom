#version 430 core

layout(triangles, invocations = 2) in;//必须使用invocations进行分层绘制，直接多次设置gl_Layer无法分层
layout(triangle_strip, max_vertices=3) out;

in vec3 vs_gs_normal[];

out vec3 gs_fs_normal;
out vec4 Color;

void main()
{
	float f = gl_InvocationID > 0 ?  -1 : 1;//正反面
	Color = gl_InvocationID > 0 ? vec4(0.0, 1.0, 1.0, 1.0) : vec4(1.0);
	for(int i = 0; i < gl_PatchVerticesIn; ++i)
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
