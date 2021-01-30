#version 330 core

vec4 MCBallCenter = vec4(0.0, 0.0, 0.0, 1.0);

uniform mat4 MVMatrix;
uniform mat4 MVPMatrix;

in vec4 MCVertex;

out vec3 OCPosition;
out vec4 ECPosition;
flat out vec4 ECBallCenter;

void main ()
{
	OCPosition = MCVertex.xyz;
	ECPosition = MVMatrix * MCVertex;
	ECBallCenter = MVMatrix * MCBallCenter;
	gl_Position = MVMatrix *MCVertex;
}

