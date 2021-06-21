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

	if (*_e->is_selected)
	{
		EGraphicCore::batch->setcolor(EColor::COLOR_GREEN);
		EGraphicCore::batch->draw_rama(*_e->position_x-10.0f, *_e->position_y-10.0f, 20.0f, 20.0f, 2.0f, EGraphicCore::gabarite_white_pixel);
	}

	if (!_e->autobuilding_group_list.empty())
	for (AutobuildingGroup* _group:_e->autobuilding_group_list)
	for (AutobuildingGroupElement* _element : _group->autobuilding_group_element_list)
	{

		if ((glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS))
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
			EGraphicCore::batch->draw_rama(*_e->position_x + *_group->offset_x + *_element->offset_x, *_e->position_y + *_group->offset_y + *_element->offset_y, *_element->size_x, *_element->size_y, 1.0f, EGraphicCore::gabarite_white_pixel);
		}
		EGraphicCore::batch->setcolor(EColor::COLOR_PINK);

		if (*_element->catched_left_side)
		{
			EGraphicCore::batch->draw_gabarite
			(
				*_e->position_x + *_group->offset_x + *_element->offset_x + 1.0f,
				*_e->position_y + *_group->offset_y + *_element->offset_y,
				2.0f,
				*_element->size_y,
				EGraphicCore::gabarite_white_pixel
			);
		}

		if (*_element->catched_right_side)
		{
			EGraphicCore::batch->draw_gabarite
			(
				*_e->position_x + *_group->offset_x + *_element->offset_x + 1.0f +*_element->size_x,
				*_e->position_y + *_group->offset_y + *_element->offset_y,
				2.0f,
				*_element->size_y,
				EGraphicCore::gabarite_white_pixel
			);
		}

		if (*_element->catched_down_side)
		{
			EGraphicCore::batch->draw_gabarite
			(
				*_e->position_x + *_group->offset_x + *_element->offset_x - 0.0f,
				*_e->position_y + *_group->offset_y + *_element->offset_y + 1.0f,
				*_element->size_x,
				2.0f,
				EGraphicCore::gabarite_white_pixel
			);
		}


		if (*_element->catched_up_side)
		{
			EGraphicCore::batch->draw_gabarite
			(
				*_e->position_x + *_group->offset_x + *_element->offset_x - 0.0f,
				*_e->position_y + *_group->offset_y + *_element->offset_y + *_element->size_y + 1.0f,
				*_element->size_x,
				2.0f,
				EGraphicCore::gabarite_white_pixel
			);
		}

		if (*_element->catched_mid)
		{
			EGraphicCore::batch->draw_gabarite
			(
				*_e->position_x + *_group->offset_x + *_element->offset_x + *_element->size_x / 2.0f - 10.0f,
				*_e->position_y + *_group->offset_y + *_element->offset_y + *_element->size_y / 2.0f - 10.0f,
				20.0f,
				20.0f,
				EGraphicCore::gabarite_white_pixel
			);
		}
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
