#include "EWindowMain.h"
#include "ExternalButtonAction.h"

# define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
#include <direct.h>
namespace fs = std::experimental::filesystem;

EButton::button_super_group* EWindowMain::super_group_texture_collection_link;
EButton::button_group* EWindowMain::group_texture_collection_link;

EButton::button_super_group* EWindowMain::super_group_autobuilding;

EButton::button_group* EWindowMain::group_grid_region_edit_link;
EButton::button_group* EWindowMain::group_grid_region_second_layer_link;
EButton::button_group* EWindowMain::group_grid_entity_list_link;
EButton::button_group* EWindowMain::button_group_autobuilding_base;

EButton::button_group* EWindowMain::button_group_autobuilding_group_element;
EButton::button_group* EWindowMain::button_group_autobuilding_group;
EButton::button_group* EWindowMain::group_grid_autobuilding_draw_order;

EButton* EWindowMain::grid_region_edit_button_link;

EButton* EWindowMain::space_between_sprites_x_button;
EButton* EWindowMain::space_between_sprites_y_button;

EButton* EWindowMain::link_button_subdivision_mid_x;
EButton* EWindowMain::link_button_subdivision_mid_y;

std::vector<EButton*>			EWindowMain::auto_size_region_button;

std::vector<Entity*>			EWindowMain::selected_entities;
EButton::EGridRegion* EWindowMain::entity_selection_region;

std::vector<Entity*>			EWindowMain::entity_list;
bool							EWindowMain::is_entity_selection_started = false;

