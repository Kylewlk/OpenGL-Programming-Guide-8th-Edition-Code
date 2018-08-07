#version 430 core

uniform float dt = 0.001;

layout(local_size_x = 128) in;

layout(rgba32f, binding=0) uniform imageBuffer par;


void main()
{

	vec4 pv = imageLoad(par, int(gl_GlobalInvocationID.x)*2);
	
	vec2 pos = vec2(pv.xy);
	vec2 vel = vec2(pv.zw);
	
	pos = pos + vel*dt*0.5;
	
	//if(pos.x>1.0 || pos.x<-1.0 || pos.y>1.0 || pos.y<-1.0)
	if(dot(pos, pos) > 2.0)
	{
		pos = vec2(0.0f);
	}
	
	imageStore(par, int(gl_GlobalInvocationID.x)*2, vec4(pos, vel));
}