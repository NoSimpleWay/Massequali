#include "EWindowMain.h"
#include "ExternalButtonAction.h"

# define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

EButton::button_super_group*	EWindowMain::super_group_texture_collection_link;
EButton::button_group*			EWindowMain::group_texture_collection_link;

EButton::button_super_group*	EWindowMain::super_group_grid_region_link;

EButton::button_group*			EWindowMain::group_grid_region_edit_link;
EButton::button_group*			EWindowMain::group_grid_region_second_layer_link;
EButton::button_group*			EWindowMain::group_grid_entity_list_link;
EButton::button_group*			EWindowMain::group_grid_all_autobuilding_regions_link;

EButton::button_group*			EWindowMain::group_grid_autobuilding_group_texture_container;
EButton::button_group*			EWindowMain::group_grid_autobuilding_group_selector;
EButton::button_group*			EWindowMain::group_grid_autobuilding_draw_order;

EButton*						EWindowMain::grid_region_edit_button_link;

EButton*						EWindowMain::space_between_sprites_x_button;
EButton*						EWindowMain::space_between_sprites_y_button;

std::vector<EButton*>			EWindowMain::auto_size_region_button;

std::vector<Entity*>			EWindowMain::selected_entities;
EButton::EGridRegion*			EWindowMain::entity_selection_region;
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
			*just_created_button_group->button_list.at(j)->gabarite->size_x  * *just_created_button_group->button_list.at(j)->gabarite->size_y
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
	super_group_grid_region_link = new EButton::button_super_group();
	button_group_list.push_back(super_group_grid_region_link);
	*super_group_grid_region_link->position_x = 800.0f;
	*super_group_grid_region_link->position_y = 50.0f;

	group_grid_entity_list_link = new EButton::button_group();
	*group_grid_entity_list_link->size_x = 120.0f;
	*group_grid_entity_list_link->size_y = 165.0f;


	
		super_group_grid_region_link->button_group_list.push_back(group_grid_entity_list_link);
		*group_grid_entity_list_link->selected_push_method = EButton::GroupPushMethod::GROUP_PUSH_METHOD_ADD_X;
		*group_grid_entity_list_link->can_be_moved_by_user = false;
		*group_grid_entity_list_link->can_be_stretched_x = true;
		*group_grid_entity_list_link->can_be_stretched_y = true;

		for (int i = 0; i < 100; i++)
		{
			but = new EButton(0.0f, 0.0f, 100.0f, 20.0f);
			but->master_window = this;
			but->master_super_group = super_group_grid_region_link;
			but->master_group = group_grid_entity_list_link;
			but->have_rama = true;

			group_grid_entity_list_link->button_list.push_back(but);

			but->description_text = "Entity #" + std::to_string(i);
			but->text = "Entity";
			*but->can_be_selected = true;
			but->data_id = i;
			but->action_on_left_click.push_back(&ExternalButtonAction::external_button_action_import_data_from_entity_to_autobuilding_interface);
				//but->gabarite = ETextureAtlas::put_texture_to_atlas("data/textures/hrusch_wall_main_002_v3.png", EWindow::default_texture_atlas);

			*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_Y;
			//group_grid_entity_list_link->button_list.push_back(but);
		}

	group_grid_region_edit_link = new EButton::button_group();
	super_group_grid_region_link->button_group_list.push_back(group_grid_region_edit_link);
	*group_grid_region_edit_link->can_be_moved_by_user = false;

	*group_grid_region_edit_link->can_be_stretched_x = true;
	*group_grid_region_edit_link->can_be_stretched_y = true;

	*group_grid_region_edit_link->selected_push_method = EButton::GroupPushMethod::GROUP_PUSH_METHOD_ADD_X;

				but = new EButton(0.0f, 0.0f, 20.0f, 20.0f);
				grid_region_edit_button_link = but;
					but->master_window = this;
					but->master_super_group = super_group_grid_region_link;
					but->master_group = group_grid_region_edit_link;
					
					group_grid_region_edit_link->button_list.push_back(but);

					but->description_text = "Grid region (just for test)";
					but->gabarite = ETextureAtlas::put_texture_to_atlas("data/textures/hrusch_wall_main_002_v3.png", EWindow::default_texture_atlas);

					but->button_size_x = min(500.0f, max(10.0f, *but->gabarite->size_x*2.0f));
					but->button_size_y = min(500.0f, max(10.0f, *but->gabarite->size_y*2.0f));

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
		super_group_grid_region_link->button_group_list.push_back(group_grid_region_second_layer_link);
		*group_grid_region_second_layer_link->size_x = 300.0f;
		*group_grid_region_second_layer_link->size_y = 200.0f;
		*group_grid_region_second_layer_link->can_be_stretched_x = false;
		*group_grid_region_second_layer_link->can_be_stretched_y = false;
		*group_grid_region_second_layer_link->can_be_moved_by_user = false;

		but = new EButton(70.0f, 70.0f, 50.0f, 20.0f);
			but->master_window = this;
			but->master_super_group = super_group_grid_region_link;
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
			but->master_super_group = super_group_grid_region_link;
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
			but->master_super_group = super_group_grid_region_link;
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
			but->master_super_group = super_group_grid_region_link;
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
			but->master_super_group = super_group_grid_region_link;
			but->master_group = group_grid_region_second_layer_link;
			*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_FREE;
			group_grid_region_second_layer_link->button_list.push_back(but);
			but->text = "Auto";
			but->action_on_left_click.push_back(&ExternalButtonAction::external_button_action_set_grid_region_auto_size);
			//but->text = "0";

		but = new EButton(190.0f + 0.0f, 70.0f - 30.0f, 50.0f, 20.0f);
			space_between_sprites_x_button = but;
			but->master_window = this;
			but->master_super_group = super_group_grid_region_link;
			but->master_group = group_grid_region_second_layer_link;
			*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_FREE;
			group_grid_region_second_layer_link->button_list.push_back(but);
			but->text = "0";
			but->have_input_mode = true;
			but->action_on_left_click.push_back(&ExternalButtonAction::external_button_action_set_grid_region_auto_size);
				just_created_SFC = new EButton::SimpleFloatChanger();
				*just_created_SFC->float_changer_type = EButton::SimpleFloatChanger::SimpleFloatChangerType::SIMPLE_FLOAT_CHANGER_BUTTON_VALUE;
				*just_created_SFC->selected_activation_type = EButton::ButtonSimpleChangerActivationType::CHANGER_ACTIVATION_TYPE_INPUT;
				*just_created_SFC->selected_mathematic_type = EButton::ButtonSimpleChangerMathematic::BUTTON_SIMPLE_VALUE_MANIPULATOR_MATHEMATIC_SET_VALUE;
				but->simple_float_changer_list.push_back(just_created_SFC);

			but = new EButton(190.0f + 0.0f, 70.0f - 55.0f, 50.0f, 20.0f);
				space_between_sprites_y_button = but;
				but->master_window = this;
				but->master_super_group = super_group_grid_region_link;
				but->master_group = group_grid_region_second_layer_link;
				*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_FREE;
				group_grid_region_second_layer_link->button_list.push_back(but);
				but->text = "0";
				but->have_input_mode = true;
				but->action_on_left_click.push_back(&ExternalButtonAction::external_button_action_set_grid_region_auto_size);
					just_created_SFC = new EButton::SimpleFloatChanger();
					*just_created_SFC->float_changer_type = EButton::SimpleFloatChanger::SimpleFloatChangerType::SIMPLE_FLOAT_CHANGER_BUTTON_VALUE;
					*just_created_SFC->selected_activation_type = EButton::ButtonSimpleChangerActivationType::CHANGER_ACTIVATION_TYPE_INPUT;
					*just_created_SFC->selected_mathematic_type = EButton::ButtonSimpleChangerMathematic::BUTTON_SIMPLE_VALUE_MANIPULATOR_MATHEMATIC_SET_VALUE;
					but->simple_float_changer_list.push_back(just_created_SFC);

			//but->text = "0";

			group_grid_all_autobuilding_regions_link = new EButton::button_group();
				*group_grid_all_autobuilding_regions_link->selected_push_method = EButton::GroupPushMethod::GROUP_PUSH_METHOD_RESET_X_ADD_Y;
				super_group_grid_region_link->button_group_list.push_back(group_grid_all_autobuilding_regions_link);
				*group_grid_all_autobuilding_regions_link->size_x = 800.0f;
				*group_grid_all_autobuilding_regions_link->size_y = 120.0f;
				*group_grid_all_autobuilding_regions_link->can_be_stretched_x = false;
				*group_grid_all_autobuilding_regions_link->can_be_stretched_y = true;
				*group_grid_all_autobuilding_regions_link->can_be_moved_by_user = false;


			for (int i=0; i<10; i++)
			{
				but = new EButton(0.0f, 0.0f, 50.0f, 50.0f);
				but->master_window = this;
				but->master_super_group = super_group_grid_region_link;
				but->master_group = group_grid_all_autobuilding_regions_link;
				*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_X;
				group_grid_all_autobuilding_regions_link->button_list.push_back(but);

				but->is_active = true;
				but->data_id = i;
				*but->can_be_selected = true;
				but->have_rama = true;
				but->action_on_left_click.push_back(&ExternalButtonAction::external_button_action_select_texture_region_button);
				but->action_on_left_double_click.push_back(&ExternalButtonAction::external_button_action_open_select_texture_window_for_autobuilding_region);
				but->action_on_right_click.push_back(&ExternalButtonAction::external_button_action_remove_autobuilding_region);
				*but->is_double_click = true;
				//but->text = "Auto";
				//but->action_on_left_click.push_back(&ExternalButtonAction::external_button_action_set_grid_region_auto_size);
			}

			but = new EButton(0.0f, 0.0f, 200.0f, 20.0f);
				group_grid_all_autobuilding_regions_link->button_list.push_back(but);
				but->master_window = this;
				but->master_super_group = super_group_grid_region_link;
				but->master_group = group_grid_all_autobuilding_regions_link;
				*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_RESET_X_AND_ADD_Y;
				*but->can_be_selected = false;
				but->action_on_left_click.push_back(&ExternalButtonAction::external_button_action_add_new_autobuilding_region);
				but->text = "Add new autobuilding region";

			but = new EButton(0.0f, 0.0f, 200.0f, 20.0f);
				group_grid_all_autobuilding_regions_link->button_list.push_back(but);
				but->master_window = this;
				but->master_super_group = super_group_grid_region_link;
				but->master_group = group_grid_all_autobuilding_regions_link;
				*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_X;
				*but->can_be_selected = false;
				but->action_on_left_click.push_back(&ExternalButtonAction::external_button_action_add_selected_region_to_autobuilding_group);
				but->text = "Add selected region to group";


			group_grid_autobuilding_group_texture_container = new EButton::button_group();
				*group_grid_autobuilding_group_texture_container->selected_push_method = EButton::GroupPushMethod::GROUP_PUSH_METHOD_RESET_X_ADD_Y;
				super_group_grid_region_link->button_group_list.push_back(group_grid_autobuilding_group_texture_container);
				*group_grid_autobuilding_group_texture_container->size_x = 800.0f;
				*group_grid_autobuilding_group_texture_container->size_y = 120.0f;
				*group_grid_autobuilding_group_texture_container->can_be_stretched_x = false;
				*group_grid_autobuilding_group_texture_container->can_be_stretched_y = true;
				*group_grid_autobuilding_group_texture_container->can_be_moved_by_user = false;

				for (int i = 0; i < 10; i++)
				{
					but = new EButton(0.0f, 0.0f, 50.0f, 50.0f);
						but->master_window = this;
						but->master_super_group = super_group_grid_region_link;
						but->master_group = group_grid_autobuilding_group_texture_container;
						*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_X;
						group_grid_autobuilding_group_texture_container->button_list.push_back(but);

						but->is_active = true;
						but->data_id = i;
						*but->can_be_selected = true;
						but->have_rama = true;
						//but->action_on_left_click.push_back(&ExternalButtonAction::external_button_action_import_region_data_to_grid_region_editor);
						//but->action_on_left_double_click.push_back(&ExternalButtonAction::external_button_action_open_select_texture_window_for_autobuilding_region);
						but->action_on_right_click.push_back(&ExternalButtonAction::external_button_action_remove_autobuilding_group_element);
						*but->is_double_click = true;
					//but->text = "Auto";
					//but->action_on_left_click.push_back(&ExternalButtonAction::external_button_action_set_grid_region_auto_size);
				}

				group_grid_autobuilding_group_selector = new EButton::button_group();
					*group_grid_autobuilding_group_selector->selected_push_method = EButton::GroupPushMethod::GROUP_PUSH_METHOD_RESET_X_ADD_Y;
					super_group_grid_region_link->button_group_list.push_back(group_grid_autobuilding_group_selector);
					*group_grid_autobuilding_group_selector->size_x = 800.0f;
					*group_grid_autobuilding_group_selector->size_y = 120.0f;
					*group_grid_autobuilding_group_selector->can_be_stretched_x = false;
					*group_grid_autobuilding_group_selector->can_be_stretched_y = true;
					*group_grid_autobuilding_group_selector->can_be_moved_by_user = false;

					for (int i = 0; i < 10; i++)
					{
						but = new EButton(0.0f, 0.0f, 100.0f, 20.0f);
						group_grid_autobuilding_group_selector->button_list.push_back(but);
						but->master_window = this;
						but->master_super_group = super_group_grid_region_link;
						but->master_group = group_grid_autobuilding_group_selector;
						*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_X;
						*but->can_be_selected = false;
						but->have_rama = true;
						*but->can_be_selected = true;
						but->action_on_left_click.push_back(&ExternalButtonAction::external_button_action_select_autobuilding_group);
						but->text = "Group #" + std::to_string(i);
					}

				but = new EButton(0.0f, 0.0f, 200.0f, 20.0f);
					group_grid_autobuilding_group_selector->button_list.push_back(but);
					but->master_window = this;
					but->master_super_group = super_group_grid_region_link;
					but->master_group = group_grid_autobuilding_group_selector;
					*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_RESET_X_AND_ADD_Y;
					*but->can_be_selected = false;
					but->action_on_left_click.push_back(&ExternalButtonAction::external_button_action_add_new_group_for_autobuilding);
					but->text = "Add new group";
					
					
				group_grid_autobuilding_draw_order = new EButton::button_group();
					*group_grid_autobuilding_draw_order->selected_push_method = EButton::GroupPushMethod::GROUP_PUSH_METHOD_RESET_X_ADD_Y;
					super_group_grid_region_link->button_group_list.push_back(group_grid_autobuilding_draw_order);
					*group_grid_autobuilding_draw_order->size_x = 800.0f;
					*group_grid_autobuilding_draw_order->size_y = 120.0f;
					*group_grid_autobuilding_draw_order->can_be_stretched_x = false;
					*group_grid_autobuilding_draw_order->can_be_stretched_y = true;
					*group_grid_autobuilding_draw_order->can_be_moved_by_user = false;

				but = new EButton(0.0f, 0.0f, 200.0f, 20.0f);
					group_grid_autobuilding_draw_order->button_list.push_back(but);
					but->master_window = this;
					but->master_super_group = super_group_grid_region_link;
					but->master_group = group_grid_autobuilding_draw_order;
					*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_RESET_X_AND_ADD_Y;
					*but->can_be_selected = false;
					but->action_on_left_click.push_back(&ExternalButtonAction::external_button_action_add_new_group_for_autobuilding);
					but->text = "Add new order";

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
			((*_gr->size_x < 0) & (*_e->position_x <= * _gr->position_x))
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

	
	for (Entity* en : entity_list)
	{
		en->draw_entity(en, EGraphicCore::batch, _d);
	}

	EGraphicCore::batch->setcolor(EColor::COLOR_RED);
	EGraphicCore::batch->draw_gabarite(get_real_world_position_x_by_mouse(main_camera)-3.0f, get_real_world_position_y_by_mouse(main_camera)-3.0f, 6.0f, 6.0f, EGraphicCore::gabarite_white_pixel);

	if (is_entity_selection_started)
	{
		EGraphicCore::batch->draw_rama(*entity_selection_region->position_x, *entity_selection_region->position_y, *entity_selection_region->size_x, *entity_selection_region->size_y, 2.0f, EGraphicCore::gabarite_white_pixel);
	}
}