EWindowMain::EWindowMain()
{
	EButton::button_super_group* just_created_button_super_group = new EButton::button_super_group();
	button_group_list.push_back(just_created_button_super_group);
	*just_created_button_super_group->position_x = 50.0f;
	*just_created_button_super_group->position_y = 50.0f;
	super_group_texture_collection_link = just_created_button_super_group;
	*just_created_button_super_group->is_active = false;

	//group_texture_variants
	EButton::button_group* just_created_button_group = new EButton::button_group();
	just_created_button_super_group->button_group_list.push_back(just_created_button_group);

	*just_created_button_group->can_be_stretched_x = false;
	*just_created_button_group->can_be_stretched_y = false;

	*just_created_button_group->size_x = 532.0f;
	*just_created_button_group->size_y = 500.0f;

	group_texture_collection_link = just_created_button_group;

	/*
	EButton* but = new EButton(0.0f, 0.0f, 50.0f, 20.0f);
	but->master_window = this;
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_Y;
	just_created_button_group->button_list.push_back(but);
	but->text = "A";

	but = new EButton(0.0f, 0.0f, 40.0f, 20.0f);
	but->master_window = this;
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_Y;
	just_created_button_group->button_list.push_back(but);
	but->text = "B";

	but = new EButton(0.0f, 0.0f, 30.0f, 20.0f);
	but->master_window = this;
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_Y;
	just_created_button_group->button_list.push_back(but);
	but->text = "C";

	but = new EButton(0.0f, 0.0f, 50.0f, 20.0f);
	but->master_window = this;
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_RESET_Y_AND_ADD_X;
	just_created_button_group->button_list.push_back(but);
	but->text = "D";*/

	EButton* but = NULL;

	for (auto& p : fs::directory_iterator("data/textures"))
	{
		{
			but = new EButton(0.0f, 0.0f, 20.0f, 20.0f);
			but->master_window = this;
			but->master_super_group = just_created_button_super_group;
			but->master_group = just_created_button_group;

			just_created_button_group->button_list.push_back(but);

			but->description_text = "" + p.path().filename().u8string().substr(0, p.path().filename().u8string().length() - 4);
			but->gabarite = ETextureAtlas::put_texture_to_atlas(p.path().u8string(), EWindow::default_texture_atlas);

			but->button_size_x = min(500.0f, max(10.0f, *but->gabarite->size_x));
			but->button_size_y = min(500.0f, max(10.0f, *but->gabarite->size_y));

			but->have_icon = true;
			but->have_bg = false;

			*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_X;
			*but->can_be_selected = true;
			but->have_rama = true;

			*but->is_double_click = true;
			but->action_on_left_double_click.push_back(&ExternalButtonAction::external_button_action_close_master_button_super_group);
		}
	}

	EButton* swap_button = NULL;
	for (int i = 0; i < just_created_button_group->button_list.size(); i++)
		for (int j = i; j < just_created_button_group->button_list.size(); j++)
			if
				(
					(i != j)
					&
					(
						*just_created_button_group->button_list.at(j)->gabarite->size_x * *just_created_button_group->button_list.at(j)->gabarite->size_y
						<
						*just_created_button_group->button_list.at(i)->gabarite->size_x * *just_created_button_group->button_list.at(i)->gabarite->size_y
						)
					)
			{
				swap_button = just_created_button_group->button_list.at(j);
				just_created_button_group->button_list.at(j) = just_created_button_group->button_list.at(i);
				just_created_button_group->button_list.at(i) = swap_button;
			}

	//vertical slider
	but = new EButton(-0.0f, 0.0f, 18.0f, *just_created_button_group->size_y);
	but->master_window = this;
	but->master_super_group = just_created_button_super_group;
	but->master_group = just_created_button_group;
	but->position_by_group_mode_x = Enums::PositionMode::RIGHT;
	but->is_slider = true;
	but->slider_is_horizontal = false;
	just_created_button_group->button_list.push_back(but);
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_FREE;
	textures_selector_slider = but;
	*but->can_be_hidden_by_search_deactivator = false;
	*but->auto_stretch_button_y_size = true;

	EButton::SimpleFloatChanger* just_created_SFC = new EButton::SimpleFloatChanger();
	*just_created_SFC->float_changer_type = EButton::SimpleFloatChanger::SimpleFloatChangerType::SIMPLE_FLOAT_CHANGER_BUTTON_VALUE;
	*just_created_SFC->selected_activation_type = EButton::ButtonSimpleChangerActivationType::CHANGER_ACTIVATION_TYPE_SLIDER_DRAG;
	just_created_SFC->target_float_pointer = just_created_button_group->button_y_scroll;
	*just_created_SFC->pre_correction_value = -0.5f;
	*just_created_SFC->selected_mathematic_type = EButton::ButtonSimpleChangerMathematic::BUTTON_SIMPLE_VALUE_MANIPULATOR_MATHEMATIC_ADD_VALUE;
	but->simple_float_changer_list.push_back(just_created_SFC);

	just_created_SFC = new EButton::SimpleFloatChanger();
	*just_created_SFC->float_changer_type = EButton::SimpleFloatChanger::SimpleFloatChangerType::SIMPLE_FLOAT_CHANGER_CONSTANT;
	*just_created_SFC->selected_activation_type = EButton::ButtonSimpleChangerActivationType::CHANGER_ACTIVATION_TYPE_SLIDER_DRAG;
	just_created_SFC->target_float_pointer = &but->slider_value;
	*just_created_SFC->float_value = 0.5f;
	but->simple_float_changer_list.push_back(just_created_SFC);

	//button_group search bar
	just_created_button_group = new EButton::button_group();
	just_created_button_super_group->button_group_list.push_back(just_created_button_group);

	//input search text button
	but = new EButton(0.0f, 0.0f, 512.0f, 20.0f);
	but->master_window = this;
	but->master_super_group = just_created_button_super_group;
	but->master_group = just_created_button_group;
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_NONE;
	just_created_button_group->button_list.push_back(but);
	but->have_input_mode = true;

	EButton::SimpleButtonSearchDeactivator* just_created_button_deactivator = new EButton::SimpleButtonSearchDeactivator();
	but->simple_button_search_deactivator_list.push_back(just_created_button_deactivator);
	just_created_button_deactivator->target_button_group = group_texture_collection_link;
	*just_created_button_deactivator->is_search_by_description = true;

	Entity*
		en = new Entity();
	entity_list.push_back(en);

	*en->position_x = 100.0f;
	*en->position_y = 200.0f;
	*en->position_z = 0.0f;

	EGraphicCore::sprite_array* just_created_sprite_array = new EGraphicCore::sprite_array();
	en->entity_sprite_array = just_created_sprite_array;
	EGraphicCore::ESprite* just_created_sprite = new EGraphicCore::ESprite();
	just_created_sprite_array->sprite_list.push_back(just_created_sprite);
	just_created_sprite->texture_gabarite = ETextureAtlas::put_texture_to_atlas("data/textures/human.png", EWindow::default_texture_atlas);
	*just_created_sprite->offset_x = -round(*just_created_sprite->texture_gabarite->size_x / 2.0f);

	*just_created_sprite->size_x = *just_created_sprite->texture_gabarite->size_x;
	*just_created_sprite->size_y = *just_created_sprite->texture_gabarite->size_y;

	en = new Entity();
	entity_list.push_back(en);

	*en->position_x = 200.0f;
	*en->position_y = 700.0f;
	*en->position_z = 0.0f;

	just_created_sprite_array = new EGraphicCore::sprite_array();
	en->entity_sprite_array = just_created_sprite_array;
	just_created_sprite = new EGraphicCore::ESprite();
	just_created_sprite_array->sprite_list.push_back(just_created_sprite);
	just_created_sprite->texture_gabarite = ETextureAtlas::put_texture_to_atlas("data/textures/human.png", EWindow::default_texture_atlas);
	*just_created_sprite->offset_x = -round(*just_created_sprite->texture_gabarite->size_x / 2.0f);

	*just_created_sprite->size_x = *just_created_sprite->texture_gabarite->size_x;
	*just_created_sprite->size_y = *just_created_sprite->texture_gabarite->size_y;

	/// <summary>
	/// grid region
	/// </summary>
	super_group_autobuilding = new EButton::button_super_group();
	button_group_list.push_back(super_group_autobuilding);
	*super_group_autobuilding->position_x = 300.0f;
	*super_group_autobuilding->position_y = 50.0f;

	group_grid_entity_list_link = new EButton::button_group();
	*group_grid_entity_list_link->size_x = 120.0f;
	*group_grid_entity_list_link->size_y = 165.0f;

	super_group_autobuilding->button_group_list.push_back(group_grid_entity_list_link);
	*group_grid_entity_list_link->selected_push_method = EButton::GroupPushMethod::GROUP_PUSH_METHOD_ADD_X;
	*group_grid_entity_list_link->can_be_moved_by_user = false;
	*group_grid_entity_list_link->can_be_stretched_x = true;
	*group_grid_entity_list_link->can_be_stretched_y = true;

	for (int i = 0; i < 100; i++)
	{
		but = new EButton(0.0f, 0.0f, 100.0f, 20.0f);
		but->master_window = this;
		but->master_super_group = super_group_autobuilding;
		but->master_group = group_grid_entity_list_link;
		but->have_rama = true;

		group_grid_entity_list_link->button_list.push_back(but);

		but->description_text = "Entity #" + std::to_string(i);
		but->text = "Entity";
		*but->can_be_selected = true;
		but->data_id = i;
		but->action_on_left_click.push_back(&ExternalButtonAction::external_button_action_select_entity_from_list);
		but->is_active = false;
		//but->gabarite = ETextureAtlas::put_texture_to_atlas("data/textures/hrusch_wall_main_002_v3.png", EWindow::default_texture_atlas);

		*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_Y;
		//group_grid_entity_list_link->button_list.push_back(but);
	}

	group_grid_region_edit_link = new EButton::button_group();
	super_group_autobuilding->button_group_list.push_back(group_grid_region_edit_link);
	*group_grid_region_edit_link->can_be_moved_by_user = false;

	*group_grid_region_edit_link->can_be_stretched_x = true;
	*group_grid_region_edit_link->can_be_stretched_y = true;

	*group_grid_region_edit_link->selected_push_method = EButton::GroupPushMethod::GROUP_PUSH_METHOD_ADD_X;

	but = new EButton(0.0f, 0.0f, 20.0f, 20.0f);
	grid_region_edit_button_link = but;
	but->master_window = this;
	but->master_super_group = super_group_autobuilding;
	but->master_group = group_grid_region_edit_link;

	group_grid_region_edit_link->button_list.push_back(but);

	but->description_text = "Grid region (just for test)";
	but->gabarite = ETextureAtlas::put_texture_to_atlas("data/textures/hrusch_wall_main_002_v3.png", EWindow::default_texture_atlas);

	but->button_size_x = min(500.0f, max(10.0f, *but->gabarite->size_x * 2.0f));
	but->button_size_y = min(500.0f, max(10.0f, *but->gabarite->size_y * 2.0f));

	but->have_icon = true;
	but->have_bg = false;

	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_X;

	//left up corner
	EButton::EGridRegion*
		just_created_grid = new EButton::EGridRegion();
	*just_created_grid->size_x = 5.0f;
	*just_created_grid->size_y = 5.0f;

	*just_created_grid->position_y = *but->gabarite->size_y - 5.0f;

	but->grid_region_list.push_back(just_created_grid);

	//up
	just_created_grid = new EButton::EGridRegion();
	*just_created_grid->size_x = *but->gabarite->size_x - 10.0f;
	*just_created_grid->size_y = 5.0;

	*just_created_grid->position_x = 5.0f;
	*just_created_grid->position_y = *but->gabarite->size_y - 5.0f;
	but->grid_region_list.push_back(just_created_grid);

	//right up corner
	just_created_grid = new EButton::EGridRegion();
	*just_created_grid->size_x = 5.0f;
	*just_created_grid->size_y = 5.0f;

	*just_created_grid->position_x = *but->gabarite->size_x - 5.0f;
	*just_created_grid->position_y = *but->gabarite->size_y - 5.0f;
	but->grid_region_list.push_back(just_created_grid);

	//left
	just_created_grid = new EButton::EGridRegion();
	*just_created_grid->size_x = 5.0f;
	*just_created_grid->size_y = *but->gabarite->size_y - 10.0f;

	*just_created_grid->position_x = 0.0f;
	*just_created_grid->position_y = 5.0f;
	but->grid_region_list.push_back(just_created_grid);

	//mid
	just_created_grid = new EButton::EGridRegion();
	*just_created_grid->size_x = *but->gabarite->size_x - 10.0f;
	*just_created_grid->size_y = *but->gabarite->size_y - 10.0f;

	*just_created_grid->position_x = 5.0f;
	*just_created_grid->position_y = 5.0f;
	but->grid_region_list.push_back(just_created_grid);

	//right
	just_created_grid = new EButton::EGridRegion();
	*just_created_grid->size_x = 5.0f;
	*just_created_grid->size_y = *but->gabarite->size_y - 10.0f;

	*just_created_grid->position_x = *but->gabarite->size_x - 5.0f;
	*just_created_grid->position_y = 5.0f;
	but->grid_region_list.push_back(just_created_grid);

	//left bottom corner
	just_created_grid = new EButton::EGridRegion();
	*just_created_grid->size_x = 5.0f;
	*just_created_grid->size_y = 5.0f;

	*just_created_grid->position_x = 0.0f;
	*just_created_grid->position_y = 0.0f;
	but->grid_region_list.push_back(just_created_grid);

	//bottom
	just_created_grid = new EButton::EGridRegion();
	*just_created_grid->size_x = *but->gabarite->size_x - 10.0f;
	*just_created_grid->size_y = 5.0f;

	*just_created_grid->position_x = 5.0f;
	*just_created_grid->position_y = 0.0f;
	but->grid_region_list.push_back(just_created_grid);

	//bottom
	just_created_grid = new EButton::EGridRegion();
	*just_created_grid->size_x = 5.0f;
	*just_created_grid->size_y = 5.0f;

	*just_created_grid->position_x = *but->gabarite->size_x - 5.0f;
	*just_created_grid->position_y = 0.0f;
	but->grid_region_list.push_back(just_created_grid);

	group_grid_region_second_layer_link = new EButton::button_group();
	*group_grid_region_second_layer_link->selected_push_method = EButton::GroupPushMethod::GROUP_PUSH_METHOD_ADD_X;
	super_group_autobuilding->button_group_list.push_back(group_grid_region_second_layer_link);
	*group_grid_region_second_layer_link->size_x = 300.0f;
	*group_grid_region_second_layer_link->size_y = 200.0f;
	*group_grid_region_second_layer_link->can_be_stretched_x = false;
	*group_grid_region_second_layer_link->can_be_stretched_y = false;
	*group_grid_region_second_layer_link->can_be_moved_by_user = false;

	but = new EButton(70.0f, 70.0f, 50.0f, 20.0f);
	but->master_window = this;
	but->master_super_group = super_group_autobuilding;
	but->master_group = group_grid_region_second_layer_link;
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_FREE;
	auto_size_region_button.push_back(but);
	group_grid_region_second_layer_link->button_list.push_back(but);
	but->have_input_mode = true;
	but->input_only_numbers = true;
	but->action_on_left_click.push_back(&ExternalButtonAction::external_button_action_set_grid_region_auto_size);
	but->action_on_input.push_back(&ExternalButtonAction::external_button_action_set_grid_region_auto_size);
	but->text = "0";
	but->input_auto_clear_text = true;

	but = new EButton(70.0f - 60.0f, 70.0f - 30.0f, 50.0f, 20.0f);
	but->master_window = this;
	but->master_super_group = super_group_autobuilding;
	but->master_group = group_grid_region_second_layer_link;
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_FREE;
	auto_size_region_button.push_back(but);
	group_grid_region_second_layer_link->button_list.push_back(but);
	but->have_input_mode = true;
	but->input_only_numbers = true;
	but->action_on_input.push_back(&ExternalButtonAction::external_button_action_set_grid_region_auto_size);
	but->text = "0";
	but->input_auto_clear_text = true;

	but = new EButton(70.0f + 60.0f, 70.0f - 30.0f, 50.0f, 20.0f);
	but->master_window = this;
	but->master_super_group = super_group_autobuilding;
	but->master_group = group_grid_region_second_layer_link;
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_FREE;
	auto_size_region_button.push_back(but);
	group_grid_region_second_layer_link->button_list.push_back(but);
	but->have_input_mode = true;
	but->input_only_numbers = true;
	but->action_on_input.push_back(&ExternalButtonAction::external_button_action_set_grid_region_auto_size);
	but->text = "0";
	but->input_auto_clear_text = true;

	but = new EButton(70.0f + 0.0f, 70.0f - 60.0f, 50.0f, 20.0f);
	but->master_window = this;
	but->master_super_group = super_group_autobuilding;
	but->master_group = group_grid_region_second_layer_link;
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_FREE;
	auto_size_region_button.push_back(but);
	group_grid_region_second_layer_link->button_list.push_back(but);
	but->have_input_mode = true;
	but->input_only_numbers = true;
	but->action_on_input.push_back(&ExternalButtonAction::external_button_action_set_grid_region_auto_size);
	but->text = "0";
	but->input_auto_clear_text = true;

	but = new EButton(70.0f + 0.0f, 70.0f - 30.0f, 50.0f, 20.0f);
	but->master_window = this;
	but->master_super_group = super_group_autobuilding;
	but->master_group = group_grid_region_second_layer_link;
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_FREE;
	group_grid_region_second_layer_link->button_list.push_back(but);
	but->text = "Auto";
	but->action_on_left_click.push_back(&ExternalButtonAction::external_button_action_set_grid_region_auto_size);
	//but->text = "0";

	but = new EButton(190.0f + 0.0f, 70.0f - 30.0f, 50.0f, 20.0f);
	space_between_sprites_x_button = but;
	but->master_window = this;
	but->master_super_group = super_group_autobuilding;
	but->master_group = group_grid_region_second_layer_link;
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_FREE;
	group_grid_region_second_layer_link->button_list.push_back(but);
	but->text = "0";
	but->have_input_mode = true;
	but->input_only_numbers = true;
	but->action_on_left_click.push_back(&ExternalButtonAction::external_button_action_set_grid_region_auto_size);
	just_created_SFC = new EButton::SimpleFloatChanger();
	*just_created_SFC->float_changer_type = EButton::SimpleFloatChanger::SimpleFloatChangerType::SIMPLE_FLOAT_CHANGER_BUTTON_VALUE;
	*just_created_SFC->selected_activation_type = EButton::ButtonSimpleChangerActivationType::CHANGER_ACTIVATION_TYPE_INPUT;
	*just_created_SFC->selected_mathematic_type = EButton::ButtonSimpleChangerMathematic::BUTTON_SIMPLE_VALUE_MANIPULATOR_MATHEMATIC_SET_VALUE;
	but->simple_float_changer_list.push_back(just_created_SFC);

	but = new EButton(190.0f + 0.0f, 70.0f - 55.0f, 50.0f, 20.0f);
	space_between_sprites_y_button = but;
	but->master_window = this;
	but->master_super_group = super_group_autobuilding;
	but->master_group = group_grid_region_second_layer_link;
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_FREE;
	group_grid_region_second_layer_link->button_list.push_back(but);
	but->text = "0";
	but->have_input_mode = true;
	but->input_only_numbers = true;
	but->action_on_left_click.push_back(&ExternalButtonAction::external_button_action_set_grid_region_auto_size);
	just_created_SFC = new EButton::SimpleFloatChanger();
	*just_created_SFC->float_changer_type = EButton::SimpleFloatChanger::SimpleFloatChangerType::SIMPLE_FLOAT_CHANGER_BUTTON_VALUE;
	*just_created_SFC->selected_activation_type = EButton::ButtonSimpleChangerActivationType::CHANGER_ACTIVATION_TYPE_INPUT;
	*just_created_SFC->selected_mathematic_type = EButton::ButtonSimpleChangerMathematic::BUTTON_SIMPLE_VALUE_MANIPULATOR_MATHEMATIC_SET_VALUE;
	but->simple_float_changer_list.push_back(just_created_SFC);

	but = new EButton(250.0f + 0.0f, 70.0f - 30.0f, 50.0f, 20.0f);
	link_button_subdivision_mid_x = but;
	but->master_window = this;
	but->master_super_group = super_group_autobuilding;
	but->master_group = group_grid_region_second_layer_link;
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_FREE;
	group_grid_region_second_layer_link->button_list.push_back(but);
	but->text = "0";
	but->have_input_mode = true;
	but->input_only_numbers = true;
	but->action_on_input.push_back(&ExternalButtonAction::external_button_action_set_button_value);
	*but->is_consumable = true;

	but = new EButton(250.0f + 0.0f, 70.0f - 55.0f, 50.0f, 20.0f);
	link_button_subdivision_mid_y = but;
	but->master_window = this;
	but->master_super_group = super_group_autobuilding;
	but->master_group = group_grid_region_second_layer_link;
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_FREE;
	group_grid_region_second_layer_link->button_list.push_back(but);
	but->text = "0";
	but->have_input_mode = true;
	but->input_only_numbers = true;
	//but->action_on_left_click.push_back(&ExternalButtonAction::external_button_action_set_grid_region_auto_size);
	but->action_on_input.push_back(&ExternalButtonAction::external_button_action_set_button_value);
	*but->is_consumable = true;
	//but->text = "0";

	button_group_autobuilding_base = new EButton::button_group();
	*button_group_autobuilding_base->selected_push_method = EButton::GroupPushMethod::GROUP_PUSH_METHOD_RESET_X_ADD_Y;
	super_group_autobuilding->button_group_list.push_back(button_group_autobuilding_base);
	*button_group_autobuilding_base->size_x = 800.0f;
	*button_group_autobuilding_base->size_y = 120.0f;
	*button_group_autobuilding_base->can_be_stretched_x = false;
	*button_group_autobuilding_base->can_be_stretched_y = true;
	*button_group_autobuilding_base->can_be_moved_by_user = false;

	for (int i = 0; i < 10; i++)
	{
		but = new EButton(0.0f, 0.0f, 50.0f, 50.0f);
		but->master_window = this;
		but->master_super_group = super_group_autobuilding;
		but->master_group = button_group_autobuilding_base;
		*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_X;
		button_group_autobuilding_base->button_list.push_back(but);

		but->is_active = true;
		but->data_id = i;
		*but->can_be_selected = true;
		but->have_rama = true;
		but->action_on_left_click.push_back(&ExternalButtonAction::external_button_action_select_autobuilding_base);
		but->action_on_left_double_click.push_back(&ExternalButtonAction::external_button_action_open_select_texture_window_for_autobuilding_base);
		but->action_on_right_click.push_back(&ExternalButtonAction::external_button_action_remove_autobuilding_base);
		but->action_on_drag.push_back(&ExternalButtonAction::external_button_action_drag_autobuilding_base);
		*but->is_double_click = true;
		//but->text = "Auto";
		//but->action_on_left_click.push_back(&ExternalButtonAction::external_button_action_set_grid_region_auto_size);
	}

	but = new EButton(0.0f, 0.0f, 200.0f, 20.0f);
	button_group_autobuilding_base->button_list.push_back(but);
	but->master_window = this;
	but->master_super_group = super_group_autobuilding;
	but->master_group = button_group_autobuilding_base;
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_RESET_X_AND_ADD_Y;
	*but->can_be_selected = false;
	but->action_on_left_click.push_back(&ExternalButtonAction::external_button_action_add_new_autobuilding_base);
	but->text = "Add new autobuilding region";

	but = new EButton(0.0f, 0.0f, 200.0f, 20.0f);
	button_group_autobuilding_base->button_list.push_back(but);
	but->master_window = this;
	but->master_super_group = super_group_autobuilding;
	but->master_group = button_group_autobuilding_base;
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_X;
	*but->can_be_selected = false;
	but->action_on_left_click.push_back(&ExternalButtonAction::external_button_action_add_selected_region_to_autobuilding_group);
	but->text = "Add selected region to group";

	button_group_autobuilding_group_element = new EButton::button_group();
	*button_group_autobuilding_group_element->selected_push_method = EButton::GroupPushMethod::GROUP_PUSH_METHOD_RESET_X_ADD_Y;
	super_group_autobuilding->button_group_list.push_back(button_group_autobuilding_group_element);
	*button_group_autobuilding_group_element->size_x = 800.0f;
	*button_group_autobuilding_group_element->size_y = 120.0f;
	*button_group_autobuilding_group_element->can_be_stretched_x = false;
	*button_group_autobuilding_group_element->can_be_stretched_y = true;
	*button_group_autobuilding_group_element->can_be_moved_by_user = false;

	for (int i = 0; i < 10; i++)
	{
		but = new EButton(0.0f, 0.0f, 50.0f, 50.0f);
		but->master_window = this;
		but->master_super_group = super_group_autobuilding;
		but->master_group = button_group_autobuilding_group_element;
		*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_X;
		button_group_autobuilding_group_element->button_list.push_back(but);

		but->is_active = true;
		but->data_id = i;
		*but->can_be_selected = true;
		but->have_rama = true;
		but->action_on_left_click.push_back(&ExternalButtonAction::external_button_action_select_autobuilding_group_element);
		//but->action_on_left_double_click.push_back(&ExternalButtonAction::external_button_action_open_select_texture_window_for_autobuilding_region);
		but->action_on_right_click.push_back(&ExternalButtonAction::external_button_action_remove_autobuilding_group_element);
		but->action_on_drag.push_back(&ExternalButtonAction::external_button_action_drag_autobuilding_group_element);
		//*but->is_double_click = true;
	//but->text = "Auto";
	//but->action_on_left_click.push_back(&ExternalButtonAction::external_button_action_set_grid_region_auto_size);
	}

	button_group_autobuilding_group = new EButton::button_group();
	*button_group_autobuilding_group->selected_push_method = EButton::GroupPushMethod::GROUP_PUSH_METHOD_RESET_X_ADD_Y;
	super_group_autobuilding->button_group_list.push_back(button_group_autobuilding_group);
	*button_group_autobuilding_group->size_x = 800.0f;
	*button_group_autobuilding_group->size_y = 120.0f;
	*button_group_autobuilding_group->can_be_stretched_x = false;
	*button_group_autobuilding_group->can_be_stretched_y = true;
	*button_group_autobuilding_group->can_be_moved_by_user = false;

	for (int i = 0; i < 10; i++)
	{
		but = new EButton(0.0f, 0.0f, 100.0f, 20.0f);
		button_group_autobuilding_group->button_list.push_back(but);
		but->master_window = this;
		but->master_super_group = super_group_autobuilding;
		but->master_group = button_group_autobuilding_group;
		*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_X;
		*but->can_be_selected = false;
		but->have_rama = true;
		*but->can_be_selected = true;
		but->action_on_left_click.push_back(&ExternalButtonAction::external_button_action_select_autobuilding_group);
		but->text = "Group #" + std::to_string(i);
		but->action_on_drag.push_back(&ExternalButtonAction::external_button_action_drag_autobuilding_group);
		//but->data_id = i;
	}

	but = new EButton(0.0f, 0.0f, 200.0f, 20.0f);
	button_group_autobuilding_group->button_list.push_back(but);
	but->master_window = this;
	but->master_super_group = super_group_autobuilding;
	but->master_group = button_group_autobuilding_group;
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_RESET_X_AND_ADD_Y;
	*but->can_be_selected = false;
	but->action_on_left_click.push_back(&ExternalButtonAction::external_button_action_add_new_group_for_autobuilding);
	but->text = "Add new group";

	group_grid_autobuilding_draw_order = new EButton::button_group();
	*group_grid_autobuilding_draw_order->selected_push_method = EButton::GroupPushMethod::GROUP_PUSH_METHOD_RESET_X_ADD_Y;
	super_group_autobuilding->button_group_list.push_back(group_grid_autobuilding_draw_order);
	*group_grid_autobuilding_draw_order->size_x = 800.0f;
	*group_grid_autobuilding_draw_order->size_y = 120.0f;
	*group_grid_autobuilding_draw_order->can_be_stretched_x = false;
	*group_grid_autobuilding_draw_order->can_be_stretched_y = true;
	*group_grid_autobuilding_draw_order->can_be_moved_by_user = false;

	but = new EButton(0.0f, 0.0f, 200.0f, 20.0f);
	group_grid_autobuilding_draw_order->button_list.push_back(but);
	but->master_window = this;
	but->master_super_group = super_group_autobuilding;
	but->master_group = group_grid_autobuilding_draw_order;
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_RESET_X_AND_ADD_Y;
	*but->can_be_selected = false;
	but->action_on_left_click.push_back(&ExternalButtonAction::external_button_action_add_new_group_for_autobuilding);
	but->text = "Add new order";

	/////////////menu save|load|other
	just_created_button_super_group = new EButton::button_super_group();
	button_group_list.push_back(just_created_button_super_group);

	*just_created_button_super_group->size_x = 300.0f;
	*just_created_button_super_group->size_y = 30.0f;
	button_group_list.push_back(just_created_button_super_group);

	just_created_button_group = new EButton::button_group();
	just_created_button_super_group->button_group_list.push_back(just_created_button_group);
	*just_created_button_group->size_x = 300.0f;
	*just_created_button_group->size_y = 30.0f;
	*just_created_button_group->can_be_stretched_x = false;
	*just_created_button_group->can_be_stretched_y = false;

	but = new EButton(0.0f, 0.0f, 50.0f, 15.0f, this, just_created_button_super_group, just_created_button_group);
	just_created_button_group->button_list.push_back(but);
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_X;
	but->action_on_left_click.push_back(&ExternalButtonAction::external_button_action_save_map);
	but->text = "Save";

	but = new EButton(0.0f, 0.0f, 50.0f, 15.0f, this, just_created_button_super_group, just_created_button_group);
	just_created_button_group->button_list.push_back(but);
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_X;
	but->action_on_left_click.push_back(&ExternalButtonAction::external_button_action_load_map);
	but->text = "Load";

	entity_selection_region = new EButton::EGridRegion();
}

