

#version 330 core
out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

float zNear = 0.1; 
float zFar  = 10000.0; 

float LinearizeDepth(float depth) 
{
    // преобразуем обратно в NDC
    float z = depth * 2.0 - 1.0; 
    return (2.0 * zNear * zFar) / (zFar + zNear - z * (zFar - zNear));	
}

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragColor = texture(texture1, TexCoord) * ourColor;
	//FragColor = vec4(gl_FragCoord.z * 100.0f, 0.0f, 0.0f, 1.0);
	//float depth = LinearizeDepth(gl_FragCoord.z) / zFar;
	//FragColor = vec4(vec3(depth), 1.0);
}

