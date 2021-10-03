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

#include <algorithm>
#include <iterator>


namespace fs = std::experimental::filesystem;

EButton::button_super_group*			EWindowMain::super_group_texture_collection_link;
EButton::button_group*					EWindowMain::group_texture_collection_link;

EButton::button_super_group*			EWindowMain::super_group_task_bar_link;
EButton::button_group*					EWindowMain::group_task_bar_link;

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
EButton* EWindowMain::link_button_sprite_fill_mode;
EButton* EWindowMain::link_button_sprite_random_count;
EButton* EWindowMain::link_button_autobuilding_seed;
EButton* EWindowMain::link_button_selected_sprite_draw_mode;


EButton* EWindowMain::link_button_autobuilding_random_offset_x;;
EButton* EWindowMain::link_button_autobuilding_random_offset_y;;


std::vector<EButton*>							EWindowMain::auto_size_region_button;

std::vector<Entity*>							EWindowMain::selected_entities;
EButton::EGridRegion*							EWindowMain::entity_selection_region;

ECamera*										EWindowMain::main_camera = new ECamera();

//std::vector<Entity*>							EWindowMain::entity_list;
bool											EWindowMain::is_entity_selection_started = false;

ECluster*										EWindowMain::cluster_static		[ECluster::CLUSTED_DIM_X][ECluster::CLUSTED_DIM_Y];
ECluster*										EWindowMain::cluster_non_static	[ECluster::CLUSTED_DIM_X][ECluster::CLUSTED_DIM_Y];

std::string										EWindowMain::w_string;

int												EWindowMain::cluster_draw_start_x;
int												EWindowMain::cluster_draw_start_y;
int												EWindowMain::cluster_draw_end_x;
int												EWindowMain::cluster_draw_end_y;

int												EWindowMain::terrain_draw_start_x;
int												EWindowMain::terrain_draw_start_y;

int												EWindowMain::terrain_draw_end_x;
int												EWindowMain::terrain_draw_end_y;

std::vector<Entity*>							EWindowMain::draw_buffer(1001);
std::vector<Entity::AutobuildingGroup*>			EWindowMain::draw_group_buffer(1001);

int												EWindowMain::last_index;

EWindowMain::terrain_tile_struct*				EWindowMain::terrain_matrix[250][250];



/// autobuilding section
EGraphicCore::ESprite*	EWindowMain::selected_sprite;
						
int						EWindowMain::selected_sprite_id;

float					EWindowMain::mid_wall_copies_x;
float					EWindowMain::mid_wall_copies_y;

float					EWindowMain::wall_full_size_x;
float					EWindowMain::wall_full_size_y;

float					EWindowMain::wall_fragment_x;
float					EWindowMain::wall_fragment_y;

float					EWindowMain::fragment_correction_factor_x;
float					EWindowMain::fragment_correction_factor_y;

int						EWindowMain::subdivision_x_count;
int						EWindowMain::subdivision_y_count;