EWindowMain::~EWindowMain()
{
}

bool EWindowMain::is_entity_in_region(Entity* _e, EButton::EGridRegion* _gr)
{
	if
		(
			(
				((*_gr->size_x > 0) & (*_e->position_x >= *_gr->position_x))
				||
				((*_gr->size_x < 0) & (*_e->position_x <= *_gr->position_x))
				)
			&
			(
				((*_gr->size_x > 0) & (*_e->position_x <= *_gr->position_x + *_gr->size_x))
				||
				((*_gr->size_x < 0) & (*_e->position_x >= *_gr->position_x + *_gr->size_x))
				)
			&
			(
				((*_gr->size_y > 0) & (*_e->position_y >= *_gr->position_y))
				||
				((*_gr->size_y < 0) & (*_e->position_y <= *_gr->position_y))
				)
			&
			(
				((*_gr->size_y > 0) & (*_e->position_y <= *_gr->position_y + *_gr->size_y))
				||
				((*_gr->size_y < 0) & (*_e->position_y >= *_gr->position_y + *_gr->size_y))
				)
			)
	{
		return true;
	}

	return false;
}

void EWindowMain::draw(float _d)
{
	reset_render();

	EGraphicCore::batch->setcolor(EColor::COLOR_GRAY);
	EGraphicCore::batch->draw_gabarite(0.0f, 0.0f, 2000.0f, 2000.0f, EGraphicCore::gabarite_white_pixel);

	EWindow::add_time_process("Draw entity");
	for (Entity* en : entity_list)
	{
		en->draw_entity(en, EGraphicCore::batch, _d);
	}

	EGraphicCore::batch->setcolor(EColor::COLOR_RED);
	EGraphicCore::batch->draw_gabarite(get_real_world_position_x_by_mouse(main_camera) - 3.0f, get_real_world_position_y_by_mouse(main_camera) - 3.0f, 6.0f, 6.0f, EGraphicCore::gabarite_white_pixel);

	if (is_entity_selection_started)
	{
		EGraphicCore::batch->draw_rama(*entity_selection_region->position_x, *entity_selection_region->position_y, *entity_selection_region->size_x, *entity_selection_region->size_y, 2.0f, EGraphicCore::gabarite_white_pixel);
	}

	if ((glfwGetKey(EWindow::main_window, GLFW_KEY_TAB) == GLFW_PRESS))
	{


		EGraphicCore::batch->reset();
		EGraphicCore::batch->setcolor(EColor::COLOR_WHITE);
		EGraphicCore::batch->draw_gabarite(0.0f, 0.0f, EGraphicCore::gabarite_full_atlas);

		EGraphicCore::batch->draw_rama(0.0f, 0.0f, 4096.0f, 4096.0f, 3.0f, EGraphicCore::gabarite_white_pixel);

	}
}

