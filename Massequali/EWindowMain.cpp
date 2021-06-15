#include "EWindowMain.h"

# define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

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

	*en->position_x = 0.0f;
	*en->position_y = 0.0f;
	*en->position_z = 0.0f;

	EGraphicCore::sprite_array* just_created_sprite_array = new EGraphicCore::sprite_array();
	en->entity_sprite_array = just_created_sprite_array;
	EGraphicCore::ESprite* just_created_sprite = new EGraphicCore::ESprite();
	just_created_sprite_array->sprite_list.push_back(just_created_sprite);
	just_created_sprite->texture_gabarite = ETextureAtlas::put_texture_to_atlas("data/textures/human.png", EWindow::default_texture_atlas);
	*just_created_sprite->offset_x = -round(*just_created_sprite->texture_gabarite->size_x / 2.0f);


	just_created_button_super_group = new EButton::button_super_group();
	button_group_list.push_back(just_created_button_super_group);
	*just_created_button_super_group->position_x = 800.0f;
	*just_created_button_super_group->position_y = 50.0f;

	just_created_button_group = new EButton::button_group();
	just_created_button_super_group->button_group_list.push_back(just_created_button_group);

				but = new EButton(0.0f, 0.0f, 20.0f, 20.0f);
					but->master_window = this;
					but->master_super_group = just_created_button_super_group;
					but->master_group = just_created_button_group;
					
					just_created_button_group->button_list.push_back(but);

					but->description_text = "Grid region (just for test)";
					but->gabarite = ETextureAtlas::put_texture_to_atlas("data/textures/hrusch_wall_main_002_v3.png", EWindow::default_texture_atlas);

					but->button_size_x = min(500.0f, max(10.0f, *but->gabarite->size_x*2.0f));
					but->button_size_y = min(500.0f, max(10.0f, *but->gabarite->size_y*2.0f));

					but->have_icon = true;
					but->have_bg = false;

					*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_X;

					EButton::EGridRegion*
					just_created_grid = new EButton::EGridRegion();
					*just_created_grid->size_x = 5.0f;
					*just_created_grid->size_y = *but->gabarite->size_y;
					but->grid_region_list.push_back(just_created_grid);

	

}

EWindowMain::~EWindowMain()
{
}

void EWindowMain::draw(float _d)
{
	reset_render();

	for (Entity* en : entity_list)
	{
		if (en->entity_sprite_array != NULL)
		{
			EGraphicCore::draw_sprite_regular(en->entity_sprite_array, EGraphicCore::batch, *en->position_x, *en->position_y, *en->position_z);
		}
	}
}

void EWindowMain::update(float _d)
{
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


