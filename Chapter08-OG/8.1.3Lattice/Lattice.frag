#version 410

layout (location = 0) out vec4 color;

in vec3 vs_fs_normal;
in vec2 fsPos;

   
vec4 Ambient = vec4(0.1, 0.3, 0.2, 1.0);
vec4 diffuse = vec4(0.6, 0.6, 0.6, 1.0);
vec4 specular = vec4(0.2, 0.2, 0.2, 1.0); 
   
vec4 BallColor = vec4(0.8,0.9,0.4,1.0);
  

void main(void)
{
	float Width = 0.02;
	vec2 pos;
	//pos =  normalize(abs(fsPos));
	pos =  abs(fsPos);
	
	pos = mod(pos, vec2(0.2));
	
	if((pos.x > Width) && (pos.y > Width))
	{
		discard;
	}
	
	
    color =Ambient  +  BallColor*diffuse * abs(vs_fs_normal.z) + specular * pow(abs(vs_fs_normal.z), 70.0);
	
	if(gl_FrontFacing)
	{
		color *=0.4;//让背面更暗
	}
	
}
