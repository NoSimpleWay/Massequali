#include "NSW_api/EWindow.h"
#include "Entity.h"

class EWindowMain : public EWindow
{
public:
	EWindowMain();
	~EWindowMain();

	ECluster* cluster_list[100][100];

	static EButton::button_super_group* super_group_texture_collection_link;
	static EButton::button_group* group_texture_collection_link;

	static EButton::button_super_group* super_group_autobuilding;

	static EButton::button_group* group_grid_region_edit_link;
	static EButton::button_group* group_grid_region_second_layer_link;
	static EButton::button_group* group_grid_entity_list_link;
	static EButton::button_group* button_group_autobuilding_base;

	static EButton::button_group* button_group_autobuilding_group_element;
	static EButton::button_group* button_group_autobuilding_group;
	static EButton::button_group* group_grid_autobuilding_draw_order;

	static EButton* grid_region_edit_button_link;

	static std::vector<EButton*> auto_size_region_button;

	static EButton* space_between_sprites_x_button;
	static EButton* space_between_sprites_y_button;

	static EButton* link_button_subdivision_mid_x;
	static EButton* link_button_subdivision_mid_y;

	static std::vector<Entity*> selected_entities;

	static EButton::EGridRegion* entity_selection_region;
	static bool is_entity_selection_started;

	static bool is_entity_in_region(Entity* _e, EButton::EGridRegion* _gr);

	EButton* textures_selector_slider;
	virtual void draw(float _d);
	virtual void update(float _d);

	void reset_render();

	static std::vector<Entity*> entity_list;

	ECamera* main_camera = new ECamera();

	static float get_real_world_position_x_by_mouse(ECamera* _camera);
	static float get_real_world_position_y_by_mouse(ECamera* _camera);

	static void update_selected_entity_list();
	static void import_data_from_entity_to_autobuilding_interface(Entity* _e);

	EGraphicCore::ESprite* create_new_sprite_if_need(int selected_sprite_id, Entity* _e, std::string _text);

	static void add_new_sprite_if_need(int _i, Entity* _e, std::string _text);

	static void generate_building(Entity* _e);

	static void convert_size_to_fragment(EGabarite* _g, float _offset_x, float _offset_y, float _size_x, float _size_y, float* _left_side, float* _right_side, float* _down_side, float* _up_side);

	static void save_map(std::string _name);
	static void load_map(std::string _name);

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
};