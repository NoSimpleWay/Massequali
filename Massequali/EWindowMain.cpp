#pragma once
#include "EWindowMain.h"
#include "ExternalButtonAction.h"

# define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
#include <direct.h>

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
//#define INCLUDE_STB_IMAGE_WRITE_H
#include "stb_image_write.h"


namespace fs = std::experimental::filesystem;

EButton::button_super_group*			EWindowMain::super_group_texture_collection_link;
EButton::button_group*					EWindowMain::group_texture_collection_link;

EButton::button_super_group*			EWindowMain::super_group_autobuilding;

EButton::button_group*					EWindowMain::group_grid_region_edit_link;
EButton::button_group*					EWindowMain::group_grid_region_second_layer_link;
EButton::button_group*					EWindowMain::group_grid_entity_list_link;
EButton::button_group*					EWindowMain::button_group_autobuilding_base;

EButton::button_group*					EWindowMain::button_group_autobuilding_group_element;
EButton::button_group*					EWindowMain::button_group_autobuilding_group;
EButton::button_group*					EWindowMain::group_grid_autobuilding_draw_order;

EButton::button_super_group*			EWindowMain::super_group_vertex_editor;
EButton::button_group*					EWindowMain::group_vertex_editor;
EButton::button_group*					EWindowMain::group_vertex_normal_color_editor;
EButton*								EWindowMain::link_to_button_vertex_editor;
EButton*								EWindowMain::link_to_button_two_dimension_gradient;

EButton* EWindowMain::grid_region_edit_button_link;

EButton* EWindowMain::space_between_sprites_x_button;
EButton* EWindowMain::space_between_sprites_y_button;

EButton* EWindowMain::link_button_subdivision_mid_x;
EButton* EWindowMain::link_button_subdivision_mid_y;

EButton* EWindowMain::link_button_sprite_push_direction;

std::vector<EButton*>			EWindowMain::auto_size_region_button;

std::vector<Entity*>			EWindowMain::selected_entities;
EButton::EGridRegion*			EWindowMain::entity_selection_region;

ECamera*						EWindowMain::main_camera = new ECamera();

//std::vector<Entity*>			EWindowMain::entity_list;
bool							EWindowMain::is_entity_selection_started = false;

ECluster*						EWindowMain::cluster_static		[ECluster::CLUSTED_DIM_X][ECluster::CLUSTED_DIM_Y];
ECluster*						EWindowMain::cluster_non_static	[ECluster::CLUSTED_DIM_X][ECluster::CLUSTED_DIM_Y];

std::string						EWindowMain::w_string;

int								EWindowMain::cluster_draw_start_x;
int								EWindowMain::cluster_draw_start_y;
int								EWindowMain::cluster_draw_end_x;
int								EWindowMain::cluster_draw_end_y;

std::vector<Entity*>							EWindowMain::draw_buffer(1001);
std::vector<Entity::AutobuildingGroup*>			EWindowMain::draw_group_buffer(1001);

int								EWindowMain::last_index;
EWindowMain::EWindowMain()
{
	create_button_groups();

	entity_selection_region = new EButton::EGridRegion();

	for (int i = 0; i < ECluster::CLUSTED_DIM_X; i++)
	for (int j = 0; j < ECluster::CLUSTED_DIM_X; j++)
	{
		cluster_static		[j][i] = new ECluster();
		cluster_non_static	[j][i] = new ECluster();
	}
}

void saveImage(char* filepath, GLFWwindow* w)
{
	ETextureAtlas::draw_to_this_FBO(EWindow::supermap_FBO, EWindow::default_texture_atlas);
	//glReadBuffer(GL_READ_FRAMEBUFFER);

	EGraphicCore::ourShader->use();
	EGraphicCore::matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

	EGraphicCore::batch->reinit();
	EGraphicCore::batch->draw_call();

	EGraphicCore::ourShader->use();
	EGraphicCore::matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

	EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3(-1.0f, -1.0f, 0.0f)); 
	EGraphicCore::matrix_transform = glm::scale(EGraphicCore::matrix_transform, glm::vec3(1.0f/256.0f, 1.0f/256.0f, 1.0f));

	unsigned int transformLoc;
	transformLoc = glGetUniformLocation(EGraphicCore::ourShader->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));

	//סבנמס באעקונא
	EGraphicCore::batch->reset();

	EGraphicCore::batch->setcolor(EColor::COLOR_WHITE);
	EGraphicCore::batch->draw_normalmap_polygon
	(
		EWindowMain::link_to_button_vertex_editor->polygon_massive,
		0.0f,
		0.0f,
		512.0f,
		512.0f,
		EGraphicCore::gabarite_white_pixel
	);

	
	EGraphicCore::batch->reinit();
	EGraphicCore::batch->draw_call();
	EGraphicCore::batch->reset();
	
	
	int width = 512, height = 512;
	//glfwGetFramebufferSize(w, &width, &height);

	//width = 100;
	//height = 100;

	GLsizei nrChannels = 4;
	GLsizei stride = nrChannels * width;
	stride += (stride % 4) ? (4 - stride % 4) : 0;
	GLsizei bufferSize = stride * height;

	std::vector<byte> buffer(bufferSize);


	glPixelStorei(GL_PACK_ALIGNMENT, 4);
	glReadBuffer(GL_FRONT);
	glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer.data());

	std::cout << "buffer.size =" << std::to_string(buffer.size()) << std::endl;

	//for (int i = 0; i < 100; i++)
	//{
	//	std::cout << "[" << std::to_string(i) << "]" << (int)buffer.at(i) << std::endl;
	//}

	//for (int i = 0; i < buffer.size(); i++ )
	//{
	//	buffer.at(i) = rand() % 256;
	//}

	stbi_flip_vertically_on_write(true);
	stbi_write_png(filepath, width, height, nrChannels, buffer.data(), stride);

	ofstream writer;

	writer.open("huita.txt");

		for (int i = 0; i < buffer.size(); i++)
		{
			//writer << '(' << buffer.at(i) << ')';
			writer << (char)(buffer.at(i) >> 8);
			//writer << '-';
			writer << (char)(buffer.at(i) & 0x00FF);
			//writer << '=';
		}
	writer.close();
	ETextureAtlas::set_this_FBO_as_active(EWindow::default_texture_atlas);
	
}

