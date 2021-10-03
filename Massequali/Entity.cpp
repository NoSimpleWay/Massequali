#include "Entity.h"
#include "ExternalButtonAction.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::draw_entity(Entity* _e, Batcher* _b, float _d)
{
	
	if (_e->entity_sprite_array != NULL)
	{
		EGraphicCore::draw_sprite_regular(_e->entity_sprite_array, EGraphicCore::batch, *_e->position_x, *_e->position_y, *_e->position_z);
	}

}

void Entity::draw_catched_element(Entity::AutobuildingGroupElement* _element, Entity* _e, Entity::AutobuildingGroup* _group, bool _always_show)
{
	//catchers
	if ((*_element->catched_left_side) || (_always_show))
	{
		EGraphicCore::batch->draw_gabarite
		(
			*_e->position_x + *_group->offset_x + *_element->offset_x + 1.0f,
			*_e->position_y + *_group->offset_y + *_element->offset_y
			+
			*_e->position_z + *_group->offset_z + *_element->offset_z,
			2.0f,
			*_element->size_y,
			EGraphicCore::gabarite_white_pixel
		);
	}

	if ((*_element->catched_right_side) || (_always_show))
	{
		EGraphicCore::batch->draw_gabarite
		(
			*_e->position_x + *_group->offset_x + *_element->offset_x + 1.0f + *_element->size_x,
			*_e->position_y + *_group->offset_y + *_element->offset_y
			+
			*_e->position_z + *_group->offset_z + *_element->offset_z,
			2.0f,
			*_element->size_y,
			EGraphicCore::gabarite_white_pixel
		);
	}

	if ((*_element->catched_down_side) || (_always_show))
	{
		EGraphicCore::batch->draw_gabarite
		(
			*_e->position_x + *_group->offset_x + *_element->offset_x - 0.0f,
			*_e->position_y + *_group->offset_y + *_element->offset_y + 1.0f
			+
			*_e->position_z + *_group->offset_z + *_element->offset_z,
			*_element->size_x,
			2.0f,
			EGraphicCore::gabarite_white_pixel
		);
	}

	if ((*_element->catched_up_side) || (_always_show))
	{
		EGraphicCore::batch->draw_gabarite
		(
			*_e->position_x + *_group->offset_x + *_element->offset_x - 0.0f,
			*_e->position_y + *_group->offset_y + *_element->offset_y + *_element->size_y + 1.0f
			+
			*_e->position_z + *_group->offset_z + *_element->offset_z,
			*_element->size_x,
			2.0f,
			EGraphicCore::gabarite_white_pixel
		);
	}

	if ((*_element->catched_mid) || (_always_show))
	{
		EGraphicCore::batch->draw_gabarite
		(
			*_e->position_x + *_group->offset_x + *_element->offset_x + *_element->size_x / 2.0f - 10.0f,
			*_e->position_y + *_group->offset_y + *_element->offset_y + *_element->size_y / 2.0f - 10.0f
			+
			*_e->position_z + *_group->offset_z + *_element->offset_z,
			20.0f,
			20.0f,
			EGraphicCore::gabarite_white_pixel
		);
	}

	if ((*_element->catched_z) || (_always_show))
	{
		EGraphicCore::batch->draw_gabarite
		(
			*_e->position_x + *_group->offset_x + *_element->offset_x + *_element->size_x / 2.0f - 3.0f,
			*_e->position_y + *_group->offset_y + *_element->offset_y + *_element->size_y / 2.0f + 10.0f
			+
			*_e->position_z + *_group->offset_z + *_element->offset_z,
			6.0f,
			30.0f,
			EGraphicCore::gabarite_white_pixel
		);
	}
}

