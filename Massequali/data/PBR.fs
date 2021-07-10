

#version 330 core
out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;
in vec2 ReflectionTexCoord;
in vec2 NormalGlossMapTexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform sampler2D SD_array[6];




float c_r;
float c_g;
float c_b;

uniform float brightness_multiplier = 10.0f;
uniform float input_gloss = 1.0f;

float level = 0.0f;
int glossy_flat = 0;
float ipr = 0.5f;
float interpolation_A = 1.0f;
float interpolation_B = 0.0f;

float gloss_power = 0.0f;

vec2 reflect_coord;

float gloss_result = 1.0f;
float matte_result = 0.0f;

void main()
{
	//gloss_power = 1.0f - (ReflectionTexCoord.y - 0.333f) * 3.0f ;
	gloss_power = input_gloss;
	gloss_power = texture(texture1, NormalGlossMapTexCoord).b;
	
	level = (1.0f - gloss_power) * 5.0;
	
	glossy_flat = clamp(int(floor(level)), 0, 5);
	interpolation_B = level - glossy_flat;
	interpolation_A = 1.0f - interpolation_B;
	
	
	
	reflect_coord = vec2(gl_FragCoord.x / 1920.0f * 0.3f + 0.3f, ReflectionTexCoord.y);
	
	//glossy_flat = 4;
	if (glossy_flat == 0)
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	{
		c_r = clamp ((texture(SD_array[0], reflect_coord).r * interpolation_A + texture(SD_array[1], reflect_coord).r * interpolation_B) * brightness_multiplier, 0.0f, 1.5f);
		c_g = clamp ((texture(SD_array[0], reflect_coord).g * interpolation_A + texture(SD_array[1], reflect_coord).g * interpolation_B) * brightness_multiplier, 0.0f, 1.25f);
		c_b = clamp ((texture(SD_array[0], reflect_coord).b * interpolation_A + texture(SD_array[1], reflect_coord).b * interpolation_B) * brightness_multiplier, 0.0f, 1.0f);
	}
	
	if (glossy_flat == 1)
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	{
		c_r = clamp ((texture(SD_array[1], reflect_coord).r * interpolation_A + texture(SD_array[2], reflect_coord).r * interpolation_B) * brightness_multiplier, 0.0f, 1.5f);
		c_g = clamp ((texture(SD_array[1], reflect_coord).g * interpolation_A + texture(SD_array[2], reflect_coord).g * interpolation_B) * brightness_multiplier, 0.0f, 1.25f);
		c_b = clamp ((texture(SD_array[1], reflect_coord).b * interpolation_A + texture(SD_array[2], reflect_coord).b * interpolation_B) * brightness_multiplier, 0.0f, 1.0f);
	}
	
	if (glossy_flat == 2)
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	{
		c_r = clamp ((texture(SD_array[2], reflect_coord).r * interpolation_A + texture(SD_array[3], reflect_coord).r * interpolation_B) * brightness_multiplier, 0.0f, 1.5f);
		c_g = clamp ((texture(SD_array[2], reflect_coord).g * interpolation_A + texture(SD_array[3], reflect_coord).g * interpolation_B) * brightness_multiplier, 0.0f, 1.25f);
		c_b = clamp ((texture(SD_array[2], reflect_coord).b * interpolation_A + texture(SD_array[3], reflect_coord).b * interpolation_B) * brightness_multiplier, 0.0f, 1.0f);
	}                                                                                                                                                                   
	                                                                                                                                                                    
	if (glossy_flat == 3)                                                                                                                                               
	// linearly interpolate between both textures (80% container, 20% awesomeface)                                                                                      
	{                                                                                                                                                                   
		c_r = clamp ((texture(SD_array[3], reflect_coord).r * interpolation_A + texture(SD_array[4], reflect_coord).r * interpolation_B) * brightness_multiplier, 0.0f, 1.5f);
		c_g = clamp ((texture(SD_array[3], reflect_coord).g * interpolation_A + texture(SD_array[4], reflect_coord).g * interpolation_B) * brightness_multiplier, 0.0f, 1.25f);
		c_b = clamp ((texture(SD_array[3], reflect_coord).b * interpolation_A + texture(SD_array[4], reflect_coord).b * interpolation_B) * brightness_multiplier, 0.0f, 1.0f);
	}
	
	if (glossy_flat == 4)
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	{
		c_r = clamp ((texture(SD_array[4], reflect_coord).r * interpolation_A + texture(SD_array[5], reflect_coord).r * interpolation_B) * brightness_multiplier, 0.0f, 1.5f);
		c_g = clamp ((texture(SD_array[4], reflect_coord).g * interpolation_A + texture(SD_array[5], reflect_coord).g * interpolation_B) * brightness_multiplier, 0.0f, 1.25f);
		c_b = clamp ((texture(SD_array[4], reflect_coord).b * interpolation_A + texture(SD_array[5], reflect_coord).b * interpolation_B) * brightness_multiplier, 0.0f, 1.0f);
	}
	
	if (glossy_flat == 5)
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	{
		c_r = clamp ((texture(SD_array[5], reflect_coord).r) * brightness_multiplier, 0.0f, 2.1f);
		c_g = clamp ((texture(SD_array[5], reflect_coord).g) * brightness_multiplier, 0.0f, 2.1f);
		c_b = clamp ((texture(SD_array[5], reflect_coord).b) * brightness_multiplier, 0.0f, 2.1f);
	}
	
	gloss_result = gloss_power;
	//gloss_result = 1.0f;
	
	matte_result = (1.0f - gloss_power);
	//matte_result = 0.0f;
	
	
	
	FragColor = texture(texture1, TexCoord)
	*
	ourColor
	*
	vec4
	(
		c_r * gloss_result + matte_result,
		c_g * gloss_result + matte_result,
		c_b * gloss_result + matte_result,
	1.0f
	);
	//FragColor = vec4(glossy_flat,glossy_flat,glossy_flat,1.0f);
	
	//FragColor.rgb = vec3(ReflectionTexCoord.y);
	//FragColor.r = gl_FragCoord.x / 1920.0f;
	//FragColor.g = gl_FragCoord.y / 1080.0f;
	//FragColor.b = 0.0f;
}