void EWindowMain::create_button_groups()
{
	//"search brick group" texture
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	EButton::button_super_group* just_created_button_super_group = new EButton::button_super_group(this);
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

	std::vector<std::string> v_description;
	std::vector<EGabarite*> v_gabarite;

	EButton* but = NULL;

	for (auto& p : fs::directory_iterator("data/textures"))
	{
		v_description.push_back("" + p.path().filename().u8string().substr(0, p.path().filename().u8string().length() - 4));
		v_gabarite.push_back(ETextureAtlas::put_texture_to_atlas(p.path().u8string(), EWindow::default_texture_atlas));
	}



	EButton* swap_button = NULL;

	for (int i = 0; i < v_gabarite.size(); i++)
	for (int j = i; j < v_gabarite.size(); j++)
			if
				(
					(i != j)
					&
					(
						sqrt(*v_gabarite.at(j)->size_x * *v_gabarite.at(j)->size_y)
						<
						sqrt(*v_gabarite.at(i)->size_x * *v_gabarite.at(i)->size_y)
						)
					)
			{

				swap(v_description.at(i), v_description.at(j));
				swap(v_gabarite.at(i), v_gabarite.at(j));
			}

	for (int i = 0; i < v_gabarite.size(); i++)
	{
		{
			but = new EButton(0.0f, 0.0f, 20.0f, 20.0f);
			but->master_window = this;
			but->master_super_group = just_created_button_super_group;
			but->master_group = just_created_button_group;

			just_created_button_group->button_list.push_back(but);

			but->description_text = "" + v_description.at(i);
			but->gabarite = v_gabarite.at(i);

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
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/*Entity*
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
	*just_created_sprite->size_y = *just_created_sprite->texture_gabarite->size_y;*/
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// grid region
	super_group_autobuilding = new EButton::button_super_group(this);
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

	//////////////////////////////////////
	//////////////////////////////////////
	//////////////////////////////////////
	//////////////////////////////////////
	but = new EButton(190.0f + 0.0f, 70.0f - 0.0f, 110.0f, 20.0f, this, super_group_autobuilding, group_grid_region_second_layer_link);
	link_button_sprite_push_direction = but;
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_FREE;
	group_grid_region_second_layer_link->button_list.push_back(but);
	//but->text = "PUSH Y";

	but->drop_text.push_back("ROOF (PUSH Y)");
	but->drop_text.push_back("WALL (PUSH Z)");
	but->drop_elements = 2;
	*but->is_consumable = true;
	but->text = but->drop_text.at(0);

	but->is_drop_list = true;
	but->action_on_drop_list_select_element.push_back(&ExternalButtonAction::external_button_action_set_button_value);
	but->target_address_for_int = NULL;

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

		but->action_on_left_double_click.push_back(&ExternalButtonAction::external_button_action_set_button_constant_value);
		*but->target_value_for_bool = true;
		but->target_address_for_bool = &but->is_input_mode_active;
		*but->is_double_click = true;

		but->action_on_input.push_back(&ExternalButtonAction::external_button_action_set_button_value);
		but->target_address_for_string = NULL;
		
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
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/////////////menu save|load|other
	just_created_button_super_group = new EButton::button_super_group(this);
	button_group_list.push_back(just_created_button_super_group);

	*just_created_button_super_group->size_x = 300.0f;
	*just_created_button_super_group->size_y = 30.0f;
	//button_group_list.push_back(just_created_button_super_group);

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

	but = new EButton(0.0f, 0.0f, 70.0f, 15.0f, this, just_created_button_super_group, just_created_button_group);
		just_created_button_group->button_list.push_back(but);
		*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_X;
		but->action_on_left_click.push_back(&ExternalButtonAction::external_button_action_create_new_entity);
		but->text = "New Entity";


	/////////////vertex editor
		super_group_vertex_editor = new EButton::button_super_group(this);
			button_group_list.push_back(super_group_vertex_editor);
			*super_group_vertex_editor->size_x = 500.0f;
			*super_group_vertex_editor->size_y = 300.0f;


			group_vertex_editor = new EButton::button_group();
				super_group_vertex_editor->button_group_list.push_back(group_vertex_editor);
				*group_vertex_editor->position_x = 0.0f;
				*group_vertex_editor->position_y = 0.0f;
				*group_vertex_editor->size_x = 520.0f;
				*group_vertex_editor->size_y = 320.0f;
				*group_vertex_editor->can_be_stretched_x = false;
				*group_vertex_editor->can_be_stretched_y = false;
				*group_vertex_editor->can_be_moved_by_user = false;

				but = new EButton(5.0f, 5.0f, 300.0f, 300.0f, this, super_group_vertex_editor, group_vertex_editor);
					link_to_button_vertex_editor = but;
					but->mode_list.push_back(new int(PolygonDrawMode::POLYGON_DRAW_MODE_NORMAL_MAP));
					but->have_bg = false;
					*but->is_double_click = true;
					but->action_on_left_double_click.push_back(ExternalButtonAction::external_button_action_open_select_texture_window_for_vertex_editor);

					Batcher::EPolygonMassive* just_created_polygon_massive = new Batcher::EPolygonMassive();
					but->polygon_massive = just_created_polygon_massive;

					Batcher::EPolygonShape* just_created_polygon_shape = new Batcher::EPolygonShape();
					just_created_polygon_massive->shape_list.push_back(just_created_polygon_shape);

					//.#
					//..
					Batcher::EPolygonVertex*
						just_created_polygon_vertex = new Batcher::EPolygonVertex();
						*just_created_polygon_vertex->position_x = 1.0f;
						*just_created_polygon_vertex->position_y = 1.0f;
						just_created_polygon_vertex->float_vector.push_back(new float(0.5f));
						just_created_polygon_vertex->float_vector.push_back(new float(0.5f));
						just_created_polygon_shape->vertex_list.push_back(just_created_polygon_vertex);
					//..
					//.#
						just_created_polygon_vertex = new Batcher::EPolygonVertex();
						*just_created_polygon_vertex->position_x = 1.0f;
						*just_created_polygon_vertex->position_y = 0.0f;
						just_created_polygon_vertex->float_vector.push_back(new float(0.5f));
						just_created_polygon_vertex->float_vector.push_back(new float(0.5f));
						just_created_polygon_shape->vertex_list.push_back(just_created_polygon_vertex);
					//..
					//#.
						just_created_polygon_vertex = new Batcher::EPolygonVertex();
						*just_created_polygon_vertex->position_x = 0.0f;
						*just_created_polygon_vertex->position_y = 0.0f;
						just_created_polygon_vertex->float_vector.push_back(new float(0.5f));
						just_created_polygon_vertex->float_vector.push_back(new float(0.5f));
						just_created_polygon_shape->vertex_list.push_back(just_created_polygon_vertex);
					//#.
					//..
						just_created_polygon_vertex = new Batcher::EPolygonVertex();
						*just_created_polygon_vertex->position_x = 0.0f;
						*just_created_polygon_vertex->position_y = 1.0f;
						just_created_polygon_vertex->float_vector.push_back(new float(0.5f));
						just_created_polygon_vertex->float_vector.push_back(new float(0.5f));
						just_created_polygon_shape->vertex_list.push_back(just_created_polygon_vertex);



					group_vertex_editor->button_list.push_back(but);
					*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_X;


					but = new EButton(5.0f, 5.0f, 100.0f, 100.0f, this, super_group_vertex_editor, group_vertex_editor);
					link_to_button_two_dimension_gradient = but;
					//but->mode_list.push_back(new int(PolygonDrawMode::POLYGON_DRAW_MODE_NORMAL_MAP));
					but->have_bg = false;
					*but->is_double_click = true;
					*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_X;
					group_vertex_editor->button_list.push_back(but);
						EButton::ETwoDimensionGradient* just_created_td_gradient = new EButton::ETwoDimensionGradient();
						*just_created_td_gradient->value_x = 0.5f;
						*just_created_td_gradient->value_y = 0.5f;
						but->two_dimension_gradient = just_created_td_gradient;
						just_created_td_gradient->color_x->set_color(EColor::COLOR_RED);
						just_created_td_gradient->color_y->set_color(EColor::COLOR_BLUE);
						but->action_on_td_gradient_drag.push_back(&ExternalButtonAction::external_button_action_change_normal_color_for_vertex);

			group_vertex_normal_color_editor = new EButton::button_group();
						super_group_vertex_editor->button_group_list.push_back(group_vertex_normal_color_editor);
						*group_vertex_normal_color_editor->position_x = 0.0f;
						*group_vertex_normal_color_editor->position_y = 0.0f;
						*group_vertex_normal_color_editor->size_x = 520.0f;
						*group_vertex_normal_color_editor->size_y = 320.0f;
						*group_vertex_normal_color_editor->can_be_stretched_x = true;
						*group_vertex_normal_color_editor->can_be_stretched_y = true;
						*group_vertex_normal_color_editor->can_be_moved_by_user = false;

						for (int i = 0; i < 4; i++)
						{
							but = new EButton(0.0f, 0.0f, 20.0f, 20.0f, this, super_group_vertex_editor, group_vertex_normal_color_editor);
							but->text = std::to_string(i);
							*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_X;
							group_vertex_normal_color_editor->button_list.push_back(but);
						}




	//world setting
	just_created_button_super_group = new EButton::button_super_group(this);
	button_group_list.push_back(just_created_button_super_group);
	*just_created_button_super_group->position_x = 500.0f;
	*just_created_button_super_group->position_y = 300.0f;

	//group_texture_variants
	just_created_button_group = new EButton::button_group();
	just_created_button_super_group->button_group_list.push_back(just_created_button_group);

	*just_created_button_group->can_be_stretched_x = false;
	*just_created_button_group->can_be_stretched_y = false;

	*just_created_button_group->size_x = 532.0f;
	*just_created_button_group->size_y = 325.0f;
	*just_created_button_group->can_be_moved_by_user = false;

	but = new EButton(0.0f, 300.0f, 200.0f, 20.0f, this, just_created_button_super_group, just_created_button_group);
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_FREE;
	just_created_button_group->button_list.push_back(but);
	but->is_drop_list = true;
	but->action_on_drop_list_select_element.push_back(&ExternalButtonAction::external_button_action_set_button_value);
	but->target_address_for_int = &EGraphicCore::selected_blur_level;
	but->drop_text.push_back("ORIGINAL     [level 0]");
	but->drop_text.push_back("BLUR 2*2     [level 1]");
	but->drop_text.push_back("BLUR 4*4     [level 2]");
	but->drop_text.push_back("BLUR 8*8     [level 3]");
	but->drop_text.push_back("BLUR 16*16   [level 4]");
	but->drop_text.push_back("BLUR 32*32   [level 5]");
	but->drop_text.push_back("BLUR 64*654  [level 6]");
	but->drop_text.push_back("BLUR 128*128 [level 7]");
	but->drop_elements = 8;
	but->text = but->drop_text.at(0);
	*but->is_consumable = false;

	//*just_created_button_super_group->position_x = 500.0f;
	but = new EButton(0.0f, 0.0f, 200.0f, 100.0f, this, just_created_button_super_group, just_created_button_group);
	but->have_icon = true;
	but->gabarite = ETextureAtlas::put_texture_to_atlas("data/textures/button_texture_sun_position.png", EWindow::default_texture_atlas);
	just_created_td_gradient = new EButton::ETwoDimensionGradient();
	*just_created_td_gradient->draw_gradient = false;
	but->action_on_td_gradient_drag.push_back(&ExternalButtonAction::external_button_action_change_sun_position);

	but->two_dimension_gradient = just_created_td_gradient;
	just_created_button_group->button_list.push_back(but);
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_Y;






	

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
	EWindow::add_time_process("Start draw");
	reset_render();

	//EGraphicCore::batch->setcolor(EColor::COLOR_GRAY);
	//EGraphicCore::batch->draw_gabarite(0.0f, 0.0f, 2000.0f, 2000.0f, EGraphicCore::gabarite_white_pixel);
	//EWindow::add_time_process("Draw alt info on ground");
	EWindow::add_time_process("Reset render");

	if (glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
	for (int i = cluster_draw_start_y; i <= cluster_draw_end_y; i++)
	for (int j = cluster_draw_start_x; j <= cluster_draw_end_x; j++)
	{
		EGraphicCore::batch->setcolor(EColor::COLOR_GRAY);
		EGraphicCore::batch->draw_rama(j * ECluster::CLUSTER_SIZE_X, i * ECluster::CLUSTER_SIZE_Y, ECluster::CLUSTER_SIZE_X, ECluster::CLUSTER_SIZE_Y, 1.0f / *main_camera->zoom, EGraphicCore::gabarite_white_pixel);


		EFont::active_font->draw(EGraphicCore::batch, std::to_string(cluster_static[j][i]->entity_list.size()), j * ECluster::CLUSTER_SIZE_X + 10.0f, i * ECluster::CLUSTER_SIZE_Y + 10.0f);
			
	}
	EWindow::add_time_process("Draw rama");


Entity* swap_entity = NULL;
//std::cout << "static[0][0] size is " << std::to_string(cluster_static[0][0]->entity_list.size()) << std::endl;
//std::cout << "non-static[0][0] size is " << std::to_string(cluster_non_static[0][0]->entity_list.size()) << std::endl;
last_index = 0;

	bool is_y_sort = false;
	//draw_buffer.clear();

	float t_z = 100.0f;
	
	last_index = 0;

	//std::cout << "----------------" << std::endl;

for (int i = cluster_draw_end_y; i >= cluster_draw_start_y; i--)
for (int j = cluster_draw_start_x; j <= cluster_draw_end_x; j++)
	{
		for (Entity* e : cluster_static[j][i]->entity_list)
		{
			for (Entity::AutobuildingGroup* a_group : e->autobuilding_group_list)
			//if (*a_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_WALL_Z)
			{
				draw_group_buffer.at(last_index) = a_group;

				/*
				if (glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
				{
					std::cout
					<<
					"push wall ["
					<<
					*a_group->name
					<<
					"]   last_index ["
					<<
					std::to_string(last_index)
					<<
					"]"
					<<
					std::endl;
				}*/


				last_index++;
			}

			
		}
	}

EWindow::add_time_process("fill draw buffer");

	bool need_sort = true;
	//std::cout << "---" << std::endl;

	
	while (need_sort)
	{
		need_sort = false;

		for (int z = 0; z < last_index - 1; z++)
		{


			/*if (glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
			{
				std::cout
					<<
					"z ("
					<<
					*draw_group_buffer.at(z)->name
					<<
					") ["
					<<
					std::to_string(*draw_group_buffer.at(z)->offset_z + *draw_group_buffer.at(z)->master_entity->position_z)
					<<
					"] z + 1 ("
					<<
					*draw_group_buffer.at(z + 1)->name
					<<
					") ["
					<<
					std::to_string(*draw_group_buffer.at(z + 1)->offset_z + *draw_group_buffer.at(z + 1)->master_entity->position_z)
					<<
					"]"
					<< std::endl;
			}*/

			/*if
				(
					(
						//(
						//	*draw_group_buffer.at(z)->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_WALL_Z
						//)
						//&

						//if close to camera
						(
							*draw_group_buffer.at(z)->offset_y + *draw_group_buffer.at(z)->master_entity->position_y
							<
							*draw_group_buffer.at(z + 1)->offset_y + *draw_group_buffer.at(z + 1)->master_entity->position_y
						)
						//and 
						&&
						(
							*draw_group_buffer.at(z)->master_entity->position_y
							+
							*draw_group_buffer.at(z)->offset_y
							+
							*draw_group_buffer.at(z)->master_entity->position_z
							+
							*draw_group_buffer.at(z)->offset_z
							+
							*draw_group_buffer.at(z)->max_height
							>=
							*draw_group_buffer.at(z)->master_entity->position_y
							+
							*draw_group_buffer.at(z)->offset_y
							+
							*draw_group_buffer.at(z)->master_entity->position_z
							+
							*draw_group_buffer.at(z)->offset_z
						)

					)
				)
			{
				swap(draw_group_buffer.at(z), draw_group_buffer.at(z + 1));
				need_sort = true;
				if (glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
				{
					std::cout
						<<
						"swap ["
						<<
						*draw_group_buffer.at(z)->name
						<<
						"] and ["
						<<
						*draw_group_buffer.at(z + 1)->name
						<<
						"]"
						<<
						std::endl;
				}
			}*/

			if
				(
					(
						//(
						//	*draw_group_buffer.at(z)->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_WALL_Z
						//)
						//&

						//if close to camera
						(
							*draw_group_buffer.at(z)->offset_y + *draw_group_buffer.at(z)->master_entity->position_y
							<
							*draw_group_buffer.at(z + 1)->offset_y + *draw_group_buffer.at(z + 1)->master_entity->position_y
						)
						//and 
						&&
						(
							*draw_group_buffer.at(z)->master_entity->position_z
							+
							*draw_group_buffer.at(z)->offset_z
							+
							*draw_group_buffer.at(z)->max_height
							>=
							*draw_group_buffer.at(z + 1)->master_entity->position_z
							+
							*draw_group_buffer.at(z + 1)->offset_z
							
						)

					)
				)
			{
				
				need_sort = true;
				/*
				if (glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
				{
					std::cout
						<<
						"swap Y ["
						<<
						*draw_group_buffer.at(z)->name
						<<
						"]("
						<<
						std::to_string
						(
							*draw_group_buffer.at(z)->offset_y + *draw_group_buffer.at(z)->master_entity->position_y
						)
						<<
						") and ["
						<<
						*draw_group_buffer.at(z + 1)->name
						<<
						"]("
						<<
						std::to_string
						(
							*draw_group_buffer.at(z + 1)->offset_y + *draw_group_buffer.at(z + 1)->master_entity->position_y
						)
						<<
						")"
						<<
						std::endl;
				}*/

				swap(draw_group_buffer.at(z), draw_group_buffer.at(z + 1));
			}
			//std::cout << "try sort z" << std::endl;
			if
				(
					(
						//(
						//	*draw_group_buffer.at(z)->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_WALL_Z
						//)
						//&

						//if far to camera
						//(
						//	*draw_group_buffer.at(z)->offset_y + *draw_group_buffer.at(z)->master_entity->position_y
						//	>
						//	*draw_group_buffer.at(z + 1)->offset_y + *draw_group_buffer.at(z + 1)->master_entity->position_y
						//)
						//&&
						//(
						//	*draw_group_buffer.at(z)->selected_direction_of_push != AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_ROOF_Y
						//)
						//and 
						//&&
						(

							*draw_group_buffer.at(z)->master_entity->position_z
							+
							*draw_group_buffer.at(z)->offset_z
							>
							*draw_group_buffer.at(z + 1)->master_entity->position_z
							+
							*draw_group_buffer.at(z + 1)->offset_z
							+
							*draw_group_buffer.at(z + 1)->max_height
						)

					)
				)
			{
				/*
				if (glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
				{
					std::cout
						<<
						"swap Z ["
						<<
						*draw_group_buffer.at(z)->name
						<<
						"]("
						<<
						std::to_string
						(
							*draw_group_buffer.at(z)->master_entity->position_z
							+
							*draw_group_buffer.at(z)->offset_z
						)
						<<
						") and ["
						<<
						*draw_group_buffer.at(z + 1)->name
						<<
						"]("
						<<
						std::to_string
						(
							*draw_group_buffer.at(z + 1)->master_entity->position_z
							+
							*draw_group_buffer.at(z + 1)->offset_z
							+
							*draw_group_buffer.at(z + 1)->max_height
						)
						<<
						")"
						<<
						std::endl;
				}
				*/
				swap(draw_group_buffer.at(z), draw_group_buffer.at(z + 1));
				need_sort = true;
				
			}
			
			/*if
				(
					(
						(
							*draw_group_buffer.at(z)->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_ROOF_Y
						)
						&
						(
							(
								*draw_group_buffer.at(z)->offset_y + *draw_group_buffer.at(z)->master_entity->position_y
								<
								*draw_group_buffer.at(z + 1)->offset_y + *draw_group_buffer.at(z + 1)->master_entity->position_y
							)
							||
							(
								*draw_group_buffer.at(z)->offset_z + *draw_group_buffer.at(z)->master_entity->position_z
								>
								*draw_group_buffer.at(z + 1)->max_height
							)

						)
					)
				)
			{
				swap(draw_group_buffer.at(z), draw_group_buffer.at(z + 1));
				need_sort = true;
				if (glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
				{
					std::cout
						<<
						"swap ["
						<<
						*draw_group_buffer.at(z)->name
						<<
						"] and ["
						<<
						*draw_group_buffer.at(z + 1)->name
						<<
						"]"
						<<
						std::endl;
				}
			}*/

			/*if ((z == last_index - 2) &(!need_sort))
			{
				break;
			}*/
		}

		//need_sort = false;
	}

EWindow::add_time_process("sort draw buffer");

EGraphicCore::batch->force_draw_call();

EGraphicCore::batch_PBR->reset();
EGraphicCore::PBR_shader->use();
EGraphicCore::matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
EGraphicCore::matrix_transform = glm::translate
(
	EGraphicCore::matrix_transform,
	glm::vec3
	(
		-1.0f + round(EGraphicCore::SCR_WIDTH / 2.0f - *main_camera->position_x) * EGraphicCore::correction_x,
		-1.0f + round(EGraphicCore::SCR_HEIGHT / 2.0f - *main_camera->position_y) * EGraphicCore::correction_y,
		0.0f
	)
);

EGraphicCore::matrix_transform = glm::scale
(
	EGraphicCore::matrix_transform,
	glm::vec3
	(
		EGraphicCore::correction_x * *main_camera->zoom,
		EGraphicCore::correction_y * *main_camera->zoom,
		1.0f
	)
);

transformLoc = glGetUniformLocation(EGraphicCore::PBR_shader->ID, "transform");
glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));
float true_height = 0.0f;

glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_2D, EWindow::skydome_light_FBO[EGraphicCore::selected_blur_level]->colorbuffer);
EGraphicCore::PBR_shader->setInt("texture2", 1);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//texture filtering
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//DRAW BUFFER
	for (int z = 0; z < last_index; z++)
	{
		
		//Entity::draw_entity(draw_buffer.at(z), EGraphicCore::batch, _d);
		for (int f = 0; f < draw_group_buffer.at(z)->sprite_list.size(); f++)
		{
			Entity::AutobuildingGroup* t_group		= draw_group_buffer.at(z);
			Entity* t_entity						= t_group->master_entity;

			
			if (*t_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_WALL_Z)
			{
				true_height = *t_entity->position_y + *t_group->sprite_list.at(f)->offset_y + *t_entity->position_z + *t_group->sprite_list.at(f)->offset_z - *main_camera->position_y + EGraphicCore::SCR_HEIGHT / 2.0f;
			}
			else
			if (*t_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_ROOF_Y)
			{
				true_height = *t_entity->position_y + *t_group->sprite_list.at(f)->offset_y + *t_entity->position_z + *t_group->sprite_list.at(f)->offset_z - *main_camera->position_y + EGraphicCore::SCR_HEIGHT / 2.0f + 1000.0f;
			}

			EGraphicCore::draw_sprite_PBR
			(
					t_group->sprite_list.at(f),
					EGraphicCore::batch_PBR,

					*t_entity->position_x,
					*t_entity->position_y,
					*t_entity->position_z,

					true_height
			);
		}
	}
	EWindow::add_time_process("Draw entities");
	EGraphicCore::batch_PBR->force_draw_call_PBR();
	EWindow::add_time_process("batch draw call [entities]");
	
	EGraphicCore::ourShader->use();


/*for (int i = cluster_draw_end_y;	i >= cluster_draw_start_y;	i--)
for (int j = cluster_draw_start_x;	j <= cluster_draw_end_x;	j++)
{
	for (Entity* e: cluster_static[j][i]->entity_list)
	{Entity::draw_entity(e, EGraphicCore::batch, _d);}

	for (Entity* e: cluster_non_static[j][i]->entity_list)
	{Entity::draw_entity(e, EGraphicCore::batch, _d);}
}*/

//std::cout << "-------" << std::endl;



for (int i = cluster_draw_start_y; i <= cluster_draw_end_y; i++)
for (int j = cluster_draw_start_x; j <= cluster_draw_end_x; j++)
{
	for (Entity* e : cluster_static[j][i]->entity_list)
	{
		Entity::draw_entity_autobuilging_helping(e, EGraphicCore::batch, _d);
	}

	for (Entity* e : cluster_non_static[j][i]->entity_list)
	{
		Entity::draw_entity_autobuilging_helping(e, EGraphicCore::batch, _d);
	}
}
EWindow::add_time_process("draw EAH");

EGraphicCore::batch->setcolor(EColor::COLOR_RED);
EGraphicCore::batch->draw_gabarite(get_real_world_position_x_by_mouse(main_camera) - 3.0f, get_real_world_position_y_by_mouse(main_camera) - 3.0f, 6.0f, 6.0f, EGraphicCore::gabarite_white_pixel);

if (is_entity_selection_started)
{
	EGraphicCore::batch->draw_rama(*entity_selection_region->position_x, *entity_selection_region->position_y, *entity_selection_region->size_x, *entity_selection_region->size_y, 2.0f, EGraphicCore::gabarite_white_pixel);
}

EGraphicCore::batch->force_draw_call();

EWindow::add_time_process("batch draw call [helpers]");
	if ((glfwGetKey(EWindow::main_window, GLFW_KEY_TAB) == GLFW_PRESS))
	{
		EGraphicCore::batch->setcolor(10.0f, 10.0f, 10.0f, 1.0f);
		EGraphicCore::batch->reset();
			ETextureAtlas::set_this_FBO_as_active(EWindow::skydome_light_FBO[0]);

			
			EGraphicCore::batch->draw_rect(0.0f, 0.0f, EWindow::skydome_light_FBO[0]->size_x, EWindow::skydome_light_FBO[0]->size_y);
		EGraphicCore::batch->force_draw_call();

		for (int i = 1; i < 8; i++)
		{
			ETextureAtlas::set_this_FBO_as_active(EWindow::skydome_light_FBO[i]);
			EGraphicCore::batch->draw_rect(0.0f, (EWindow::skydome_light_FBO[0]->size_y + 5.0f) * i, EWindow::skydome_light_FBO[0]->size_x, EWindow::skydome_light_FBO[0]->size_y);
			EGraphicCore::batch->force_draw_call();
		}



		ETextureAtlas::set_this_FBO_as_active(EWindow::default_texture_atlas);


		/*EGraphicCore::batch->reset();
		EGraphicCore::batch->setcolor(EColor::COLOR_WHITE);
		EGraphicCore::batch->draw_gabarite(0.0f, 0.0f, EGraphicCore::gabarite_full_atlas);

		EGraphicCore::batch->draw_rama(0.0f, 0.0f, 4096.0f, 4096.0f, 3.0f, EGraphicCore::gabarite_white_pixel);*/

	}


	if
	(
		(glfwGetKey(EWindow::main_window, GLFW_KEY_F1) == GLFW_PRESS)
		&
		(!EWindow::button_main_group_pressed)
	)
	{
		EWindow::button_main_group_pressed = true;
		saveImage((char*)"zzz.png", EWindow::main_window);
	}
	

	


}

