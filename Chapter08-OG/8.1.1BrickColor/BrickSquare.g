#version 410

layout (location = 0) out vec4 color;

in vec2 fsPos;
  
vec4 BrickColor = vec4(1.0,0.5,0.0,1.0);
vec4 MortarColor = vec4(0.8, 0.8, 0.8, 1.0);

vec2 BrickSize = vec2(0.3, 0.15);
vec2 BrickPct = vec2(0.9, 0.9); //BrickColor颜色在砖中占的比例，剩余则为MortarColor
vec2 BrickPct2 = vec2(0.905, 0.905); 
  
   
void main(void)
{
	vec2 position, userBrick;
	
	position = fsPos/BrickSize;
	
	//这两行与下面if-else代码效果完全一致
	// if(fract(position.y *0.5) > 0.5)
		// position.x += 0.5;
		
	if (position.y > 0)//X轴上半部分
	{
		if(int(position.y)%2 == 1)//奇数行
		{
			position.x += 0.5;//使得砖灰MortarColor绘制在砖的中部
		}
	}
	else//X轴下半部分
	{
		if(int(position.y)%2 == 0)//偶数行
		{
			position.x += 0.5;//使得砖灰MortarColor绘制在砖的中部
		}
	}
			
	position = fract(position);
	userBrick = step(BrickPct,position);
	//userBrick = smoothstep(BrickPct, BrickPct2, position);
	userBrick = vec2(1.0)- userBrick;
	vec4 finalColor= mix(MortarColor, BrickColor, userBrick.x*userBrick.y);

    color =finalColor;
}

