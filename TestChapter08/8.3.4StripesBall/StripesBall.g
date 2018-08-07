#version 410

layout (location = 0) out vec4 color;

in vec3 vs_fs_normal;
in vec2 fsPos;
in vec2 texCoord;
   
vec4 Ambient = vec4(0.1, 0.2, 0.2, 1.0);
vec4 diffuse = vec4(0.6, 0.6, 0.6, 1.0);
vec4 specular = vec4(0.2, 0.2, 0.2, 1.0); 
   
vec4 BallColor = vec4(0.9,0.9,0.9,1.0);
  

void main(void)
{
	
	float t = 0.0;
	float freq = 16.0;
	
	t = fract(texCoord.s * freq);
	
	float triangle = abs(2.0* t - 1.0);

	//float square = step(0.5, triangle);

	// float square = smoothstep(0.45, 0.55, triangle); //圆心处依然走样

	float edge = 0.0;
	// float dp = length(vec2(dFdx(texCoord.s), dFdy(texCoord.s)));	
	float dp = fwidth(texCoord.s);
	edge = clamp(dp*freq*3.0, 0.0, 0.45);
	float square = smoothstep(0.5 -edge, 0.5 +edge, triangle);
	
    color =  BallColor * square;
	
}