void EWindowMain::update(float _d)
{
	EWindow::add_time_process("===--- update begin ---===");
	if (_d > 0.1) { _d = 0.1f; }

	cluster_draw_start_x = floor((*main_camera->position_x - EGraphicCore::SCR_WIDTH / 2.0f) / ECluster::CLUSTER_SIZE_X) - 5; cluster_draw_start_x = max(cluster_draw_start_x, 0);
	cluster_draw_start_y = floor((*main_camera->position_y - EGraphicCore::SCR_HEIGHT / 2.0f) / ECluster::CLUSTER_SIZE_Y) - 5; cluster_draw_start_y = max(cluster_draw_start_y, 0);

	cluster_draw_end_x = floor((*main_camera->position_x + EGraphicCore::SCR_WIDTH / 2.0f) / ECluster::CLUSTER_SIZE_X) + 5; cluster_draw_end_x = min(cluster_draw_end_x, ECluster::CLUSTED_DIM_X);
	cluster_draw_end_y = floor((*main_camera->position_y + EGraphicCore::SCR_HEIGHT / 2.0f) / ECluster::CLUSTER_SIZE_Y) + 5; cluster_draw_end_y = min(cluster_draw_end_y, ECluster::CLUSTED_DIM_Y);

	std::vector <Entity*>* t_vec;

	ECluster* t_cluster = NULL;

	if ((glfwGetKey(EWindow::main_window, GLFW_KEY_Z) == GLFW_PRESS))
	{
		if (ExternalButtonAction::get_entity() != NULL)
		{
			*ExternalButtonAction::get_entity()->position_z += mouse_speed_y;
			*ExternalButtonAction::get_entity()->position_z = max(*ExternalButtonAction::get_entity()->position_z, 0.0f);
		}
	}

	if ((glfwGetKey(EWindow::main_window, GLFW_KEY_C) == GLFW_PRESS))
	{
		if (ExternalButtonAction::get_entity() != NULL)
		{
			*ExternalButtonAction::get_entity()->previvous_cluster_x = floor(*ExternalButtonAction::get_entity()->position_x / ECluster::CLUSTER_SIZE_X);
			*ExternalButtonAction::get_entity()->previvous_cluster_y = floor(*ExternalButtonAction::get_entity()->position_y / ECluster::CLUSTER_SIZE_Y);

			*ExternalButtonAction::get_entity()->position_x += mouse_speed_x;
			*ExternalButtonAction::get_entity()->position_y += mouse_speed_y;

			if
			(
				(*ExternalButtonAction::get_entity()->previvous_cluster_x != floor(*ExternalButtonAction::get_entity()->position_x / ECluster::CLUSTER_SIZE_X))
				||
				(*ExternalButtonAction::get_entity()->previvous_cluster_y != floor(*ExternalButtonAction::get_entity()->position_y / ECluster::CLUSTER_SIZE_Y))
			)
			{
				if (*ExternalButtonAction::get_entity()->selected_cluster_mode == EntityClusterMode::ENTITY_CLUSTER_MODE_STATIC)
				{
					
					t_cluster
					=
					cluster_static
					[*ExternalButtonAction::get_entity()->previvous_cluster_x]
					[*ExternalButtonAction::get_entity()->previvous_cluster_y];

					
				}

				if (*ExternalButtonAction::get_entity()->selected_cluster_mode == EntityClusterMode::ENTITY_CLUSTER_MODE_NON_STATIC)
				{
					t_cluster
					=
					cluster_non_static
					[*ExternalButtonAction::get_entity()->previvous_cluster_x]
					[*ExternalButtonAction::get_entity()->previvous_cluster_y];
				}

				for (int i = 0; i < t_cluster->entity_list.size(); i++)
				{

					if (t_cluster->entity_list.at(i) == ExternalButtonAction::get_entity())
					{

						t_cluster->entity_list.erase(t_cluster->entity_list.begin() + i);
						/*std::cout << "erase cluster. new size [" << std::to_string
						(
							cluster_static
							[*ExternalButtonAction::get_entity()->previvous_cluster_x]
						[*ExternalButtonAction::get_entity()->previvous_cluster_y]
						->entity_list.size()
							) << "]" << std::endl;*/
						break;
					}
				}

				std::cout << "cluster x[" << std::to_string(floor(*ExternalButtonAction::get_entity()->position_x / ECluster::CLUSTER_SIZE_X)) << "]" << std::endl;
				std::cout << "cluster y[" << std::to_string(floor(*ExternalButtonAction::get_entity()->position_y / ECluster::CLUSTER_SIZE_Y)) << "]" << std::endl;

				
					//t_vec.erase(std::remove(t_vec.begin(), t_vec.end(), ExternalButtonAction::get_entity()), t_vec.end());

					put_entity_to_map(ExternalButtonAction::get_entity());
				
			}
		}
	}

	if
	(
		(!EButton::any_overlap)
		&
		(EWindow::top_overlaped_group == NULL)
	)
	{
		if (scroll > 0)
		{
			*main_camera->zoom *= 2.0f;

			*main_camera->position_x *= 2.0f;
			*main_camera->position_y *= 2.0f;
		}

		if (scroll < 0)
		{
			*main_camera->zoom /= 2.0f;

			*main_camera->position_x /= 2.0f;
			*main_camera->position_y /= 2.0f;
		}
	}

	int selected_group_element_id = -1;

	
	for (int i = cluster_draw_start_y; i <= cluster_draw_end_y; i++)
	for (int j = cluster_draw_start_x; j<= cluster_draw_end_x; j++)
	{
		autobuilding_updater(cluster_static[j][i]->entity_list);
		autobuilding_updater(cluster_non_static[j][i]->entity_list);
	}

	if (ExternalButtonAction::get_entity() != NULL)
	{
		generate_building(ExternalButtonAction::get_entity());
	}

	EWindow::add_time_process("Autobuilding updater");

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

		for (int i = cluster_draw_start_y; i <= cluster_draw_end_y; i++)
		for (int j = cluster_draw_start_x; j <= cluster_draw_end_x; j++)
		{
			entity_selection_process(cluster_static[j][i]->entity_list);
			entity_selection_process(cluster_non_static[j][i]->entity_list);
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

	if (EWindow::top_overlaped_group == NULL)
	{
		if ((glfwGetKey(EWindow::main_window, GLFW_KEY_W) == GLFW_PRESS)) { *main_camera->speed_y += _d * 200.0f; }
		if ((glfwGetKey(EWindow::main_window, GLFW_KEY_S) == GLFW_PRESS)) { *main_camera->speed_y -= _d * 200.0f; }

		if ((glfwGetKey(EWindow::main_window, GLFW_KEY_D) == GLFW_PRESS)) { *main_camera->speed_x += _d * 200.0f; }
		if ((glfwGetKey(EWindow::main_window, GLFW_KEY_A) == GLFW_PRESS)) { *main_camera->speed_x -= _d * 200.0f; }
	}

	*main_camera->position_x += *main_camera->speed_x;
	*main_camera->position_y += *main_camera->speed_y;

	*main_camera->speed_x *= pow(0.0001f, _d);
	*main_camera->speed_y *= pow(0.0001f, _d);
	/*
	if (*main_camera->speed_x > 0.0f) { *main_camera->speed_x -= _d * 50.0f; } else { *main_camera->speed_x += _d * 50.0f; }
	if (*main_camera->speed_y > 0.0f) { *main_camera->speed_y -= _d * 50.0f; } else { *main_camera->speed_y += _d * 50.0f; }

	if (abs(*main_camera->speed_x) <= 5.0f) { *main_camera->speed_x = 0.0f; }
	if (abs(*main_camera->speed_y) <= 5.0f) { *main_camera->speed_y = 0.0f; }*/

	EWindow::add_time_process("end update");
}

void EWindowMain::entity_selection_process(std::vector<Entity*> _v)
{
	for (Entity* e : _v)
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
}

void EWindowMain::autobuilding_updater(std::vector<Entity*> _v)
{
	float catch_size = 5.0f;
	for (Entity* e : _v)
	{
		for (Entity::AutobuildingGroup* a_group : e->autobuilding_group_list)
		{

			if
				(
					(ExternalButtonAction::get_selected_autobuilding_group(e) != NULL)
					&&
					(ExternalButtonAction::get_selected_autobuilding_group(e) == a_group)
					&
					(get_real_world_position_x_by_mouse(main_camera) >= *e->position_x + *a_group->offset_x - 30.0f)
					&
					(get_real_world_position_x_by_mouse(main_camera) <= *e->position_x + *a_group->offset_x + 30.0f)
					&
					(get_real_world_position_y_by_mouse(main_camera) >= *e->position_y + *e->position_z + *a_group->offset_y + *a_group->offset_z - 30.0f)
					&
					(get_real_world_position_y_by_mouse(main_camera) <= *e->position_y + *e->position_z + *a_group->offset_y + *a_group->offset_z + 30.0f)
					)
			{
				if (!LMB) { *a_group->is_catched = true; }
			}
			else
			{
				if (!LMB) { *a_group->is_catched = false; }
			}

			if (*a_group->is_catched)
			{
				if (LMB)
				{
					if (glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
					{
						*a_group->offset_z += mouse_speed_y;
						*a_group->offset_z = max(*a_group->offset_z, 0.0f);
					}
					else
					{
						*a_group->offset_x += mouse_speed_x;
						*a_group->offset_y += mouse_speed_y;
					}
				}
			}

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
						&
						(
							(
								(ExternalButtonAction::get_entity() != NULL)
								&&
								(ExternalButtonAction::get_entity() == e)
								)
							/*||
							(
								(ExternalButtonAction::get_entity() == NULL)
							)*/
							)

						)
				{
					if
						(
							(get_real_world_position_x_by_mouse(main_camera) >= *e->position_x + *a_group->offset_x + *a_element->offset_x - catch_size)
							&
							(get_real_world_position_x_by_mouse(main_camera) <= *e->position_x + *a_group->offset_x + *a_element->offset_x + catch_size)
							&
							(get_real_world_position_y_by_mouse(main_camera) >= *e->position_y + *e->position_z + *a_group->offset_y + *a_group->offset_y + *a_element->offset_y + *a_element->offset_z - catch_size)
							&
							(get_real_world_position_y_by_mouse(main_camera) <= *e->position_y + *e->position_z + *a_group->offset_y + *a_group->offset_y + *a_element->offset_y + *a_element->size_y + *a_element->offset_z + catch_size)
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
							(get_real_world_position_x_by_mouse(main_camera) >= *e->position_x + *a_group->offset_x + *a_element->offset_x + *a_element->size_x - catch_size)
							&
							(get_real_world_position_x_by_mouse(main_camera) <= *e->position_x + *a_group->offset_x + *a_element->offset_x + *a_element->size_x + catch_size)
							&
							(get_real_world_position_y_by_mouse(main_camera) >= *e->position_y + *e->position_z + *a_group->offset_y + *a_group->offset_z + *a_element->offset_y + *a_element->offset_z - catch_size)
							&
							(get_real_world_position_y_by_mouse(main_camera) <= *e->position_y + *e->position_z + *a_group->offset_y + *a_group->offset_z + *a_element->offset_y + *a_element->size_y + *a_element->offset_z + catch_size)
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
							(get_real_world_position_x_by_mouse(main_camera) >= *e->position_x + *a_group->offset_x + *a_element->offset_x - catch_size)
							&
							(get_real_world_position_x_by_mouse(main_camera) <= *e->position_x + *a_group->offset_x + *a_element->offset_x + *a_element->size_x + catch_size)
							&
							(get_real_world_position_y_by_mouse(main_camera) >= *e->position_y + *e->position_z + *a_group->offset_y + *a_group->offset_z + *a_element->offset_y + *a_element->offset_z - catch_size)
							&
							(get_real_world_position_y_by_mouse(main_camera) <= *e->position_y + *e->position_z + *a_group->offset_y + *a_group->offset_z + *a_element->offset_y + *a_element->offset_z + catch_size)
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
							(get_real_world_position_x_by_mouse(main_camera) >= *e->position_x + *a_group->offset_x + *a_element->offset_x - catch_size)
							&
							(get_real_world_position_x_by_mouse(main_camera) <= *e->position_x + *a_group->offset_x + *a_element->offset_x + *a_element->size_x + catch_size)
							&
							(get_real_world_position_y_by_mouse(main_camera) >= *e->position_y + *e->position_z + *a_group->offset_y + *a_group->offset_z + *a_element->offset_y + *a_element->size_y + *a_element->offset_z - catch_size)
							&
							(get_real_world_position_y_by_mouse(main_camera) <= *e->position_y + *e->position_z + *a_group->offset_y + *a_group->offset_z + *a_element->offset_y + *a_element->size_y + *a_element->offset_z + catch_size)
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
							(get_real_world_position_y_by_mouse(main_camera) >= *e->position_y + *e->position_z + *a_group->offset_y + *a_group->offset_z + *a_element->offset_y + *a_element->offset_z + *a_element->size_y / 2.0f - 10.0f)
							&
							(get_real_world_position_y_by_mouse(main_camera) <= *e->position_y + *e->position_z + *a_group->offset_y + *a_group->offset_z + *a_element->offset_y + *a_element->offset_z + *a_element->size_y / 2.0f + 10.0f)
							)
					{
						if (!LMB) { *a_element->catched_mid = true; }
					}
					else
					{
						if (!LMB) { *a_element->catched_mid = false; }
					}

					if
						(
							(get_real_world_position_x_by_mouse(main_camera) >= *e->position_x + *a_group->offset_x + *a_element->offset_x + *a_element->size_x / 2.0f - 5.0f)
							&
							(get_real_world_position_x_by_mouse(main_camera) <= *e->position_x + *a_group->offset_x + *a_element->offset_x + *a_element->size_x / 2.0f + 5.0f)
							&
							(get_real_world_position_y_by_mouse(main_camera) >= *e->position_y + *e->position_z + *a_group->offset_y + *a_group->offset_z + *a_element->offset_y + *a_element->offset_z + *a_element->size_y / 2.0f + 10.0f)
							&
							(get_real_world_position_y_by_mouse(main_camera) <= *e->position_y + *e->position_z + *a_group->offset_y + *a_group->offset_z + *a_element->offset_y + *a_element->offset_z + *a_element->size_y / 2.0f + 40.0f)
							)
					{
						if (!LMB) { *a_element->catched_z = true; }
					}
					else
					{
						if (!LMB) { *a_element->catched_z = false; }
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

						if (*a_element->catched_z)
						{
							*a_element->offset_z += mouse_speed_y / *main_camera->zoom;
							*a_element->offset_z = max(*a_element->offset_z, 0.0f);
							//*a_element->offset_x += mouse_speed_x / *main_camera->zoom;
							//generate_building(e);
						}
					}
				}
				else
				{
					*a_element->catched_mid = false;
					*a_element->catched_z = false;

					*a_element->catched_left_side = false;
					*a_element->catched_right_side = false;
					*a_element->catched_up_side = false;
					*a_element->catched_down_side = false;
				}


			}

			
		}

		
	}
}

