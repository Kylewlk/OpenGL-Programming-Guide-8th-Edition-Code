#version 430 core

out vec4 FragColor;


in vec2 fsPos;
in vec2 fsTex;



void main()
{	
		
	FragColor = vec4(1.0, 0.0, 0.0, 1.0) * fsTex.s + vec4(0.0, 1.0, 0.0, 1.0) * fsTex.t; 
}