void EWindowMain::update(float _d)
{
	if (!EButton::any_overlap)
	{
		if (scroll > 0) { *main_camera->zoom *= 2.0f; }
		if (scroll < 0) { *main_camera->zoom /= 2.0f; }
	}

	int selected_group_element_id = -1;

	EWindow::add_time_process("Autobuilding generate");
	for (Entity* e : entity_list)
		for (Entity::AutobuildingGroup* a_group : e->autobuilding_group_list)
			for (Entity::AutobuildingGroupElement* a_element : a_group->autobuilding_group_element_list)
			{
				/*std::cout
					<<
					" selected group: ["
					<<
					std::to_string(ExternalButtonAction::get_autobuilding_group_id())
					<<
					"] selected element: ["
					<<
					std::to_string(ExternalButtonAction::get_autobuilding_group_element_id())
					<<
					"]"
					<<
					std::endl;*/

				if
					(
						(
							(ExternalButtonAction::get_selected_autobuilding_group_element(e) != NULL)
							&&
							(ExternalButtonAction::get_selected_autobuilding_group_element(e) == a_element)
							)
						||
						(ExternalButtonAction::get_selected_autobuilding_group_element(e) == NULL)
						||
						(glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_ALT) != GLFW_PRESS)
						)
				{
					if
						(
							(get_real_world_position_x_by_mouse(main_camera) >= *e->position_x + *a_group->offset_x + *a_element->offset_x - 3.0f)
							&
							(get_real_world_position_x_by_mouse(main_camera) <= *e->position_x + *a_group->offset_x + *a_element->offset_x + 3.0f)
							&
							(get_real_world_position_y_by_mouse(main_camera) >= *e->position_y + *a_group->offset_y + *a_element->offset_y - 3.0f)
							&
							(get_real_world_position_y_by_mouse(main_camera) <= *e->position_y + *a_group->offset_y + *a_element->offset_y + *a_element->size_y + 3.0f)
							)
					{
						if (!LMB) { *a_element->catched_left_side = true; }
					}
					else
					{
						if (!LMB) { *a_element->catched_left_side = false; }
					}

					if
						(
							(get_real_world_position_x_by_mouse(main_camera) >= *e->position_x + *a_group->offset_x + *a_element->offset_x + *a_element->size_x - 3.0f)
							&
							(get_real_world_position_x_by_mouse(main_camera) <= *e->position_x + *a_group->offset_x + *a_element->offset_x + *a_element->size_x + 3.0f)
							&
							(get_real_world_position_y_by_mouse(main_camera) >= *e->position_y + *a_group->offset_y + *a_element->offset_y - 3.0f)
							&
							(get_real_world_position_y_by_mouse(main_camera) <= *e->position_y + *a_group->offset_y + *a_element->offset_y + *a_element->size_y + 3.0f)
							)
					{
						if (!LMB) { *a_element->catched_right_side = true; }
					}
					else
					{
						if (!LMB) { *a_element->catched_right_side = false; }
					}

					if
						(
							(get_real_world_position_x_by_mouse(main_camera) >= *e->position_x + *a_group->offset_x + *a_element->offset_x - 3.0f)
							&
							(get_real_world_position_x_by_mouse(main_camera) <= *e->position_x + *a_group->offset_x + *a_element->offset_x + *a_element->size_x + 3.0f)
							&
							(get_real_world_position_y_by_mouse(main_camera) >= *e->position_y + *a_group->offset_y + *a_element->offset_y - 3.0f)
							&
							(get_real_world_position_y_by_mouse(main_camera) <= *e->position_y + *a_group->offset_y + *a_element->offset_y + 3.0f)
							)
					{
						if (!LMB) { *a_element->catched_down_side = true; }
					}
					else
					{
						if (!LMB) { *a_element->catched_down_side = false; }
					}

					if
						(
							(get_real_world_position_x_by_mouse(main_camera) >= *e->position_x + *a_group->offset_x + *a_element->offset_x - 3.0f)
							&
							(get_real_world_position_x_by_mouse(main_camera) <= *e->position_x + *a_group->offset_x + *a_element->offset_x + *a_element->size_x + 3.0f)
							&
							(get_real_world_position_y_by_mouse(main_camera) >= *e->position_y + *a_group->offset_y + *a_element->offset_y + *a_element->size_y - 3.0f)
							&
							(get_real_world_position_y_by_mouse(main_camera) <= *e->position_y + *a_group->offset_y + *a_element->offset_y + *a_element->size_y + 3.0f)
							)
					{
						if (!LMB) { *a_element->catched_up_side = true; }
					}
					else
					{
						if (!LMB) { *a_element->catched_up_side = false; }
					}

					if
						(
							(get_real_world_position_x_by_mouse(main_camera) >= *e->position_x + *a_group->offset_x + *a_element->offset_x + *a_element->size_x / 2.0f - 10.0f)
							&
							(get_real_world_position_x_by_mouse(main_camera) <= *e->position_x + *a_group->offset_x + *a_element->offset_x + *a_element->size_x / 2.0f + 10.0f)
							&
							(get_real_world_position_y_by_mouse(main_camera) >= *e->position_y + *a_group->offset_y + *a_element->offset_y + *a_element->size_y / 2.0f - 10.0f)
							&
							(get_real_world_position_y_by_mouse(main_camera) <= *e->position_y + *a_group->offset_y + *a_element->offset_y + *a_element->size_y / 2.0f + 10.0f)
							)
					{
						if (!LMB) { *a_element->catched_mid = true; }
					}
					else
					{
						if (!LMB) { *a_element->catched_mid = false; }
					}

					if (LMB)
					{
						if (*a_element->catched_left_side)
						{
							*a_element->size_x -= mouse_speed_x / *main_camera->zoom;
							*a_element->offset_x += mouse_speed_x / *main_camera->zoom;

							//generate_building(e);
						}

						if (*a_element->catched_right_side)
						{
							*a_element->size_x += mouse_speed_x / *main_camera->zoom;
							//*a_element->offset_x += mouse_speed_x / *main_camera->zoom;
							//generate_building(e);
						}

						if (*a_element->catched_down_side)
						{
							*a_element->size_y -= mouse_speed_y / *main_camera->zoom;
							*a_element->offset_y += mouse_speed_y / *main_camera->zoom;

							//generate_building(e);
						}

						if (*a_element->catched_up_side)
						{
							*a_element->size_y += mouse_speed_y / *main_camera->zoom;
							//*a_element->offset_x += mouse_speed_x / *main_camera->zoom;
							//generate_building(e);
						}

						if (*a_element->catched_mid)
						{
							*a_element->offset_x += mouse_speed_x / *main_camera->zoom;
							*a_element->offset_y += mouse_speed_y / *main_camera->zoom;
							//*a_element->offset_x += mouse_speed_x / *main_camera->zoom;
							//generate_building(e);
						}
					}
				}
				else
				{
					*a_element->catched_mid = false;

					*a_element->catched_left_side = false;
					*a_element->catched_right_side = false;
					*a_element->catched_up_side = false;
					*a_element->catched_down_side = false;
				}

				generate_building(e);
			}

	if (glfwGetKey(EWindow::main_window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		selected_entities.clear();

		if (!is_entity_selection_started)
		{
			is_entity_selection_started = true;

			*entity_selection_region->position_x = get_real_world_position_x_by_mouse(main_camera);
			*entity_selection_region->position_y = get_real_world_position_y_by_mouse(main_camera);
		}
		else
		{
			*entity_selection_region->size_x = get_real_world_position_x_by_mouse(main_camera) - *entity_selection_region->position_x;
			*entity_selection_region->size_y = get_real_world_position_y_by_mouse(main_camera) - *entity_selection_region->position_y;
		}

		for (Entity* e : entity_list)
		{
			if (is_entity_in_region(e, entity_selection_region))
			{
				*e->is_selected = true;
				selected_entities.push_back(e);
			}
			else
			{
				*e->is_selected = false;
			}
		}

		update_selected_entity_list();
	}
	else
	{
		*entity_selection_region->size_x = 0.0f;
		*entity_selection_region->size_y = 0.0f;

		*entity_selection_region->position_x = 0.0f;
		*entity_selection_region->position_y = 0.0f;

		is_entity_selection_started = false;
	}

	if ((glfwGetKey(EWindow::main_window, GLFW_KEY_W) == GLFW_PRESS)) { *main_camera->speed_y += _d * 100.0f; }
	if ((glfwGetKey(EWindow::main_window, GLFW_KEY_S) == GLFW_PRESS)) { *main_camera->speed_y -= _d * 100.0f; }

	if ((glfwGetKey(EWindow::main_window, GLFW_KEY_D) == GLFW_PRESS)) { *main_camera->speed_x += _d * 100.0f; }
	if ((glfwGetKey(EWindow::main_window, GLFW_KEY_A) == GLFW_PRESS)) { *main_camera->speed_x -= _d * 100.0f; }

	*main_camera->position_x += *main_camera->speed_x;
	*main_camera->position_y += *main_camera->speed_y;

	*main_camera->speed_x *= pow(0.1, _d);
	*main_camera->speed_y *= pow(0.1, _d);
	/*
	if (*main_camera->speed_x > 0.0f) { *main_camera->speed_x -= _d * 50.0f; } else { *main_camera->speed_x += _d * 50.0f; }
	if (*main_camera->speed_y > 0.0f) { *main_camera->speed_y -= _d * 50.0f; } else { *main_camera->speed_y += _d * 50.0f; }

	if (abs(*main_camera->speed_x) <= 5.0f) { *main_camera->speed_x = 0.0f; }
	if (abs(*main_camera->speed_y) <= 5.0f) { *main_camera->speed_y = 0.0f; }*/
}

void EWindowMain::reset_render()
{
	glClearColor(EColor::COLOR_LAZURE_SHADOW->color_red, EColor::COLOR_LAZURE_SHADOW->color_green, EColor::COLOR_LAZURE_SHADOW->color_blue, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	EGraphicCore::batch->reinit();
	EGraphicCore::batch->draw_call();

	EGraphicCore::ourShader->use();
	EGraphicCore::matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

	//if ((glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_ALT) != GLFW_PRESS))
	{
		EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3(-1.0f - EGraphicCore::correction_x / 2.0f * 0.0f + round(EGraphicCore::SCR_WIDTH / 2.0f - *main_camera->position_x) * EGraphicCore::correction_x, -1.0f - EGraphicCore::correction_y / 2.0f * 0.0f + round(EGraphicCore::SCR_HEIGHT / 2.0f - *main_camera->position_y) * EGraphicCore::correction_y, 0.0f));
	}
	////
	//{
	///	EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3(-1.0f - *main_camera->position_x, -1.0f - *main_camera->position_y, -1.0f));
	//}

	EGraphicCore::matrix_transform = glm::scale(EGraphicCore::matrix_transform, glm::vec3(EGraphicCore::correction_x * *main_camera->zoom, EGraphicCore::correction_y * *main_camera->zoom, 1.0f));

	transformLoc = glGetUniformLocation(EGraphicCore::ourShader->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));

	//����� �������
	EGraphicCore::batch->reset();
}

float EWindowMain::get_real_world_position_x_by_mouse(ECamera* _camera)
{
	return (mouse_x + *_camera->position_x - round(EGraphicCore::SCR_WIDTH / 2.0f)) / *_camera->zoom;
}

