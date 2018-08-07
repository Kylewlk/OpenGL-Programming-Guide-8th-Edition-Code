#version 410

layout (location = 0) out vec4 color;

in vec3 vs_fs_normal;
in float fsTexCoord;
   
vec4 Ambient = vec4(0.0, 0.1, 0.0, 1.0);
vec4 diffuse = vec4(0.1, 0.5, 0.7, 1.0);
vec4 specular = vec4(0.1, 0.2, 0.4, 1.0); 
   
vec4 StripeColor = vec4(1.0);
vec4 BackColor = vec4(0.0, 0.0, 0.0, 1.0);
   
 float Width = 0.5; // ������ռ����
 float Fuzz = 0.04; // ���������
 float Scale = 20.0;// ��������
   
   
void main(void)
{
	float scaledT = fract(fsTexCoord*Scale);//�Ŵ�������Ȼ��ȡС�����֡�
	float frac1 = clamp(scaledT/Fuzz, 0.0, 1.0);//����fuzz����������ʱ1.
	float frac2 = clamp((scaledT-Width)/Fuzz, 0.0, 1.0);//����fuzz+width������������1
	frac1 = frac1 * (1-frac2);//�����Ƿ�ʱ������ɫ�����˷�������������ҪôΪ0��ҪôΪ1
	frac1 = frac1 * frac1 *(3.0- (2.0 * frac1));//Hermite��ֵ���������㣬ʵ����2��3�д����Ѿ��߱�������������ֻ�Ǽ������д��뷴����Ч�����á�
	vec4 finalColor = mix(BackColor, StripeColor, frac1);

    color =Ambient  + finalColor * diffuse * abs(vs_fs_normal.z) + specular * pow(abs(vs_fs_normal.z), 70.0);
}
