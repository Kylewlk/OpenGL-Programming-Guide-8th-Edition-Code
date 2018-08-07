#version 430 core

layout(location=0) in vec4 Pos;
layout(location=1) in vec4 Color;

uniform float dt = 0.001;
layout(rgba32f, binding=0) uniform imageBuffer par;

out vec4 fsColor;

void main()
{
	gl_Position = vec4(Pos.xy, 0.0, 1.0);
	fsColor = Color;
	
	
	
	vec2 pos = Pos.xy;
	vec2 vel = vec2(Pos.zw);
	
	pos = pos + vel*dt*0.5;
	
	//if(pos.x>1.0 || pos.x<-1.0 || pos.y>1.0 || pos.y<-1.0)
	if(dot(pos, pos) > 2.0)
	{
		pos = vec2(0.0f);
	}
	
	imageStore(par, gl_VertexID * 2, vec4(pos, vel));

}

