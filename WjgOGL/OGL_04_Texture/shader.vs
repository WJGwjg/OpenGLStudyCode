#version 330 core
layout (location = 0) in vec3 aPos;			// 位置变量的属性位置值为 0 
layout (location = 1) in vec3 aColor;		// 颜色变量的属性位置值为 1
layout (location = 2) in vec2 aTexCoord;	// 纹理坐标的属性位置值为 2

out vec3 ourColor;		// 为片段着色器指定一个颜色输出
out vec2 TexCoord;		// 把纹理坐标传递给片段着色器

void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
	TexCoord = aTexCoord;
}