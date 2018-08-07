#version 410

layout (location = 0) out vec4 color;

in vec3 vs_fs_normal;
in vec2 fsTex;

   
vec4 Ambient = vec4(0.1, 0.1, 0.1, 1.0);
vec4 diffuse = vec4(0.6, 0.6, 0.6, 1.0);
vec4 specular = vec4(0.2, 0.2, 0.2, 1.0); 
   
vec4 BrickColor = vec4(1.0,0.5,0.0,1.0);
vec4 MortarColor = vec4(0.8, 0.8, 0.8, 1.0);

vec2 BrickSize = vec2(0.1, 0.05);
vec2 BrickPct = vec2(0.88, 0.88); 
  
   
void main(void)
{
	vec2 position, userBrick;
	
	position = fsTex/BrickSize;
	
	if(fract(position.y *0.5) > 0.5)
		position.x += 0.5;
	position = fract(position);
	userBrick = step(position, BrickPct);
	
	vec4 finalColor= mix(MortarColor, BrickColor, userBrick.x*userBrick.y);

    color =Ambient  + finalColor * diffuse * abs(vs_fs_normal.z) + specular * pow(abs(vs_fs_normal.z), 70.0);
}