EWindowMain::EWindowMain()
{
	EWindowMain::terrain_tile_struct* just_created_terrain_tile = NULL;

	for (int i = 0; i < TILES_COUNT_X; i++)
	for (int j = 0; j < TILES_COUNT_Y; j++)
	{
		just_created_terrain_tile = new EWindowMain::terrain_tile_struct();

		terrain_matrix[j][i] = just_created_terrain_tile;

		just_created_terrain_tile->terrain_texture = ETextureAtlas::put_texture_to_atlas("data/textures/beton_plates_terrain.png", EWindow::default_texture_atlas);
		just_created_terrain_tile->normal_gloss_texture = ETextureAtlas::get_normal_gloss_map_from_regular_texture_path("data/textures/beton_plates_terrain.png", EWindow::default_texture_atlas);

		*just_created_terrain_tile->texture_offset_x = (40.0f * (rand() % 3)) / 4096.0f;
		*just_created_terrain_tile->texture_offset_y = (40.0f * (rand() % 2)) / 4096.0f;

		*just_created_terrain_tile->size_x = 40.0f;
		*just_created_terrain_tile->size_y = 40.0f;
	}

	

	create_button_groups();

	entity_selection_region = new EButton::EGridRegion();

	for (int i = 0; i < ECluster::CLUSTED_DIM_Y; i++)
	for (int j = 0; j < ECluster::CLUSTED_DIM_X; j++)
	{
		cluster_static		[j][i] = new ECluster();
		cluster_non_static	[j][i] = new ECluster();
	}

	for (int i = 0; i < ECluster::CLUSTED_DIM_Y; i++)
	for (int j = 0; j < ECluster::CLUSTED_DIM_X; j++)
	for (int tx = 0; tx < 5; tx++)
	for (int ty = 0; ty < 5; ty++)
	{
		//cluster_static[j][i]->terrain_vertex_data_buffer[tx][ty];
		ECluster::bake_terrain_data
		(
			cluster_static[j][i],

			(float)(j) * (float)ECluster::CLUSTER_SIZE_X + tx * 40.0f,
			(float)(i) * (float)ECluster::CLUSTER_SIZE_Y + ty * 40.0f,

			*terrain_matrix[j * 5 + tx][i * 5 + ty]->size_x,
			*terrain_matrix[j * 5 + tx][i * 5 + ty]->size_y,

			*terrain_matrix[j * 5 + tx][i * 5 + ty]->texture_offset_x,
			*terrain_matrix[j * 5 + tx][i * 5 + ty]->texture_offset_y,

			terrain_matrix[j * 5 + tx][i * 5 + ty]->terrain_texture,
			terrain_matrix[j * 5 + tx][i * 5 + ty]->normal_gloss_texture
		);
	}

	load_map("test");
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

	super_group_task_bar_link = new EButton::button_super_group(this);
			super_group_task_bar_link->button_close->is_active = false;

			group_task_bar_link = new EButton::button_group();
			super_group_task_bar_link->button_group_list.push_back(group_task_bar_link);
	

	//"search brick group" texture
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	EButton::button_super_group* just_created_button_super_group = new EButton::button_super_group(this);
	create_button_for_task_list(this, super_group_task_bar_link, group_task_bar_link, just_created_button_super_group->is_active, "Textures list");

	button_group_list.push_back(super_group_task_bar_link);

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

	/// <summary>
	/// lol
	/// </summary>
	

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
	create_button_for_task_list(this, super_group_task_bar_link, group_task_bar_link, super_group_autobuilding->is_active, "Autobuilding");
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
	*group_grid_region_second_layer_link->size_x = 600.0f;
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
	but->description_text = "Region border up";

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
	but->description_text = "Region border left";

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
	but->description_text = "Region border right";

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
	but->description_text = "Region border down";

	but = new EButton(70.0f + 0.0f, 70.0f - 30.0f, 50.0f, 20.0f);
	but->master_window = this;
	but->master_super_group = super_group_autobuilding;
	but->master_group = group_grid_region_second_layer_link;
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_FREE;
	group_grid_region_second_layer_link->button_list.push_back(but);
	but->text = "Auto";
	but->action_on_left_click.push_back(&ExternalButtonAction::external_button_action_set_grid_region_auto_size);
	//but->text = "0";
	but->description_text = "Auto generate texture regions";

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
	but->description_text = "Space between sprites x";

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
	but->description_text = "Space between sprites y";

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
	but->description_text = "Vertical or horizontal orientation";

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
	but->description_text = "Texture rendomizator subdivision x";

	

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
	but->description_text = "Texture rendomizator subdivision y";

	//seed
	but = new EButton(5.0f, *group_grid_region_second_layer_link->size_y - 25.0f, 50.0f, 20.0f);
	link_button_autobuilding_seed = but;
	but->master_window = this;
	but->master_super_group = super_group_autobuilding;
	but->master_group = group_grid_region_second_layer_link;
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_FREE;
	group_grid_region_second_layer_link->button_list.push_back(but);
	but->text = "0";
	but->description_text = "Random seed";
	but->have_input_mode = true;
	but->input_only_numbers = true;
	//but->action_on_left_click.push_back(&ExternalButtonAction::external_button_action_set_grid_region_auto_size);
	but->action_on_input.push_back(&ExternalButtonAction::external_button_action_set_button_value);
	*but->is_consumable = true;
	//but->text = "0";


	//drop list roof/wall mode
	button_group_autobuilding_base = new EButton::button_group();
	*button_group_autobuilding_base->selected_push_method = EButton::GroupPushMethod::GROUP_PUSH_METHOD_RESET_X_ADD_Y;
	super_group_autobuilding->button_group_list.push_back(button_group_autobuilding_base);
	*button_group_autobuilding_base->size_x = 800.0f;
	*button_group_autobuilding_base->size_y = 120.0f;
	*button_group_autobuilding_base->can_be_stretched_x = false;
	*button_group_autobuilding_base->can_be_stretched_y = true;
	*button_group_autobuilding_base->can_be_moved_by_user = false;

	but = new EButton(250.0f + 55.0f, 70.0f - 30.0f, 50.0f, 20.0f, this, super_group_autobuilding, group_grid_region_second_layer_link);
	link_button_autobuilding_random_offset_x = but;
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_FREE;
	but->description_text = "Random offset x";
	//but->input_hint = "offset x";
	but->have_input_mode = true;
	but->input_only_numbers = true;
	*but->is_consumable = true;
	but->text = "0";
	but->action_on_input.push_back(&ExternalButtonAction::external_button_action_set_button_value);
	group_grid_region_second_layer_link->button_list.push_back(but);

	but = new EButton(250.0f + 55.0f, 70.0f - 55.0f, 50.0f, 20.0f, this, super_group_autobuilding, group_grid_region_second_layer_link);
	link_button_autobuilding_random_offset_y = but;
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_FREE;
	but->description_text = "Random offset y";
	//but->input_hint = "offset y";
	but->have_input_mode = true;
	but->input_only_numbers = true;
	*but->is_consumable = true;
	but->text = "0";
	but->action_on_input.push_back(&ExternalButtonAction::external_button_action_set_button_value);
	group_grid_region_second_layer_link->button_list.push_back(but);

	but = new EButton(250.0f + 55.0f, 70.0f - 0.0f, 110.0f, 20.0f, this, super_group_autobuilding, group_grid_region_second_layer_link);
			link_button_sprite_fill_mode = but;
			*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_FREE;
			group_grid_region_second_layer_link->button_list.push_back(but);
			//but->text = "PUSH Y";

			but->drop_text.push_back("TILE");
			but->drop_text.push_back("RANDOM PLACE");
			but->drop_elements = 2;
			*but->is_consumable = true;
			but->text = but->drop_text.at(0);
			but->description_text = "Fill rectandle area or random fill";

			but->is_drop_list = true;
			but->action_on_drop_list_select_element.push_back(&ExternalButtonAction::external_button_action_set_button_value);
			but->target_address_for_int = NULL;

	but = new EButton(250.0f + 170.0f, 70.0f - 0.0f, 50.0f, 20.0f, this, super_group_autobuilding, group_grid_region_second_layer_link);
			link_button_sprite_random_count = but;
			*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_FREE;
			but->description_text = "Random sprites count";
			//but->input_hint = "offset y";
			but->have_input_mode = true;
			but->input_only_numbers = true;
			*but->is_consumable = true;
			but->text = "0";
			but->action_on_input.push_back(&ExternalButtonAction::external_button_action_set_button_value);
			group_grid_region_second_layer_link->button_list.push_back(but);
			
		but = new EButton(250.0f + 225.0f, 70.0f - 0.0f, 110.0f, 20.0f, this, super_group_autobuilding, group_grid_region_second_layer_link);
			link_button_selected_sprite_draw_mode = but;
			*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_FREE;
			group_grid_region_second_layer_link->button_list.push_back(but);
			//but->text = "PUSH Y";

			but->drop_text.push_back("NORMAL");
			but->drop_text.push_back("AO SHADOW");
			but->drop_elements = 2;
			*but->is_consumable = true;
			but->text = but->drop_text.at(0);
			but->description_text = "Sprite draw mode (Normal/AO shadow)";

			but->is_drop_list = true;
			but->action_on_drop_list_select_element.push_back(&ExternalButtonAction::external_button_action_set_button_value);
			but->action_on_drop_list_select_element.push_back(&ExternalButtonAction::external_button_action_select_sprite_draw_mode);
			but->target_address_for_int = NULL;

	for (int i = 0; i < 20; i++)
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


	//group element
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

	//group
	for (int i = 0; i < 20; i++)
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
		but->action_on_right_click.push_back(&ExternalButtonAction::external_button_action_remove_autobuilding_group);
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
	


	/////////////vertex editor
		super_group_vertex_editor = new EButton::button_super_group(this);
		create_button_for_task_list(this, super_group_task_bar_link, group_task_bar_link, super_group_vertex_editor->is_active, "Vertex editor");

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
					but->action_on_left_double_click.push_back(ExternalButtonAction::external_button_action_select_texture_window_for_vertex_editor);

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
	create_button_for_task_list(this, super_group_task_bar_link, group_task_bar_link, just_created_button_super_group->is_active, "World setting");

	button_group_list.push_back(just_created_button_super_group);
	*just_created_button_super_group->position_x = 700.0f;
	*just_created_button_super_group->position_y = 300.0f;

	//group_texture_variants
	just_created_button_group = new EButton::button_group();
	just_created_button_super_group->button_group_list.push_back(just_created_button_group);

	*just_created_button_group->can_be_stretched_x = false;
	*just_created_button_group->can_be_stretched_y = false;

	*just_created_button_group->size_x = 232.0f;
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
	but->drop_text.push_back("BLUR 64*64   [level 6]");
	but->drop_text.push_back("BLUR 128*128 [level 7]");
	but->drop_elements = 8;
	but->text = but->drop_text.at(0);
	*but->is_consumable = false;

	

	//*just_created_button_super_group->position_x = 500.0f;
	but = new EButton(0.0f, 0.0f, 200.0f, 100.0f, this, just_created_button_super_group, just_created_button_group);
	but->have_icon = true;
	but->gabarite = ETextureAtlas::put_texture_to_atlas("data/textures/button_texture_sun_position[3].png", EWindow::default_texture_atlas);
	just_created_td_gradient = new EButton::ETwoDimensionGradient();
	*just_created_td_gradient->draw_gradient = false;
	but->action_on_td_gradient_drag.push_back(&ExternalButtonAction::external_button_action_change_sun_position);

	but->two_dimension_gradient = just_created_td_gradient;
	just_created_button_group->button_list.push_back(but);
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_Y;
	
	just_created_button_group = new EButton::button_group();
	just_created_button_super_group->button_group_list.push_back(just_created_button_group);
	*just_created_button_group->selected_push_method = EButton::GroupPushMethod::GROUP_PUSH_METHOD_ADD_X;

	but = new EButton (0.0f, 0.0f, 100.0f, 60.0f, this, just_created_button_super_group, just_created_button_group);
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_X;
	//but->is_slider = true;
	*but->is_radial_button = true;
	*but->maximum_value = 1.0f;
	but->target_address_for_float = &EGraphicCore::sun_size;
	but->action_on_slider_drag.push_back(&ExternalButtonAction::external_button_action_set_button_value);
	just_created_button_group->button_list.push_back(but);
	but->description_text = "Sun size";
	*but->side_text = "Sun size";
	but->text_color->set_color(EColor::COLOR_ORANGE);
	but->bg_color->set_color(EColor::COLOR_ORANGE);
	but->have_rama = true;
	*but->is_consumable = true;

	but = new EButton(0.0f, 0.0f, 100.0f, 60.0f, this, just_created_button_super_group, just_created_button_group);
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_Y;
	//but->is_slider = true;
	*but->is_radial_button = true;
	*but->maximum_value = 2.0f;
	but->slider_value_multiplier = 0.1f;
	but->target_address_for_float = &EGraphicCore::sun_matte_power;
	but->action_on_slider_drag.push_back(&ExternalButtonAction::external_button_action_set_button_value);
	just_created_button_group->button_list.push_back(but);
	but->description_text = "Sun bright";
	*but->side_text = "Sun bright";
	but->text_color->set_color(EColor::COLOR_YELLOW);
	but->bg_color->set_color(EColor::COLOR_YELLOW);
	but->have_rama = true;
	*but->is_consumable = true;

	but = new EButton(0.0f, 0.0f, 100.0f, 60.0f, this, just_created_button_super_group, just_created_button_group);
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_RESET_Y_AND_ADD_X;
	//but->is_slider = true;
	*but->is_radial_button = true;
	*but->maximum_value = 1.0f;
	//but->target_address_for_float = &EGraphicCore::suskyn_lum;
	but->target_address_for_float = &EGraphicCore::sky_lum;
	but->action_on_slider_drag.push_back(&ExternalButtonAction::external_button_action_set_button_value);
	just_created_button_group->button_list.push_back(but);
	but->description_text = "Sky bright";
	*but->side_text = "Sky bright";
	but->text_color->set_color(EColor::COLOR_BLUE);
	but->bg_color->set_color(EColor::COLOR_BLUE);
	//but->have_bg = false;
	but->have_rama = true;
	*but->is_consumable = true;

	but = new EButton(0.0f, 0.0f, 100.0f, 60.0f, this, just_created_button_super_group, just_created_button_group);
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_X;
	//but->is_slider = true;
	*but->is_radial_button = true;
	*but->maximum_value = 1.0f;
	//but->target_address_for_float = &EGraphicCore::suskyn_lum;
	but->target_address_for_float = &EGraphicCore::ground_lum;
	but->action_on_slider_drag.push_back(&ExternalButtonAction::external_button_action_set_button_value);
	just_created_button_group->button_list.push_back(but);
	but->description_text = "Ground bright";
	*but->side_text = "Ground bright";
	but->text_color->set_color(EColor::COLOR_GREEN);
	but->bg_color->set_color(EColor::COLOR_GREEN);
	but->have_rama = true;
	*but->is_consumable = true;

	but = new EButton(0.0f, 0.0f, 100.0f, 60.0f, this, just_created_button_super_group, just_created_button_group);
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_X;
	//but->is_slider = true;
	*but->is_radial_button = true;
	*but->maximum_value = 10.0f;
	but->slider_value_multiplier = 0.1f;
	//but->target_address_for_float = &EGraphicCore::suskyn_lum;
	but->target_address_for_float = &EGraphicCore::blur_size;
	but->action_on_slider_drag.push_back(&ExternalButtonAction::external_button_action_set_button_value);
	just_created_button_group->button_list.push_back(but);
	but->description_text = "Blur size";
	*but->side_text = "Blur size";
	but->have_rama = true;
	*but->is_consumable = true;
	but->text_color->set_color(EColor::COLOR_WHITE);
	but->bg_color->set_color(EColor::COLOR_WHITE);

	but = new EButton(0.0f, 0.0f, 100.0f, 60.0f, this, just_created_button_super_group, just_created_button_group);
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_Y;
	//but->is_slider = true;
	*but->is_radial_button = true;
	*but->maximum_value = 10.0f;
	but->slider_value_multiplier = 0.1f;
	//but->target_address_for_float = &EGraphicCore::suskyn_lum;
	but->target_address_for_float = &EGraphicCore::blur_size_buffer;
	but->action_on_slider_drag.push_back(&ExternalButtonAction::external_button_action_set_button_value);
	just_created_button_group->button_list.push_back(but);
	but->description_text = "Blur size[2]";
	*but->side_text = "Blur size[2]";
	but->have_rama = true;
	*but->is_consumable = true;
	but->text_color->set_color(EColor::COLOR_WHITE);
	but->bg_color->set_color(EColor::COLOR_WHITE);

	but = new EButton(0.0f, 0.0f, 100.0f, 60.0f, this, just_created_button_super_group, just_created_button_group);
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_X;
	//but->is_slider = true;
	*but->is_radial_button = true;
	*but->maximum_value = 100.0f;
	but->slider_value_multiplier = 0.1f;
	//but->target_address_for_float = &EGraphicCore::suskyn_lum;
	but->target_address_for_float = &EGraphicCore::brightness_multiplier;
	but->action_on_slider_drag.push_back(&ExternalButtonAction::external_button_action_set_button_value);
	just_created_button_group->button_list.push_back(but);
	but->description_text = "Skydome light reflection multiplier";
	*but->side_text = "Reflection";
	but->have_rama = true;
	*but->is_consumable = true;
	but->text_color->set_color(EColor::COLOR_WHITE);
	but->bg_color->set_color(EColor::COLOR_WHITE);

	but = new EButton(0.0f, 0.0f, 100.0f, 60.0f, this, just_created_button_super_group, just_created_button_group);
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_Y;
	//but->is_slider = true;
	*but->is_radial_button = true;
	*but->maximum_value = 2.0f;
	but->slider_value_multiplier = 0.5f;
	//but->target_address_for_float = &EGraphicCore::suskyn_lum;
	but->target_address_for_float = &EGraphicCore::sky_ambient_light_power;
	but->action_on_slider_drag.push_back(&ExternalButtonAction::external_button_action_set_button_value);
	just_created_button_group->button_list.push_back(but);
	but->description_text = "Sky light on non-sun angle";
	*but->side_text = "Sky light";
	but->have_rama = true;
	*but->is_consumable = true;
	but->text_color->set_color(EColor::COLOR_WHITE);
	but->bg_color->set_color(EColor::COLOR_WHITE);

	but->text_color->set_color(EColor::COLOR_WHITE);
	but->bg_color->set_color(EColor::COLOR_WHITE);


	//top free sky light
	but = new EButton(0.0f, 0.0f, 100.0f, 60.0f, this, just_created_button_super_group, just_created_button_group);
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_Y;
	//but->is_slider = true;
	*but->is_radial_button = true;
	*but->maximum_value = 2.0f;
	but->slider_value_multiplier = 0.5f;
	//but->target_address_for_float = &EGraphicCore::suskyn_lum;
	but->target_address_for_float = &EGraphicCore::sky_free_top_light;
	but->action_on_slider_drag.push_back(&ExternalButtonAction::external_button_action_set_button_value);
	just_created_button_group->button_list.push_back(but);
	but->description_text = "Free top sky light multiplier";
	*but->side_text = "Top light";
	but->have_rama = true;
	*but->is_consumable = true;
	but->text_color->set_color(EColor::COLOR_WHITE);
	but->bg_color->set_color(EColor::COLOR_WHITE);

	but->text_color->set_color(EColor::COLOR_WHITE);
	but->bg_color->set_color(EColor::COLOR_WHITE);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/////////////menu save|load|other
	just_created_button_super_group = new EButton::button_super_group(this);
	button_group_list.push_back(just_created_button_super_group);

	*just_created_button_super_group->size_x = 300.0f;
	*just_created_button_super_group->size_y = 30.0f;

	*just_created_button_super_group->inmovable_on_list = true;

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





	

}

EWindowMain::~EWindowMain()
{
}

