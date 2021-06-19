#pragma once
#include "NSW_api/EWindow.h"
#include "Entity.h"

class ExternalButtonAction
{
public:
	static void external_button_action_scroll_texture_list(EButton* _b, float _f);
	static void external_button_action_set_grid_region_auto_size(EButton* _b, float _f);
	static void external_button_action_import_data_from_entity_to_autobuilding_interface(EButton* _b, float _f);
	static void external_button_action_add_new_autobuilding_region(EButton* _b, float _f);
	static void external_button_action_remove_autobuilding_region(EButton* _b, float _f);
	static void external_button_action_select_autobuilding_base(EButton* _b, float _f);
	static void external_button_action_open_select_texture_window_for_autobuilding_region(EButton* _b, float _f);
	static void external_button_action_select_texture_for_autobuilding_region(EButton* _b, float _f);
	static void external_button_action_add_selected_region_to_autobuilding_group(EButton* _b, float _f);
	static void external_button_action_add_new_group_for_autobuilding(EButton* _b, float _f);
	static void external_button_action_select_autobuilding_group(EButton* _b, float _f);

	static void external_button_action_remove_autobuilding_group_element(EButton* _b, float _f);
	static void external_button_action_close_master_button_super_group(EButton* _b, float _f);

	static void external_button_action_set_button_value(EButton* _b, float _f);





	static Entity* get_entity();
	static bool valid_entity_select();
	static int get_autobuilding_base_id();
	static int get_autobuilding_group_element_id();
	static int get_autobuilding_group_id();

	static Entity::AutobiuldingGroup*				get_selected_autobuilding_group(Entity* _e);
	static Entity::AutobuildingGroupElement*		get_selected_autobuilding_group_element(Entity* _e);
	static Entity::AutobuildingBase*			get_selected_autobuilding_base(Entity* _e);
};