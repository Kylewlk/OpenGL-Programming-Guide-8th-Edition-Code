#version 430 core

layout (binding = 0, rgba32f) uniform image2D  col;

uniform sampler2D tex;

in vec2 texPos;

out vec4 FragColor;


void main()
{
	FragColor = imageLoad(col, ivec2(gl_FragCoord.xy));
	
	//FragColor = texture(tex, texPos);
	//FragColor = vec4(0.6, 0.0, 0.2, 1.0);
	if(length(FragColor) < 0.0001)
	 discard;
}



