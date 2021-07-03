#pragma once

#include "EColor.h"
#include "EGabarite.h"
#include <vector>


class Batcher
{

public:
	struct EPolygonVertex
	{
		float* position_x = new float(0.0f);
		float* position_y = new float(0.0f);

		EPolygonVertex();
		~EPolygonVertex();

		bool* is_catched = new bool(false);

		std::vector <float*> float_vector;
	};

	struct EPolygonShape
	{
		std::vector<EPolygonVertex*> vertex_list;

		EPolygonVertex* selected_vertex = NULL;

		bool* catched_up_side =		new bool(false);
		bool* catched_down_side =	new bool(false);
		bool* catched_left_side =	new bool(false);
		bool* catched_right_side =	new bool(false);

		bool* catched_mid_side =	new bool(false);

		float* pos_x = new float(0.0f);
		float* pos_y = new float(0.0f);

		float* size_x = new float(0.0f);
		float* size_y = new float(0.0f);


		EPolygonShape();
		~EPolygonShape();
	};

	struct EPolygonMassive
	{
		std::vector<EPolygonShape*> shape_list;

		EPolygonMassive();
		~EPolygonMassive();
	};

	Batcher();

	void init();
	void init_shadowmap();
	void init_terrain();
	void init_PBR();

	void draw_rect(float _x, float _y, float _w, float _h);
	void draw_rect_position(float _x, float _y, float _x2, float _y2);
	void draw_rect_without_color(float _x, float _y, float _w, float _h, int _tx, int _ty);
	void draw_with_custom_uv(float _x, float _y, float _w, float _h, float _start_x, float _start_y, float _end_x, float _end_y);

	void draw_gabarite_screen_space(float _start_x, float _start_y, float _size_x, float _size_y, EGabarite* _g);

	void draw_gabarite(float _x, float _y, float _w, float _h, EGabarite* _g);

	void draw_sprite(float _x, float _y, float _w, float _h, float _left, float _right, float _down, float _up, EGabarite* _g);
	void draw_sprite_PBR(float _x, float _y, float _w, float _h, float _left, float _right, float _down, float _up, EGabarite* _g, float _z);

	void draw_AO_shadow(float _x, float _y, float _size_x, float _size_y, float _size, EGabarite* _g);

	void draw_depthmap_polygon	(EPolygonMassive* _p_massive, float _start_x, float _start_y, float _size_x, float _size_y, EGabarite* _g);
	void draw_normalmap_polygon	(EPolygonMassive* _p_massive, float _start_x, float _start_y, float _size_x, float _size_y, EGabarite* _g);

	void draw_two_dimension_gradient	(float _start_x, float _start_y, float _size_x, float _size_y, EGabarite* _g, EColor* _color_x, EColor* _color_y);



	void draw_gabarite(float _x, float _y, EGabarite* _g);

	void draw_terrain(float _x, float _y, EGabarite* _g);
	void draw_terrain_with_offset(float _x, float _y, float _left, float _right, float _up, float _down, EGabarite* _g);

	void draw_gabarite_skew(float _x, float _y, float _collision_x, float _collision_y, float _tall, EGabarite* _g, float _bottom_skew);
	void draw_gabarite_ark_shadow(float _x, float _y, EGabarite* _g);

	void draw_gabarite_shadowmap(float _x, float _y, float _w, float _h, EGabarite* _g, EGabarite* _supermap, float _z);
	void draw_gabarite_shadowmap_fragment(float _x, float _y, float _w, float _h, EGabarite* _g, EGabarite* _supermap, float _z, float _fx, float _fy);
	void draw_gabarite_shadowmap_fragment_mirrored(float _x, float _y, float _w, float _h, EGabarite* _g, EGabarite* _supermap, float _z, float _fx, float _fy);

	void draw_gabarite_with_offset(float _x, float _y, float _w, float _h, float _offset_x, float _offset_y, float _offset_end_x, float _offset_end_y, EGabarite* _g);

	void fill_indices();

	void setcolor_255(int _r, int _g, int _b, int _a);
	void setcolor(float _r, float _g, float _b, float _a);
	~Batcher();

	float batch_color_r;
	float batch_color_g;
	float batch_color_b;
	float batch_color_a;

	int batch_force_draw_call = 12000;

	void reinit();

	unsigned int id = 0;
	unsigned int VBO, VAO, EBO = 0;

	unsigned int indices_id = 0;
	unsigned int indices_order = 0;

	float vertices[1000 * 32];
	unsigned int indices[1000 * 6];

	void draw_call();
	void draw_call_terrain();
	void draw_call_shadowmap();

	void reset();

	void setcolor(EColor* _color);
	void setcolor(EColorCollection* _color);

	void setcolor_lum(EColorCollection* _color, float _lum);
	void setcolor_alpha(EColorCollection* _color, float _a);
	void setcolor_lumalpha(EColorCollection* _color, float _lum, float _a);
	void draw_rama(float _x, float _y, float _sx, float _sy, float _t, EGabarite* _g);
	void draw_rama(float _x, float _y, float _sx, float _sy, float _t);
	void draw_rect_gabarite_custom_uv(float _x, float _y, float _w, float _h, EGabarite* _g, float _sx, float _sy, float _ex, float _ey);

	void draw_simple_rect(float _x, float _y, float _size_x, float _size_y);

	void force_draw_call();
	void force_draw_call_terrain();
	void force_draw_call_shadowmap();

	static float shadow_FBO_w;
	static float shadow_FBO_h;
	static float zoom;

	static float skew_factor;

	void set_interpolated_color(EColorCollection* _a, EColorCollection* _b, float _value);
};