void Entity::draw_entity_autobuilging_helping(Entity* _e, Batcher* _b, float _d)
{

	if ((glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS))
	{
		EGraphicCore::batch->setcolor(EColor::COLOR_LIME);
		EGraphicCore::batch->draw_rama
		(
			*_e->position_x - 5.0f,
			*_e->position_y,
			10.0f,
			5.0f,
			2.0f,
			EGraphicCore::gabarite_white_pixel
		);
	}

	//HIGHLIGHT
	if (!_e->autobuilding_group_list.empty())
		for (AutobuildingGroup* _group : _e->autobuilding_group_list)
			for (AutobuildingGroupElement* _element : _group->autobuilding_group_element_list)
			{
				if (*_element->highlight_time > 0.0f)
				{
					EGraphicCore::batch->setcolor_alpha(EColor::COLOR_LIME, *_element->highlight_time);
					EGraphicCore::batch->draw_gabarite
					(
						*_e->position_x + *_group->offset_x + *_element->offset_x,
						*_e->position_y + *_group->offset_y + *_element->offset_y
						+ *_e->position_z + *_group->offset_z + *_element->offset_z,
						*_element->size_x,
						*_element->size_y,
						EGraphicCore::gabarite_white_pixel
					);

					*_element->highlight_time -= _d * 5.0f;
				}
			}

	
	//if ((glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS))
	{

		//transparent drag point and ramas
		if (!_e->autobuilding_group_list.empty())
			for (AutobuildingGroup* _group : _e->autobuilding_group_list)
			{

				if
					(
						(*_group->offset_z > 0.0f)
						&
						(glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
						&
						(ExternalButtonAction::get_selected_autobuilding_group(_e) != NULL)
					)
				{
					//std::cout << "blue z-shadow" << std::endl;
					EGraphicCore::batch->setcolor_alpha(EColor::COLOR_DARK_BLUE, 0.1f);
					EGraphicCore::batch->draw_gabarite
					(
						*_e->position_x + *_group->offset_x + *_group->pseudo_pos_x,
						*_e->position_y + *_group->offset_y,
						*_group->pseudo_size_x,
						*_group->pseudo_size_y + 5.0f,
						EGraphicCore::gabarite_white_pixel
					);

					EGraphicCore::batch->setcolor_alpha(EColor::COLOR_WHITE, 1.0f);

					EGraphicCore::batch->draw_gabarite
					(
						*_e->position_x + *_group->offset_x + *_group->pseudo_pos_x,
						*_e->position_y + *_group->offset_y,
						3.0f,
						*_group->offset_z,
						EGraphicCore::gabarite_white_pixel
					);
				}

				for (AutobuildingGroupElement* _element : _group->autobuilding_group_element_list)
				{


					//draw border rama
					if
						(
							(glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
							&&
							(ExternalButtonAction::get_entity() != NULL)
							&&
							(ExternalButtonAction::get_entity() == _e)	
						)
					{
						if
							(
								(ExternalButtonAction::get_selected_autobuilding_group_element(_e) != NULL)
								&&
								(ExternalButtonAction::get_selected_autobuilding_group_element(_e) == _element)

							)
						{
							EGraphicCore::batch->setcolor(EColor::COLOR_WHITE);
						}
						else
						{
							EGraphicCore::batch->setcolor_alpha(EColor::COLOR_BLACK, 0.5f);
						}

						EGraphicCore::batch->draw_rama
						(
							*_e->position_x + *_group->offset_x + *_element->offset_x,
							*_e->position_y +*_e->position_z + *_group->offset_y + *_group->offset_z + *_element->offset_y + *_element->offset_z,
							*_element->size_x,
							*_element->size_y,
							1.0f,
							EGraphicCore::gabarite_white_pixel
						);
					}

					if
						(
							(ExternalButtonAction::get_selected_autobuilding_group(_e) != NULL)
							&&
							(ExternalButtonAction::get_selected_autobuilding_group(_e) == _group)
							&&
							(ExternalButtonAction::get_entity() != NULL)
							&&
							(ExternalButtonAction::get_entity() == _e)
						)
					{

						if (*_group->is_catched)
						{EGraphicCore::batch->setcolor(EColor::COLOR_YELLOW);}
						else
						{EGraphicCore::batch->setcolor_alpha(EColor::COLOR_ORANGE, 0.5f);}

						EGraphicCore::batch->draw_gabarite
						(
							*_e->position_x + *_group->offset_x + *_group->pseudo_pos_x,
							*_e->position_y + *_e->position_z + *_group->offset_y + *_group->offset_z - 11.0f,
							*_group->pseudo_size_x,
							10.0f,
							EGraphicCore::gabarite_white_pixel
						);

						if (*_group->offset_z > 0.0f)
						{
							EGraphicCore::batch->setcolor_alpha(EColor::COLOR_YELLOW, 0.5f);

							EGraphicCore::batch->draw_gabarite
							(
								*_e->position_x + *_group->offset_x + *_group->pseudo_pos_x,
								*_e->position_y + *_group->offset_y - 20.0f,
								*_group->pseudo_size_x,
								20.0f,
								EGraphicCore::gabarite_white_pixel
							);

							EGraphicCore::batch->draw_rama
							(
								*_e->position_x + *_group->offset_x + *_group->pseudo_pos_x,
								*_e->position_y + *_group->offset_y - 20.0f,
								*_group->pseudo_size_x,
								*_group->offset_z + 25.0f,
								2.0f,
								EGraphicCore::gabarite_white_pixel
							);

						}
					}

					if ((glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS))
					{
						if
							(
								(ExternalButtonAction::get_entity() != NULL)
								&&
								(ExternalButtonAction::get_entity() == _e)
								&&
								(ExternalButtonAction::get_selected_autobuilding_group_element(_e) != NULL)
								&&
								(ExternalButtonAction::get_selected_autobuilding_group_element(_e) == _element)
							)

						{
							EGraphicCore::batch->setcolor_alpha(EColor::COLOR_RED, 0.33f);
							draw_catched_element(_element, _e, _group, true);
						}
					}


					EGraphicCore::batch->setcolor(EColor::COLOR_PINK);
					draw_catched_element(_element, _e, _group, false);

					EGraphicCore::batch->setcolor(EColor::COLOR_BLACK);
					if (*_element->catched_mid)
					{
						EFont::active_font->draw
						(
							EGraphicCore::batch,
								"x:"
								+
								EString::float_to_string(*_element->offset_x)
								+
								" y:"
								+
								EString::float_to_string(*_element->offset_y),
							*_e->position_x + *_group->offset_x + *_element->offset_x + *_element->size_x / 2.0f,
							*_e->position_y + *_group->offset_y + *_element->offset_y + *_e->position_z + *_group->offset_z + *_element->offset_z + *_element->size_y / 2.0f
						);
					}
				}

				/*
				if
				(
					(_e == ExternalButtonAction::get_entity())
					&&
					(glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
					&&
					(ExternalButtonAction::get_selected_autobuilding_group(_e) != NULL)
					&&
					(ExternalButtonAction::get_selected_autobuilding_group(_e) == _group)
					&&
					(ExternalButtonAction::valid_entity_select()
					
					
				)
				)
				{
					EGraphicCore::batch->setcolor(EColor::COLOR_GREEN);
					EGraphicCore::batch->draw_gabarite(*_e->position_x + *_group->offset_x - 500.0f, *_e->position_y + *_group->offset_y + *_group->bottom_offset, 1000.0f, 3.0f, EGraphicCore::gabarite_white_pixel);
					EGraphicCore::batch->draw_gabarite(*_e->position_x + *_group->offset_x - 500.0f, *_e->position_y + *_group->offset_y + *_group->up_offset, 1000.0f, 3.0f, EGraphicCore::gabarite_white_pixel);
				}*/

			}
	}




	if (*_e->is_selected)
	{
		EGraphicCore::batch->setcolor(EColor::COLOR_GREEN);
		EGraphicCore::batch->draw_rama(*_e->position_x - 10.0f, *_e->position_y - 10.0f, 20.0f, 20.0f, 2.0f, EGraphicCore::gabarite_white_pixel);
	}
}

ECamera::ECamera()
{
}

ECamera::~ECamera()
{
}

Entity::AutobuildingBase::AutobuildingBase()
{
	for (int i = 0; i < 9; i++)
	{
		EButton::EGridRegion* just_created_grid_region = new EButton::EGridRegion();

		grid_region.push_back(just_created_grid_region);
	}
}

/*
void ECluster::bake_terrain_data(ECluster* _cluster)
{

	
}*/

void ECluster::bake_terrain_data
(
	ECluster* _cluster,

	float _x,
	float _y,
	
	float _size_x,
	float _size_y,
	
	float _texture_offset_x,
	float _texture_offset_y,
	
	EGabarite* _texture,
	EGabarite* _normal_gloss_map
)
{
	//std::cout << "debil: " << std::to_string(_cluster->btd_last_id) << std::endl;
	//xyz
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 0] = (_x + _size_x);
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 1] = (_y + _size_y);
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 2] = (0.0f);

	//color
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 3] = 1.0f;
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 4] = 1.0f;
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 5] = 1.0f;
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 6] = 1.0f;

	//uv
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 7] = *_texture->x + _texture_offset_x + _size_x / 4096.0f;
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 8] = *_texture->y + _texture_offset_y + _size_y / 4096.0f;

	//uv reflection
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 9] = 0.0f;
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 10] = (0.0f + _size_y) / 1080.0f;

	//normal gloss
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 11] = *_normal_gloss_map->x + _texture_offset_x + _size_x / 4096.0f;
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 12] = *_normal_gloss_map->y + _texture_offset_y + _size_y / 4096.0f;



	//..
	//.#

	//xyz
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 13] = (_x + _size_x);
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 14] = _y;
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 15] = 0.0f;
	//vertices[id + 10] = 0;

	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 16] = 1.0f;
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 17] = 1.0f;
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 18] = 1.0f;
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 19] = 1.0f;

	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 20] = *_texture->x + _texture_offset_x + _size_x / 4096.0f;
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 21] = *_texture->y + _texture_offset_y;

	//uv reflection
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 22] = 0.0f;
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 23] = (0.0f) / 1080.0f;

	//normal gloss
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 24] = *_normal_gloss_map->x + _texture_offset_x + _size_x / 4096.0f;
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 25] = *_normal_gloss_map->y + _texture_offset_y;


	//..
	//#.
	// 
	//xyz
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 26] = _x;
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 27] = _y;
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 28] = 0.0f;

	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 29] = 1.0f;
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 30] = 1.0f;
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 31] = 1.0f;
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 32] = 1.0f;

	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 33] = *_texture->x + _texture_offset_x;
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 34] = *_texture->y + _texture_offset_y;

	//uv reflection
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 35] = 0.0f;
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 36] = (0.0f) / 1080.0f;


	//normal gloss
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 37] = *_normal_gloss_map->x + _texture_offset_x;
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 38] = *_normal_gloss_map->y + _texture_offset_y;

	//#.
	//..
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 39] = _x;
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 40] = (_y + _size_y);
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 41] = (0.0f + 0.0f);
	//vertices[id + 26] = 0;

	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 42] = 1.0f;
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 43] = 1.0f;
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 44] = 1.0f;
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 45] = 1.0f;

	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 46] = *_texture->x + _texture_offset_x;
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 47] = *_texture->y + _texture_offset_y + _size_y / 4096.0f;

	//uv reflection
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 48] = 0.0f;
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 49] = (0.0f + _size_y) / 1080.0f;

	//normal gloss
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 50] = *_normal_gloss_map->x + _texture_offset_x;
	_cluster->terrain_vertex_data_buffer[_cluster->btd_last_id + 51] = *_normal_gloss_map->y + _texture_offset_y + _size_y / 4096.0f;

	_cluster->btd_last_id += 52;
}