EButton* EWindowMain::create_button_for_task_list(EWindow* _window, EButton::button_super_group* _super_group, EButton::button_group* _group, bool* _target_bool, std::string _text)
{
	EButton* but = new EButton(0.0f, 0.0f, 150.0f, 20.0f, _window, _super_group, _group);
	but->action_on_left_click.push_back(&ExternalButtonAction::external_button_action_set_button_constant_value);
	*but->target_value_for_bool = true;
	but->target_address_for_bool = _target_bool;
	_group->button_list.push_back(but);
	but->text = _text;
	return but;
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

	if (glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
	{
		for (int i = cluster_draw_start_y; i <= cluster_draw_end_y; i++)
		for (int j = cluster_draw_start_x; j <= cluster_draw_end_x; j++)
		{
			EGraphicCore::batch->setcolor(EColor::COLOR_GRAY);
			EGraphicCore::batch->draw_rama(j * ECluster::CLUSTER_SIZE_X, i * ECluster::CLUSTER_SIZE_Y, ECluster::CLUSTER_SIZE_X, ECluster::CLUSTER_SIZE_Y, 1.0f / *main_camera->zoom, EGraphicCore::gabarite_white_pixel);

			EFont::active_font->draw(EGraphicCore::batch, std::to_string(cluster_static[j][i]->entity_list.size()), j * ECluster::CLUSTER_SIZE_X + 10.0f, i * ECluster::CLUSTER_SIZE_Y + 10.0f);
		}

	}

	/*if (glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_ALT) != GLFW_PRESS)
	{

	}*/

	EWindow::add_time_process("Draw rama");


Entity* swap_entity = NULL;
last_index = 0;

	bool is_y_sort = false;
	//draw_buffer.clear();

	float t_z = 100.0f;
	
	last_index = 0;

for (int i = cluster_draw_end_y; i >= cluster_draw_start_y; i--)
for (int j = cluster_draw_start_x; j <= cluster_draw_end_x; j++)
	{
		for (Entity* e : cluster_static[j][i]->entity_list)
		{
			for (Entity::AutobuildingGroup* a_group : e->autobuilding_group_list)
			//if (*a_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_WALL_Z)
			{
				draw_group_buffer.at(last_index) = a_group;

				last_index++;
			}
		}
	}

EWindow::add_time_process("fill draw buffer");

	bool need_sort = true;

	while (need_sort)
	{
		need_sort = false;

		for (int z = 0; z < last_index - 1; z++)
		{

			if
				(
					(

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
				

				swap(draw_group_buffer.at(z), draw_group_buffer.at(z + 1));
			}
			
			if
				(
					(
						
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
				swap(draw_group_buffer.at(z), draw_group_buffer.at(z + 1));
				need_sort = true;
				
			}
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
		-1.0f
	)
);

EGraphicCore::matrix_transform = glm::scale
(
	EGraphicCore::matrix_transform,
	glm::vec3
	(
		EGraphicCore::correction_x * *main_camera->zoom,
		EGraphicCore::correction_y * *main_camera->zoom,
		EGraphicCore::correction_y * *main_camera->zoom
	)
);

transformLoc = glGetUniformLocation(EGraphicCore::PBR_shader->ID, "transform");
glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));
float true_height = 0.0f;

glUniform1f(glGetUniformLocation(EGraphicCore::PBR_shader->ID, "brightness_multiplier"), EGraphicCore::brightness_multiplier);

glUniform1f(glGetUniformLocation(EGraphicCore::PBR_shader->ID, "skydome_light_power"), EGraphicCore::sky_ambient_light_power);
glUniform1f(glGetUniformLocation(EGraphicCore::PBR_shader->ID, "free_top_light"), EGraphicCore::sky_free_top_light);
glUniform1f(glGetUniformLocation(EGraphicCore::PBR_shader->ID, "direct_sun_matte_multiplier"), EGraphicCore::sun_matte_power);

glUniform1f(glGetUniformLocation(EGraphicCore::PBR_shader->ID, "sun_position_x"), EGraphicCore::sun_position_x);
glUniform1f(glGetUniformLocation(EGraphicCore::PBR_shader->ID, "sun_position_y"), EGraphicCore::sun_position_y);


glUniform1f(glGetUniformLocation(EGraphicCore::PBR_shader->ID, "sun_zenith"), EGraphicCore::sun_zenith_factor);

glUniform1f(glGetUniformLocation(EGraphicCore::PBR_shader->ID, "screen_offset_x"), -*main_camera->position_x + EGraphicCore::SCR_WIDTH	/ 2.0f);
glUniform1f(glGetUniformLocation(EGraphicCore::PBR_shader->ID, "screen_offset_y"), -*main_camera->position_y + EGraphicCore::SCR_HEIGHT / 2.0f);

glActiveTexture(GL_TEXTURE0);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//texture filtering
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
glBindTexture(GL_TEXTURE_2D, EWindow::default_texture_atlas->colorbuffer);
EGraphicCore::PBR_shader->setInt("texture1", 0);



glActiveTexture(GL_TEXTURE1);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//texture filtering
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
glBindTexture(GL_TEXTURE_2D, EWindow::default_texture_atlas->colorbuffer);
EGraphicCore::PBR_shader->setInt("normal_gloss_map_texture", 1);

for (int i = 0; i < skydome_texture_levels; i++)
{
	glActiveTexture(GL_TEXTURE2 + i);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, EWindow::skydome_light_FBO[i]->colorbuffer);//1
	EGraphicCore::PBR_shader->setInt("SD_array[" + std::to_string(i) + "]", i + 2);
}


/*
glActiveTexture(GL_TEXTURE7);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//texture filtering
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
glBindTexture(GL_TEXTURE_2D, EWindow::skydome_light_FBO[5]->colorbuffer);//1/32
EGraphicCore::PBR_shader->setInt("SD_array[5]", 7);
EWindow::add_time_process("Set shader parameters");*/


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
				true_height =*t_entity->position_z + *t_group->sprite_list.at(f)->offset_z;
			}
			else
			if (*t_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_ROOF_Y)
			{
				true_height = *t_entity->position_y + *t_group->sprite_list.at(f)->offset_y - *main_camera->position_y + EGraphicCore::SCR_HEIGHT / 2.0f;
			}


			//EGraphicCore::batch_PBR->setcolor_lum(EColor::COLOR_WHITE, 1.0f - );
			//if (t_group->base)
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
	
	if ((glfwGetKey(EWindow::main_window, GLFW_KEY_TAB) == GLFW_PRESS) && (false))
	{
		
		EGraphicCore::batch->setcolor(10.0f, 10.0f, 10.0f, 1.0f);
		EGraphicCore::batch->reset();
			ETextureAtlas::set_this_FBO_as_active(EWindow::skydome_light_FBO[0]);

			
			EGraphicCore::batch->draw_rect(0.0f, 0.0f, EWindow::skydome_light_FBO[0]->size_x, EWindow::skydome_light_FBO[0]->size_y);
		EGraphicCore::batch->force_draw_call();

		for (int i = 1; i < skydome_texture_levels; i++)
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
	


	if ((glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS) && (true))
	{
		EGraphicCore::ourShader->use();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBlendEquation(GL_FUNC_ADD);
		ETextureAtlas::set_this_FBO_as_active(EWindow::default_texture_atlas);

		EGraphicCore::matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3(-1.0f, -1.0f, 0.0f));
		EGraphicCore::matrix_transform = glm::scale(EGraphicCore::matrix_transform, glm::vec3(EGraphicCore::correction_x * 1.0f, EGraphicCore::correction_y * 1.0f, 1.0f));
		transformLoc = glGetUniformLocation(EGraphicCore::ourShader->ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));

		EGraphicCore::batch->setcolor_lum(EColor::COLOR_WHITE, 0.1f);
		EGraphicCore::batch->draw_gabarite(EGraphicCore::SCR_WIDTH - 168.0f, 8.0f, 160.0f, 150.0f, EGraphicCore::gabarite_white_pixel);

		EGraphicCore::batch->setcolor_lum(EColor::COLOR_WHITE, 0.9f);
		EFont::active_font->draw(EGraphicCore::batch, "Cluster start draw (x): " + std::to_string(cluster_draw_start_x), EGraphicCore::SCR_WIDTH - 165.0f, 100.0f);
		EFont::active_font->draw(EGraphicCore::batch, "Cluster end draw (x): " + std::to_string(cluster_draw_end_x), EGraphicCore::SCR_WIDTH - 165.0f, 100.0f - 15.0f);
		EFont::active_font->draw(EGraphicCore::batch, "Cluster start draw (y): " + std::to_string(cluster_draw_start_y), EGraphicCore::SCR_WIDTH - 165.0f, 100.0f - 30.0f);
		EFont::active_font->draw(EGraphicCore::batch, "Cluster end draw (y): " + std::to_string(cluster_draw_end_y), EGraphicCore::SCR_WIDTH - 165.0f, 100.0f - 45.0f);

		EGraphicCore::batch->force_draw_call();
	}
}