void EWindowMain::reset_render()
{

	glClearColor(EColor::COLOR_LAZURE_SHADOW->color_red, EColor::COLOR_LAZURE_SHADOW->color_green, EColor::COLOR_LAZURE_SHADOW->color_blue, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	EGraphicCore::AO_shader->use();
		EGraphicCore::matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3(-1.0f - EGraphicCore::correction_x / 2.0f * 0.0f + round(EGraphicCore::SCR_WIDTH / 2.0f - *main_camera->position_x) * EGraphicCore::correction_x, -1.0f - EGraphicCore::correction_y / 2.0f * 0.0f + round(EGraphicCore::SCR_HEIGHT / 2.0f - *main_camera->position_y) * EGraphicCore::correction_y, 0.0f));
		EGraphicCore::matrix_transform = glm::scale(EGraphicCore::matrix_transform, glm::vec3(EGraphicCore::correction_x * *main_camera->zoom, EGraphicCore::correction_y * *main_camera->zoom, 1.0f));
		transformLoc = glGetUniformLocation(EGraphicCore::AO_shader->ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));

	//סבנמס באעקונא
	EGraphicCore::batch->reset();



	/*
	
	GENERATE AO SHADOW
	
	*/
	generate_AO_shadow();
	
	EGraphicCore::ourShader->use();
	ETextureAtlas::set_this_FBO_as_active(EWindow::AO_shadow_FBO);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);

		EGraphicCore::matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3(-1.0f, -1.0f, 0.0f));
		EGraphicCore::matrix_transform = glm::scale(EGraphicCore::matrix_transform, glm::vec3(1.0f, 1.0f, 1.0f));
		transformLoc = glGetUniformLocation(EGraphicCore::ourShader->ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));

		//EGraphicCore::batch->draw_rect(0.0f, 0.0f, 2.0f, 2.0f);
		EGraphicCore::batch->reinit();
		EGraphicCore::batch->draw_call();
		EGraphicCore::batch->reset();



	ETextureAtlas::draw_to_this_FBO(EWindow::skydome_light_FBO[0], EWindow::default_texture_atlas);
	EGraphicCore::batch->reset();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//



		EGraphicCore::ourShader->use();
		//glUniform1f(glGetUniformLocation(EGraphicCore::simple_blur->ID, "blur_size_x"), 1.0f / 4096.0f * 0.5f);
		//glUniform1f(glGetUniformLocation(EGraphicCore::simple_blur->ID, "blur_size_y"), 1.0f / 4096.0f * 0.5f);
		EGraphicCore::matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3(-1.0f, -1.0f, 0.0f));
		EGraphicCore::matrix_transform = glm::scale(EGraphicCore::matrix_transform, glm::vec3(2.0f, 2.0f, 1.0f));
		transformLoc = glGetUniformLocation(EGraphicCore::ourShader->ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));



		//sky
		glClearColor(0.04f, 0.040f, 0.40f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		EGraphicCore::batch->setcolor(0.1f * EGraphicCore::sun_position_y, 0.104f * EGraphicCore::sun_position_y * EGraphicCore::sun_position_y, 0.11f * EGraphicCore::sun_position_y * EGraphicCore::sun_position_y, 1.0f);
		EGraphicCore::batch->draw_gabarite(0.0f, 0.0f, 1.0f, 1.000f, EGraphicCore::gabarite_white_pixel);

		//sun
		EGraphicCore::batch->setcolor(1.0f, 0.9f, 0.8f, 1.0f);
		EGraphicCore::batch->draw_gabarite(EGraphicCore::sun_position_x - 0.025f * 1.0f, EGraphicCore::sun_position_y - 0.025f * 1.0f, 0.05f * 1.0f, 0.05f * 1.0f, EGraphicCore::gabarite_sun);

		//ground (grass)
		EGraphicCore::batch->setcolor(0.085f * EGraphicCore::sun_position_y, 0.084f * EGraphicCore::sun_position_y, 0.083f * EGraphicCore::sun_position_y, 1.0f);
		EGraphicCore::batch->draw_gabarite(0.0f, 0.0f, 1.0f, 0.25f, EGraphicCore::gabarite_white_pixel);
	EGraphicCore::batch->force_draw_call();

	EGraphicCore::simple_blur->use();
	transformLoc = glGetUniformLocation(EGraphicCore::simple_blur->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));

	

	EGraphicCore::batch->setcolor(EColor::COLOR_WHITE);
	

	for (int i = 0; i < 7; i++)
	{
		glUniform1f(glGetUniformLocation(EGraphicCore::simple_blur->ID, "blur_size_x"), 1.0f / skydome_light_FBO[i + 1]->size_x * (8.0f - i));
		glUniform1f(glGetUniformLocation(EGraphicCore::simple_blur->ID, "blur_size_y"), 1.0f / skydome_light_FBO[i + 1]->size_y * (8.0f - i));
		ETextureAtlas::draw_to_this_FBO(EWindow::skydome_light_FBO[i + 1], EWindow::skydome_light_FBO[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//
		EGraphicCore::batch->draw_rect(0.0f, 0.0f, 1.0f, 1.0f);
		EGraphicCore::batch->force_draw_call();
	}



	EGraphicCore::ourShader->use();
	ETextureAtlas::set_this_FBO_as_active(EWindow::default_texture_atlas);

	EGraphicCore::matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3(-1.0f - EGraphicCore::correction_x / 2.0f * 0.0f + round(EGraphicCore::SCR_WIDTH / 2.0f - *main_camera->position_x) * EGraphicCore::correction_x, -1.0f - EGraphicCore::correction_y / 2.0f * 0.0f + round(EGraphicCore::SCR_HEIGHT / 2.0f - *main_camera->position_y) * EGraphicCore::correction_y, 0.0f));
	EGraphicCore::matrix_transform = glm::scale(EGraphicCore::matrix_transform, glm::vec3(EGraphicCore::correction_x * *main_camera->zoom, EGraphicCore::correction_y * *main_camera->zoom, 1.0f));
	transformLoc = glGetUniformLocation(EGraphicCore::ourShader->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));

}

