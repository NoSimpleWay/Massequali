#include "EWindowMain.h"
#include "ExternalButtonAction.h"

# define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

EButton::button_super_group*	EWindowMain::super_group_texture_collection_link;
EButton::button_group*			EWindowMain::group_texture_collection_link;

EButton::button_super_group*	EWindowMain::super_group_grid_region_link;

EButton::button_group*			EWindowMain::group_grid_region_link;
EButton::button_group*			EWindowMain::group_grid_region_second_layer_link;
EButton::button_group*			EWindowMain::group_grid_entity_list_link;

EButton*						EWindowMain::grid_region_button_link;

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

	Entity* en = new Entity();
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

	/// <summary>
	/// grid region
	/// </summary>
	super_group_grid_region_link = new EButton::button_super_group();
	button_group_list.push_back(super_group_grid_region_link);
	*super_group_grid_region_link->position_x = 800.0f;
	*super_group_grid_region_link->position_y = 50.0f;

	group_grid_entity_list_link = new EButton::button_group();
	*group_grid_entity_list_link->size_x = 120.0f;
	*group_grid_entity_list_link->size_y = 500.0f;


	
		super_group_grid_region_link->button_group_list.push_back(group_grid_entity_list_link);
		*group_grid_entity_list_link->selected_push_method = EButton::GroupPushMethod::GROUP_PUSH_METHOD_ADD_X;
		*group_grid_entity_list_link->can_be_moved_by_user = false;
		*group_grid_entity_list_link->can_be_stretched_x = false;
		*group_grid_entity_list_link->can_be_stretched_y = false;

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
				//but->gabarite = ETextureAtlas::put_texture_to_atlas("data/textures/hrusch_wall_main_002_v3.png", EWindow::default_texture_atlas);

			*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_Y;
			//group_grid_entity_list_link->button_list.push_back(but);
		}

	group_grid_region_link = new EButton::button_group();
	super_group_grid_region_link->button_group_list.push_back(group_grid_region_link);
	*group_grid_region_link->can_be_moved_by_user = false;
	*group_grid_region_link->selected_push_method = EButton::GroupPushMethod::GROUP_PUSH_METHOD_ADD_X;

				but = new EButton(0.0f, 0.0f, 20.0f, 20.0f);
				grid_region_button_link = but;
					but->master_window = this;
					but->master_super_group = super_group_grid_region_link;
					but->master_group = group_grid_region_link;
					
					group_grid_region_link->button_list.push_back(but);

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

	EGraphicCore::matrix_transform = glm::scale(EGraphicCore::matrix_transform, glm::vec3(EGraphicCore::correction_x, EGraphicCore::correction_y, 1.0f));

	transformLoc = glGetUniformLocation(EGraphicCore::ourShader->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));

	//סבנמס באעקונא
	EGraphicCore::batch->reset();
}

float EWindowMain::get_real_world_position_x_by_mouse(ECamera* _camera)
{
	return (mouse_x + *_camera->position_x) * *_camera->zoom - round(EGraphicCore::SCR_WIDTH / 2.0f);
}

float EWindowMain::get_real_world_position_y_by_mouse(ECamera* _camera)
{
	return (mouse_y + *_camera->position_y) * *_camera->zoom - round(EGraphicCore::SCR_HEIGHT / 2.0f);
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


