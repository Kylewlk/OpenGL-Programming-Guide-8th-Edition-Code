#version 410

layout (location = 0) out vec4 color;

in vec2 fsPos;

  
vec4 BrickColor = vec4(1.0,0.5,0.0,1.0);
vec4 MortarColor = vec4(0.8, 0.8, 0.8, 1.0);

vec2 BrickSize = vec2(0.3, 0.15);
vec2 BrickPct = vec2(0.8, 0.85); 
vec2 BrickPct2 = vec2(0.95, 0.85); 
vec2 MortarPct = vec2(1.0) - BrickPct;
 
vec2 Integral(vec2 x, vec2 p)
{
	vec2 f = (floor(x )*(p));
	vec2 m = max(fract(x)-(vec2(1.0) - p), vec2(0.0));
	
	return f+m;
} 
   
void main(void)
{
	vec2 position, fw, useBrick;
	
	// Determine position within the brick pattern
	position = fsPos / BrickSize;
	
	// Adjust every other row by an offset of half a brick
	if (fract(position.y * 0.5) >= 0.5)
		position.x += 0.5;	
		
		
	// Calculate filter size
	fw = min(fwidth(position), vec2(0.05));
	//fw = vec2(0.0025);
	//fw.x = dFdx(position.x) + min(dFdy(position.x), 0.02);
	//fw.y = dFdx(position.y) + dFdy(position.y);;
	
	// if(dFdy(position.x) <= 0.6)//dFdy(position.x)有时值会很大
	// {
		// color = vec4(0.0, 1.0, 0.0, 1.0);
	// }
	// else
	// {
		// color = vec4(1.0, 0.0, 0.0, 1.0);
	// }
	
	// Perform filtering by integrating the 2D pulse made by the
	// brick pattern over the filter width and height
	useBrick = (Integral(position + fw, BrickPct)- Integral(position, BrickPct))   / fw;
	
	// Determine final color
	color = min(mix(MortarColor, BrickColor, useBrick.x * useBrick.y), vec4(1.0));

}