float EWindowMain::get_real_world_position_y_by_mouse(ECamera* _camera)
{
	return (mouse_y + *_camera->position_y - round(EGraphicCore::SCR_HEIGHT / 2.0f)) / *_camera->zoom;
}

void EWindowMain::update_selected_entity_list()
{
	for (int i = 0; i < group_grid_entity_list_link->button_list.size(); i++)
	{
		if (i < selected_entities.size())
		{
			group_grid_entity_list_link->button_list.at(i)->is_active = true;
		}
		else
		{
			group_grid_entity_list_link->button_list.at(i)->is_active = false;
		}
	}
}

void EWindowMain::create_new_elements_of_autobuilding_if_need(Entity* _e)
{
	Entity::AutobuildingBase* just_created_autobuilding_region;
	EButton::EGridRegion* just_created_grid_region;

	if
		(
			(_e->autobuilding_base_list.empty())
			&
			(glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
			)
	{
		just_created_autobuilding_region = new Entity::AutobuildingBase();
		_e->autobuilding_base_list.push_back(just_created_autobuilding_region);

		EWindowMain::grid_region_edit_button_link->grid_region_list.clear();

		/*
		for (int i = 0; i < 9; i++)
		{
			just_created_grid_region = new EButton::EGridRegion();

			just_created_autobuilding_region->texture_region_list.push_back(just_created_grid_region);
			EWindowMain::grid_region_button_link->grid_region_list.push_back(just_created_grid_region);
		}*/

		just_created_autobuilding_region->main_texture = ETextureAtlas::put_texture_to_atlas("data/textures/hrusch_wall_main_002_v1.png", EWindow::default_texture_atlas);
		button_group_autobuilding_base->selected_button = button_group_autobuilding_base->button_list.at(0);
	}

	if
		(
			(_e->autobuilding_group_list.empty())
			&
			(glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
			)
	{
		Entity::AutobuildingGroup* just_created_autobuilding_group = new Entity::AutobuildingGroup();
		Entity::AutobuildingGroupElement* just_created_autobuilding_group_element = new Entity::AutobuildingGroupElement();
		just_created_autobuilding_group_element->autobuilding_base = _e->autobuilding_base_list.at(0);
		just_created_autobuilding_group->autobuilding_group_element_list.push_back(just_created_autobuilding_group_element);

		_e->autobuilding_group_list.push_back(just_created_autobuilding_group);

		button_group_autobuilding_group->selected_button = button_group_autobuilding_group->button_list.at(0);
		button_group_autobuilding_group_element->selected_button = button_group_autobuilding_group_element->button_list.at(0);

		EWindowMain::grid_region_edit_button_link->grid_region_list.clear();
		for (int i = 0; i < _e->autobuilding_base_list.at(0)->grid_region.size(); i++)
		{
			EWindowMain::grid_region_edit_button_link->grid_region_list.push_back(_e->autobuilding_base_list.at(0)->grid_region.at(i));
		}

		EWindowMain::grid_region_edit_button_link->gabarite = _e->autobuilding_base_list.at(0)->main_texture;
	}

	//if (_e->)
}

void EWindowMain::convert_size_to_fragment(EGabarite* _g, float _offset_x, float _offset_y, float _size_x, float _size_y, float* _left_side, float* _right_side, float* _down_side, float* _up_side)
{
	*_left_side = _offset_x / 4096.0f;
	*_down_side = _offset_y / 4096.0f;

	*_right_side = (*_g->size_x - _size_x - _offset_x) / 4096.0f;
	*_up_side = (*_g->size_y - _size_y - _offset_y) / 4096.0f;
}

void EWindowMain::save_map(std::string _name)
{
	ofstream writer;

	_mkdir("test");
	writer.open("test/" + _name + ".txt");
	std::string w_string = "";

	//std::cout << "try save" << std::endl;
	for (Entity* e : EWindowMain::entity_list)
	{
		w_string += "CREATE_NEW_ENTITY";
		w_string += '\n';

		w_string += "entity_position";
		w_string += '\t';
		w_string += EString::float_to_string(*e->position_x);
		w_string += '\t';
		w_string += EString::float_to_string(*e->position_y);
		w_string += '\t';
		w_string += EString::float_to_string(*e->position_z);
		w_string += '\n';

		for (Entity::AutobuildingBase* a_base : e->autobuilding_base_list)
		{
			w_string += "CREATE_NEW_AUTOBUILDING_BASE";
			w_string += '\n';

			w_string += "autobuilding_base_main_texture";
			w_string += '\t';
			w_string += (a_base->main_texture->name);
			w_string += '\n';

			w_string += "autobuilding_base_space_between_sprites";
			w_string += '\t';
			w_string += EString::float_to_string(*a_base->space_between_sprite_x);
			w_string += '\t';
			w_string += EString::float_to_string(*a_base->space_between_sprite_y);
			w_string += '\n';

			for (EButton::EGridRegion* gr : a_base->grid_region)
			{
				w_string += "CREATE_NEW_GRID_REGION";
				w_string += '\n';

				w_string += "grid_region_position_and_size";
				w_string += '\t';
				w_string += EString::float_to_string(*gr->position_x);
				w_string += '\t';
				w_string += EString::float_to_string(*gr->position_y);
				w_string += '\t';
				w_string += EString::float_to_string(*gr->size_x);
				w_string += '\t';
				w_string += EString::float_to_string(*gr->size_y);
				w_string += '\n';

				w_string += "grid_region_subdivision";
				w_string += '\t';
				w_string += std::to_string(*gr->subdivision_x);
				w_string += '\t';
				w_string += std::to_string(*gr->subdivision_y);
				w_string += '\n';
			}
		}

		for (Entity::AutobuildingGroup* a_group : e->autobuilding_group_list)
		{
			w_string += "CREATE_NEW_AUTOBUILDING_GROUP";
			w_string += '\n';
			w_string += "autobuilding_group_offset_and_size";
			w_string += '\t';
			w_string += EString::float_to_string(*a_group->offset_x);
			w_string += '\t';
			w_string += EString::float_to_string(*a_group->offset_y);
			w_string += '\t';
			w_string += EString::float_to_string(*a_group->offset_z);
			w_string += '\t';
			w_string += EString::float_to_string(*a_group->size_x);
			w_string += '\t';
			w_string += EString::float_to_string(*a_group->size_y);
			w_string += '\n';

			for (Entity::AutobuildingGroupElement* a_element : a_group->autobuilding_group_element_list)
			{
				w_string += "CREATE_NEW_AUTOBUILDING_GROUP_ELEMENT";
				w_string += '\n';

				w_string += "autobuilding_group_element_offset_and_size";
				w_string += '\t';
				w_string += EString::float_to_string(*a_element->offset_x);
				w_string += '\t';
				w_string += EString::float_to_string(*a_element->offset_y);
				w_string += '\t';
				w_string += EString::float_to_string(*a_element->offset_z);
				w_string += '\t';
				w_string += EString::float_to_string(*a_element->size_x);
				w_string += '\t';
				w_string += EString::float_to_string(*a_element->size_y);
				w_string += '\n';

				int math_id = 0;
				for (Entity::AutobuildingBase* a_base : e->autobuilding_base_list)
				{
					if (a_base == a_element->autobuilding_base)
					{
						w_string += "autobuilding_group_element_base_id";
						w_string += '\t';
						w_string += std::to_string(math_id);
						w_string += '\n';
					}

					math_id++;
				}
			}
		}

		w_string += "PUT_ENTITY_TO_MAP";
		w_string += '\n';
	}

	writer << w_string;
	writer.close();
}

void EWindowMain::load_map(std::string _name)
{
	ifstream myfile;
	myfile.open("test/" + _name + ".txt");
	std::string line;

	Entity* jc_entity = NULL;
	Entity::AutobuildingGroup* jc_group = NULL;
	Entity::AutobuildingGroupElement* jc_group_element = NULL;
	Entity::AutobuildingBase* jc_base = NULL;

	EButton::EGridRegion* jc_grid_region = NULL;

	EWindowMain::entity_list.clear();

	while (getline(myfile, line))
	{
		EFile::data_parser(line);

		for (int i = 0; i < EFile::array_size; i++)
		{
			//std::cout << "=" << EFile::data_array[i] << "=" << std::endl;

			if (EFile::data_array[i] == "CREATE_NEW_ENTITY")
			{
				jc_entity = new Entity();
				std::cout << "______created new entity" << endl;
			}

			if ((EFile::data_array[i] == "entity_position") & (jc_entity != NULL))
			{
				i++; *jc_entity->position_x = EMath::to_float(EFile::data_array[i]);
				i++; *jc_entity->position_y = EMath::to_float(EFile::data_array[i]);
				i++; *jc_entity->position_z = EMath::to_float(EFile::data_array[i]);
			}

			///////////////////////BASE SECTION
			if ((EFile::data_array[i] == "CREATE_NEW_AUTOBUILDING_BASE") & (jc_entity != NULL))
			{
				jc_base = new Entity::AutobuildingBase();
				jc_base->grid_region.clear();
				//jc_group_element->autobuilding_base = jc_base;

				jc_entity->autobuilding_base_list.push_back(jc_base);

				std::cout << "______created new base" << endl;
			}

			if ((EFile::data_array[i] == "autobuilding_base_main_texture") & (jc_base != NULL))
			{
				i++; jc_base->main_texture = ETextureAtlas::put_texture_to_atlas(EFile::data_array[i], EWindow::default_texture_atlas);
			}

			if ((EFile::data_array[i] == "autobuilding_base_space_between_sprites") & (jc_base != NULL))
			{
				i++; *jc_base->space_between_sprite_x = EMath::to_float(EFile::data_array[i]);
				i++; *jc_base->space_between_sprite_y = EMath::to_float(EFile::data_array[i]);
			}

			if ((EFile::data_array[i] == "CREATE_NEW_GRID_REGION") & (jc_base != NULL))
			{
				jc_grid_region = new EButton::EGridRegion();
				jc_base->grid_region.push_back(jc_grid_region);

				std::cout << "______created new grid region" << endl;
			}

			if ((EFile::data_array[i] == "grid_region_position_and_size") & (jc_grid_region != NULL))
			{
				i++; *jc_grid_region->position_x = EMath::to_float(EFile::data_array[i]);	std::cout << "#_____set grid pos x [" << std::to_string(*jc_grid_region->position_x) << "]" << endl;
				i++; *jc_grid_region->position_y = EMath::to_float(EFile::data_array[i]);	std::cout << "#_____set grid pos y [" << std::to_string(*jc_grid_region->position_y) << "]" << endl;
				i++; *jc_grid_region->size_x = EMath::to_float(EFile::data_array[i]);		std::cout << "#_____set grid size x [" << std::to_string(*jc_grid_region->size_x) << "]" << endl;
				i++; *jc_grid_region->size_y = EMath::to_float(EFile::data_array[i]);		std::cout << "#_____set grid size y [" << std::to_string(*jc_grid_region->size_y) << "]" << endl;
			}

			if ((EFile::data_array[i] == "grid_region_subdivision") & (jc_grid_region != NULL))
			{
				i++; *jc_grid_region->subdivision_x = std::stoi(EFile::data_array[i]);
				i++; *jc_grid_region->subdivision_y = std::stoi(EFile::data_array[i]);
			}

			///////////////////////GROUP SECTION
			if ((EFile::data_array[i] == "CREATE_NEW_AUTOBUILDING_GROUP") & (jc_entity != NULL))
			{
				jc_group = new Entity::AutobuildingGroup();
				jc_entity->autobuilding_group_list.push_back(jc_group);

				std::cout << "______created new group" << endl;
			}

			if ((EFile::data_array[i] == "autobuilding_group_offset_and_size") & (jc_group != NULL))
			{
				i++; *jc_group->offset_x = EMath::to_float(EFile::data_array[i]);
				i++; *jc_group->offset_y = EMath::to_float(EFile::data_array[i]);
				i++; *jc_group->offset_z = EMath::to_float(EFile::data_array[i]);
				i++; *jc_group->size_x = EMath::to_float(EFile::data_array[i]);
				i++; *jc_group->size_y = EMath::to_float(EFile::data_array[i]);
			}

			///////////////////////ELEMENT SECTION
			if ((EFile::data_array[i] == "CREATE_NEW_AUTOBUILDING_GROUP_ELEMENT") & (jc_group != NULL))
			{
				jc_group_element = new Entity::AutobuildingGroupElement();
				jc_group->autobuilding_group_element_list.push_back(jc_group_element);

				std::cout << "______created new group element" << endl;
			}

			if ((EFile::data_array[i] == "autobuilding_group_element_offset_and_size") & (jc_group_element != NULL))
			{
				i++; *jc_group_element->offset_x = EMath::to_float(EFile::data_array[i]);
				i++; *jc_group_element->offset_y = EMath::to_float(EFile::data_array[i]);
				i++; *jc_group_element->offset_z = EMath::to_float(EFile::data_array[i]);
				i++; *jc_group_element->size_x = EMath::to_float(EFile::data_array[i]);
				i++; *jc_group_element->size_y = EMath::to_float(EFile::data_array[i]);
			}

			if ((EFile::data_array[i] == "autobuilding_group_element_base_id") & (jc_group_element != NULL))
			{
				i++;
				if
					(
						(std::stoi(EFile::data_array[i]) >= 0)
						&&
						(std::stoi(EFile::data_array[i]) < jc_entity->autobuilding_base_list.size())
						&&
						(jc_entity->autobuilding_base_list.at(std::stoi(EFile::data_array[i])) != NULL)
						)
				{
					jc_group_element->autobuilding_base = jc_entity->autobuilding_base_list.at(std::stoi(EFile::data_array[i]));
				}
			}

			if ((EFile::data_array[i] == "PUT_ENTITY_TO_MAP") & (jc_entity != NULL))
			{
				EWindowMain::entity_list.push_back(jc_entity);
				EWindowMain::generate_building(jc_entity);
			}
		}
	}

	myfile.close();
}

void EWindowMain::add_new_sprite_if_need(int _i, Entity* _e, std::string _text)
{
	if (_i >= _e->entity_sprite_array->sprite_list.size())
	{
		EGraphicCore::ESprite* jcs = new EGraphicCore::ESprite();
		_e->entity_sprite_array->sprite_list.push_back(jcs);

		std::cout << "create new sprite (" << _text << "), new size of sprites is [" << std::to_string(_e->entity_sprite_array->sprite_list.size()) << "]" << std::endl;
	}
}

void EWindowMain::generate_building(Entity* _e)
{
	EGraphicCore::ESprite* selected_sprite = NULL;
	int selected_sprite_id = 0;

	/*for (int i = 0; i < (100 - _e->entity_sprite_array->sprite_list.size()); i++)
	{
		EGraphicCore::ESprite* just_created_sprite = new EGraphicCore::ESprite();
		_e->entity_sprite_array->sprite_list.push_back(just_created_sprite);
	}*/

	/*for (EGraphicCore::ESprite* spr : _e->entity_sprite_array->sprite_list)
	{
		EGraphicCore::reset_sprite_data(spr);
	}*/

	//add_new_sprite_if_need(0, _e);

	if (_e->entity_sprite_array == NULL)
	{
		_e->entity_sprite_array = new EGraphicCore::sprite_array();
	}
	//std::cout << "ebanye dauny 00" << std::endl;

	//std::cout << "ebanye dauny 01" << std::endl;

	float mid_wall_copies_x = 0.0f;
	float mid_wall_copies_y = 0.0f;

	float wall_full_size_x = 0.0f;
	float wall_full_size_y = 0.0f;

	float wall_fragment_x = 0.0f;
	float wall_fragment_y = 0.0f;

	float fragment_correction_factor_x = 1.0f;
	float fragment_correction_factor_y = 1.0f;

	int subdivision_x_count = 0;
	int subdivision_y_count = 0;

	for (Entity::AutobuildingGroup* a_group : _e->autobuilding_group_list)
	{
		srand(1);
		//srand(time(NULL)
		for (Entity::AutobuildingGroupElement* a_element : a_group->autobuilding_group_element_list)
		{
			//std::cout << "Copies x [" << std::to_string(mid_wall_copies_x) << "]" << std::endl;
			//std::cout << "Copies y [" << std::to_string(mid_wall_copies_y) << "]" << std::endl;

			//fragment_correction_factor_y = 1.0f;

			//		copies_x
			//		copies_y
			//		correction_x
			//		correction_y
			//		full_size_x
			//		full_size_y
			//		start_x
			//		start_y

			//mid wall
			subdivision_x_count = *a_element->autobuilding_base->grid_region.at(GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_MID)->subdivision_x;
			subdivision_y_count = *a_element->autobuilding_base->grid_region.at(GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_MID)->subdivision_y;

			wall_full_size_x = round((*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_MID)->size_x) / (subdivision_x_count + 1.0f));
			wall_full_size_y = round((*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_MID)->size_y) / (subdivision_y_count + 1.0f));

			/*std::cout
			<<
			" WFS x: ["
			<<
			std::to_string(wall_full_size_x)
			<<
			"] WFS y: ["
			<<
			std::to_string(wall_full_size_y)
			<<
			"]"
			<<
			std::endl
			<<
			std::endl;*/

			mid_wall_copies_x
				=
				(
					*a_element->size_x
					-
					*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT)->size_x
					-
					*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT)->size_x
					) / (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x);

			mid_wall_copies_y
				=
				(
					*a_element->size_y
					-
					*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_UP)->size_y
					-
					*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_DOWN)->size_y
					)
				/ (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y);

			fragment_correction_factor_x = wall_full_size_x / (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x);
			fragment_correction_factor_y = wall_full_size_y / (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y);

			if
				(
					(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_MID)->size_x > 0)
					&
					(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_MID)->size_y > 0)
					)
				for (int yy = 0; yy < ceil(mid_wall_copies_y); yy++)
					for (int xx = 0; xx < ceil(mid_wall_copies_x); xx++)
					{
						add_new_sprite_if_need(selected_sprite_id, _e, "mid wall");

						selected_sprite = _e->entity_sprite_array->sprite_list.at(selected_sprite_id);
						EGraphicCore::reset_sprite_data(selected_sprite);

						wall_fragment_x = min(1.0f, (mid_wall_copies_x + 0.0f - xx) / fragment_correction_factor_x);
						wall_fragment_y = min(1.0f, (mid_wall_copies_y + 0.0f - yy) / fragment_correction_factor_y);

						*selected_sprite->offset_x = *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT)->size_x;
						*selected_sprite->offset_x += xx * (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x) + *a_group->offset_x + *a_element->offset_x;

						*selected_sprite->offset_y = 0.0f;
						*selected_sprite->offset_y += *a_group->offset_y + *a_element->offset_y;

						*selected_sprite->offset_z = *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_DOWN)->size_y;
						*selected_sprite->offset_z += yy * (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y) + *a_group->offset_z + *a_element->offset_z;

						convert_size_to_fragment
						(
							a_element->autobuilding_base->main_texture,
							round(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT)->size_x + (wall_full_size_x * (rand() % (subdivision_x_count + 1)))),
							round(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_DOWN)->size_y + (wall_full_size_y * (rand() % (subdivision_y_count + 1)))),
							round(wall_full_size_x * wall_fragment_x),
							round(wall_full_size_y * wall_fragment_y),
							selected_sprite->fragment_left,
							selected_sprite->fragment_right,
							selected_sprite->fragment_down,
							selected_sprite->fragment_up
						);

						*selected_sprite->size_x = round(wall_full_size_x * wall_fragment_x);
						*selected_sprite->size_y = round(wall_full_size_y * wall_fragment_y);

						selected_sprite->texture_gabarite = a_element->autobuilding_base->main_texture;

						selected_sprite_id++;
					}

			//bottom
			if
				(
					(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_DOWN)->size_x > 0)
					&
					(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_DOWN)->size_y > 0)
					//(*a_element->autobuilding_texture_region->texture_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_DOWN)->size_y > 0)
					)
			{
				subdivision_x_count = *a_element->autobuilding_base->grid_region.at(GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_MID)->subdivision_x;
				subdivision_y_count = *a_element->autobuilding_base->grid_region.at(GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_DOWN)->subdivision_y;

				wall_full_size_x = round((*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_DOWN)->size_x) / (subdivision_x_count + 1.0f));
				wall_full_size_y = round((*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_DOWN)->size_y) / (subdivision_y_count + 1.0f));

				mid_wall_copies_x
					=
					(
						*a_element->size_x
						-
						*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT)->size_x
						-
						*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT)->size_x
						) / (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x);

				mid_wall_copies_y
					=
					(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_DOWN)->size_y)
					/ (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y);

				fragment_correction_factor_x = wall_full_size_x / (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x);
				fragment_correction_factor_y = wall_full_size_y / (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y);

				for (int yy = 0; yy < ceil(mid_wall_copies_y); yy++)
					for (int xx = 0; xx < ceil(mid_wall_copies_x); xx++)
					{
						add_new_sprite_if_need(selected_sprite_id, _e, "bottom");

						selected_sprite = _e->entity_sprite_array->sprite_list.at(selected_sprite_id);
						EGraphicCore::reset_sprite_data(selected_sprite);

						wall_fragment_x = min(1.0f, (mid_wall_copies_x + 0.0f - xx) / fragment_correction_factor_x);
						wall_fragment_y = min(1.0f, (mid_wall_copies_y + 0.0f - yy) / fragment_correction_factor_y);

						*selected_sprite->offset_x = *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT)->size_x;
						*selected_sprite->offset_x += xx * (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x) + *a_group->offset_x + *a_element->offset_x;

						*selected_sprite->offset_y = 0.0f;
						*selected_sprite->offset_y += *a_group->offset_y + *a_element->offset_y;

						*selected_sprite->offset_z = 0.0f;
						*selected_sprite->offset_z += yy * (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y) + *a_group->offset_z + *a_element->offset_z;

						convert_size_to_fragment
						(
							a_element->autobuilding_base->main_texture,
							round(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT)->size_x + (wall_full_size_x * (rand() % (subdivision_x_count + 1)))),
							round(wall_full_size_y * (rand() % (subdivision_y_count + 1))),
							round(wall_full_size_x * wall_fragment_x),
							round(wall_full_size_y * wall_fragment_y),
							selected_sprite->fragment_left,
							selected_sprite->fragment_right,
							selected_sprite->fragment_down,
							selected_sprite->fragment_up
						);

						*selected_sprite->size_x = round(wall_full_size_x * wall_fragment_x);
						*selected_sprite->size_y = round(wall_full_size_y * wall_fragment_y);

						selected_sprite->texture_gabarite = a_element->autobuilding_base->main_texture;

						selected_sprite_id++;
					}
			}

			//up
			if
				(
					(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_UP)->size_x > 0)
					&
					(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_UP)->size_y > 0)
					)
			{
				subdivision_x_count = *a_element->autobuilding_base->grid_region.at(GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_MID)->subdivision_x;
				subdivision_y_count = *a_element->autobuilding_base->grid_region.at(GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_UP)->subdivision_y;

				wall_full_size_x = round((*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_UP)->size_x) / (subdivision_x_count + 1.0f));
				wall_full_size_y = round((*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_UP)->size_y) / (subdivision_y_count + 1.0f));

				mid_wall_copies_x
					=
					(
						*a_element->size_x
						-
						*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT)->size_x
						-
						*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT)->size_x
						) / (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x);

				mid_wall_copies_y
					=
					(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_UP)->size_y)
					/ (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y);

				fragment_correction_factor_x = wall_full_size_x / (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x);
				fragment_correction_factor_y = wall_full_size_y / (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y);

				for (int yy = 0; yy < ceil(mid_wall_copies_y); yy++)
					for (int xx = 0; xx < ceil(mid_wall_copies_x); xx++)
					{
						add_new_sprite_if_need(selected_sprite_id, _e, "up");

						selected_sprite = _e->entity_sprite_array->sprite_list.at(selected_sprite_id);
						EGraphicCore::reset_sprite_data(selected_sprite);

						wall_fragment_x = min(1.0f, (mid_wall_copies_x + 0.0f - xx) / fragment_correction_factor_x);
						wall_fragment_y = min(1.0f, (mid_wall_copies_y + 0.0f - yy) / fragment_correction_factor_y);

						*selected_sprite->offset_x = *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT)->size_x;
						*selected_sprite->offset_x += xx * (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x) + *a_group->offset_x + *a_element->offset_x;

						*selected_sprite->offset_y = 0.0f;
						*selected_sprite->offset_y += *a_group->offset_y + *a_element->offset_y;

						*selected_sprite->offset_z = *a_element->size_y - *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_UP)->size_y;
						*selected_sprite->offset_z += yy * (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y) + *a_group->offset_z + *a_element->offset_z;

						convert_size_to_fragment
						(
							a_element->autobuilding_base->main_texture,
							round(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_UP)->position_x + wall_full_size_x * (rand() % (subdivision_x_count + 1))),
							round(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_UP)->position_y + wall_full_size_y * (rand() % (subdivision_y_count + 1))),
							round(wall_full_size_x * wall_fragment_x),
							round(wall_full_size_y * wall_fragment_y),
							selected_sprite->fragment_left,
							selected_sprite->fragment_right,
							selected_sprite->fragment_down,
							selected_sprite->fragment_up
						);

						*selected_sprite->size_x = round(wall_full_size_x * wall_fragment_x);
						*selected_sprite->size_y = round(wall_full_size_y * wall_fragment_y);

						selected_sprite->texture_gabarite = a_element->autobuilding_base->main_texture;

						selected_sprite_id++;
					}
			}

			//left
			if
				(
					(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT)->size_x > 0)
					&
					(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT)->size_y > 0)
					)
			{
				subdivision_x_count = *a_element->autobuilding_base->grid_region.at(GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT)->subdivision_x;
				subdivision_y_count = *a_element->autobuilding_base->grid_region.at(GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_MID)->subdivision_y;

				wall_full_size_x = round((*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT)->size_x) / (subdivision_x_count + 1.0f));
				wall_full_size_y = round((*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT)->size_y) / (subdivision_y_count + 1.0f));

				mid_wall_copies_x
					=
					(
						(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT)->size_x)

						) / (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x);

				mid_wall_copies_y
					=
					(
						*a_element->size_y
						-
						*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_UP)->size_y
						-
						*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_DOWN)->size_y
						)
					/ (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y);

				fragment_correction_factor_x = wall_full_size_x / (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x);
				fragment_correction_factor_y = wall_full_size_y / (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y);

				for (int yy = 0; yy < ceil(mid_wall_copies_y); yy++)
					for (int xx = 0; xx < ceil(mid_wall_copies_x); xx++)
					{
						add_new_sprite_if_need(selected_sprite_id, _e, "left");

						selected_sprite = _e->entity_sprite_array->sprite_list.at(selected_sprite_id);
						EGraphicCore::reset_sprite_data(selected_sprite);

						wall_fragment_x = min(1.0f, (mid_wall_copies_x + 0.0f - xx) / fragment_correction_factor_x);
						wall_fragment_y = min(1.0f, (mid_wall_copies_y + 0.0f - yy) / fragment_correction_factor_y);

						*selected_sprite->offset_x = 0.0f;
						*selected_sprite->offset_x += xx * (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x) + *a_group->offset_x + *a_element->offset_x;

						*selected_sprite->offset_y = 0.0f;
						*selected_sprite->offset_y += *a_group->offset_y + *a_element->offset_y;

						*selected_sprite->offset_z = *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT)->position_y;
						*selected_sprite->offset_z += yy * (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y) + *a_group->offset_z + *a_element->offset_z;

						convert_size_to_fragment
						(
							a_element->autobuilding_base->main_texture,
							wall_full_size_x * (rand() % (subdivision_x_count + 1)),
							round(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT)->position_y + wall_full_size_y * (rand() % (subdivision_y_count + 1))),
							round(wall_full_size_x * wall_fragment_x),
							round(wall_full_size_y * wall_fragment_y),
							selected_sprite->fragment_left,
							selected_sprite->fragment_right,
							selected_sprite->fragment_down,
							selected_sprite->fragment_up
						);

						*selected_sprite->size_x = round(wall_full_size_x * wall_fragment_x);
						*selected_sprite->size_y = round(wall_full_size_y * wall_fragment_y);

						selected_sprite->texture_gabarite = a_element->autobuilding_base->main_texture;

						selected_sprite_id++;
					}
			}

			//left-down
			if
				(
					(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT_DOWN_CORNER)->size_x > 0)
					&
					(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT_DOWN_CORNER)->size_y > 0)
					)
			{
				subdivision_x_count = *a_element->autobuilding_base->grid_region.at(GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT_DOWN_CORNER)->subdivision_x;
				subdivision_y_count = *a_element->autobuilding_base->grid_region.at(GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT_DOWN_CORNER)->subdivision_y;

				wall_full_size_x = round((*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT_DOWN_CORNER)->size_x) / (subdivision_x_count + 1.0f));
				wall_full_size_y = round((*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT_DOWN_CORNER)->size_y) / (subdivision_y_count + 1.0f));

				mid_wall_copies_x
					=
					(
						*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT_DOWN_CORNER)->size_x
						)
					/ (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x);

				mid_wall_copies_y
					=
					(
						*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT_DOWN_CORNER)->size_y
						)
					/ (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y);

				fragment_correction_factor_x = wall_full_size_x / (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x);
				fragment_correction_factor_y = wall_full_size_y / (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y);

				for (int yy = 0; yy < ceil(mid_wall_copies_y); yy++)
					for (int xx = 0; xx < ceil(mid_wall_copies_x); xx++)
					{
						add_new_sprite_if_need(selected_sprite_id, _e, "left_down");

						selected_sprite = _e->entity_sprite_array->sprite_list.at(selected_sprite_id);
						EGraphicCore::reset_sprite_data(selected_sprite);

						wall_fragment_x = min(1.0f, (mid_wall_copies_x + 0.0f - xx) / fragment_correction_factor_x);
						wall_fragment_y = min(1.0f, (mid_wall_copies_y + 0.0f - yy) / fragment_correction_factor_y);

						*selected_sprite->offset_x = 0.0f;
						*selected_sprite->offset_x += xx * (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x) + *a_group->offset_x + *a_element->offset_x;

						*selected_sprite->offset_y = 0.0f;
						*selected_sprite->offset_y += *a_group->offset_y + *a_element->offset_y;

						*selected_sprite->offset_z = 0.0f;
						*selected_sprite->offset_z += yy * (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y) + *a_group->offset_z + *a_element->offset_z;

						convert_size_to_fragment
						(
							a_element->autobuilding_base->main_texture,
							wall_full_size_x * (rand() % (subdivision_x_count + 1)),
							wall_full_size_y * (rand() % (subdivision_y_count + 1)),
							round(wall_full_size_x * wall_fragment_x),
							round(wall_full_size_y * wall_fragment_y),
							selected_sprite->fragment_left,
							selected_sprite->fragment_right,
							selected_sprite->fragment_down,
							selected_sprite->fragment_up
						);

						*selected_sprite->size_x = round(wall_full_size_x * wall_fragment_x);
						*selected_sprite->size_y = round(wall_full_size_y * wall_fragment_y);

						selected_sprite->texture_gabarite = a_element->autobuilding_base->main_texture;

						selected_sprite_id++;
					}
			}

			//left-up
			if
				(
					(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT_UP_CORNER)->size_x > 0)
					&
					(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT_UP_CORNER)->size_y > 0)
					)
			{
				subdivision_x_count = *a_element->autobuilding_base->grid_region.at(GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT_UP_CORNER)->subdivision_x;
				subdivision_y_count = *a_element->autobuilding_base->grid_region.at(GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT_UP_CORNER)->subdivision_y;

				wall_full_size_x = round((*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT_UP_CORNER)->size_x) / (subdivision_x_count + 1.0f));
				wall_full_size_y = round((*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT_UP_CORNER)->size_y) / (subdivision_y_count + 1.0f));

				mid_wall_copies_x
					=
					(
						*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT_UP_CORNER)->size_x
						)
					/ (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x);

				mid_wall_copies_y
					=
					(
						*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT_UP_CORNER)->size_y
						)
					/ (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y);

				fragment_correction_factor_x = wall_full_size_x / (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x);
				fragment_correction_factor_y = wall_full_size_y / (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y);

				for (int yy = 0; yy < ceil(mid_wall_copies_y); yy++)
					for (int xx = 0; xx < ceil(mid_wall_copies_x); xx++)
					{
						add_new_sprite_if_need(selected_sprite_id, _e, "left_up");

						selected_sprite = _e->entity_sprite_array->sprite_list.at(selected_sprite_id);
						EGraphicCore::reset_sprite_data(selected_sprite);

						wall_fragment_x = min(1.0f, (mid_wall_copies_x + 0.0f - xx) / fragment_correction_factor_x);
						wall_fragment_y = min(1.0f, (mid_wall_copies_y + 0.0f - yy) / fragment_correction_factor_y);

						*selected_sprite->offset_x = 0.0f;
						*selected_sprite->offset_x += xx * (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x) + *a_group->offset_x + *a_element->offset_x;

						*selected_sprite->offset_y = 0.0f;
						*selected_sprite->offset_y += *a_group->offset_y + *a_element->offset_y;

						*selected_sprite->offset_z = *a_element->size_y - *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT_UP_CORNER)->size_y;
						*selected_sprite->offset_z += yy * (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y) + *a_group->offset_z + *a_element->offset_z;

						convert_size_to_fragment
						(
							a_element->autobuilding_base->main_texture,
							wall_full_size_x * (rand() % (subdivision_x_count + 1)),
							round(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT_UP_CORNER)->position_y + wall_full_size_y * (rand() % (subdivision_y_count + 1))),
							round(wall_full_size_x * wall_fragment_x),
							round(wall_full_size_y * wall_fragment_y),
							selected_sprite->fragment_left,
							selected_sprite->fragment_right,
							selected_sprite->fragment_down,
							selected_sprite->fragment_up
						);

						*selected_sprite->size_x = round(wall_full_size_x * wall_fragment_x);
						*selected_sprite->size_y = round(wall_full_size_y * wall_fragment_y);

						selected_sprite->texture_gabarite = a_element->autobuilding_base->main_texture;

						selected_sprite_id++;
					}
			}

			//right
			if
				(
					(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT)->size_x > 0)
					&
					(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT)->size_y > 0)
					)
			{
				subdivision_x_count = *a_element->autobuilding_base->grid_region.at(GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT)->subdivision_x;
				subdivision_y_count = *a_element->autobuilding_base->grid_region.at(GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_MID)->subdivision_y;

				wall_full_size_x = round((*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT)->size_x) / (subdivision_x_count + 1.0f));
				wall_full_size_y = round((*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT)->size_y) / (subdivision_y_count + 1.0f));

				mid_wall_copies_x
					=
					(
						(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT)->size_x)

						) / (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x);

				mid_wall_copies_y
					=
					(
						*a_element->size_y
						-
						*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_UP)->size_y
						-
						*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_DOWN)->size_y
						)
					/ (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y);

				fragment_correction_factor_x = wall_full_size_x / (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x);
				fragment_correction_factor_y = wall_full_size_y / (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y);

				for (int yy = 0; yy < ceil(mid_wall_copies_y); yy++)
					for (int xx = 0; xx < ceil(mid_wall_copies_x); xx++)
					{
						add_new_sprite_if_need(selected_sprite_id, _e, "right");

						selected_sprite = _e->entity_sprite_array->sprite_list.at(selected_sprite_id);
						EGraphicCore::reset_sprite_data(selected_sprite);

						wall_fragment_x = min(1.0f, (mid_wall_copies_x + 0.0f - xx) / fragment_correction_factor_x);
						wall_fragment_y = min(1.0f, (mid_wall_copies_y + 0.0f - yy) / fragment_correction_factor_y);

						*selected_sprite->offset_x = *a_element->size_x - *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT)->size_x;
						*selected_sprite->offset_x += xx * (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x) + *a_group->offset_x + *a_element->offset_x;

						*selected_sprite->offset_y = 0.0f;
						*selected_sprite->offset_y += *a_group->offset_y + *a_element->offset_y;

						*selected_sprite->offset_z = *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT)->position_y;
						*selected_sprite->offset_z += yy * (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y) + *a_group->offset_z + *a_element->offset_z;

						convert_size_to_fragment
						(
							a_element->autobuilding_base->main_texture,
							round(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT)->position_x + wall_full_size_x * (rand() % (subdivision_x_count + 1))),
							round(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT)->position_y + wall_full_size_y * (rand() % (subdivision_y_count + 1))),
							round(wall_full_size_x * wall_fragment_x),
							round(wall_full_size_y * wall_fragment_y),
							selected_sprite->fragment_left,
							selected_sprite->fragment_right,
							selected_sprite->fragment_down,
							selected_sprite->fragment_up
						);

						*selected_sprite->size_x = round(wall_full_size_x * wall_fragment_x);
						*selected_sprite->size_y = round(wall_full_size_y * wall_fragment_y);

						selected_sprite->texture_gabarite = a_element->autobuilding_base->main_texture;

						selected_sprite_id++;
					}
			}

			//right-down
			if
				(
					(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT_DOWN_CORNER)->size_x > 0)
					&
					(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT_DOWN_CORNER)->size_y > 0)
					)
			{
				subdivision_x_count = *a_element->autobuilding_base->grid_region.at(GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT_DOWN_CORNER)->subdivision_x;
				subdivision_y_count = *a_element->autobuilding_base->grid_region.at(GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT_DOWN_CORNER)->subdivision_y;

				wall_full_size_x = round((*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT_DOWN_CORNER)->size_x) / (subdivision_x_count + 1.0f));
				wall_full_size_y = round((*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT_DOWN_CORNER)->size_y) / (subdivision_y_count + 1.0f));

				mid_wall_copies_x
					=
					(
						(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT_DOWN_CORNER)->size_x)

						) / (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x);

				mid_wall_copies_y
					=
					(
						*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT_DOWN_CORNER)->size_y
						)
					/ (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y);

				fragment_correction_factor_x = wall_full_size_x / (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x);
				fragment_correction_factor_y = wall_full_size_y / (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y);

				for (int yy = 0; yy < ceil(mid_wall_copies_y); yy++)
					for (int xx = 0; xx < ceil(mid_wall_copies_x); xx++)
					{
						add_new_sprite_if_need(selected_sprite_id, _e, "right_down");

						selected_sprite = _e->entity_sprite_array->sprite_list.at(selected_sprite_id);
						EGraphicCore::reset_sprite_data(selected_sprite);

						wall_fragment_x = min(1.0f, (mid_wall_copies_x + 0.0f - xx) / fragment_correction_factor_x);
						wall_fragment_y = min(1.0f, (mid_wall_copies_y + 0.0f - yy) / fragment_correction_factor_y);

						*selected_sprite->offset_x = *a_element->size_x - *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT_DOWN_CORNER)->size_x;
						*selected_sprite->offset_x += xx * (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x) + *a_group->offset_x + *a_element->offset_x;

						*selected_sprite->offset_y = 0.0f;
						*selected_sprite->offset_y += *a_group->offset_y + *a_element->offset_y;

						*selected_sprite->offset_z = 0.0f;
						*selected_sprite->offset_z += yy * (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y) + *a_group->offset_z + *a_element->offset_z;

						convert_size_to_fragment
						(
							a_element->autobuilding_base->main_texture,
							round(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT_DOWN_CORNER)->position_x + wall_full_size_x * (rand() % (subdivision_x_count + 1))),
							round(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT_DOWN_CORNER)->position_y + wall_full_size_y * (rand() % (subdivision_y_count + 1))),
							round(wall_full_size_x * wall_fragment_x),
							round(wall_full_size_y * wall_fragment_y),
							selected_sprite->fragment_left,
							selected_sprite->fragment_right,
							selected_sprite->fragment_down,
							selected_sprite->fragment_up
						);

						*selected_sprite->size_x = round(wall_full_size_x * wall_fragment_x);
						*selected_sprite->size_y = round(wall_full_size_y * wall_fragment_y);

						selected_sprite->texture_gabarite = a_element->autobuilding_base->main_texture;

						selected_sprite_id++;
					}
			}

			//right-up
			if
				(
					(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT_UP_CORNER)->size_x > 0)
					&
					(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT_UP_CORNER)->size_y > 0)
					)
			{
				subdivision_x_count = *a_element->autobuilding_base->grid_region.at(GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT_UP_CORNER)->subdivision_x;
				subdivision_y_count = *a_element->autobuilding_base->grid_region.at(GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT_UP_CORNER)->subdivision_y;

				wall_full_size_x = round((*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT_UP_CORNER)->size_x) / (subdivision_x_count + 1.0f));
				wall_full_size_y = round((*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT_UP_CORNER)->size_y) / (subdivision_y_count + 1.0f));

				mid_wall_copies_x
					=
					(
						(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT_UP_CORNER)->size_x)

						) / (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x);

				mid_wall_copies_y
					=
					(
						*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT_UP_CORNER)->size_y
						)
					/ (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y);

				fragment_correction_factor_x = wall_full_size_x / (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x);
				fragment_correction_factor_y = wall_full_size_y / (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y);

				for (int yy = 0; yy < ceil(mid_wall_copies_y); yy++)
					for (int xx = 0; xx < ceil(mid_wall_copies_x); xx++)
					{
						add_new_sprite_if_need(selected_sprite_id, _e, "right_up");

						selected_sprite = _e->entity_sprite_array->sprite_list.at(selected_sprite_id);
						EGraphicCore::reset_sprite_data(selected_sprite);

						wall_fragment_x = min(1.0f, (mid_wall_copies_x + 0.0f - xx) / fragment_correction_factor_x);
						wall_fragment_y = min(1.0f, (mid_wall_copies_y + 0.0f - yy) / fragment_correction_factor_y);

						*selected_sprite->offset_x = *a_element->size_x - *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT_UP_CORNER)->size_x;
						*selected_sprite->offset_x += xx * (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x) + *a_group->offset_x + *a_element->offset_x;

						*selected_sprite->offset_y = 0.0f;
						*selected_sprite->offset_y += *a_group->offset_y + *a_element->offset_y;

						*selected_sprite->offset_z = *a_element->size_y - *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT_UP_CORNER)->size_y;
						*selected_sprite->offset_z += yy * (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y) + *a_group->offset_z + *a_element->offset_z;

						convert_size_to_fragment
						(
							a_element->autobuilding_base->main_texture,
							round(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT_UP_CORNER)->position_x + wall_full_size_x * (rand() % (subdivision_x_count + 1))),
							round(*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT_UP_CORNER)->position_y + wall_full_size_y * (rand() % (subdivision_y_count + 1))),
							round(wall_full_size_x * wall_fragment_x),
							round(wall_full_size_y * wall_fragment_y),
							selected_sprite->fragment_left,
							selected_sprite->fragment_right,
							selected_sprite->fragment_down,
							selected_sprite->fragment_up
						);

						*selected_sprite->size_x = round(wall_full_size_x * wall_fragment_x);
						*selected_sprite->size_y = round(wall_full_size_y * wall_fragment_y);

						selected_sprite->texture_gabarite = a_element->autobuilding_base->main_texture;

						selected_sprite_id++;
					}
			}

			/*std::cout
				<<
				" fragment x: ["
				<<
				std::to_string(wall_fragment_x)
				<<
				"] fragment y: ["
				<<
				std::to_string(wall_fragment_y)
				<<
				"]"
				<<
				std::endl;

			std::cout
				<<
				" correction x: ["
				<<
				std::to_string(fragment_correction_factor_x)
				<<
				"] correction y: ["
				<<
				std::to_string(fragment_correction_factor_y)
				<<
				"]"
				<<
				std::endl;*/

				//a_element->autobuilding_texture_region->texture_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT_UP_CORNER);
		}
	}

	if (true)
	{
		for (int i = selected_sprite_id; i < _e->entity_sprite_array->sprite_list.size(); i++)
		{
			EGraphicCore::reset_sprite_data(_e->entity_sprite_array->sprite_list.at(i));
		}

		if
			(
				(_e->entity_sprite_array->sprite_list.size() > 0)
				&&
				//(_e->entity_sprite_array->sprite_list.at(_e->entity_sprite_array->sprite_list.size() - 1)->texture_gabarite == NULL)
				(selected_sprite_id < _e->entity_sprite_array->sprite_list.size())
				&&
				(true)
				)
		{
			//std::cout << "pre remove empty sprite, new size of sprites is [" << std::to_string(_e->entity_sprite_array->sprite_list.size()) << "]" << std::endl;

			EGraphicCore::ESprite* deleted_sprite
				=
				_e->entity_sprite_array->sprite_list.at(_e->entity_sprite_array->sprite_list.size() - 1);

			if (_e->entity_sprite_array->sprite_list.size() > 1)
			{
				_e->entity_sprite_array->sprite_list.erase(_e->entity_sprite_array->sprite_list.begin() + _e->entity_sprite_array->sprite_list.size() - 1);

				delete deleted_sprite;
			}
			//else
			//{_e->entity_sprite_array->sprite_list.clear(); }
			/*
			if (_e->entity_sprite_array->sprite_list.size() == 1)
			{
			}
			else
			{
				//EGraphicCore::ESprite* deleted_sprite = _e->entity_sprite_array->sprite_list.at(_e->entity_sprite_array->sprite_list.size() - 1);
				_e->entity_sprite_array->sprite_list.erase(_e->entity_sprite_array->sprite_list.begin() + _e->entity_sprite_array->sprite_list.size() - 1);
			}*/

			std::cout << "remove empty sprite, new size of sprites is [" << std::to_string(_e->entity_sprite_array->sprite_list.size()) << "]" << std::endl;
		}
	}
}