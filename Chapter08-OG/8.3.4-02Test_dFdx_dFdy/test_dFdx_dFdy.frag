#version 430

layout (location = 0) out vec4 color;

layout (location = 1) uniform int type;

in vec2 fsPos;
in float fsfp;  
   
void main(void)
{
	float dp = 100;
	
	switch(type)
	{
	case 1:
		dp = dFdx(fsfp);
		if(1.999969<= dp && dp <= 2.0)//因为float精度问题不能直接用等于
		{
			color = vec4(0.0, 1.0, 0.0, 1.0);
		}
		else
		{
			color = vec4(1.0, 0.0, 0.0, 1.0);
		}
		break;
	case 2:
		dp = dFdy(fsfp);
		if(2.9999<= dp && dp <= 3.0)//因为float精度问题不能直接用等于
		{
			color = vec4(0.0, 1.0, 0.0, 1.0);
		}
		else
		{
			color = vec4(1.0, 0.0, 0.0, 1.0);
		}
		break;
	case 3:
		dp = dFdx(fsfp);
		if(dp == 2.0)//因为float精度问题有些位置不会是绿色
		{
			color = vec4(0.0, 1.0, 0.0, 1.0);
		}
		else
		{
			color = vec4(1.0, 0.0, 0.0, 1.0);
		}

		break;
	case 4:
		//dp = dFdy(fsPos.y);
		dp = dFdx(fsPos.x);
		if((2.0/400.0 - 0.0000001)<= dp && dp <= (2.0001/400.0))//因为float精度问题不能直接用等于
		{
			color = vec4(0.0, 1.0, 0.0, 1.0);
		}
		else
		{
			color = vec4(1.0, 0.0, 0.0, 1.0);
		}
		break;
	default:
		color = vec4(1.0, 0.0, 0.0, 1.0);

	}

}

