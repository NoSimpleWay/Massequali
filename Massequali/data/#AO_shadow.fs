

#version 330 core
out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

float lum = 0.0f;

void main()
{
	lum = ourColor.r;
	lum = 1.0f - pow(1.0f - lum, 3.0f);
	lum = 1.0f - (1.0f - lum)/4.0f;
	
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragColor.rgb = texture(texture1, TexCoord).rgb * lum;
	FragColor.a = texture(texture1, TexCoord).a * ourColor.a;
	
}

