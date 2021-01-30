#version 410 core

out vec4 FragColor;

vec3 C1 = vec3(0.1, 0.3, 0.1);
vec3 C2 = vec3(1.0, 1.0, 1.0);

vec3 C3 = (C1+C2)/2.0;

in vec2 fsPos;
in vec2 fsTex;

float Freq = 10.0;

void main()
{
	vec3 color;
	// vec2 texCoord = fsTex * Freq;
	// if(fract(texCoord.y) >= 0.5)
		// texCoord.x += 0.5;
	// texCoord = fract(texCoord);
	// color = mix(C1, C2, step(0.5, texCoord.x));
	// FragColor = vec4(color, 1.0);

	 // Determine the width of the projection of one pixel into
	// s-t space
	vec2 fw = fwidth(fsTex);
	
	// Determine the amount of fuzziness
	vec2 fuzz = fw * Freq * 2.0;
	float fuzzMax = max(fuzz.s, fuzz.t);
	
	// Determine the position in the checkerboard pattern
	vec2 checkPos = fract(fsTex * Freq);
	if (fuzzMax < 0.5)
	{
		// If the filter width is small enough,
		// compute the pattern color
		vec2 p = smoothstep(vec2(0.5), vec2(0.5)+ fuzz, checkPos) + (vec2(1.0) - smoothstep(vec2(0.0), fuzz, checkPos));
		color = mix(C1, C2, p.x * p.y + (1.0 - p.x) * (1.0 - p.y));
		
		// Fade in the average color when we get close to the limit
		color=mix(color,C3,smoothstep(0.125,0.5,fuzzMax));
	}
	else
	{
		// Otherwise, use only the average color
		color = C3;
	}
	FragColor = vec4(color, 1.0); 
}






