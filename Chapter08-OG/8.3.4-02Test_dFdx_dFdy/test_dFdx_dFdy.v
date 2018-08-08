#version 430

layout (location = 0) in vec4 position;

layout (location = 0) uniform mat4 view_mat;

out vec2 fsPos;
out float fsfp;

void main(void)
{
	vec4 Pos = view_mat * position;
    gl_Position = Pos;

	fsPos = (Pos.xy) ;

   //视口大小为400*400，glutInitWindowSize(400, 400);
   //窗口左边为[-1, 1],所以每个像素对应的窗口左边幅度为(2.0/400.0)
	fsfp =   2.0*(400.0/2.0)*Pos.x
	       + 3.0*(400.0/2.0)*Pos.y   
		   + 200.0;
}
