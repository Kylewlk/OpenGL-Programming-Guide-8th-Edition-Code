#version 410

layout (location = 0) out vec4 color;

in vec3 vs_fs_normal;
in vec4 fsPos;
in vec2 texCoord;
   
vec4 Ambient = vec4(0.4, 0.4, 0.4, 1.0);
vec4 diffuse = vec4(0.7, 0.7, 0.7, 1.0);
vec4 specular = vec4(0.2, 0.2, 0.2, 1.0); 

   
vec4 BallColor = vec4(0.9,0.9,0.9,1.0);
  

void main(void)
{
	
	float t = 0.0;
	float freq = 10.0; //条带数，由于3D模型的纹理坐标不连续，freq = 16.0时无法实现反走样。
	
	t = fract(texCoord.s * freq);
	
	float triangle = abs(2.0* t - 1.0);

//	float square = step(0.5, triangle);//走样很明显
//	float square = smoothstep(0.48, 0.52, triangle); //圆心处依然走样

	//根据像素宽度自动改变反走样宽度
	float edge = 0.0;
	float dp = fwidth(t);//dp = length(vec2(dFdx(texCoord.s), dFdy(texCoord.s)));	
	edge = clamp(dp*2.0, 0.0, 0.5);
	float square = smoothstep(0.5 -edge, 0.5 +edge, triangle);
	
	square = square * square *(3.0- (2.0 * square));	
    BallColor =  BallColor * square;
	
	color = BallColor*Ambient 
	        + BallColor*diffuse * abs(vs_fs_normal.z)
			+ specular * pow(abs(vs_fs_normal.z), 70.0);
}
