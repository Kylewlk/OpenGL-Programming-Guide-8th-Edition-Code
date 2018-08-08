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

   //�ӿڴ�СΪ400*400��glutInitWindowSize(400, 400);
   //�������Ϊ[-1, 1],����ÿ�����ض�Ӧ�Ĵ�����߷���Ϊ(2.0/400.0)
	fsfp =   2.0*(400.0/2.0)*Pos.x
	       + 3.0*(400.0/2.0)*Pos.y   
		   + 200.0;
}