void EWindowMain::update(float _d)
{
	if (scroll > 0) { *main_camera->zoom *= 2.0f; }
	if (scroll < 0) { *main_camera->zoom /= 2.0f; }
	
	for (Entity* e : entity_list)
	for (Entity::AutobiuldingRegionGroup* a_group:e->autobuilding_region_group_list)
	for (Entity::AutobuildingRegionEntityElement* a_element:a_group->AB_entity_region_element_list)
	{
		if
		(
			(get_real_world_position_x_by_mouse(main_camera)	 >=	 *e->position_x + *a_group->offset_x + *a_element->offset_x - 3.0f)
			&
			(get_real_world_position_x_by_mouse(main_camera)	 <=	 *e->position_x + *a_group->offset_x + *a_element->offset_x + 3.0f)
			&
			(get_real_world_position_y_by_mouse(main_camera)	 >=	 *e->position_y + *a_group->offset_y + *a_element->offset_y - 3.0f)
			&
			(get_real_world_position_y_by_mouse(main_camera)	 <=	 *e->position_y + *a_group->offset_y + *a_element->offset_y + *a_element->size_y + 3.0f)
		)
		{if (!LMB) { *a_element->catched_left_side = true; }}
		else
		{if (!LMB) { *a_element->catched_left_side = false; }}

		if
		(
			(get_real_world_position_x_by_mouse(main_camera)	 >=	 *e->position_x + *a_group->offset_x + *a_element->offset_x + *a_element->size_x - 3.0f)
			&
			(get_real_world_position_x_by_mouse(main_camera)	 <=	 *e->position_x + *a_group->offset_x + *a_element->offset_x + *a_element->size_x + 3.0f)
			&
			(get_real_world_position_y_by_mouse(main_camera)	 >=	 *e->position_y + *a_group->offset_y + *a_element->offset_y - 3.0f)
			&
			(get_real_world_position_y_by_mouse(main_camera)	 <=	 *e->position_y + *a_group->offset_y + *a_element->offset_y + *a_element->size_y + 3.0f)
		)
		{if (!LMB) { *a_element->catched_right_side = true; }}
		else
		{if (!LMB) { *a_element->catched_right_side = false; }}

		if
		(
			(get_real_world_position_x_by_mouse(main_camera)	 >=	 *e->position_x + *a_group->offset_x + *a_element->offset_x - 3.0f)
			&
			(get_real_world_position_x_by_mouse(main_camera)	 <=	 *e->position_x + *a_group->offset_x + *a_element->offset_x + *a_element->size_x + 3.0f)
			&
			(get_real_world_position_y_by_mouse(main_camera)	 >=	 *e->position_y + *a_group->offset_y + *a_element->offset_y - 3.0f)
			&
			(get_real_world_position_y_by_mouse(main_camera)	 <=	 *e->position_y + *a_group->offset_y + *a_element->offset_y + 3.0f)
		)
		{if (!LMB) { *a_element->catched_down_side = true; }}
		else
		{if (!LMB) { *a_element->catched_down_side = false; }}

		if
		(
			(get_real_world_position_x_by_mouse(main_camera)	 >=	 *e->position_x + *a_group->offset_x + *a_element->offset_x - 3.0f)
			&
			(get_real_world_position_x_by_mouse(main_camera)	 <=	 *e->position_x + *a_group->offset_x + *a_element->offset_x + *a_element->size_x + 3.0f)
			&
			(get_real_world_position_y_by_mouse(main_camera)	 >=	 *e->position_y + *a_group->offset_y + *a_element->offset_y + *a_element->size_y - 3.0f)
			&
			(get_real_world_position_y_by_mouse(main_camera)	 <=	 *e->position_y + *a_group->offset_y + *a_element->offset_y + *a_element->size_y + 3.0f)
		)
		{if (!LMB) { *a_element->catched_up_side = true; }}
		else
		{if (!LMB) { *a_element->catched_up_side = false; }}

		if
		(
			(get_real_world_position_x_by_mouse(main_camera)	 >=	 *e->position_x + *a_group->offset_x + *a_element->offset_x + *a_element->size_x / 2.0f - 10.0f)
			&
			(get_real_world_position_x_by_mouse(main_camera)	 <=	 *e->position_x + *a_group->offset_x + *a_element->offset_x + *a_element->size_x / 2.0f + 10.0f)
			&
			(get_real_world_position_y_by_mouse(main_camera)	 >=	 *e->position_y + *a_group->offset_y + *a_element->offset_y + *a_element->size_y / 2.0f - 10.0f)
			&
			(get_real_world_position_y_by_mouse(main_camera)	 <=	 *e->position_y + *a_group->offset_y + *a_element->offset_y + *a_element->size_y / 2.0f + 10.0f)
		)
		{if (!LMB) { *a_element->catched_mid = true; }}
		else
		{if (!LMB) { *a_element->catched_mid = false; }}

		if (LMB)
		{
			if (*a_element->catched_left_side)
			{
				*a_element->size_x		-= mouse_speed_x / *main_camera->zoom;
				*a_element->offset_x	+= mouse_speed_x / *main_camera->zoom;

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
		*entity_selection_region->size_x		= 0.0f;
		*entity_selection_region->size_y		= 0.0f;

		*entity_selection_region->position_x	= 0.0f;
		*entity_selection_region->position_y	= 0.0f;

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

	if ((glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_ALT) != GLFW_PRESS))
	{
		EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3(-1.0f - EGraphicCore::correction_x / 2.0f + round(EGraphicCore::SCR_WIDTH / 2.0f - *main_camera->position_x) * EGraphicCore::correction_x, -1.0f - EGraphicCore::correction_y / 2.0f + round(EGraphicCore::SCR_HEIGHT / 2.0f - *main_camera->position_y) * EGraphicCore::correction_y, 0.0f));
	}
	else
	{
		EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3(-1.0f - *main_camera->position_x, -1.0f - *main_camera->position_y, -1.0f));
	}

	EGraphicCore::matrix_transform = glm::scale(EGraphicCore::matrix_transform, glm::vec3(EGraphicCore::correction_x * *main_camera->zoom, EGraphicCore::correction_y * *main_camera->zoom, 1.0f));

	transformLoc = glGetUniformLocation(EGraphicCore::ourShader->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));

	//סבנמס באעקונא
	EGraphicCore::batch->reset();
}