void EWindowMain::update(float _d)
{
	
	EWindow::add_time_process("===--- update begin ---===");
	if (_d > 0.1) { _d = 0.1f; }

	cluster_draw_start_x = floor((*main_camera->position_x - EGraphicCore::SCR_WIDTH / 2.0f) / *main_camera->zoom / ECluster::CLUSTER_SIZE_X) - 1; cluster_draw_start_x = max(cluster_draw_start_x, 0);
	cluster_draw_start_y = floor((*main_camera->position_y - EGraphicCore::SCR_HEIGHT / 2.0f) / *main_camera->zoom / ECluster::CLUSTER_SIZE_Y) - 1; cluster_draw_start_y = max(cluster_draw_start_y, 0);

	cluster_draw_end_x = floor((*main_camera->position_x + EGraphicCore::SCR_WIDTH / 2.0f) / *main_camera->zoom / ECluster::CLUSTER_SIZE_X) + 1; cluster_draw_end_x = min(cluster_draw_end_x, ECluster::CLUSTED_DIM_X - 1);
	cluster_draw_end_y = floor((*main_camera->position_y + EGraphicCore::SCR_HEIGHT / 2.0f) / *main_camera->zoom / ECluster::CLUSTER_SIZE_Y) + 1; cluster_draw_end_y = min(cluster_draw_end_y, ECluster::CLUSTED_DIM_Y - 1);




	terrain_draw_start_x	= floor((*main_camera->position_x - EGraphicCore::SCR_WIDTH / 2.0f)		/ *main_camera->zoom / 40.0f) - 1; terrain_draw_start_x	= max(terrain_draw_start_x, 0);
	terrain_draw_start_y	= floor((*main_camera->position_y - EGraphicCore::SCR_HEIGHT / 2.0f)	/ *main_camera->zoom / 40.0f) - 1; terrain_draw_start_y	= max(terrain_draw_start_y, 0);
																																	   
	terrain_draw_end_x		= floor((*main_camera->position_x + EGraphicCore::SCR_WIDTH / 2.0f)		/ *main_camera->zoom / 40.0f) + 1; terrain_draw_end_x	= min(terrain_draw_end_x, TILES_COUNT_X - 1);
	terrain_draw_end_y		= floor((*main_camera->position_y + EGraphicCore::SCR_HEIGHT / 2.0f)	/ *main_camera->zoom / 40.0f) + 1; terrain_draw_end_y	= min(terrain_draw_end_y, TILES_COUNT_Y - 1);

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

		if (!selected_entities.empty())
		{
			
			*super_group_autobuilding->is_active = true;
			ExternalButtonAction::external_button_action_select_entity_from_list(group_grid_entity_list_link->button_list.at(0), 0.1f);
		}
		else
		{
			*super_group_autobuilding->is_active = false;
		}
	}
	else
	{
		*entity_selection_region->size_x = 0.0f;
		*entity_selection_region->size_y = 0.0f;

		*entity_selection_region->position_x = 0.0f;
		*entity_selection_region->position_y = 0.0f;

		is_entity_selection_started = false;
	}

	//*main_camera->speed_x = 0.0f;
	//*main_camera->speed_y = 0.0f;
	*main_camera->speed_x /= pow(1000.0f, _d);
	*main_camera->speed_y /= pow(1000.0f, _d);



	//if (!key_pressed_array[GLFW_KEY_W]) { std::cout << "YOU FUCKING DOLBOYOB?[camera control]" << std::endl; }
	if (EWindow::operable_button == NULL)
	{

		//if (!key_pressed_array[GLFW_KEY_W]) { std::cout << &key_pressed_array[GLFW_KEY_W] << std::endl; }


		if (key_pressed_array[GLFW_KEY_W])		{ *main_camera->speed_y = round(1000.0f);	}
		if (key_pressed_array[GLFW_KEY_S])		{ *main_camera->speed_y = round(-1000.0f);	}

		if (key_pressed_array[GLFW_KEY_D])		{ *main_camera->speed_x = round(1000.0f);	}
		if (key_pressed_array[GLFW_KEY_A])		{ *main_camera->speed_x = round(-1000.0f);	}
	}

	if (!key_pressed_array[GLFW_KEY_LEFT_SHIFT])
	{
		*main_camera->position_x += (*main_camera->speed_x * _d);
		*main_camera->position_y += (*main_camera->speed_y * _d);
	}
	else
	{
		*main_camera->position_x += (*main_camera->speed_x * _d * 0.1f);
		*main_camera->position_y += (*main_camera->speed_y * _d * 0.1f);
	}


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

	bool any_catch = false;

	Entity::AutobuildingGroupElement* last_matched_element = NULL;

	for (Entity* e : _v)
	{
		for (Entity::AutobuildingGroup* a_group : e->autobuilding_group_list)
		{

			if
				(
					(ExternalButtonAction::get_selected_autobuilding_group(e) != NULL)
					&&
					(ExternalButtonAction::get_selected_autobuilding_group(e) == a_group)
					&&
					(get_real_world_position_x_by_mouse(main_camera) >= *e->position_x + *a_group->offset_x + *a_group->pseudo_pos_x)
					&&
					(get_real_world_position_x_by_mouse(main_camera) <= *e->position_x + *a_group->offset_x + *a_group->pseudo_pos_x + *a_group->pseudo_size_x)
					&&
					(get_real_world_position_y_by_mouse(main_camera) >= *e->position_y + *e->position_z + *a_group->offset_y + *a_group->offset_z - 20.0f)
					&&
					(get_real_world_position_y_by_mouse(main_camera) <= *e->position_y + *e->position_z + *a_group->offset_y + *a_group->offset_z - 0.0f)
				)
			{
				if (!LMB) { *a_group->is_catched = true; any_catch = true; }
			}
			else
			{
				if (!LMB) { *a_group->is_catched = false; }
			}

			

			//catches
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
				//any_catch = false;


				//if valid group element, group, and entity
				if
					(
						(
							(
								(ExternalButtonAction::get_selected_autobuilding_group_element(e) != NULL)
								&&
								(ExternalButtonAction::get_selected_autobuilding_group_element(e) == a_element)
								&&
								(ExternalButtonAction::get_selected_autobuilding_group(e) != NULL)
								&&
								(ExternalButtonAction::get_selected_autobuilding_group(e) == a_group)
							)
							||
							(ExternalButtonAction::get_selected_autobuilding_group_element(e) == NULL)
							||
							(glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_ALT) != GLFW_PRESS)
						)
						&&
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

					//left
					//prevert overlap gabarites and group border, for up/down/left/right
					{
						if
							(
								(get_real_world_position_x_by_mouse(main_camera) >= *e->position_x + *a_group->offset_x + *a_element->offset_x - catch_size)
								&&
								(get_real_world_position_x_by_mouse(main_camera) <= *e->position_x + *a_group->offset_x + *a_element->offset_x + catch_size)
								&&
								(get_real_world_position_y_by_mouse(main_camera) >= *e->position_y + *e->position_z + *a_group->offset_y + *a_group->offset_z + *a_element->offset_y + *a_element->offset_z - catch_size)
								&&
								(get_real_world_position_y_by_mouse(main_camera) <= *e->position_y + *e->position_z + *a_group->offset_y + *a_group->offset_z + *a_element->offset_y + *a_element->size_y + *a_element->offset_z + catch_size)
							)
						{
							if (!LMB) { *a_element->catched_left_side = true; any_catch = true; *a_group->is_catched = false; }
						}
						else
						{
							if (!LMB) { *a_element->catched_left_side = false; }
						}

						//right
						if
							(
								(get_real_world_position_x_by_mouse(main_camera) >= *e->position_x + *a_group->offset_x + *a_element->offset_x + *a_element->size_x - catch_size)
								&&
								(get_real_world_position_x_by_mouse(main_camera) <= *e->position_x + *a_group->offset_x + *a_element->offset_x + *a_element->size_x + catch_size)
								&&
								(get_real_world_position_y_by_mouse(main_camera) >= *e->position_y + *e->position_z + *a_group->offset_y + *a_group->offset_z + *a_element->offset_y + *a_element->offset_z - catch_size)
								&&
								(get_real_world_position_y_by_mouse(main_camera) <= *e->position_y + *e->position_z + *a_group->offset_y + *a_group->offset_z + *a_element->offset_y + *a_element->size_y + *a_element->offset_z + catch_size)
								)
						{
							if (!LMB) { *a_element->catched_right_side = true; any_catch = true; *a_group->is_catched = false;}
						}
						else
						{
							if (!LMB) { *a_element->catched_right_side = false; }
						}

						//down
						if
							(
								(get_real_world_position_x_by_mouse(main_camera) >= *e->position_x + *a_group->offset_x + *a_element->offset_x - catch_size)
								&&
								(get_real_world_position_x_by_mouse(main_camera) <= *e->position_x + *a_group->offset_x + *a_element->offset_x + *a_element->size_x + catch_size)
								&&
								(get_real_world_position_y_by_mouse(main_camera) >= *e->position_y + *e->position_z + *a_group->offset_y + *a_group->offset_z + *a_element->offset_y + *a_element->offset_z - catch_size)
								&&
								(get_real_world_position_y_by_mouse(main_camera) <= *e->position_y + *e->position_z + *a_group->offset_y + *a_group->offset_z + *a_element->offset_y + *a_element->offset_z + catch_size)
								)
						{
							if (!LMB) { *a_element->catched_down_side = true; any_catch = true; *a_group->is_catched = false;}
						}
						else
						{
							if (!LMB) { *a_element->catched_down_side = false; }
						}

						//up
						if
							(
								(get_real_world_position_x_by_mouse(main_camera) >= *e->position_x + *a_group->offset_x + *a_element->offset_x - catch_size)
								&&
								(get_real_world_position_x_by_mouse(main_camera) <= *e->position_x + *a_group->offset_x + *a_element->offset_x + *a_element->size_x + catch_size)
								&&
								(get_real_world_position_y_by_mouse(main_camera) >= *e->position_y + *e->position_z + *a_group->offset_y + *a_group->offset_z + *a_element->offset_y + *a_element->size_y + *a_element->offset_z - catch_size)
								&&
								(get_real_world_position_y_by_mouse(main_camera) <= *e->position_y + *e->position_z + *a_group->offset_y + *a_group->offset_z + *a_element->offset_y + *a_element->size_y + *a_element->offset_z + catch_size)
								)
						{
							if (!LMB) { *a_element->catched_up_side = true; any_catch = true; *a_group->is_catched = false;}
						}
						else
						{
							if (!LMB) { *a_element->catched_up_side = false; }
						}
					}


					//mid
					if
						(
							(get_real_world_position_x_by_mouse(main_camera) >= *e->position_x + *a_group->offset_x + *a_element->offset_x + *a_element->size_x / 2.0f - 10.0f)
							&&
							(get_real_world_position_x_by_mouse(main_camera) <= *e->position_x + *a_group->offset_x + *a_element->offset_x + *a_element->size_x / 2.0f + 10.0f)
							&&
							(get_real_world_position_y_by_mouse(main_camera) >= *e->position_y + *e->position_z + *a_group->offset_y + *a_group->offset_z + *a_element->offset_y + *a_element->offset_z + *a_element->size_y / 2.0f - 10.0f)
							&&
							(get_real_world_position_y_by_mouse(main_camera) <= *e->position_y + *e->position_z + *a_group->offset_y + *a_group->offset_z + *a_element->offset_y + *a_element->offset_z + *a_element->size_y / 2.0f + 10.0f)
						)
					{
						if (!LMB) { *a_element->catched_mid = true; any_catch = true; *a_group->is_catched = false;}
					}
					else
					{
						if (!LMB) { *a_element->catched_mid = false; }
					}

					//z
					if
						(
							(get_real_world_position_x_by_mouse(main_camera) >= *e->position_x + *a_group->offset_x + *a_element->offset_x + *a_element->size_x / 2.0f - 5.0f)
							&&
							(get_real_world_position_x_by_mouse(main_camera) <= *e->position_x + *a_group->offset_x + *a_element->offset_x + *a_element->size_x / 2.0f + 5.0f)
							&&
							(get_real_world_position_y_by_mouse(main_camera) >= *e->position_y + *e->position_z + *a_group->offset_y + *a_group->offset_z + *a_element->offset_y + *a_element->offset_z + *a_element->size_y / 2.0f + 10.0f)
							&&
							(get_real_world_position_y_by_mouse(main_camera) <= *e->position_y + *e->position_z + *a_group->offset_y + *a_group->offset_z + *a_element->offset_y + *a_element->offset_z + *a_element->size_y / 2.0f + 40.0f)
						)
					{
						if (!LMB) { *a_element->catched_z = true; any_catch = true;}
					}
					else
					{
						if (!LMB) { *a_element->catched_z = false; }
					}

					if (LMB)
					{
						if (*a_element->catched_left_side)
						{
							any_catch = true;
							*a_element->size_x -= mouse_speed_x / *main_camera->zoom;
							*a_element->offset_x += mouse_speed_x / *main_camera->zoom;

							//generate_building(e);
						}

						if (*a_element->catched_right_side)
						{
							any_catch = true;
							*a_element->size_x += mouse_speed_x / *main_camera->zoom;
							//*a_element->offset_x += mouse_speed_x / *main_camera->zoom;
							//generate_building(e);
						}

						if (*a_element->catched_down_side)
						{
							any_catch = true;
							*a_element->size_y -= mouse_speed_y / *main_camera->zoom;
							*a_element->offset_y += mouse_speed_y / *main_camera->zoom;

							//generate_building(e);
						}

						if (*a_element->catched_up_side)
						{
							any_catch = true;
							*a_element->size_y += mouse_speed_y / *main_camera->zoom;
							//*a_element->offset_x += mouse_speed_x / *main_camera->zoom;
							//generate_building(e);
						}

						if (*a_element->catched_mid)
						{
							any_catch = true;
							*a_element->offset_x += mouse_speed_x / *main_camera->zoom;
							*a_element->offset_y += mouse_speed_y / *main_camera->zoom;
							//*a_element->offset_x += mouse_speed_x / *main_camera->zoom;
							//generate_building(e);
						}

						if (*a_element->catched_z)
						{
							any_catch = true;
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

			//group catch can be overcatched by side borders
			if (*a_group->is_catched)
			{
				if (LMB)
				{
					any_catch = true;

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
			

			//select element by group
			for (Entity::AutobuildingGroupElement* a_element : a_group->autobuilding_group_element_list)
			{
				if
					(
						(LMB)
						&&
						(glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_ALT) != GLFW_PRESS)
						&&
						(!any_catch)
						&&
						(EWindow::top_overlaped_group == NULL)
						&&
						(EWindow::operable_button == NULL)
						&&
						(get_real_world_position_x_by_mouse(main_camera) >= *e->position_x + *a_group->offset_x + *a_element->offset_x)
						&&
						(get_real_world_position_x_by_mouse(main_camera) <= *e->position_x + *a_group->offset_x + *a_element->offset_x + *a_element->size_x)
						&&
						(get_real_world_position_y_by_mouse(main_camera) >= *e->position_y + *a_group->offset_y + *a_element->offset_y + *e->position_z + *a_group->offset_z + *a_element->offset_z)
						&&
						(get_real_world_position_y_by_mouse(main_camera) <= *e->position_y + *a_group->offset_y + *a_element->offset_y + *e->position_z + *a_group->offset_z + *a_element->offset_z + *a_element->size_y)
						&&
						(
							(
								(last_matched_element != NULL)
								&&
								(
									pow
									(get_real_world_position_x_by_mouse(main_camera) - (*e->position_x + *last_matched_element->offset_x + *last_matched_element->master_group->offset_x + *last_matched_element->size_x / 2.0f), 2)
									+
									pow
									(
										get_real_world_position_y_by_mouse(main_camera)
										-
										(
											*e->position_y + *last_matched_element->offset_y + *last_matched_element->master_group->offset_y
											+
											*e->position_z + *last_matched_element->offset_z + *last_matched_element->master_group->offset_z
											+
											*last_matched_element->size_y / 2.0f
											), 2
									)

									>

									pow
									(get_real_world_position_x_by_mouse(main_camera) - (*e->position_x + *a_element->offset_x + *a_element->master_group->offset_x + *a_element->size_x / 2.0f), 2)
									+
									pow
									(
										get_real_world_position_y_by_mouse(main_camera)
										-
										(
											*e->position_y + *a_element->offset_y + *a_element->master_group->offset_y
											+
											*e->position_z + *a_element->offset_z + *a_element->master_group->offset_z
											+
											*a_element->size_y / 2.0f
											), 2
									)
								)
							)
							||
							(last_matched_element == NULL)
							//||
							//(true)
							)
						)
				{
					last_matched_element = a_element; //*a_element->offset_x += 1.0f;
				}
			}

		
	}

	if (last_matched_element != NULL)
	{
		int id = 0;

		for (Entity::AutobuildingGroup* group : e->autobuilding_group_list)
		{
			if (group == last_matched_element->master_group)
			{
				EWindowMain::button_group_autobuilding_group->selected_button = EWindowMain::button_group_autobuilding_group->button_list.at(id);
				ExternalButtonAction::external_button_action_select_autobuilding_group(EWindowMain::button_group_autobuilding_group->button_list.at(id), 0.1f);
			}

			id++;
		}

		id = 0;

		for (Entity::AutobuildingGroupElement* ele : last_matched_element->master_group->autobuilding_group_element_list)
		{
			if (ele == last_matched_element)
			{
				//EWindowMain::button_group_autobuilding_group_element->selected_button = EWindowMain::button_group_autobuilding_group_element->button_list.at(id);
				EWindowMain::button_group_autobuilding_group_element->selected_button = EWindowMain::button_group_autobuilding_group_element->button_list.at(id);

				ExternalButtonAction::external_button_action_select_autobuilding_group_element(EWindowMain::button_group_autobuilding_group_element->button_list.at(id), 0.1f);
			}

			id++;
		}

	}
		}
}

void EWindowMain::reset_render()
{
	EGraphicCore::sun_zenith_factor = abs(EGraphicCore::sun_position_y - 0.66f) * 3.0f;
	EGraphicCore::sun_zenith_factor = (1.0f - EGraphicCore::sun_zenith_factor) * 2.0f;
	EMath::clamp_value_float(&EGraphicCore::sun_zenith_factor, 0.0f, 1.0f);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	



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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);

	float
		sun_zenith_factor_sun = abs(EGraphicCore::sun_position_y - 0.66f) * 3.0f;
	sun_zenith_factor_sun = (1.0f - sun_zenith_factor_sun) * 2.0f;
	EMath::clamp_value_float(&sun_zenith_factor_sun, 0.0f, 1.0f);

	//sky
	EGraphicCore::batch->setcolor
	(
		sqrt(EGraphicCore::sun_zenith_factor) * EGraphicCore::sky_lum,
		EGraphicCore::sun_zenith_factor * EGraphicCore::sky_lum,
		EGraphicCore::sun_zenith_factor * EGraphicCore::sun_zenith_factor * EGraphicCore::sky_lum,
		1.0f
	);
	EGraphicCore::batch->draw_gabarite(0.0f, 0.0f, 1.0f, 1.0f, EGraphicCore::gabarite_sky);



	//sun
	EGraphicCore::batch->setcolor
	(
		1.0f * 1.0f * sqrt(sun_zenith_factor_sun),
		0.8f * 1.0f * sun_zenith_factor_sun,
		0.5f * 1.0f * sun_zenith_factor_sun * sun_zenith_factor_sun,
		1.0f
	);


	EGraphicCore::batch->draw_gabarite
	(
		(EGraphicCore::sun_position_x * 2.0f - 0.5f) - EGraphicCore::sun_size * 0.25f,
		(EGraphicCore::sun_position_y * 2.0f - 0.5f) - EGraphicCore::sun_size * 0.5f,
		EGraphicCore::sun_size * 0.5f,
		EGraphicCore::sun_size,
		EGraphicCore::gabarite_sun
	);

	//ground (grass)
	//EGraphicCore::batch->setcolor(0.85f * EGraphicCore::ground_lum, 0.80f * EGraphicCore::ground_lum, 0.75f * EGraphicCore::ground_lum, 1.0f);
	//EGraphicCore::batch->draw_gabarite(0.0f, 0.0f, 1.0f, 0.45f, EGraphicCore::gabarite_white_pixel

	EGraphicCore::batch->setcolor
	(
		sqrt(EGraphicCore::sun_zenith_factor) * EGraphicCore::sky_lum,
		EGraphicCore::sun_zenith_factor * EGraphicCore::sky_lum,
		EGraphicCore::sun_zenith_factor * EGraphicCore::sun_zenith_factor * EGraphicCore::sky_lum,
		1.0f
	);
	EGraphicCore::batch->draw_gabarite(0.0f - *main_camera->position_x / 100000.0f, 0.0f, 1.0f, 0.5f, EGraphicCore::gabarite_panorama);
	EGraphicCore::batch->force_draw_call();

	EGraphicCore::simple_blur->use();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);
	transformLoc = glGetUniformLocation(EGraphicCore::simple_blur->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));



	EGraphicCore::batch->setcolor(EColor::COLOR_WHITE);

	//blur skydome
	for (int i = 0; i < skydome_texture_levels - 1; i++)
	{
		glUniform1f(glGetUniformLocation(EGraphicCore::simple_blur->ID, "blur_size_x"), (1.0f / skydome_light_FBO[i]->size_x) * (EGraphicCore::blur_size_buffer));
		glUniform1f(glGetUniformLocation(EGraphicCore::simple_blur->ID, "blur_size_y"), (1.0f / skydome_light_FBO[i]->size_y) * (EGraphicCore::blur_size_buffer));
		ETextureAtlas::draw_to_this_FBO(EWindow::skydome_light_FBO_buffer[i + 1], EWindow::skydome_light_FBO[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//
		EGraphicCore::batch->draw_rect(0.0f, 0.0f, 1.0f, 1.0f);
		EGraphicCore::batch->force_draw_call();

		glUniform1f(glGetUniformLocation(EGraphicCore::simple_blur->ID, "blur_size_x"), (1.0f / skydome_light_FBO[i]->size_x) * (EGraphicCore::blur_size));
		glUniform1f(glGetUniformLocation(EGraphicCore::simple_blur->ID, "blur_size_y"), (1.0f / skydome_light_FBO[i]->size_y) * (EGraphicCore::blur_size));
		ETextureAtlas::draw_to_this_FBO(EWindow::skydome_light_FBO[i + 1], EWindow::skydome_light_FBO_buffer[i + 1]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//
		EGraphicCore::batch->draw_rect(0.0f, 0.0f, 1.0f, 1.0f);
		EGraphicCore::batch->force_draw_call();
	}

	EWindow::add_time_process("Prepare skydome reflection");

	draw_terrain();
	
	/*
	
	GENERATE AO SHADOW
	
	*/

	

	generate_AO_shadow();

	EWindow::add_time_process("Generate AO shadow");
	
	
	

	EGraphicCore::simple_blur->use();
	ETextureAtlas::set_this_FBO_as_active(EWindow::AO_shadow_FBO);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_ZERO, GL_SRC_COLOR);
	glBlendEquationSeparate(GL_FUNC_ADD, GL_MAX);

				EGraphicCore::matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
				EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3(-1.0f, -1.0f, 0.0f));
				EGraphicCore::matrix_transform = glm::scale(EGraphicCore::matrix_transform, glm::vec3(1.0f, 1.0f, 1.0f));
				transformLoc = glGetUniformLocation(EGraphicCore::simple_blur->ID, "transform");
				glUniform1f(glGetUniformLocation(EGraphicCore::simple_blur->ID, "blur_size_x"), (1.0f / EWindow::AO_shadow_FBO->size_x));
				glUniform1f(glGetUniformLocation(EGraphicCore::simple_blur->ID, "blur_size_y"), (1.0f / EWindow::AO_shadow_FBO->size_y));
				glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));

				
				EGraphicCore::batch->setcolor_alpha(EColor::COLOR_WHITE, 1.0f);
				//EGraphicCore::batch->setcolor(0.8, 0.9f, 1.0f, 1.0f);
				EGraphicCore::batch->draw_rect(0.0f, 0.0f, 2.0f, 2.0f);
				EGraphicCore::batch->reinit();
				EGraphicCore::batch->draw_call();
				EGraphicCore::batch->reset();

		EWindow::add_time_process("Draw AO shadow");
	
		


	EGraphicCore::ourShader->use();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);
	ETextureAtlas::set_this_FBO_as_active(EWindow::default_texture_atlas);

	EGraphicCore::matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3(-1.0f - EGraphicCore::correction_x / 2.0f * 0.0f + round(EGraphicCore::SCR_WIDTH / 2.0f - *main_camera->position_x) * EGraphicCore::correction_x, -1.0f - EGraphicCore::correction_y / 2.0f * 0.0f + round(EGraphicCore::SCR_HEIGHT / 2.0f - *main_camera->position_y) * EGraphicCore::correction_y, 0.0f));
	EGraphicCore::matrix_transform = glm::scale(EGraphicCore::matrix_transform, glm::vec3(EGraphicCore::correction_x * *main_camera->zoom, EGraphicCore::correction_y * *main_camera->zoom, 1.0f));
	transformLoc = glGetUniformLocation(EGraphicCore::ourShader->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));

}

