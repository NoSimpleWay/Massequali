#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec2 reflectionTexCoord;
layout (location = 4) in vec2 normalGlossMapTexCoord;

out vec4 ourColor;
out vec2 TexCoord;
out vec2 ReflectionTexCoord;
out vec2 NormalGlossMapTexCoord;

out vec3 WorldPosition;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	
	ourColor = aColor;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	ReflectionTexCoord = vec2(reflectionTexCoord.x, reflectionTexCoord.y);
	NormalGlossMapTexCoord = vec2(normalGlossMapTexCoord.x, normalGlossMapTexCoord.y);
	
	WorldPosition
	=
	vec3
	(
		(gl_Position.x + 1.0f) / 2.0f,
		(gl_Position.y + 1.0f) / 2.0f,
		(gl_Position.z + 1.0f) / 2.0f
	);
	
	gl_Position = transform * vec4(aPos.x, aPos.y + aPos.z, 1.0, 1.0);
}