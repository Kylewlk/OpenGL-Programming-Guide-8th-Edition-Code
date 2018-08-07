#version 330 core

uniform vec3 LightPosition;


layout(location = 0) in vec4 MCVertex;
layout(location = 1) in vec2 TexCoord0;

flat out vec3 LightDir;
out vec3 EyeDir;//局部坐标系下顶点的坐标
out vec2 TexCoord;
flat out vec3 EyeCoord;

//vec3 LightPosition = vec3(0.0f, 0.0f, -3.0f);
vec3 MCNormal = vec3(0.0, 0.0, -1.0);
vec3 MCTangent = vec3(0.0, 1.0, 0.0);
vec3 Eye = vec3(0.0, 0.0, -5.0);

void main()
{
	EyeDir = vec3(MCVertex);
	TexCoord = TexCoord0.st;
	
	vec3 n = normalize(MCNormal);   //z
	vec3 t = normalize(MCTangent);  //x
	vec3 b = cross(n, t);           //y
	
	mat3 vertLocalMat = mat3(t,b,n);//矩阵可以将向量或者坐标转换到顶点局部坐标系下

	LightDir = normalize(vertLocalMat * LightPosition);

	EyeDir = normalize(vertLocalMat * EyeDir);
	
	EyeCoord = normalize(vertLocalMat * Eye);

	gl_Position = MCVertex;
}