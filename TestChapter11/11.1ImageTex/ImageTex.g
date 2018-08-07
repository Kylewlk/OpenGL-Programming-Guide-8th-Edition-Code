#version 430 core

layout (binding = 1, rgba32f) uniform image2D  buf;

out vec4 FragColor;

in vec3 Normal;

void main()
{
	vec4 color;
	color = vec4(0.6, 1.0, 0.3, 1.0) * abs(Normal.z);
	
	imageStore(buf, ivec2(gl_FragCoord.x-150, gl_FragCoord.y-150), color);
	imageStore(buf, ivec2(gl_FragCoord.x-150, gl_FragCoord.y+150), color);
	imageStore(buf, ivec2(gl_FragCoord.x+150, gl_FragCoord.y-150), color);
	imageStore(buf, ivec2(gl_FragCoord.x+150, gl_FragCoord.y+150), color);
	FragColor = color;
}


