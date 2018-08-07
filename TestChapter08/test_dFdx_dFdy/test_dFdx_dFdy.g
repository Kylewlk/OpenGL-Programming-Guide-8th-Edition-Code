#version 410

layout (location = 0) out vec4 color;

in vec2 fsPos;
in float fsfp;
  
  
   
void main(void)
{
	float dp = dFdx(fsfp);
	// float dp = dFdy(fsPos.y);
	
	if(dp <= 2.0)
	{
		color = vec4(0.0, 1.0, 0.0, 1.0);
	}
	else
	{
		color = vec4(1.0, 0.0, 0.0, 1.0);
	}
	
	
	
	color = color*(ceil((fsfp+300.0)/100.0)/10.0);
}

