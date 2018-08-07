#version 410 core

out vec4 FragColor;

uniform float dt;

vec3 C1 = vec3(0.9, 0.3, 0.1);
vec3 C2 = vec3(1.0, 1.0, 0.0);

vec3 C3 = (C1+C2)/2.0;

in vec2 fsPos;
in vec2 fsTex;


vec2 hash22(vec2 p)
{
    p = vec2( dot(p,vec2(127.1,311.7)),
              dot(p,vec2(269.5,183.3)));

    return -1.0 + 2.0 * fract(sin(p)*43758.5453123);
}
float noise(vec2 p)
{
    vec2 pi = floor(p);
    vec2 pf = p - pi;

    vec2 w = pf * pf * (3.0 - 2.0 * pf);

    return mix(mix(dot(hash22(pi + vec2(0.0, 0.0)), pf - vec2(0.0, 0.0)), 
                   dot(hash22(pi + vec2(1.0, 0.0)), pf - vec2(1.0, 0.0)), w.x), 
               mix(dot(hash22(pi + vec2(0.0, 1.0)), pf - vec2(0.0, 1.0)), 
                   dot(hash22(pi + vec2(1.0, 1.0)), pf - vec2(1.0, 1.0)), w.x),
               w.y);
}


float noise_sum_abs_sin(vec2 p)
{
    float f = 0.0;
    p = p * 7.0;
    f += 1.0000 * abs(noise(p)); p = 2.0 * p;
    f += 0.5000 * abs(noise(p)); p = 2.0 * p;
    f += 0.2500 * abs(noise(p)); p = 2.0 * p;
    f += 0.1250 * abs(noise(p)); p = 2.0 * p;
    f += 0.0625 * abs(noise(p)); p = 2.0 * p;
    f = sin(f + p.x/32.0);

    return f;
}

float noise_sum(vec2 p)
{
    float f = 0.0;
    p = p * 4.0;
    f += 1.0000 * noise(p); p = 2.0 * p;
    f += 0.5000 * noise(p); p = 2.0 * p;
    f += 0.2500 * noise(p); p = 2.0 * p;
    f += 0.1250 * noise(p); p = 2.0 * p;
    f += 0.0625 * noise(p); p = 2.0 * p;

   return f;
}

float noise_sum_abs(vec2 p)
{
    float f = 0.0;
    p = p * 7.0;
    f += 1.0000 * abs(noise(p)); p = 2.0 * p;
    f += 0.5000 * abs(noise(p)); p = 2.0 * p;
    f += 0.2500 * abs(noise(p)); p = 2.0 * p;
    f += 0.1250 * abs(noise(p)); p = 2.0 * p;
    f += 0.0625 * abs(noise(p)); p = 2.0 * p;

    return f;
}

void main()
{
	vec2 Tex = fsTex;
	if(dt > 0.00001)
	{
		 Tex.x += noise_sum(fsPos + vec2(dt, dt))/40.0;
	}

	vec3 color = mix(C1, C2, noise_sum(Tex));
	
	
	FragColor = vec4(color, 1.0); 
}






