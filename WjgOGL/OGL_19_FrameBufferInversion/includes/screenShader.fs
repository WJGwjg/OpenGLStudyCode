#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

//片段着色器会更加基础，我们做的唯一一件事就是从生成的纹理中采样
void main()
{    
    //FragColor = texture(texture1, TexCoords);
	//FragColor = texture(screenTexture, TexCoords);

	//Inversion反相：在片段着色器中仅仅使用一行代码，就能让整个场景的颜色都反相了
	FragColor = vec4(vec3(1.0 - texture(screenTexture, TexCoords)), 1.0);
}