void EWindowMain::draw_terrain()
{
	ETextureAtlas::set_this_FBO_as_active(EWindow::default_texture_atlas);
	glEnable(GL_BLEND);
	//glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);
	

	EGraphicCore::PBR_shader->use();


	EGraphicCore::matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	EGraphicCore::matrix_transform = glm::translate
	(
		EGraphicCore::matrix_transform,
		glm::vec3
		(
			-1.0f + round(EGraphicCore::SCR_WIDTH / 2.0f - *main_camera->position_x) * EGraphicCore::correction_x,
			-1.0f + round(EGraphicCore::SCR_HEIGHT / 2.0f - *main_camera->position_y) * EGraphicCore::correction_y,
			-1.0f
		)
	);

	EGraphicCore::matrix_transform = glm::scale
	(
		EGraphicCore::matrix_transform,
		glm::vec3
		(
			EGraphicCore::correction_x * *main_camera->zoom,
			EGraphicCore::correction_y * *main_camera->zoom,
			EGraphicCore::correction_y * *main_camera->zoom
		)
	);

	transformLoc = glGetUniformLocation(EGraphicCore::PBR_shader->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));
	float true_height = 0.0f;

	glUniform1f(glGetUniformLocation(EGraphicCore::PBR_shader->ID, "brightness_multiplier"), EGraphicCore::brightness_multiplier);

	glUniform1f(glGetUniformLocation(EGraphicCore::PBR_shader->ID, "input_gloss"), EGraphicCore::gloss_input);

	glUniform1f(glGetUniformLocation(EGraphicCore::PBR_shader->ID, "sun_position_x"), EGraphicCore::sun_position_x);
	glUniform1f(glGetUniformLocation(EGraphicCore::PBR_shader->ID, "sun_position_y"), EGraphicCore::sun_position_y);


	glUniform1f(glGetUniformLocation(EGraphicCore::PBR_shader->ID, "sun_zenith"), EGraphicCore::sun_zenith_factor);

	glUniform1f(glGetUniformLocation(EGraphicCore::PBR_shader->ID, "screen_offset_x"), -*main_camera->position_x + EGraphicCore::SCR_WIDTH / 2.0f);
	glUniform1f(glGetUniformLocation(EGraphicCore::PBR_shader->ID, "screen_offset_y"), -*main_camera->position_y + EGraphicCore::SCR_HEIGHT / 2.0f);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, EWindow::default_texture_atlas->colorbuffer);
	EGraphicCore::PBR_shader->setInt("texture1", 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glActiveTexture(GL_TEXTURE1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, EWindow::default_texture_atlas->colorbuffer);
	EGraphicCore::PBR_shader->setInt("normal_gloss_map_texture", 1);


	for (int i = 0; i < skydome_texture_levels; i++)
	{
		glActiveTexture(GL_TEXTURE2 + i);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_2D, EWindow::skydome_light_FBO[i]->colorbuffer);//1
		EGraphicCore::PBR_shader->setInt("SD_array[" + std::to_string(i) + "]", i + 2);
	}

	/*
	glActiveTexture(GL_TEXTURE7);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, EWindow::skydome_light_FBO[5]->colorbuffer);//1/32
	EGraphicCore::PBR_shader->setInt("SD_array[5]", 7);*/



	EGraphicCore::batch_PBR->setcolor(EColor::COLOR_WHITE);
	EGraphicCore::batch_PBR->reset();
	if (key_pressed_array[GLFW_KEY_LEFT_SHIFT])
	{
			for (int i = terrain_draw_start_y; i <= terrain_draw_end_y; i++)
			for (int j = terrain_draw_start_x; j <= terrain_draw_end_x; j++)
			{

				if (terrain_matrix[j][i] != NULL)
				{
					EGraphicCore::batch_PBR->draw_terrain_PBR
					(
						j * 40.0f,
						i * 40.0f,
						0.0f,

						*terrain_matrix[j][i]->size_x,
						*terrain_matrix[j][i]->size_y,
						0.0f,

						*terrain_matrix[j][i]->texture_offset_x,
						*terrain_matrix[j][i]->texture_offset_y,

						terrain_matrix[j][i]->terrain_texture,
						terrain_matrix[j][i]->normal_gloss_texture,

						0.0f
					);
				}
				else
				{
					std::cout << "DOLBOYOB?" << " [" << std::to_string(j) << "][" << std::to_string(i) << "]" << std::endl;
				}
			}

			EGraphicCore::batch_PBR->force_draw_call_PBR();
	}
	else
	{
		for (int j = cluster_draw_start_x; j <= cluster_draw_end_x; j++)
		{
			for (int i = cluster_draw_start_y; i <= cluster_draw_end_y; i++)
			{

				std::copy
				(
					std::begin(cluster_static[j][i]->terrain_vertex_data_buffer),
					std::end(cluster_static[j][i]->terrain_vertex_data_buffer),
					std::begin(EGraphicCore::batch_PBR->vertices) + EGraphicCore::batch_PBR->id
				);

				EGraphicCore::batch_PBR->id += 52 * 25;

				if (EGraphicCore::batch_PBR->id > 25000)
				{
					//logger_param("forceful drawcall PBR, because vertices data more than 25000", EGraphicCore::batch_PBR->id);
					EGraphicCore::batch_PBR->force_draw_call_PBR();
					//EWindow::add_time_process("Draw terrain force draw call [" + std::to_string(i) + "]");
				}
			}

			//logger_param("last_id", EGraphicCore::batch_PBR->id);

			
		}

		
		EGraphicCore::batch_PBR->force_draw_call_PBR();
	}

	EWindow::add_time_process("Draw terrain draw call");

	//EGraphicCore::batch_PBR->force_draw_call_PBR();
	//EGraphicCore::batch_PBR->reset();


}

