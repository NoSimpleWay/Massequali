#pragma once
#include "NSW_api/EWindow.h"
#include "Entity.h"
#include "ExternalEnums.h"


class EWindowMain : public EWindow
{
public:
	EWindowMain();
	void create_button_groups();
	~EWindowMain();

	ECluster* cluster_list[100][100];

	static EButton::button_super_group*		super_group_texture_collection_link;
	static EButton::button_group*			group_texture_collection_link;

	static EButton::button_super_group*		super_group_task_bar_link;
	static EButton::button_group*			group_task_bar_link;

	static EButton::button_super_group*		super_group_autobuilding;

	static EButton::button_group*			group_grid_region_edit_link;
	static EButton::button_group*			group_grid_region_second_layer_link;
	static EButton::button_group*			group_grid_entity_list_link;
	static EButton::button_group*			button_group_autobuilding_base;

	static EButton::button_group*			button_group_autobuilding_group_element;
	static EButton::button_group*			button_group_autobuilding_group;
	static EButton::button_group*			group_grid_autobuilding_draw_order;

	static EButton::button_super_group*		super_group_vertex_editor;
	static EButton::button_group*			group_vertex_editor;
	static EButton::button_group*			group_vertex_normal_color_editor;
	static EButton*							link_to_button_vertex_editor;
	static EButton*							link_to_button_two_dimension_gradient;

	static EButton::button_super_group*		super_group_world_setting;
	static EButton::button_group*			group_world_setting_sun;
	static EButton*							link_to_button_sun_position;


	static EButton*							grid_region_edit_button_link;

	static std::vector<EButton*>			auto_size_region_button;

	static EButton*							space_between_sprites_x_button;
	static EButton*							space_between_sprites_y_button;

	static EButton*							link_button_subdivision_mid_x;
	static EButton*							link_button_subdivision_mid_y;

	static EButton*							link_button_sprite_push_direction;
	static EButton*							link_button_sprite_fill_mode;
	static EButton*							link_button_sprite_random_count;
	static EButton*							link_button_selected_sprite_draw_mode;

	static EButton*							link_button_autobuilding_seed;

	static EButton*							link_button_autobuilding_random_offset_x;
	static EButton*							link_button_autobuilding_random_offset_y;

	static std::vector<Entity*>				selected_entities;

	static EButton::EGridRegion*			entity_selection_region;
	static bool								is_entity_selection_started;

	static EButton* create_button_for_task_list(EWindow* _window, EButton::button_super_group* _super_group, EButton::button_group* _group, bool* _target_bool, std::string _text);

	static bool is_entity_in_region(Entity* _e, EButton::EGridRegion* _gr);

	EButton* textures_selector_slider;
	virtual void draw(float _d);
	virtual void update(float _d);

	void entity_selection_process(std::vector<Entity*> _v);

	void autobuilding_updater(std::vector<Entity*> _v);

	void reset_render();
	void draw_terrain();

	void generate_AO_shadow();

	//static std::vector<Entity*> entity_list;

	static ECamera* main_camera;

	static float get_real_world_position_x_by_mouse(ECamera* _camera);
	static float get_real_world_position_y_by_mouse(ECamera* _camera);

	static void update_selected_entity_list();
	static void create_new_elements_of_autobuilding_if_need(Entity* _e);

	EGraphicCore::ESprite* create_new_sprite_if_need(int selected_sprite_id, Entity* _e, std::string _text);

	static void add_new_sprite_if_need(int _i, Entity* _e, std::string _text);
	static void add_new_sprite_to_group_if_need(int _i, Entity::AutobuildingGroup* _gr, std::string _text);

	static void generate_building(Entity* _e);

	static void convert_size_to_fragment(EGabarite* _g, float _offset_x, float _offset_y, float _size_x, float _size_y, float* _left_side, float* _right_side, float* _down_side, float* _up_side);

	static void save_map(std::string _name);
	static void add_entity_data_to_save_string(Entity* e);
	static void load_map(std::string _name);
	static std::string w_string;
	static ECluster* cluster_static[ECluster::CLUSTED_DIM_X][ECluster::CLUSTED_DIM_Y];
	static ECluster* cluster_non_static[ECluster::CLUSTED_DIM_X][ECluster::CLUSTED_DIM_Y];

	static int cluster_draw_start_x;
	static int cluster_draw_start_y;

	static int cluster_draw_end_x;
	static int cluster_draw_end_y;

	static int terrain_draw_start_x;
	static int terrain_draw_start_y;
			   
	static int terrain_draw_end_x;
	static int terrain_draw_end_y;

	static std::vector<Entity*> draw_buffer;
	static std::vector<Entity::AutobuildingGroup*> draw_group_buffer;

	static int last_index;

	///
	static EGraphicCore::ESprite*	selected_sprite;
	
	static int						selected_sprite_id;

	static float					mid_wall_copies_x;
	static float					mid_wall_copies_y;

	static float					wall_full_size_x;
	static float					wall_full_size_y;

	static float					wall_fragment_x;
	static float					wall_fragment_y;

	static float					fragment_correction_factor_x;
	static float					fragment_correction_factor_y;

	static int						subdivision_x_count;
	static int						subdivision_y_count;

	///
	//EGabarite* terrain_texture;

	struct terrain_tile_struct
	{
		EGabarite* terrain_texture;
		EGabarite* normal_gloss_texture;

		float* texture_offset_x = new float(0.0f);
		float* texture_offset_y = new float(0.0f);

		float* size_x = new float(0.0f);
		float* size_y = new float(0.0f);

		terrain_tile_struct();
		~terrain_tile_struct();

	};

	static terrain_tile_struct* terrain_matrix[250][250];

	const int TILES_COUNT_X = 200;
	const int TILES_COUNT_Y = 200;


	enum GridRegionNameByOrder
	{
		GRID_REGION_NAME_BY_ORDER_LEFT_UP_CORNER,
		GRID_REGION_NAME_BY_ORDER_UP,
		GRID_REGION_NAME_BY_ORDER_RIGHT_UP_CORNER,

		GRID_REGION_NAME_BY_ORDER_LEFT,
		GRID_REGION_NAME_BY_ORDER_MID,
		GRID_REGION_NAME_BY_ORDER_RIGHT,

		GRID_REGION_NAME_BY_ORDER_LEFT_DOWN_CORNER,
		GRID_REGION_NAME_BY_ORDER_DOWN,
		GRID_REGION_NAME_BY_ORDER_RIGHT_DOWN_CORNER
	};

	enum AutoGridSizeButtonByOrder
	{
		AUTO_GRID_SIZE_BUTTON_BY_ORDER_UP,
		AUTO_GRID_SIZE_BUTTON_BY_ORDER_LEFT,
		AUTO_GRID_SIZE_BUTTON_BY_ORDER_RIGT,
		AUTO_GRID_SIZE_BUTTON_BY_ORDER_DOWN
	};

	static void put_entity_to_map(Entity* _e);

	static void draw_vertical_border_element(float _x, float _y, float _z, float _DH_offset, Entity::AutobuildingGroup* _group, Entity::AutobuildingGroupElement* _element, int _border_enum, float _texture_offset, int _id);
};