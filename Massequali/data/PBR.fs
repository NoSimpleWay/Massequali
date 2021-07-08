

#version 330 core
out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;
in vec2 ReflectionTexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

float c_r;
float c_g;
float c_b;

uniform float brightness_multiplier = 10.0f;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	c_r = clamp (texture(texture2, vec2(gl_FragCoord.x / 1920.0f * 0.3f + 0.3f, ReflectionTexCoord.y)).r * brightness_multiplier, 0.0f, 2.1f);
	c_g = clamp (texture(texture2, vec2(gl_FragCoord.x / 1920.0f * 0.3f + 0.3f, ReflectionTexCoord.y)).g * brightness_multiplier, 0.0f, 2.1f);
	c_b = clamp (texture(texture2, vec2(gl_FragCoord.x / 1920.0f * 0.3f + 0.3f, ReflectionTexCoord.y)).b * brightness_multiplier, 0.0f, 2.1f);
	
	FragColor = texture(texture1, TexCoord) * ourColor * vec4(c_r, c_g, c_b, 1.0f);
	
	//FragColor.rgb = vec3(ReflectionTexCoord.y);
	//FragColor.r = gl_FragCoord.x / 1920.0f;
	//FragColor.g = gl_FragCoord.y / 1080.0f;
	//FragColor.b = 0.0f;
}

