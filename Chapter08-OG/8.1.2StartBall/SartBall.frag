#version 330 core

vec4 HalfSpace[5];

float StripeWidth = 0.3;
float InOrOutInit = -3.0; // -3.0
float FWidth = 0.005; // = 0.005

vec4 StarColor = vec4(0.6, 0.0, 0.0, 1.0);
vec4 StripeColor = vec4(0.0, 0.3, 0.6, 1.0);
vec4 BaseColor = vec4(0.6, 0.5, 0.0, 1.0);

vec4 LightDir = vec4(0.57735, 0.57735, 0.57735, 0.0); // light direction, should be normalized
vec4 HVector = vec4(0.32506, 0.32506, 0.88808, 0.0); // reflection vector for infinite light
vec4 SpecularColor = vec4(1.0, 1.0, 1.0, 1.0);
float SpecularExponent = 200.0;


float Ka=0.3;
float Kd=0.7;
float Ks=0.4;

in vec4 ECPosition; // surface position in eye coordinates
in vec3 OCPosition; // surface position in object coordinates
flat in vec4 ECBallCenter; // ball center in eye coordinates


out vec4 FragColor;


void main()
{
	HalfSpace[0] = vec4(1.0, 0.0, 0.0, 0.2);
	HalfSpace[1] = vec4(0.309016994, 0.951056516, 0.0, 0.2);
	HalfSpace[2] = vec4(-0.809016994, 0.587785252, 0.0, 0.2);
	HalfSpace[3] = vec4(-0.809016994, -0.587785252, 0.0, 0.2);
	HalfSpace[4] = vec4(0.309016994, -0.951056516, 0.0, 0.2);
	
	
	vec3 normal; // Analytically computed normal
	vec4 pShade; // Point in shader space
	vec4 surfColor; // Computed color of the surface
	float intensity; // Computed light intensity
	vec4 distance; // Computed distance values
	float inorout; // Counter for classifying star pattern
	
	pShade.xyz = normalize(OCPosition.xyz);
	pShade.w = 1.0;
	
	inorout = InOrOutInit; // initialize inorout to -3.0
	
	distance[0] = dot(pShade, HalfSpace[0]);
	distance[1] = dot(pShade, HalfSpace[1]);
	distance[2] = dot(pShade, HalfSpace[2]);
	distance[3] = dot(pShade, HalfSpace[3]);
	
	//float FWidth = fwidth(pShade);
	distance = smoothstep(-FWidth, FWidth, distance);
	
	inorout += dot(distance, vec4(1.0));
	
	distance.x = dot(pShade, HalfSpace[4]);
	distance.y = StripeWidth - abs(pShade.z);
	distance.xy = smoothstep(-FWidth, FWidth, distance.xy);
	inorout += distance.x;
	
	inorout = clamp(inorout, 0.0, 1.0);
	
	surfColor = mix(BaseColor, StarColor, inorout);
	surfColor = mix(surfColor, StripeColor, distance.y);
	
	// Calculate analytic normal of a sphere
	normal = normalize(ECPosition.xyz-ECBallCenter.xyz);
	
	// Per-fragment diffuse lighting
	intensity = Ka; // ambient
	intensity += Kd * clamp(dot(LightDir.xyz, normal), 0.0, 1.0);

	surfColor *= intensity;
	
	
	// Per-fragment specular lighting
	intensity = clamp(dot(HVector.xyz, normal), 0.0, 1.0);
	intensity = Ks * pow(intensity, SpecularExponent);
	surfColor.rgb += SpecularColor.rgb * intensity;
	FragColor = surfColor;
}

