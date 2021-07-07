

#version 330 core
out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float blur_size_x = 1.0f/4096.0f;
uniform float blur_size_y = 1.0f/4096.0f;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragColor.rgba
	=
	(
		texture(texture1, TexCoord)
		+
		
		texture(texture1, TexCoord + vec2(-blur_size_x, blur_size_y))
		+
		texture(texture1, TexCoord + vec2(0.0f, blur_size_y))
		+
		texture(texture1, TexCoord + vec2(blur_size_x, blur_size_y))
		+
		
		texture(texture1, TexCoord + vec2(-blur_size_x, 0.0f))
		+
		texture(texture1, TexCoord + vec2(blur_size_x, 0.0f))
		
		
		+
		texture(texture1, TexCoord + vec2(-blur_size_x, -blur_size_y))
		+
		texture(texture1, TexCoord + vec2(0.0f, -blur_size_y))
		+
		texture(texture1, TexCoord + vec2(blur_size_x, -blur_size_y))
	)
	/
	9.0f
	*
	ourColor.rgba;
	//FragColor.r = gl_FragCoord.x / 1920.0f;
	//FragColor.g = gl_FragCoord.y / 1080.0f;
	//FragColor.b = 0.0f;
}

