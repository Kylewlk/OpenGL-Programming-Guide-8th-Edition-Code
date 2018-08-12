#version 430 core


layout(quads, equal_spacing, cw) in;
//layout(triangles, equal_spacing, cw, point_mode) in;


in vec4 TCcolor[];

flat out vec4 color;

void main()
{
	float u = gl_TessCoord.x;
	float um = 1 - u;
	float v = gl_TessCoord.y;
	float vm = 1 - v;
	
	gl_Position = um*vm * gl_in[0].gl_Position 
	             + u*vm * gl_in[1].gl_Position 
				 + u * v * gl_in[2].gl_Position
				 + um * v * gl_in[3].gl_Position;


	color = TCcolor[0]*um*vm 
	       + TCcolor[1]*u*vm  
		   + TCcolor[2]*v * u
		   + TCcolor[3]*um * v;

}




