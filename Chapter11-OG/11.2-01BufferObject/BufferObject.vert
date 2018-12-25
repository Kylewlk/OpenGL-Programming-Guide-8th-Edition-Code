#version 430


layout (location = 0) in vec4 position;
layout (location = 3) in vec2 TexCoord;

struct itemType
{
	vec4 pos;
	vec2 tex;
};

layout (std430, binding = 0) buffer bufferObject {
	int count;
	itemType items[8];//这里必须设置长度，否则会链接失败
	itemType items2[];//最后一个数组可不设置长度
};

out vec2 fsPos;
out vec2 fsTex;

void main(void)
{
    gl_Position = position;
	fsPos = position.xy;
	fsTex = TexCoord;

	//count = count + 1;//计数错误
	atomicAdd(count, 1);
	items[gl_VertexID].pos = position;
	items[gl_VertexID].tex = TexCoord;
}
