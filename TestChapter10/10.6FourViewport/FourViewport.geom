#version 430 core
layout(triangles, invocations=4) in;
layout(triangle_strip, max_vertices=3) out;

uniform mat4 Vmatrix[4];

in vec3 vs_gs_normal[];

out vec3 gs_fs_normal;

void main()
{
	for(int i = 0; i < gl_in.length(); ++i)
	{
		gl_ViewportIndex = gl_InvocationID;
		gl_Position = Vmatrix[gl_InvocationID]*gl_in[i].gl_Position;
		gs_fs_normal = vs_gs_normal[i];
		EmitVertex();
	}
}