void EWindowMain::generate_AO_shadow()
{
	EGraphicCore::AO_shader->use();
		EGraphicCore::matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3(-1.0f + round(EGraphicCore::SCR_WIDTH / 2.0f - *main_camera->position_x) * EGraphicCore::correction_x, -1.0f + round(EGraphicCore::SCR_HEIGHT / 2.0f - *main_camera->position_y) * EGraphicCore::correction_y, 0.0f));
		EGraphicCore::matrix_transform = glm::scale(EGraphicCore::matrix_transform, glm::vec3(EGraphicCore::correction_x * *main_camera->zoom, EGraphicCore::correction_y * *main_camera->zoom, 1.0f));
		transformLoc = glGetUniformLocation(EGraphicCore::AO_shader->ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));
	EGraphicCore::batch->reset();

	ETextureAtlas::draw_to_this_FBO(EWindow::AO_shadow_FBO, EWindow::default_texture_atlas);


	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	//glBlendEquation(GL_FUNC_ADD);
	//glBlendEquation(GL_MIN);
	glBlendEquationSeparate(GL_MIN, GL_MAX);
	//EGraphicCore::batch->setcolor(EColor::COLOR_WHITE);
	//EGraphicCore::batch->draw_gabarite(0.0f, 0.0f, 10000.0f, 10000.0f, EGraphicCore::gabarite_white_pixel);

	EGraphicCore::batch->setcolor(EColor::COLOR_BLACK);

	float z_factor = 0.0f;

	for (int i = cluster_draw_start_y; i <= cluster_draw_end_y; i++)
		for (int j = cluster_draw_start_x; j <= cluster_draw_end_x; j++)
		{
			for (Entity* e : cluster_static[j][i]->entity_list)
				for (Entity::AutobuildingGroup* a_group : e->autobuilding_group_list)
				for (Entity::AutobuildingGroupElement* a_element : a_group->autobuilding_group_element_list)
				{

					if (*a_element->autobuilding_base->selected_sprite_draw_mode == SpriteDrawMode::SPRITE_DRAW_MODE_AO_SHADOW)
					{
						z_factor = 1.0f - (*a_element->offset_z / (*a_element->offset_z + 10.0f));

						//z_factor = 0.0f;
						//z_factor *= z_factor;
						EGraphicCore::batch->setcolor_lum(EColor::COLOR_WHITE, z_factor);

						EGraphicCore::batch->draw_AO_shadow
						(
							*e->position_x + *a_group->offset_x + *a_element->offset_x,
							*e->position_y + *a_group->offset_y + *a_element->offset_y,
							*a_element->size_x,
							*a_element->size_y,
							*a_element->offset_z * 10.0f,
							EGraphicCore::gabarite_white_pixel
						);
					}
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

		if (!selected_entities.empty())
		{
			group_grid_entity_list_link->selected_button = group_grid_entity_list_link->button_list.at(0);
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

		w_string += "autobuilding_base_random_offset";
		w_string += '\t';
		w_string += std::to_string(*a_base->random_space_between_sprite_x);
		w_string += '\t';
		w_string += std::to_string(*a_base->random_space_between_sprite_y);
		w_string += '\n';

		w_string += "autobuilding_selected_sprite_fill_mode";
		w_string += '\t';
		w_string += std::to_string(*a_base->selected_sprite_fill_mode);
		w_string += '\n';

		w_string += "autobuilding_random_sprite_count";
		w_string += '\t';
		w_string += std::to_string(*a_base->random_sprite_count);
		w_string += '\n';


		w_string += "autobuilding_base_selected_draw_mode";
		w_string += '\t';
		w_string += std::to_string(*a_base->selected_sprite_draw_mode);
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


		w_string += "autobuilding_group_seed";
		w_string += '\t';
		w_string += std::to_string(*a_group->seed);
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
				//std::cout << "______created new entity" << endl;
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

				//std::cout << "______created new base" << endl;
			}

			if ((EFile::data_array[i] == "autobuilding_base_main_texture") & (jc_base != NULL))
			{
				i++; jc_base->main_texture = ETextureAtlas::put_texture_to_atlas(EFile::data_array[i], EWindow::default_texture_atlas);

				jc_base->normal_gloss_map_texture = ETextureAtlas::get_normal_gloss_map_from_regular_texture_path(jc_base->main_texture->name, EWindow::default_texture_atlas);
			}

			if ((EFile::data_array[i] == "autobuilding_base_space_between_sprites") & (jc_base != NULL))
			{
				i++; *jc_base->space_between_sprite_x = EMath::to_float(EFile::data_array[i]);
				i++; *jc_base->space_between_sprite_y = EMath::to_float(EFile::data_array[i]);
			}

			if ((EFile::data_array[i] == "autobuilding_base_random_offset") & (jc_base != NULL))
			{
				i++; *jc_base->random_space_between_sprite_x = std::stoi(EFile::data_array[i]);
				i++; *jc_base->random_space_between_sprite_y = std::stoi(EFile::data_array[i]);
			}

			if ((EFile::data_array[i] == "autobuilding_selected_sprite_fill_mode") & (jc_base != NULL))
			{
				i++; *jc_base->selected_sprite_fill_mode = std::stoi(EFile::data_array[i]);
			}

			if ((EFile::data_array[i] == "autobuilding_random_sprite_count") & (jc_base != NULL))
			{
				i++; *jc_base->random_sprite_count = std::stoi(EFile::data_array[i]);
			}

			if ((EFile::data_array[i] == "autobuilding_base_selected_draw_mode") & (jc_base != NULL))
			{
				i++; *jc_base->selected_sprite_draw_mode = std::stoi(EFile::data_array[i]);
			}

			if ((EFile::data_array[i] == "CREATE_NEW_GRID_REGION") & (jc_base != NULL))
			{
				jc_grid_region = new EButton::EGridRegion();
				jc_base->grid_region.push_back(jc_grid_region);

				//std::cout << "______created new grid region" << endl;
			}

			if ((EFile::data_array[i] == "grid_region_position_and_size") & (jc_grid_region != NULL))
			{
				i++; *jc_grid_region->position_x = EMath::to_float(EFile::data_array[i]);	//std::cout << "#_____set grid pos x [" << std::to_string(*jc_grid_region->position_x) << "]" << endl;
				i++; *jc_grid_region->position_y = EMath::to_float(EFile::data_array[i]);	//std::cout << "#_____set grid pos y [" << std::to_string(*jc_grid_region->position_y) << "]" << endl;
				i++; *jc_grid_region->size_x = EMath::to_float(EFile::data_array[i]);		//std::cout << "#_____set grid size x [" << std::to_string(*jc_grid_region->size_x) << "]" << endl;
				i++; *jc_grid_region->size_y = EMath::to_float(EFile::data_array[i]);		//std::cout << "#_____set grid size y [" << std::to_string(*jc_grid_region->size_y) << "]" << endl;
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

				//std::cout << "______created new group" << endl;
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

			if ((EFile::data_array[i] == "autobuilding_group_seed") & (jc_group != NULL))
			{
				i++; *jc_group->seed = std::stoi(EFile::data_array[i]);
			}

			///////////////////////ELEMENT SECTION
			if ((EFile::data_array[i] == "CREATE_NEW_AUTOBUILDING_GROUP_ELEMENT") & (jc_group != NULL))
			{
				jc_group_element = new Entity::AutobuildingGroupElement();
				jc_group->autobuilding_group_element_list.push_back(jc_group_element);

				jc_group_element->master_group = jc_group;

				//std::cout << "______created new group element" << endl;
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

void EWindowMain::draw_vertical_border_element(float _x, float _y, float _z, Entity::AutobuildingGroup* _group, Entity::AutobuildingGroupElement* _element, int _border_enum, float _texture_offset, int _id)
{
	if
		(
			(*_element->autobuilding_base->grid_region.at(_border_enum)->size_x > 0)
			&
			(*_element->autobuilding_base->grid_region.at(_border_enum)->size_y > 0)
			//(*a_element->autobuilding_texture_region->texture_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_DOWN)->size_y > 0)
		)
	{
		subdivision_x_count = *_element->autobuilding_base->grid_region.at(GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_MID)->subdivision_x;
		subdivision_y_count = *_element->autobuilding_base->grid_region.at(_border_enum)->subdivision_y;

		wall_full_size_x = round((*_element->autobuilding_base->grid_region.at(_border_enum)->size_x) / (subdivision_x_count + 1.0f));
		wall_full_size_y = round((*_element->autobuilding_base->grid_region.at(_border_enum)->size_y) / (subdivision_y_count + 1.0f));



		//mid_wall_copies_y = 1.0f;

		fragment_correction_factor_x = wall_full_size_x / (wall_full_size_x + *_element->autobuilding_base->space_between_sprite_x);
		fragment_correction_factor_y = 1.0f;

		for (int yy = 0; yy < ceil(1.0f); yy++)
			//for (int xx = 0; xx < ceil(mid_wall_copies_x); xx++)
			{
				add_new_sprite_to_group_if_need(selected_sprite_id, _group, "bottom");

				selected_sprite = _group->sprite_list.at(selected_sprite_id);
				EGraphicCore::reset_sprite_data(selected_sprite);

				wall_fragment_x = min(1.0f, (mid_wall_copies_x + 0.0f - _id) / fragment_correction_factor_x);
				wall_fragment_y = min(1.0f, (1.0f + 0.0f - yy) / fragment_correction_factor_y);

				//*selected_sprite->offset_x = *_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT)->size_x;
				*selected_sprite->offset_x = _x;
				*selected_sprite->offset_x += _id * (wall_full_size_x + *_element->autobuilding_base->space_between_sprite_x) + *_group->offset_x + *_element->offset_x;

				if (*_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_WALL_Z)
				{
					*selected_sprite->offset_y = _y;
					//*selected_sprite->offset_y += *_group->offset_y + *_element->offset_y;

					*selected_sprite->offset_z = _z;
					*selected_sprite->offset_z += yy * (wall_full_size_y + *_element->autobuilding_base->space_between_sprite_y);
					*selected_sprite->size_z = round(wall_full_size_y * wall_fragment_y);
				}

				if (*_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_ROOF_Y)
				{
					*selected_sprite->offset_z = _z;
					//*selected_sprite->offset_z += *_group->offset_z + *_element->offset_z;

					*selected_sprite->offset_y = _y;
					*selected_sprite->offset_y += yy * (wall_full_size_y + *_element->autobuilding_base->space_between_sprite_y);
					*selected_sprite->size_y = round(wall_full_size_y * wall_fragment_y);
				}


				convert_size_to_fragment
				(
					_element->autobuilding_base->main_texture,
					round(*_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT)->size_x + (wall_full_size_x * (rand() % (subdivision_x_count + 1)))),
					round(_texture_offset + wall_full_size_y * (rand() % (subdivision_y_count + 1))),
					round(wall_full_size_x * wall_fragment_x),
					round(wall_full_size_y * wall_fragment_y),
					selected_sprite->fragment_left,
					selected_sprite->fragment_right,
					selected_sprite->fragment_down,
					selected_sprite->fragment_up
				);

				*selected_sprite->size_x = round(wall_full_size_x * wall_fragment_x);


				selected_sprite->texture_gabarite = _element->autobuilding_base->main_texture;
				selected_sprite->normal_gloss_map_gabarite = _element->autobuilding_base->normal_gloss_map_texture;

				selected_sprite_id++;
			}
	}
}

/*
void EWindowMain::draw_vertical_border_element(float _x, float _y)
{
}
*/

void EWindowMain::add_new_sprite_if_need(int _i, Entity* _e, std::string _text)
{
	if (_i >= _e->entity_sprite_array->sprite_list.size())
	{
		EGraphicCore::ESprite* jcs = new EGraphicCore::ESprite();
		_e->entity_sprite_array->sprite_list.push_back(jcs);

		//std::cout << "create new sprite (" << _text << "), new size of sprites is [" << std::to_string(_e->entity_sprite_array->sprite_list.size()) << "]" << std::endl;
	}
}

void EWindowMain::add_new_sprite_to_group_if_need(int _i, Entity::AutobuildingGroup* _gr, std::string _text)
{
	if (_i >= _gr->sprite_list.size())
	{
		EGraphicCore::ESprite* jcs = new EGraphicCore::ESprite();
		_gr->sprite_list.push_back(jcs);

		//std::cout << "create new sprite to group (" << _text << "), new size of sprites is [" << std::to_string(_gr->sprite_list.size()) << "]" << std::endl;
	}
}

void EWindowMain::generate_building(Entity* _e)
{
	selected_sprite					= NULL;
	selected_sprite_id				= 0;

	 mid_wall_copies_x				= 0.0f;
	 mid_wall_copies_y				= 0.0f;

	 wall_full_size_x				= 0.0f;
	 wall_full_size_y				= 0.0f;

	 wall_fragment_x				= 0.0f;
	 wall_fragment_y				= 0.0f;

	 fragment_correction_factor_x	= 1.0f;
	 fragment_correction_factor_y	= 1.0f;

	 subdivision_x_count			= 0;
	 subdivision_y_count			= 0;

	for (Entity::AutobuildingGroup* a_group : _e->autobuilding_group_list)
	{
		/*for (EGraphicCore::ESprite* spr : a_group->sprite_list)
		{
			EGraphicCore::reset_sprite_data(spr);
		}*/

		selected_sprite_id = 0;
		srand(*a_group->seed);
		//srand(time(NULL)

		*a_group->bottom_offset = 9999.0f;
		*a_group->up_offset = -9000.0f;

		*a_group->max_height = 10.0;

		*a_group->pseudo_pos_x = 10000.0f;
		*a_group->pseudo_pos_x2 = -10000.0f;
		*a_group->pseudo_size_x = 0.0f;

		*a_group->pseudo_pos_y = 10000.0f;
		*a_group->pseudo_pos_y = -10000.0f;
		*a_group->pseudo_size_y = 0.0f;

		*a_group->pseudo_pos_z = 10000.0f;
		*a_group->pseudo_pos_z = -10000.0f;
		*a_group->pseudo_size_z = 0.0f;

		for (Entity::AutobuildingGroupElement* a_element : a_group->autobuilding_group_element_list)
		if (*a_element->autobuilding_base->selected_sprite_draw_mode == SpriteDrawMode::SPRITE_DRAW_MODE_NORMAL)
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
				if (*a_element->offset_z < *a_group->pseudo_pos_z)									{*a_group->pseudo_pos_z		= *a_group->pseudo_pos_z;}
				if (*a_element->offset_z + *a_element->size_y > * a_group->pseudo_pos_z2)			{*a_group->pseudo_pos_z2	= *a_element->offset_z + *a_element->size_y; }
				if (*a_group->pseudo_pos_z2 - *a_group->pseudo_pos_z > * a_group->pseudo_size_z) { *a_group->pseudo_size_z = *a_group->pseudo_pos_z2 - *a_group->pseudo_pos_z; }
				//if (*a_element->offset_z + *a_element->size_y > *a_group->pseudo_size_z)	{*a_group->pseudo_size_z = *a_element->offset_z + *a_element->size_y;}
			}

			if (*a_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_ROOF_Y)
			{
				if (*a_element->offset_y < *a_group->pseudo_pos_y)									{*a_group->pseudo_pos_y = *a_group->pseudo_pos_y;}
				if (*a_element->offset_y + *a_element->size_y > * a_group->pseudo_pos_y2)			{*a_group->pseudo_pos_y2 = *a_element->offset_y + *a_element->size_y; }
				if (*a_group->pseudo_pos_y2 - *a_group->pseudo_pos_y > * a_group->pseudo_size_y)	{*a_group->pseudo_size_y = *a_group->pseudo_pos_y2 - *a_group->pseudo_pos_y; }
				//if (*a_element->offset_y + *a_element->size_y > * a_group->pseudo_size_y)	{*a_group->pseudo_size_y = *a_element->offset_y + *a_element->size_y;}
			}

			/// //////////////
			/*	left	*/if (*a_element->offset_x < *a_group->pseudo_pos_x)								{*a_group->pseudo_pos_x		= *a_element->offset_x;}
			/*	right	*/if (*a_element->offset_x + *a_element->size_x > *a_group->pseudo_pos_x2)			{*a_group->pseudo_pos_x2	= *a_element->offset_x + *a_element->size_x;}
			/*	size x	*/if (*a_group->pseudo_pos_x2 - *a_group->pseudo_pos_x > * a_group->pseudo_size_x)	{*a_group->pseudo_size_x	= *a_group->pseudo_pos_x2 - *a_group->pseudo_pos_x;}

			/*
			if (*a_element->offset_x + *a_element->size_x - *a_group->pseudo_pos_x > * a_group->pseudo_size_x)
			{
				*a_group->pseudo_size_x = *a_element->offset_x + *a_element->size_x - *a_group->pseudo_pos_x;
			}*/





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

			if (*a_element->autobuilding_base->selected_sprite_fill_mode == SpriteFillMode::SPRITE_FILL_MODE_TILE)
				{
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

								*selected_sprite->size_z = round(wall_full_size_y * wall_fragment_y);
								*selected_sprite->offset_z += (rand() % 100 / 100.0f) * *a_element->autobuilding_base->random_space_between_sprite_y;
							}

							if (*a_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_ROOF_Y)
							{
								*selected_sprite->offset_z = 0.0f;
								*selected_sprite->offset_z += *a_group->offset_z + *a_element->offset_z;

								*selected_sprite->offset_y = *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_DOWN)->size_y;
								*selected_sprite->offset_y += yy * (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y) + *a_group->offset_y + *a_element->offset_y;

								*selected_sprite->size_y = round(wall_full_size_y * wall_fragment_y);
								*selected_sprite->offset_y += (rand() % 100 / 100.0f) * *a_element->autobuilding_base->random_space_between_sprite_y;

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
							*selected_sprite->offset_x += (rand() % 100 / 100.0f) * *a_element->autobuilding_base->random_space_between_sprite_x;

							selected_sprite->texture_gabarite = a_element->autobuilding_base->main_texture;
							selected_sprite->normal_gloss_map_gabarite = a_element->autobuilding_base->normal_gloss_map_texture;

							selected_sprite_id++;
						}
				}

			float saved_mid_wall_full_size_x = wall_full_size_x;
			float saved_mid_wall_full_size_y = wall_full_size_y;

			if (false)
			for (int yy = 0; yy < ceil(mid_wall_copies_y) - 2; yy++)
			for (int xx = 0; xx < ceil(mid_wall_copies_x); xx++)
			{
					EWindowMain::draw_vertical_border_element
					(
						/*offset x */				*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT)->size_x,
						/*offset y */				*a_group->offset_y + *a_element->offset_y,
						/*offset height/depth */	*a_group->offset_z + *a_element->offset_z + yy * saved_mid_wall_full_size_y,
						/*autobuilding group*/		a_group,
						/*autobuilding element*/	a_element,
						/*id of grid region*/		EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_DOWN,
						/*texture offset (y)*/		0.0f,
						xx
					);

					//up
					EWindowMain::draw_vertical_border_element
					(
						/*offset x */				*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT)->size_x,
						/*offset y */				*a_group->offset_y + *a_element->offset_y,
						/*offset height/depth */	*a_group->offset_z + *a_element->offset_z + saved_mid_wall_full_size_y - (*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_UP)->size_y) + yy * saved_mid_wall_full_size_y,
						/*autobuilding group*/		a_group,
						/*autobuilding element*/	a_element,
						/*id of grid region*/		EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_UP,
						/*texture offset (y)*/		*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_UP)->position_y,
						xx
					);
			}

			if (*a_element->autobuilding_base->selected_sprite_fill_mode == SpriteFillMode::SPRITE_FILL_MODE_RANDOM)
				{
						for (int z = 0; z < *a_element->autobuilding_base->random_sprite_count; z++)
						{
							add_new_sprite_to_group_if_need(selected_sprite_id, a_group, "mid wall");

							selected_sprite = a_group->sprite_list.at(selected_sprite_id);
							EGraphicCore::reset_sprite_data(selected_sprite);

							wall_fragment_x = 1.0f;
							wall_fragment_y = 1.0f;

							*selected_sprite->offset_x = *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT)->size_x;
							*selected_sprite->offset_x += *a_group->offset_x + *a_element->offset_x;
							*selected_sprite->offset_x += (*a_element->size_x - wall_full_size_x) * (rand() % 100 / 100.0f);
							

							if (*a_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_WALL_Z)
							{
								*selected_sprite->offset_y = 0.0f;
								*selected_sprite->offset_y += *a_group->offset_y + *a_element->offset_y;

								*selected_sprite->offset_z = *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_DOWN)->size_y;
								*selected_sprite->offset_z += *a_group->offset_z + *a_element->offset_z;
								*selected_sprite->offset_z += (*a_element->size_y - wall_full_size_y) * (rand() % 100 / 100.0f);

								*selected_sprite->size_z = round(wall_full_size_y * wall_fragment_y);
								*selected_sprite->offset_z += (rand() % 100 / 100.0f) * *a_element->autobuilding_base->random_space_between_sprite_y;
							}

							if (*a_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_ROOF_Y)
							{
								*selected_sprite->offset_z = 0.0f;
								*selected_sprite->offset_z += *a_group->offset_z + *a_element->offset_z;

								*selected_sprite->offset_y = *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_DOWN)->size_y;
								*selected_sprite->offset_y += *a_group->offset_y + *a_element->offset_y;
								*selected_sprite->offset_y += (*a_element->size_y - wall_full_size_y) * (rand() % 100 / 100.0f);

								*selected_sprite->size_y = round(wall_full_size_y * wall_fragment_y);
								*selected_sprite->offset_y += (rand() % 100 / 100.0f) * *a_element->autobuilding_base->random_space_between_sprite_y;

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
							//*selected_sprite->offset_x += (rand() % 100 / 100.0f) * *a_element->autobuilding_base->random_space_between_sprite_x;

							selected_sprite->texture_gabarite = a_element->autobuilding_base->main_texture;
							selected_sprite->normal_gloss_map_gabarite = a_element->autobuilding_base->normal_gloss_map_texture;

							selected_sprite_id++;
						}
				}

			mid_wall_copies_x
				=
				(
					*a_element->size_x
					-
					*a_element->autobuilding_base->grid_region.at(GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT)->size_x
					-
					*a_element->autobuilding_base->grid_region.at(GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT)->size_x
				) / (wall_full_size_x + *a_element->autobuilding_base->space_between_sprite_x);

			//bottom
			for (int xx = 0; xx < ceil(mid_wall_copies_x); xx++)
			{
				EWindowMain::draw_vertical_border_element
				(
					/*offset x */				*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT)->size_x,
					/*offset y */				*a_group->offset_y + *a_element->offset_y,
					/*offset height/depth */	*a_group->offset_z + *a_element->offset_z,
					/*autobuilding group*/		a_group,
					/*autobuilding element*/	a_element,
					/*id of grid region*/		EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_DOWN,
					/*texture offset (y)*/		0.0f,
					xx
				);

				//up
				EWindowMain::draw_vertical_border_element
				(
					/*offset x */				*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT)->size_x,
					/*offset y */				*a_group->offset_y + *a_element->offset_y,
					/*offset height/depth */	*a_group->offset_z + *a_element->offset_z + (*a_element->size_y - *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_UP)->size_y),
					/*autobuilding group*/		a_group,
					/*autobuilding element*/	a_element,
					/*id of grid region*/		EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_UP,
					/*texture offset (y)*/		*a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_UP)->position_y,
					xx
				);
			}


			//up
			

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

				mid_wall_copies_x = 1.0f;

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

				fragment_correction_factor_x = 1.0f;
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

							*selected_sprite->size_z = round(wall_full_size_y * wall_fragment_y);
						}

						if (*a_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_ROOF_Y)
						{
							*selected_sprite->offset_z = 0.0f;
							*selected_sprite->offset_z += *a_group->offset_z + *a_element->offset_z;

							*selected_sprite->offset_y = *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT)->position_y;
							*selected_sprite->offset_y += yy * (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y) + *a_group->offset_y + *a_element->offset_y;

							*selected_sprite->size_y = round(wall_full_size_y * wall_fragment_y);
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
						

						selected_sprite->texture_gabarite = a_element->autobuilding_base->main_texture;
						selected_sprite->normal_gloss_map_gabarite = a_element->autobuilding_base->normal_gloss_map_texture;

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

				mid_wall_copies_x = 1.0f;

				mid_wall_copies_y = 1.0f;

				fragment_correction_factor_x = 1.0f;
				fragment_correction_factor_y = 1.0f;

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

							*selected_sprite->size_z = round(wall_full_size_y * wall_fragment_y);
						}
						
						if (*a_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_ROOF_Y)
						{
							*selected_sprite->offset_z = 0.0f;
							*selected_sprite->offset_z += *a_group->offset_z + *a_element->offset_z;

							*selected_sprite->offset_y = 0.0f;
							*selected_sprite->offset_y += yy * (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y) + *a_group->offset_y + *a_element->offset_y;

							*selected_sprite->size_y = round(wall_full_size_y * wall_fragment_y);
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
						

						selected_sprite->texture_gabarite = a_element->autobuilding_base->main_texture;
						selected_sprite->normal_gloss_map_gabarite = a_element->autobuilding_base->normal_gloss_map_texture;

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

				mid_wall_copies_x =	1.0f;
				mid_wall_copies_y = 1.0f;

				fragment_correction_factor_x = 1.0f;
				fragment_correction_factor_y = 1.0f;

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

							*selected_sprite->size_z = round(wall_full_size_y * wall_fragment_y);
						}

						if (*a_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_ROOF_Y)
						{
							*selected_sprite->offset_z = 0.0f;
							*selected_sprite->offset_z += *a_group->offset_z + *a_element->offset_z;

							*selected_sprite->offset_y = *a_element->size_y - *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT_UP_CORNER)->size_y;
							*selected_sprite->offset_y += yy * (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y) + *a_group->offset_y + *a_element->offset_y;

							*selected_sprite->size_y = round(wall_full_size_y * wall_fragment_y);
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
						

						selected_sprite->texture_gabarite = a_element->autobuilding_base->main_texture;
						selected_sprite->normal_gloss_map_gabarite = a_element->autobuilding_base->normal_gloss_map_texture;

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

				mid_wall_copies_x = 1.0f;

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

				fragment_correction_factor_x = 1.0f;
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

							*selected_sprite->size_z = round(wall_full_size_y * wall_fragment_y);
						}

						if (*a_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_ROOF_Y)
						{
							*selected_sprite->offset_z = 0.0f;
							*selected_sprite->offset_z += *a_group->offset_z + *a_element->offset_z;

							*selected_sprite->offset_y = *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT)->position_y;
							*selected_sprite->offset_y += yy * (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y) + *a_group->offset_y + *a_element->offset_y;

							*selected_sprite->size_y = round(wall_full_size_y * wall_fragment_y);
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
						

						selected_sprite->texture_gabarite = a_element->autobuilding_base->main_texture;
						selected_sprite->normal_gloss_map_gabarite = a_element->autobuilding_base->normal_gloss_map_texture;

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
				
				mid_wall_copies_x = 1.0f;
				mid_wall_copies_y = 1.0f;

				fragment_correction_factor_x = 1.0f;
				fragment_correction_factor_y = 1.0f;

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

							*selected_sprite->size_z = round(wall_full_size_y * wall_fragment_y);
						}
						if (*a_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_ROOF_Y)
						{
							*selected_sprite->offset_z = 0.0f;
							*selected_sprite->offset_z += *a_group->offset_z + *a_element->offset_z;

							*selected_sprite->offset_y = 0.0f;
							*selected_sprite->offset_y += yy * (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y) + *a_group->offset_y + *a_element->offset_y;

							*selected_sprite->size_y = round(wall_full_size_y * wall_fragment_y);
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

						selected_sprite->texture_gabarite = a_element->autobuilding_base->main_texture;
						selected_sprite->normal_gloss_map_gabarite = a_element->autobuilding_base->normal_gloss_map_texture;

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

				mid_wall_copies_x = 1.0f;
				mid_wall_copies_y = 1.0f;

				fragment_correction_factor_x = 1.0f;
				fragment_correction_factor_y = 1.0f;

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

							*selected_sprite->size_z = round(wall_full_size_y * wall_fragment_y);
						}

						if (*a_group->selected_direction_of_push == AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_ROOF_Y)
						{
							*selected_sprite->offset_z = 0.0f;
							*selected_sprite->offset_z += *a_group->offset_z + *a_element->offset_z;

							*selected_sprite->offset_y = *a_element->size_y - *a_element->autobuilding_base->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT_UP_CORNER)->size_y;
							*selected_sprite->offset_y += yy * (wall_full_size_y + *a_element->autobuilding_base->space_between_sprite_y) + *a_group->offset_y + *a_element->offset_y;

							*selected_sprite->size_y = round(wall_full_size_y * wall_fragment_y);
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

						selected_sprite->texture_gabarite = a_element->autobuilding_base->main_texture;
						selected_sprite->normal_gloss_map_gabarite = a_element->autobuilding_base->normal_gloss_map_texture;

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

				//std::cout << "Dovboyob" << std::endl;
				delete deleted_sprite;
				//std::cout << "Dovboyob 2" << std::endl;
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

EWindowMain::terrain_tile_struct::terrain_tile_struct()
{
}

EWindowMain::terrain_tile_struct::~terrain_tile_struct()
{
}