float EWindowMain::get_real_world_position_x_by_mouse(ECamera* _camera)
{
	return (mouse_x + *_camera->position_x - round(EGraphicCore::SCR_WIDTH / 2.0f)) / *_camera->zoom ;
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
		{group_grid_entity_list_link->button_list.at(i)->is_active = false;}
	}
}

void EWindowMain::import_data_from_entity_to_autobuilding_interface(Entity* _e)
{
	Entity::AutobuildingRegionTexture* just_created_autobuilding_region;
	EButton::EGridRegion* just_created_grid_region;

	if (_e->autobuilding_region_list.empty())
	{
		just_created_autobuilding_region = new Entity::AutobuildingRegionTexture();
		_e->autobuilding_region_list.push_back(just_created_autobuilding_region);

		EWindowMain::grid_region_edit_button_link->grid_region_list.clear();

		/*
		for (int i = 0; i < 9; i++)
		{
			just_created_grid_region = new EButton::EGridRegion();

			just_created_autobuilding_region->texture_region_list.push_back(just_created_grid_region);
			EWindowMain::grid_region_button_link->grid_region_list.push_back(just_created_grid_region);
		}*/

		just_created_autobuilding_region->main_texture = ETextureAtlas::put_texture_to_atlas("data/textures/hrusch_wall_main_002_v1.png", EWindow::default_texture_atlas);
	}

	EWindowMain::grid_region_edit_button_link->grid_region_list.clear();
	for (int i = 0; i < _e->autobuilding_region_list.at(0)->texture_region_list.size(); i++)
	{
		EWindowMain::grid_region_edit_button_link->grid_region_list.push_back(_e->autobuilding_region_list.at(0)->texture_region_list.at(i));
	}

	EWindowMain::grid_region_edit_button_link->gabarite = _e->autobuilding_region_list.at(0)->main_texture;
	//if (_e->)
}

