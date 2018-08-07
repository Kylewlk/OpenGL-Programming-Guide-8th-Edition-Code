#version 410

layout (location = 0) out vec4 color;

in vec3 vs_fs_normal;
in float fsTexCoord;
   
vec4 Ambient = vec4(0.0, 0.1, 0.0, 1.0);
vec4 diffuse = vec4(0.1, 0.5, 0.7, 1.0);
vec4 specular = vec4(0.1, 0.2, 0.4, 1.0); 
   
vec4 StripeColor = vec4(1.0);
vec4 BackColor = vec4(0.0, 0.0, 0.0, 1.0);
   
 float Width = 0.5; // 条带所占比例
 float Fuzz = 0.04; // 反走样宽度
 float Scale = 20.0;// 条带条数
   
   
void main(void)
{
	float scaledT = fract(fsTexCoord*Scale);//放大纹理部分然后取小数部分。
	float frac1 = clamp(scaledT/Fuzz, 0.0, 1.0);//除了fuzz区域，其他都时1.
	float frac2 = clamp((scaledT-Width)/Fuzz, 0.0, 1.0);//除了fuzz+width区域，其他都是1
	frac1 = frac1 * (1-frac2);//计算是否时条带颜色，除了放走样区域，其他要么为0，要么为1
	frac1 = frac1 * frac1 *(3.0- (2.0 * frac1));//Hermite插值反走样运算，实际上2、3行代码已经具备反走样能力，只是加上这行代码反走样效果更好。
	vec4 finalColor = mix(BackColor, StripeColor, frac1);

    color =Ambient  + finalColor * diffuse * abs(vs_fs_normal.z) + specular * pow(abs(vs_fs_normal.z), 70.0);
}
