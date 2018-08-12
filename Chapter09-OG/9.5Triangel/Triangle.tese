#version 430 core


layout(triangles, equal_spacing, cw) in;
//layout(triangles, equal_spacing, cw, point_mode) in;


in vec4 TCcolor[];

flat out vec4 color;

void main()
{
	float u = gl_TessCoord.x;
	float v = gl_TessCoord.y;
	float w = gl_TessCoord.z;
	
	gl_Position = u * gl_in[0].gl_Position + v * gl_in[1].gl_Position + w * gl_in[2].gl_Position;
	color = TCcolor[0]*u + TCcolor[1]*v + TCcolor[2]*w;
}