void EWindowMain::generate_building(Entity* _e)
{
	EGraphicCore::ESprite* selected_sprite = NULL;
	int selected_sprite_id = 0;

	for (int i = 0; i < (100 - _e->entity_sprite_array->sprite_list.size()); i++)
	{
		EGraphicCore::ESprite* just_created_sprite = new EGraphicCore::ESprite();
		_e->entity_sprite_array->sprite_list.push_back(just_created_sprite);
	}

	for (EGraphicCore::ESprite* spr : _e->entity_sprite_array->sprite_list)
	{
		EGraphicCore::reset_sprite_data(spr);
	}

	selected_sprite = _e->entity_sprite_array->sprite_list.at(0);

	float mid_wall_copies_x = 0.0f;
	float mid_wall_copies_y = 0.0f;

	float wall_full_size_x = 0.0f;
	float wall_full_size_y = 0.0f;

	float wall_fragment_x = 0.0f;
	float wall_fragment_y = 0.0f;

	if (selected_sprite_id < _e->entity_sprite_array->sprite_list.size())
	for (Entity::AutobiuldingRegionGroup* a_group : _e->autobuilding_region_group_list)
	{
		for (Entity::AutobuildingRegionEntityElement* a_element : a_group->AB_entity_region_element_list)
		{
			

			

			wall_full_size_x
			=
			(*a_element->autobuilding_texture_region->main_texture->size_x)
			-
			*a_element->autobuilding_texture_region->texture_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT)->size_x
			-
			*a_element->autobuilding_texture_region->texture_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT)->size_x;

			wall_full_size_y
				=
				(*a_element->autobuilding_texture_region->main_texture->size_y)
				-
				*a_element->autobuilding_texture_region->texture_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_UP)->size_y
				-
				*a_element->autobuilding_texture_region->texture_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_DOWN)->size_y;

			mid_wall_copies_x
			=
			(
				*a_element->size_x
				-
				*a_element->autobuilding_texture_region->texture_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT)->size_x
				-
				*a_element->autobuilding_texture_region->texture_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT)->size_x
			) / (wall_full_size_x + *a_element->autobuilding_texture_region->space_between_sprite_x);

			mid_wall_copies_y
			=
			(
				*a_element->size_y
				-
				*a_element->autobuilding_texture_region->texture_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_UP)->size_y
				-
				*a_element->autobuilding_texture_region->texture_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_DOWN)->size_y
			)
			/ (wall_full_size_y + *a_element->autobuilding_texture_region->space_between_sprite_y);


			//std::cout << "Copies x [" << std::to_string(mid_wall_copies_x) << "]" << std::endl;
			//std::cout << "Copies y [" << std::to_string(mid_wall_copies_y) << "]" << std::endl;

			for (int yy = 0; yy < ceil(mid_wall_copies_y); yy++)
			for (int xx = 0; xx < ceil(mid_wall_copies_x); xx++)
			{
				wall_fragment_x = min(1.0f, mid_wall_copies_x + 0.0f - xx);
				wall_fragment_y = min(1.0f, mid_wall_copies_y + 0.0f - yy);

				selected_sprite = _e->entity_sprite_array->sprite_list.at(selected_sprite_id);

				*selected_sprite->offset_x
				=
				*a_element->autobuilding_texture_region->texture_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT)
				->size_x;
				
				*selected_sprite->offset_x += xx * (wall_full_size_x + *a_element->autobuilding_texture_region->space_between_sprite_x) + *a_group->offset_x + *a_element->offset_x;


				*selected_sprite->offset_y
				=
				*a_element->autobuilding_texture_region->texture_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_DOWN)
				->size_y;

				*selected_sprite->offset_y += yy * (wall_full_size_y + *a_element->autobuilding_texture_region->space_between_sprite_y) + *a_group->offset_y + *a_element->offset_y;

				*selected_sprite->fragment_left
				=
				*a_element->autobuilding_texture_region->texture_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT)
				->size_x / 4096.0f;

				*selected_sprite->fragment_right
				=
				(*a_element->autobuilding_texture_region->texture_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT)
				->size_x + (1.0f - wall_fragment_x) * wall_full_size_x) / 4096.0f;

				*selected_sprite->fragment_down
				=
				(*a_element->autobuilding_texture_region->texture_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_DOWN)
				->size_y) / 4096.0f;

				*selected_sprite->fragment_up
				=
				(*a_element->autobuilding_texture_region->texture_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_UP)
				->size_y + (1.0f - wall_fragment_y) * wall_full_size_y) / 4096.0f;

				*selected_sprite->size_x = wall_full_size_x * wall_fragment_x;
				*selected_sprite->size_y = wall_full_size_y * wall_fragment_y;

				selected_sprite->texture_gabarite = a_element->autobuilding_texture_region->main_texture;

				selected_sprite_id++;
			}

			//a_element->autobuilding_texture_region->texture_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT_UP_CORNER);
		}
	}

}