void EWindowMain::generate_AO_shadow()
{
	ETextureAtlas::draw_to_this_FBO(EWindow::AO_shadow_FBO, EWindow::default_texture_atlas);


	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glBlendEquation(GL_MIN);
	//EGraphicCore::batch->setcolor(EColor::COLOR_WHITE);
	//EGraphicCore::batch->draw_gabarite(0.0f, 0.0f, 10000.0f, 10000.0f, EGraphicCore::gabarite_white_pixel);

	EGraphicCore::batch->setcolor(EColor::COLOR_BLACK);

	for (int i = cluster_draw_start_y; i <= cluster_draw_end_y; i++)
		for (int j = cluster_draw_start_x; j <= cluster_draw_end_x; j++)
		{
			for (Entity* e : cluster_static[j][i]->entity_list)
				for (Entity::AutobuildingGroup* a_group : e->autobuilding_group_list)
				{
					EGraphicCore::batch->draw_AO_shadow
					(
						*e->position_x + *a_group->offset_x - 100.0f,
						*e->position_y + *a_group->offset_y - 5.0f,
						200.0f,
						200.0f,
						500.0f,
						EGraphicCore::gabarite_white_pixel
					);
				}
		}

	EGraphicCore::batch->force_draw_call();
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
		just_created_autobuilding_group->master_entity = _e;
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
	w_string = "";

	//std::cout << "try save" << std::endl;
	for (int i = 0; i < ECluster::CLUSTED_DIM_Y; i++)
	for (int j = 0; j < ECluster::CLUSTED_DIM_X; j++)
	for (Entity* e : EWindowMain::cluster_static[j][i]->entity_list)
	{
		add_entity_data_to_save_string(e);
	}

	for (int i = 0; i < ECluster::CLUSTED_DIM_Y; i++)
	for (int j = 0; j < ECluster::CLUSTED_DIM_X; j++)
	for (Entity* e : EWindowMain::cluster_non_static[j][i]->entity_list)
	{
		add_entity_data_to_save_string(e);
	}

	writer << w_string;
	writer.close();
}

