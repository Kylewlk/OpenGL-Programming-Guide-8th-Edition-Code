#version 330 core

uniform mat4 model_matrix;

layout(location = 0) in vec4 MCVertex;
 layout(location = 1) in vec3 MCNormal;//法线方向
 layout(location = 2) in vec3 MCTangent;//切线方向
layout(location = 3) in vec2 TexCoord0;

out vec3 LightDir;
out vec3 EyeDir;//局部坐标系下顶点的坐标
out vec2 TexCoord;
out vec3 EyeCoord;

vec3 Eye = vec3(0.0, 0.0, -5.0);
vec3 LightDirection = vec3(0.0f, 0.0f, -3.0f);

void main()
{
	vec4 Pos = model_matrix * MCVertex;
	TexCoord = TexCoord0.st;
	EyeDir = Pos.xyz;
	
	mat3 VecTransform = mat3(transpose(inverse(model_matrix)));//向量转换矩阵，具体原理参考书本592页附录E.1.2

	vec3 n = normalize(VecTransform * MCNormal);   //z
	vec3 t = normalize(VecTransform * MCTangent);  //x
	vec3 b = cross(n, t);           //y
	
	mat3 VertLocalMat = mat3(t,b,n);

	LightDir = normalize(VertLocalMat * LightDirection);

	EyeDir = normalize(VertLocalMat * EyeDir);
	
	EyeCoord = normalize(VertLocalMat * Eye);

	gl_Position = Pos;
}