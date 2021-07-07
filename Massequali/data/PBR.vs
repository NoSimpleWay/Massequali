#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec2 reflectionTexCoord;

out vec4 ourColor;
out vec2 TexCoord;
out vec2 ReflectionTexCoord;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(aPos, 1.0, 1.0);
	ourColor = aColor;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	ReflectionTexCoord = vec2(reflectionTexCoord.x, reflectionTexCoord.y);
}