void EWindowMain::add_entity_data_to_save_string(Entity* e)
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

		w_string += "direction_of_sprite_push";
		w_string += '\t';
		w_string += std::to_string(*a_group->selected_direction_of_push);
		w_string += '\n';

		w_string += "autobuilding_group_name";
		w_string += '\t';
		w_string += *a_group->name;
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

	for (int i = 0; i < ECluster::CLUSTED_DIM_Y; i++)
	for (int j = 0; j < ECluster::CLUSTED_DIM_X; j++)
	{
		cluster_static[j][i]->entity_list.clear();
		cluster_non_static[j][i]->entity_list.clear();
			//EWindowMain::entity_list.clear();
	}

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
				jc_group->master_entity = jc_entity;
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

			if ((EFile::data_array[i] == "direction_of_sprite_push") & (jc_group != NULL))
			{
				i++; *jc_group->selected_direction_of_push = EMath::to_float(EFile::data_array[i]);
			}

			if ((EFile::data_array[i] == "autobuilding_group_name") & (jc_group != NULL))
			{
				i++; *jc_group->name = EFile::data_array[i];
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
				//EWindowMain::entity_list.push_back(jc_entity);
				put_entity_to_map(jc_entity);
				EWindowMain::generate_building(jc_entity);
			}
		}
	}

	myfile.close();
}

