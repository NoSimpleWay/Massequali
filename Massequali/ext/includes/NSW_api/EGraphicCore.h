#pragma once


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "EGabarite.h"

#include <stb_image.h>
#include <learnopengl/shader_s.h>
#include "NSW_api/Batcher.h"
#include "EGabarite.h"
#include <vector>

class EGraphicCore {
public:
	static unsigned char* data1;
	static unsigned int texture[32];
	static int width, height, nrChannels;

	static int last_texture_w;
	static int last_texture_h;

	static Shader* ourShader;
	static Shader* shadowmap;
	static Shader* shader_terrain;
	static Shader* lightmap_blur;
	static Shader* lightmap_spread;

	static Batcher* batch;
	static Batcher* batch_shadowmap;
	static Batcher* batch_terrain;

	static glm::mat4 matrix_transform;

	static int SCR_WIDTH;
	static int SCR_HEIGHT;

	static float correction_x;
	static float correction_y;

	static void load_texture(char const* _path, int _id);

	static std::vector<EGabarite*> gabarite_list;
	//static std::vector<EGabarite*> gabarite_collection;

	static EGabarite* gabarite_white_pixel;
	static EGabarite* gabarite_tileset;
	static EGabarite* gabarite_small_wood_button_bg;
	static EGabarite* gabarite_wood_button_bg;
	static EGabarite* gabarite_ERROR;
	static EGabarite* gabarite_radial_button;
	static EGabarite* gabarite_radial_button_dot;
	static EGabarite* gabarite_supermap_placeholder;
	static EGabarite* gabarite_full_atlas;

	EGraphicCore();
	~EGraphicCore();

	

	struct ESprite
	{
		EGabarite* texture_gabarite = NULL;

		float*	 offset_x = new float(0.0f);
		float*	 offset_y = new float(0.0f);
		float*	 offset_z = new float(0.0f);

		float*	 fragment_x = new float(0.0f);
		float*	 fragment_y = new float(0.0f);

		float*	 fragment_left = new float(0.0f);
		float*	 fragment_right = new float(0.0f);
		float*	 fragment_down = new float(0.0f);
		float*	 fragment_up = new float(0.0f);

		float* size_x = new float(10.0f);
		float* size_y = new float(10.0f);

		~ESprite();
	};

	struct sprite_array
	{
		std::vector <ESprite*> sprite_list;

		//Entity* master_entity;
		//EButton* master_button;
	};

	static void draw_sprite_regular(sprite_array* _sprite_array, Batcher* _batch, float _offset_x, float _offset_y, float _offset_z);
	static void reset_sprite_data(EGraphicCore::ESprite* _sprite);
	
};