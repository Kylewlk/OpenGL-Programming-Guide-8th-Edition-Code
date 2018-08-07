#version 430 core

layout(location = 0) uniform float time_step;
layout(location = 0) in vec4 viPos;
layout(location = 1) in vec4 Rect;

out vec4 color;

out vec4 oPostion;

void main()
{
	vec4 vPos = viPos;
	vPos.y = vPos.y - 0.4 * time_step;
	if(vPos.y < -0.9)
	{
		vPos.y = 0.9;
	}
	gl_Position = vPos;
	oPostion = vPos;
	//color = vec4(1.0, 0.0, 0.0, 1.0);

	if( vPos.x > Rect[0] && vPos.x < Rect[1] 
	   && vPos.y > Rect[2] && vPos.y < Rect[3])
	{
		color = vec4(1.0, 0.0, 0.0, 1.0);
	}
	else
	{
		color = vec4(0.0, 1.0, 0.0, 1.0);
	}
}