void EWindowMain::put_entity_to_map(Entity* _e)
{
	int cluster_position_x = floor(*_e->position_x / ECluster::CLUSTER_SIZE_X);
	int cluster_position_y = floor(*_e->position_y / ECluster::CLUSTER_SIZE_Y);
	//ExternalEnums
	if (*_e->selected_cluster_mode == EntityClusterMode::ENTITY_CLUSTER_MODE_STATIC)
	{
		cluster_static[cluster_position_x][cluster_position_y]->entity_list.push_back(_e);
	}

	if (*_e->selected_cluster_mode == EntityClusterMode::ENTITY_CLUSTER_MODE_NON_STATIC)
	{
		cluster_non_static[cluster_position_x][cluster_position_y]->entity_list.push_back(_e);
	}
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

void EWindowMain::add_new_sprite_to_group_if_need(int _i, Entity::AutobuildingGroup* _gr, std::string _text)
{
	if (_i >= _gr->sprite_list.size())
	{
		EGraphicCore::ESprite* jcs = new EGraphicCore::ESprite();
		_gr->sprite_list.push_back(jcs);

		std::cout << "create new sprite to group (" << _text << "), new size of sprites is [" << std::to_string(_gr->sprite_list.size()) << "]" << std::endl;
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

	//if (_e->entity_sprite_array == NULL)
	//{
	//	_e->entity_sprite_array = new EGraphicCore::sprite_array();
	//}
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
		selected_sprite_id = 0;
		srand(1);
		//srand(time(NULL)

		*a_group->bottom_offset = 9999.0f;
		*a_group->up_offset = -9000.0f;

		*a_group->max_height = 10.0;

		*a_group->pseudo_pos_x = 10000.0f;
		*a_group->pseudo_size_x = 0.0f;

		*a_group->pseudo_pos_y = 10000.0f;
		*a_group->pseudo_size_y = 0.0f;

		*a_group->pseudo_pos_z = 10000.0f;
		*a_group->pseudo_size_z = 0.0f;

		for (Entity::AutobuildingGroupElement* a_element : a_group->autobuilding_group_element_list)
		{
			if
			(
				(*a_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_WALL_Z)
				&&
				(*a_element->offset_z + *a_element->size_y + *a_group->offset_z > *a_group->max_height)
			)
			{
				*a_group->max_height = *a_element->offset_z + *a_element->size_y;

			}

			if
				(
					(*a_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_ROOF_Y)
					&&
					(*a_element->offset_z + *a_group->offset_z > * a_group->max_height)
				)
			{
				*a_group->max_height = *a_element->offset_z;
			}

			///
			if (*a_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_WALL_Z)
			{
				if (*a_element->offset_z < *a_group->pseudo_pos_z)
				{
					*a_group->pseudo_pos_z = *a_group->pseudo_pos_z;
				}

				if (*a_element->offset_z + *a_element->size_y > *a_group->pseudo_size_z)
				{
					*a_group->pseudo_size_z = *a_element->offset_z + *a_element->size_y;
				}
			}

			if (*a_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_ROOF_Y)
			{
				if (*a_element->offset_y < *a_group->pseudo_pos_y)
				{
					*a_group->pseudo_pos_y = *a_group->pseudo_pos_y;
				}

				if (*a_element->offset_y + *a_element->size_y > * a_group->pseudo_size_y)
				{
					*a_group->pseudo_size_y = *a_element->offset_y + *a_element->size_y;
				}
			}

			if (*a_element->offset_x < *a_group->pseudo_pos_x)
			{
				*a_group->pseudo_pos_x = *a_element->offset_x;
			}

			if (*a_element->offset_x + *a_element->size_x - *a_group->pseudo_pos_x > * a_group->pseudo_size_x)
			{
				*a_group->pseudo_size_x = *a_element->offset_x + *a_element->size_x - *a_group->pseudo_pos_x;
			}

			if (*a_element->offset_y + *a_element->offset_z < * a_group->bottom_offset) { *a_group->bottom_offset = *a_element->offset_y + *a_element->offset_z; }
			if (*a_element->offset_y + *a_element->offset_z + *a_element->size_y > * a_group->up_offset) { *a_group->up_offset = *a_element->offset_y + *a_element->size_y + *a_element->offset_z; }
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
						add_new_sprite_to_group_if_need(selected_sprite_id, a_group, "mid wall");

						selected_sprite = a_group->sprite_list.at(selected_sprite_id);
						EGraphicCore::reset_sprite_data(selected_sprite);

						wall_fragment_x = min(1.0f, (mid_wall_copies_x + 0.0f - xx) / fragment_correction_factor_x);
						wall_fragment_y = min(1.0f, (mid_wall_copies_y + 0.0f - yy) / fragment_correction_factor_y);

						*selected_sprite->offset_x = *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT)->size_x;
						*selected_sprite->offset_x += xx * (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x) + *a_group->offset_x + *a_element->offset_x;

						if (*a_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_WALL_Z)
						{
							*selected_sprite->offset_y = 0.0f;
							*selected_sprite->offset_y += *a_group->offset_y + *a_element->offset_y;

							*selected_sprite->offset_z = *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_DOWN)->size_y;
							*selected_sprite->offset_z += yy * (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y) + *a_group->offset_z + *a_element->offset_z;
						}

						if (*a_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_ROOF_Y)
						{
							 *selected_sprite->offset_z = 0.0f;
							 *selected_sprite->offset_z += *a_group->offset_z + *a_element->offset_z;

							 *selected_sprite->offset_y = *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_DOWN)->size_y;
							 *selected_sprite->offset_y += yy * (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y) + *a_group->offset_y + *a_element->offset_y;

						}
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
						add_new_sprite_to_group_if_need(selected_sprite_id, a_group, "bottom");

						selected_sprite = a_group->sprite_list.at(selected_sprite_id);
						EGraphicCore::reset_sprite_data(selected_sprite);

						wall_fragment_x = min(1.0f, (mid_wall_copies_x + 0.0f - xx) / fragment_correction_factor_x);
						wall_fragment_y = min(1.0f, (mid_wall_copies_y + 0.0f - yy) / fragment_correction_factor_y);

						*selected_sprite->offset_x = *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT)->size_x;
						*selected_sprite->offset_x += xx * (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x) + *a_group->offset_x + *a_element->offset_x;
						
						if (*a_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_WALL_Z)
						{
							*selected_sprite->offset_y = 0.0f;
							*selected_sprite->offset_y += *a_group->offset_y + *a_element->offset_y;

							*selected_sprite->offset_z = 0.0f;
							*selected_sprite->offset_z += yy * (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y) + *a_group->offset_z + *a_element->offset_z;
						}
						
						if (*a_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_ROOF_Y)
						{
							*selected_sprite->offset_z = 0.0f;
							*selected_sprite->offset_z += *a_group->offset_z + *a_element->offset_z;

							*selected_sprite->offset_y = 0.0f;
							*selected_sprite->offset_y += yy * (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y) + *a_group->offset_y + *a_element->offset_y;
						}
						

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
						add_new_sprite_to_group_if_need(selected_sprite_id, a_group, "up");

						selected_sprite = a_group->sprite_list.at(selected_sprite_id);
						EGraphicCore::reset_sprite_data(selected_sprite);

						wall_fragment_x = min(1.0f, (mid_wall_copies_x + 0.0f - xx) / fragment_correction_factor_x);
						wall_fragment_y = min(1.0f, (mid_wall_copies_y + 0.0f - yy) / fragment_correction_factor_y);

						*selected_sprite->offset_x = *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT)->size_x;
						*selected_sprite->offset_x += xx * (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x) + *a_group->offset_x + *a_element->offset_x;
						if (*a_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_WALL_Z)
						{
							*selected_sprite->offset_y = 0.0f;
							*selected_sprite->offset_y += *a_group->offset_y + *a_element->offset_y;

							*selected_sprite->offset_z = *a_element->size_y - *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_UP)->size_y;
							*selected_sprite->offset_z += yy * (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y) + *a_group->offset_z + *a_element->offset_z;
						}

						if (*a_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_ROOF_Y)
						{
							*selected_sprite->offset_z = 0.0f;
							*selected_sprite->offset_z += *a_group->offset_z + *a_element->offset_z;

							*selected_sprite->offset_y = *a_element->size_y - *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_UP)->size_y;
							*selected_sprite->offset_y += yy * (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y) + *a_group->offset_y + *a_element->offset_y;
						}
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
						add_new_sprite_to_group_if_need(selected_sprite_id, a_group, "left");

						selected_sprite = a_group->sprite_list.at(selected_sprite_id);
						EGraphicCore::reset_sprite_data(selected_sprite);

						wall_fragment_x = min(1.0f, (mid_wall_copies_x + 0.0f - xx) / fragment_correction_factor_x);
						wall_fragment_y = min(1.0f, (mid_wall_copies_y + 0.0f - yy) / fragment_correction_factor_y);

						*selected_sprite->offset_x = 0.0f;
						*selected_sprite->offset_x += xx * (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x) + *a_group->offset_x + *a_element->offset_x;
						if (*a_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_WALL_Z)
						{
							*selected_sprite->offset_y = 0.0f;
							*selected_sprite->offset_y += *a_group->offset_y + *a_element->offset_y;

							*selected_sprite->offset_z = *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT)->position_y;
							*selected_sprite->offset_z += yy * (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y) + *a_group->offset_z + *a_element->offset_z;
						}

						if (*a_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_ROOF_Y)
						{
							*selected_sprite->offset_z = 0.0f;
							*selected_sprite->offset_z += *a_group->offset_z + *a_element->offset_z;

							*selected_sprite->offset_y = *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT)->position_y;
							*selected_sprite->offset_y += yy * (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y) + *a_group->offset_y + *a_element->offset_y;
						}
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
						add_new_sprite_to_group_if_need(selected_sprite_id, a_group, "left-down");

						selected_sprite = a_group->sprite_list.at(selected_sprite_id);
						EGraphicCore::reset_sprite_data(selected_sprite);

						wall_fragment_x = min(1.0f, (mid_wall_copies_x + 0.0f - xx) / fragment_correction_factor_x);
						wall_fragment_y = min(1.0f, (mid_wall_copies_y + 0.0f - yy) / fragment_correction_factor_y);

						*selected_sprite->offset_x = 0.0f;
						*selected_sprite->offset_x += xx * (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x) + *a_group->offset_x + *a_element->offset_x;
						
						if (*a_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_WALL_Z)
						{
							*selected_sprite->offset_y = 0.0f;
							*selected_sprite->offset_y += *a_group->offset_y + *a_element->offset_y;

							*selected_sprite->offset_z = 0.0f;
							*selected_sprite->offset_z += yy * (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y) + *a_group->offset_z + *a_element->offset_z;
						}
						
						if (*a_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_ROOF_Y)
						{
							*selected_sprite->offset_z = 0.0f;
							*selected_sprite->offset_z += *a_group->offset_z + *a_element->offset_z;

							*selected_sprite->offset_y = 0.0f;
							*selected_sprite->offset_y += yy * (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y) + *a_group->offset_y + *a_element->offset_y;
						}
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
						add_new_sprite_to_group_if_need(selected_sprite_id, a_group, "left-up");

						selected_sprite = a_group->sprite_list.at(selected_sprite_id);
						EGraphicCore::reset_sprite_data(selected_sprite);

						wall_fragment_x = min(1.0f, (mid_wall_copies_x + 0.0f - xx) / fragment_correction_factor_x);
						wall_fragment_y = min(1.0f, (mid_wall_copies_y + 0.0f - yy) / fragment_correction_factor_y);

						*selected_sprite->offset_x = 0.0f;
						*selected_sprite->offset_x += xx * (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x) + *a_group->offset_x + *a_element->offset_x;

						if (*a_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_WALL_Z)
						{
							*selected_sprite->offset_y = 0.0f;
							*selected_sprite->offset_y += *a_group->offset_y + *a_element->offset_y;

							*selected_sprite->offset_z = *a_element->size_y - *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT_UP_CORNER)->size_y;
							*selected_sprite->offset_z += yy * (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y) + *a_group->offset_z + *a_element->offset_z;
						}

						if (*a_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_ROOF_Y)
						{
							*selected_sprite->offset_z = 0.0f;
							*selected_sprite->offset_z += *a_group->offset_z + *a_element->offset_z;

							*selected_sprite->offset_y = *a_element->size_y - *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT_UP_CORNER)->size_y;
							*selected_sprite->offset_y += yy * (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y) + *a_group->offset_y + *a_element->offset_y;
						}
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
						add_new_sprite_to_group_if_need(selected_sprite_id, a_group, "right");

						selected_sprite = a_group->sprite_list.at(selected_sprite_id);
						EGraphicCore::reset_sprite_data(selected_sprite);

						wall_fragment_x = min(1.0f, (mid_wall_copies_x + 0.0f - xx) / fragment_correction_factor_x);
						wall_fragment_y = min(1.0f, (mid_wall_copies_y + 0.0f - yy) / fragment_correction_factor_y);

						*selected_sprite->offset_x = *a_element->size_x - *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT)->size_x;
						*selected_sprite->offset_x += xx * (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x) + *a_group->offset_x + *a_element->offset_x;
						
						if (*a_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_WALL_Z)
						{
							*selected_sprite->offset_y = 0.0f;
							*selected_sprite->offset_y += *a_group->offset_y + *a_element->offset_y;

							*selected_sprite->offset_z = *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT)->position_y;
							*selected_sprite->offset_z += yy * (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y) + *a_group->offset_z + *a_element->offset_z;
						}

						if (*a_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_ROOF_Y)
						{
							*selected_sprite->offset_z = 0.0f;
							*selected_sprite->offset_z += *a_group->offset_z + *a_element->offset_z;

							*selected_sprite->offset_y = *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT)->position_y;
							*selected_sprite->offset_y += yy * (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y) + *a_group->offset_y + *a_element->offset_y;
						}

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
						add_new_sprite_to_group_if_need(selected_sprite_id, a_group, "right-down");

						selected_sprite = a_group->sprite_list.at(selected_sprite_id);
						EGraphicCore::reset_sprite_data(selected_sprite);

						wall_fragment_x = min(1.0f, (mid_wall_copies_x + 0.0f - xx) / fragment_correction_factor_x);
						wall_fragment_y = min(1.0f, (mid_wall_copies_y + 0.0f - yy) / fragment_correction_factor_y);

						*selected_sprite->offset_x = *a_element->size_x - *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT_DOWN_CORNER)->size_x;
						*selected_sprite->offset_x += xx * (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x) + *a_group->offset_x + *a_element->offset_x;

						if (*a_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_WALL_Z)
						{
							*selected_sprite->offset_y = 0.0f;
							*selected_sprite->offset_y += *a_group->offset_y + *a_element->offset_y;

							*selected_sprite->offset_z = 0.0f;
							*selected_sprite->offset_z += yy * (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y) + *a_group->offset_z + *a_element->offset_z;
						}
						if (*a_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_ROOF_Y)
						{
							*selected_sprite->offset_z = 0.0f;
							*selected_sprite->offset_z += *a_group->offset_z + *a_element->offset_z;

							*selected_sprite->offset_y = 0.0f;
							*selected_sprite->offset_y += yy * (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y) + *a_group->offset_y + *a_element->offset_y;
						}
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
						add_new_sprite_to_group_if_need(selected_sprite_id, a_group, "right-up");

						selected_sprite = a_group->sprite_list.at(selected_sprite_id);
						EGraphicCore::reset_sprite_data(selected_sprite);

						wall_fragment_x = min(1.0f, (mid_wall_copies_x + 0.0f - xx) / fragment_correction_factor_x);
						wall_fragment_y = min(1.0f, (mid_wall_copies_y + 0.0f - yy) / fragment_correction_factor_y);

						*selected_sprite->offset_x = *a_element->size_x - *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT_UP_CORNER)->size_x;
						*selected_sprite->offset_x += xx * (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x) + *a_group->offset_x + *a_element->offset_x;
						
						if (*a_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_WALL_Z)
						{
							*selected_sprite->offset_y = 0.0f;
							*selected_sprite->offset_y += *a_group->offset_y + *a_element->offset_y;

							*selected_sprite->offset_z = *a_element->size_y - *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT_UP_CORNER)->size_y;
							*selected_sprite->offset_z += yy * (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y) + *a_group->offset_z + *a_element->offset_z;
						}

						if (*a_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_ROOF_Y)
						{
							*selected_sprite->offset_z = 0.0f;
							*selected_sprite->offset_z += *a_group->offset_z + *a_element->offset_z;

							*selected_sprite->offset_y = *a_element->size_y - *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT_UP_CORNER)->size_y;
							*selected_sprite->offset_y += yy * (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y) + *a_group->offset_y + *a_element->offset_y;
						}

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
	

	if (true)
	{
		for (int i = selected_sprite_id; i < a_group->sprite_list.size(); i++)
		{
			EGraphicCore::reset_sprite_data(a_group->sprite_list.at(i));
		}

		if
			(
				(a_group->sprite_list.size() > 0)
				&&
				//(_e->entity_sprite_array->sprite_list.at(_e->entity_sprite_array->sprite_list.size() - 1)->texture_gabarite == NULL)
				(selected_sprite_id < a_group->sprite_list.size())
				&&
				(true)
				)
		{
			//std::cout << "pre remove empty sprite, new size of sprites is [" << std::to_string(_e->entity_sprite_array->sprite_list.size()) << "]" << std::endl;

			EGraphicCore::ESprite* deleted_sprite
				=
				a_group->sprite_list.at(a_group->sprite_list.size() - 1);

			if (a_group->sprite_list.size() > 1)
			{
				a_group->sprite_list.erase(a_group->sprite_list.begin() + a_group->sprite_list.size() - 1);

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

			std::cout << "remove empty sprite, new size of sprites is [" << std::to_string(a_group->sprite_list.size()) << "]" << std::endl;
		}
	}

	}
}