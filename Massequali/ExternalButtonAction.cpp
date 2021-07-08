#include "ExternalButtonAction.h"
#include "EWindowMain.h"

void ExternalButtonAction::external_button_action_scroll_texture_list(EButton* _b, float _f)
{
}

void ExternalButtonAction::external_button_action_set_grid_region_auto_size(EButton* _b, float _f)
{
	//std::cout << "Z" << std::endl;
	float target_value_up = EMath::to_float(EWindowMain::auto_size_region_button.at(EWindowMain::AutoGridSizeButtonByOrder::AUTO_GRID_SIZE_BUTTON_BY_ORDER_UP)->text);;
	float target_value_down = EMath::to_float(EWindowMain::auto_size_region_button.at(EWindowMain::AutoGridSizeButtonByOrder::AUTO_GRID_SIZE_BUTTON_BY_ORDER_DOWN)->text);
	float target_value_left = EMath::to_float(EWindowMain::auto_size_region_button.at(EWindowMain::AutoGridSizeButtonByOrder::AUTO_GRID_SIZE_BUTTON_BY_ORDER_LEFT)->text);
	float target_value_right = EMath::to_float(EWindowMain::auto_size_region_button.at(EWindowMain::AutoGridSizeButtonByOrder::AUTO_GRID_SIZE_BUTTON_BY_ORDER_RIGT)->text);

	EButton::EGridRegion* target_grid_region;
	EButton* target_button = EWindowMain::grid_region_edit_button_link;

	target_grid_region = EWindowMain::grid_region_edit_button_link->grid_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT_UP_CORNER);
	*target_grid_region->position_x = 0.0f;
	*target_grid_region->position_y = target_button->button_size_y / target_button->icon_size_multiplier - target_value_up;
	*target_grid_region->size_x = target_value_left;
	*target_grid_region->size_y = target_value_up;

	target_grid_region = EWindowMain::grid_region_edit_button_link->grid_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_UP);
	*target_grid_region->position_x = target_value_left;
	*target_grid_region->position_y = target_button->button_size_y / target_button->icon_size_multiplier - target_value_up;
	*target_grid_region->size_x = target_button->button_size_x / target_button->icon_size_multiplier - target_value_left - target_value_right;
	*target_grid_region->size_y = target_value_up;

	target_grid_region = EWindowMain::grid_region_edit_button_link->grid_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT_UP_CORNER);
	*target_grid_region->position_x = target_button->button_size_x / target_button->icon_size_multiplier - target_value_right;
	*target_grid_region->position_y = target_button->button_size_y / target_button->icon_size_multiplier - target_value_up;
	*target_grid_region->size_x = target_value_right;
	*target_grid_region->size_y = target_value_up;

	target_grid_region = EWindowMain::grid_region_edit_button_link->grid_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT);
	*target_grid_region->position_x = 0.0f;
	*target_grid_region->position_y = target_value_down;
	*target_grid_region->size_x = target_value_left;
	*target_grid_region->size_y = target_button->button_size_y / target_button->icon_size_multiplier - target_value_up - target_value_down;

	target_grid_region = EWindowMain::grid_region_edit_button_link->grid_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_MID);
	*target_grid_region->position_x = target_value_left;
	*target_grid_region->position_y = target_value_down;
	*target_grid_region->size_x = target_button->button_size_x / target_button->icon_size_multiplier - target_value_left - target_value_right;
	*target_grid_region->size_y = target_button->button_size_y / target_button->icon_size_multiplier - target_value_up - target_value_down;

	std::cout << "region mid size [" << std::to_string(*target_grid_region->size_x) << "][" << std::to_string(*target_grid_region->size_y) << "]" << std::endl;

	target_grid_region = EWindowMain::grid_region_edit_button_link->grid_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT);
	*target_grid_region->position_x = target_button->button_size_x / target_button->icon_size_multiplier - target_value_right;
	*target_grid_region->position_y = target_value_down;
	*target_grid_region->size_x = target_value_right;
	*target_grid_region->size_y = target_button->button_size_y / target_button->icon_size_multiplier - target_value_up - target_value_down;

	target_grid_region = EWindowMain::grid_region_edit_button_link->grid_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT_DOWN_CORNER);
	*target_grid_region->position_x = 0.0f;
	*target_grid_region->position_y = 0.0f;
	*target_grid_region->size_x = target_value_left;
	*target_grid_region->size_y = target_value_down;

	target_grid_region = EWindowMain::grid_region_edit_button_link->grid_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_DOWN);
	*target_grid_region->position_x = target_value_left;
	*target_grid_region->position_y = 0.0f;
	*target_grid_region->size_x = target_button->button_size_x / target_button->icon_size_multiplier - target_value_left - target_value_right;
	*target_grid_region->size_y = target_value_down;

	target_grid_region = EWindowMain::grid_region_edit_button_link->grid_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT_DOWN_CORNER);
	*target_grid_region->position_x = target_button->button_size_x / target_button->icon_size_multiplier - target_value_right;
	*target_grid_region->position_y = 0.0f;
	*target_grid_region->size_x = target_value_right;
	*target_grid_region->size_y = target_value_down;
	/*
	*EWindowMain::grid_region_button_link->grid_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT_UP_CORNER)
	->size_x = target_value_left;

	*EWindowMain::grid_region_button_link->grid_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT_UP_CORNER)
	->size_y = std::stof(EWindowMain::auto_size_region_button.at(EWindowMain::AutoGridSizeButtonByOrder::AUTO_GRID_SIZE_BUTTON_BY_ORDER_UP)->text);
	*/

	/*
	*EWindowMain::grid_region_button_link->grid_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_UP)->
		size_x = EWindowMain::grid_region_button_link->button_size_x
		-
		std::stof(EWindowMain::auto_size_region_button.at(EWindowMain::AutoGridSizeButtonByOrder::AUTO_GRID_SIZE_BUTTON_BY_ORDER_LEFT)->text);

	*EWindowMain::grid_region_button_link->grid_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT_UP_CORNER)
		->size_y = std::stof(EWindowMain::auto_size_region_button.at(EWindowMain::AutoGridSizeButtonByOrder::AUTO_GRID_SIZE_BUTTON_BY_ORDER_UP)->text);*/
		//gr->pos
}

void ExternalButtonAction::external_button_action_select_entity_from_list(EButton* _b, float _f)
{
	Entity* en = NULL;

	if (valid_entity_select())
	{
		en = get_entity();
		EWindowMain::create_new_elements_of_autobuilding_if_need(en);


		//EWindowMain::button_group_autobuilding_group_element->selected_button = EWindowMain::button_group_autobuilding_group_element->button_list.at(0);



		EButton::update_data_id_for_buttons(EWindowMain::button_group_autobuilding_group_element);
		EButton::update_data_id_for_buttons(EWindowMain::button_group_autobuilding_group);
		EButton::update_data_id_for_buttons(EWindowMain::button_group_autobuilding_base);
	
		EWindowMain::button_group_autobuilding_group->selected_button				= NULL;
		EWindowMain::button_group_autobuilding_group_element->selected_button		= NULL;
		EWindowMain::button_group_autobuilding_base->selected_button				= NULL;

		if ((en->autobuilding_group_list.size() > 0)||(false))
		{
			EWindowMain::button_group_autobuilding_group->selected_button = EWindowMain::button_group_autobuilding_group->button_list.at(0);

			if (en->autobuilding_group_list.at(0)->autobuilding_group_element_list.size() > 0)
			{EWindowMain::button_group_autobuilding_group_element->selected_button = EWindowMain::button_group_autobuilding_group_element->button_list.at(0);}
			
		}
		
		//select fisrt button (base)
		if (en->autobuilding_base_list.size() > 0)
		{ EWindowMain::button_group_autobuilding_base->selected_button = EWindowMain::button_group_autobuilding_base->button_list.at(0); }
		
		
		//select base
		if (EWindowMain::button_group_autobuilding_base->selected_button != NULL)
		{
			external_button_action_select_autobuilding_base(EWindowMain::button_group_autobuilding_base->selected_button, 0.0f);
		}

		/*
		if (EWindowMain::button_group_autobuilding_group_element->selected_button != NULL)
		{
			//action_select(EWindowMain::button_group_autobuilding_group_element->selected_button, 0.0f);
		}*/

		//select group
		if (EWindowMain::button_group_autobuilding_group->selected_button != NULL)
		{
			external_button_action_select_autobuilding_group(EWindowMain::button_group_autobuilding_group->selected_button, 0.0f);
		}

		//hide or show base button
		for (int i = 0; i < EWindowMain::button_group_autobuilding_base->button_list.size(); i++)
			if (*EWindowMain::button_group_autobuilding_base->button_list.at(i)->can_be_selected)
			{
				if (i < en->autobuilding_base_list.size())
				{
					EWindowMain::button_group_autobuilding_base->button_list.at(i)->is_active = true;
					EWindowMain::button_group_autobuilding_base->button_list.at(i)->gabarite = en->autobuilding_base_list.at(i)->main_texture;
				}
				else
				{
					EWindowMain::button_group_autobuilding_base->button_list.at(i)->is_active = false;
				}
			}

		//hide or show group element
		for (int i = 0; i < EWindowMain::button_group_autobuilding_group_element->button_list.size(); i++)
			if (*EWindowMain::button_group_autobuilding_group_element->button_list.at(i)->can_be_selected)
			{
				if
					(
						(EWindowMain::button_group_autobuilding_group->selected_button != NULL)
						&&
						(!en->autobuilding_group_list.empty())
						&&
						(!en->autobuilding_group_list.at(get_autobuilding_group_id())->autobuilding_group_element_list.empty())
						&&
						(i < en->autobuilding_group_list.at(get_autobuilding_group_id())->autobuilding_group_element_list.size())
					)
				{
					EWindowMain::button_group_autobuilding_group_element->button_list.at(i)->is_active = true;
					EWindowMain::button_group_autobuilding_group_element->button_list.at(i)->gabarite
					=
					get_selected_autobuilding_group(get_entity())->autobuilding_group_element_list.at(i)->autobuilding_base->main_texture;

				}
				else
				{
					EWindowMain::button_group_autobuilding_group_element->button_list.at(i)->is_active = false;

				}
			}

		//hide or show group
		for (int i = 0; i < EWindowMain::button_group_autobuilding_group->button_list.size(); i++)
			if (*EWindowMain::button_group_autobuilding_group->button_list.at(i)->can_be_selected)
			{
				if
					(
						(i < en->autobuilding_group_list.size())
						)
				{
					EWindowMain::button_group_autobuilding_group->button_list.at(i)->is_active = true;
					EWindowMain::button_group_autobuilding_group->button_list.at(i)->text = *en->autobuilding_group_list.at(i)->name;
				}
				else
				{
					EWindowMain::button_group_autobuilding_group->button_list.at(i)->is_active = false;

				}
			}

		//select group button
		if (!en->autobuilding_group_list.empty())
		{
			EWindowMain::button_group_autobuilding_group->selected_button = EWindowMain::button_group_autobuilding_group->button_list.at(0);
		}
		else
		{
			EWindowMain::button_group_autobuilding_group->selected_button = NULL;
		}

		

		for (Entity::AutobuildingGroup* a_group : en->autobuilding_group_list)
			for (Entity::AutobuildingGroupElement* a_element : a_group->autobuilding_group_element_list)
			{
				*a_element->highlight_time = 0.5f;
			}

		//external_button_action_set_grid_region_auto_size(NULL, 0.1f);
		
	}
}

void ExternalButtonAction::external_button_action_add_new_autobuilding_base(EButton* _b, float _f)
{
	for (EButton* b : EWindowMain::button_group_autobuilding_base->button_list)
	{
		if (!b->is_active)
		{
			b->is_active = true;
			//b->gabarite = ETextureAtlas::put_texture_to_atlas("data/textures/hrusch_wall_main_002_v1.png", EWindow::default_texture_atlas);
			//using namespace std::chrono;
			//std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

			srand(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
			b->gabarite = EWindowMain::group_texture_collection_link->button_list.at(rand() % EWindowMain::group_texture_collection_link->button_list.size())->gabarite;
			Entity* en = NULL;

			if (valid_entity_select())
			{
				en = get_entity();

				Entity::AutobuildingBase* just_created_autobuilding_region = new Entity::AutobuildingBase();
				en->autobuilding_base_list.push_back(just_created_autobuilding_region);
				just_created_autobuilding_region->main_texture = b->gabarite;
			}
			b->update(0.1f);
			b->update_additional(0.1f);
			break;
		}
	}

	EButton::update_data_id_for_buttons(EWindowMain::button_group_autobuilding_base);
}

void ExternalButtonAction::external_button_action_remove_autobuilding_base(EButton* _b, float _f)
{
	if (valid_entity_select())
	{
		//search destroyed texture region on autobuilding regions
		int id = 0;
		for (Entity::AutobuildingGroup* a_group : get_entity()->autobuilding_group_list)
			for (Entity::AutobuildingGroupElement* a_element : a_group->autobuilding_group_element_list)
			{
				if (a_element->autobuilding_base == get_entity()->autobuilding_base_list.at(_b->data_id))
				{
					a_group->autobuilding_group_element_list.erase(a_group->autobuilding_group_element_list.begin() + id);

					EWindowMain::button_group_autobuilding_group_element->button_list.at(id)->is_active = false;
				}

				id++;
			}

		get_entity()
			->
			autobuilding_base_list.erase
			(
				get_entity()
				->
				autobuilding_base_list.begin()
				+
				_b->data_id
			);

		_b->is_active = false;

		EButton::update_data_id_for_buttons(EWindowMain::button_group_autobuilding_base);
		EButton::update_data_id_for_buttons(EWindowMain::button_group_autobuilding_group_element);
	}
}

void ExternalButtonAction::external_button_action_create_new_entity(EButton* _b, float _f)
{
	Entity* _e = new Entity();

	*_e->position_x = *EWindowMain::main_camera->position_x + EGraphicCore::SCR_WIDTH / 2000.0f;
	*_e->position_y = *EWindowMain::main_camera->position_y + EGraphicCore::SCR_HEIGHT / 2000.0f;

	EWindowMain::put_entity_to_map(_e);
}

void ExternalButtonAction::external_button_action_select_autobuilding_base(EButton* _b, float _f)
{
	if
	(
		(valid_entity_select())
		&&
		(get_selected_autobuilding_base(get_entity()) != NULL)
	)
	{
		EWindowMain::grid_region_edit_button_link->gabarite
			=
			get_entity()->autobuilding_base_list.at(_b->data_id)->main_texture;

		if
			(
				(*EWindowMain::grid_region_edit_button_link->gabarite->size_x < 100.0f)
				||
				(*EWindowMain::grid_region_edit_button_link->gabarite->size_y < 100.0f)
				)
		{
			EWindowMain::grid_region_edit_button_link->button_size_x = *EWindowMain::grid_region_edit_button_link->gabarite->size_x * 2.0f;
			EWindowMain::grid_region_edit_button_link->button_size_y = *EWindowMain::grid_region_edit_button_link->gabarite->size_y * 2.0f;
		}
		else
		{
			EWindowMain::grid_region_edit_button_link->button_size_x = *EWindowMain::grid_region_edit_button_link->gabarite->size_x * 1.0f;
			EWindowMain::grid_region_edit_button_link->button_size_y = *EWindowMain::grid_region_edit_button_link->gabarite->size_y * 1.0f;
			if
				(
					(*EWindowMain::grid_region_edit_button_link->gabarite->size_x > 400.0f)
					||
					(*EWindowMain::grid_region_edit_button_link->gabarite->size_y > 400.0f)
					)
			{
				EWindowMain::grid_region_edit_button_link->button_size_x = *EWindowMain::grid_region_edit_button_link->gabarite->size_x * 0.5f;
				EWindowMain::grid_region_edit_button_link->button_size_y = *EWindowMain::grid_region_edit_button_link->gabarite->size_y * 0.5f;
			}
		}

		EWindowMain::grid_region_edit_button_link->grid_region_list
			=
			get_entity()->autobuilding_base_list.at(_b->data_id)->grid_region;

		EWindowMain::space_between_sprites_x_button->simple_float_changer_list.at(0)->target_float_pointer
			=
			get_entity()->autobuilding_base_list.at(_b->data_id)->space_between_sprite_x;
		EWindowMain::space_between_sprites_x_button->text = EString::float_to_string(*get_entity()->autobuilding_base_list.at(_b->data_id)->space_between_sprite_x);

		EWindowMain::space_between_sprites_y_button->simple_float_changer_list.at(0)->target_float_pointer
			=
			get_entity()->autobuilding_base_list.at(_b->data_id)->space_between_sprite_y;
		EWindowMain::space_between_sprites_y_button->text = EString::float_to_string(*get_entity()->autobuilding_base_list.at(_b->data_id)->space_between_sprite_y);

		EWindowMain::link_button_subdivision_mid_x->target_address_for_int
			=
			get_entity()->autobuilding_base_list.at(_b->data_id)->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_MID)->subdivision_x;

		EWindowMain::link_button_subdivision_mid_y->target_address_for_int
			=
			get_entity()->autobuilding_base_list.at(_b->data_id)->grid_region.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_MID)->subdivision_y;

		EButton::EGridRegion* target_grid_region;
		EButton*
			target_button = EWindowMain::auto_size_region_button.at(EWindowMain::AutoGridSizeButtonByOrder::AUTO_GRID_SIZE_BUTTON_BY_ORDER_LEFT);
		target_button->text = EString::float_to_string(*EWindowMain::grid_region_edit_button_link->grid_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT)->size_x);

		target_button = EWindowMain::auto_size_region_button.at(EWindowMain::AutoGridSizeButtonByOrder::AUTO_GRID_SIZE_BUTTON_BY_ORDER_RIGT);
		target_button->text = EString::float_to_string(*EWindowMain::grid_region_edit_button_link->grid_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT)->size_x);

		target_button = EWindowMain::auto_size_region_button.at(EWindowMain::AutoGridSizeButtonByOrder::AUTO_GRID_SIZE_BUTTON_BY_ORDER_DOWN);
		target_button->text = EString::float_to_string(*EWindowMain::grid_region_edit_button_link->grid_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_DOWN)->size_y);

		target_button = EWindowMain::auto_size_region_button.at(EWindowMain::AutoGridSizeButtonByOrder::AUTO_GRID_SIZE_BUTTON_BY_ORDER_UP);
		target_button->text = EString::float_to_string(*EWindowMain::grid_region_edit_button_link->grid_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_UP)->size_y);

		//EWindowMain::link_button_subdivision_mid_x->text = std::to_string(*get_entity()->autobuilding_base_list.at(_b->data_id)->texture_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_MID)->subdivision_x);
		//EWindowMain::link_button_subdivision_mid_y->text = std::to_string(*get_entity()->autobuilding_base_list.at(_b->data_id)->texture_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_MID)->subdivision_x);


	}
}

void ExternalButtonAction::external_button_action_open_select_texture_window_for_autobuilding_base(EButton* _b, float _f)
{
	*EWindowMain::super_group_texture_collection_link->is_active = true;

	for (EButton* b : EWindowMain::group_texture_collection_link->button_list)
		if (*b->can_be_selected)
		{
			b->action_on_left_click.clear();
			b->action_on_left_click.push_back(&external_button_action_select_texture_for_autobuilding_region);
		}
}

void ExternalButtonAction::external_button_action_open_select_texture_window_for_vertex_editor(EButton* _b, float _f)
{
	*EWindowMain::super_group_texture_collection_link->is_active = true;

	for (EButton* b : EWindowMain::group_texture_collection_link->button_list)
		if (*b->can_be_selected)
		{
			b->action_on_left_click.clear();
			b->action_on_left_click.push_back(&external_button_action_select_texture_for_vertex_editor);
		}
}

void ExternalButtonAction::external_button_action_select_texture_for_autobuilding_region(EButton* _b, float _f)
{
	if (valid_entity_select())
	{
		EWindowMain::grid_region_edit_button_link->gabarite
			=
			_b->gabarite;

		get_entity()->
			autobuilding_base_list.at(get_autobuilding_base_id())->
			main_texture
			=
			_b->gabarite;

		EWindowMain::button_group_autobuilding_base->selected_button->gabarite = _b->gabarite;

		EWindowMain::grid_region_edit_button_link->button_size_x = *EWindowMain::grid_region_edit_button_link->gabarite->size_x * 1.0f;
		EWindowMain::grid_region_edit_button_link->button_size_y = *EWindowMain::grid_region_edit_button_link->gabarite->size_y * 1.0f;

		if
			(
				(*EWindowMain::grid_region_edit_button_link->gabarite->size_x < 100.0f)
				||
				(*EWindowMain::grid_region_edit_button_link->gabarite->size_y < 100.0f)
				)
		{
			EWindowMain::grid_region_edit_button_link->button_size_x = *EWindowMain::grid_region_edit_button_link->gabarite->size_x * 2.0f;
			EWindowMain::grid_region_edit_button_link->button_size_y = *EWindowMain::grid_region_edit_button_link->gabarite->size_y * 2.0f;
		}

		if
			(
				(*EWindowMain::grid_region_edit_button_link->gabarite->size_x > 200.0f)
				||
				(*EWindowMain::grid_region_edit_button_link->gabarite->size_y > 200.0f)
				)
		{
			EWindowMain::grid_region_edit_button_link->button_size_x = *EWindowMain::grid_region_edit_button_link->gabarite->size_x * 0.5f;
			EWindowMain::grid_region_edit_button_link->button_size_y = *EWindowMain::grid_region_edit_button_link->gabarite->size_y * 0.5f;
		}

		if (EWindowMain::button_group_autobuilding_group->selected_button != NULL)
		{
			external_button_action_select_autobuilding_group(EWindowMain::button_group_autobuilding_group->selected_button, 0.0f);
		}
	}
}

void ExternalButtonAction::external_button_action_select_texture_for_vertex_editor(EButton* _b, float _f)
{
	EWindowMain::link_to_button_vertex_editor->gabarite = _b->gabarite;
	EWindowMain::link_to_button_vertex_editor->have_icon = true;

	EWindowMain::link_to_button_vertex_editor->button_size_x = *_b->gabarite->size_x * 2.0f;
	EWindowMain::link_to_button_vertex_editor->button_size_y = *_b->gabarite->size_y * 2.0f;

	*EWindowMain::group_vertex_editor->size_x = *_b->gabarite->size_x * 2.0f + 10.0f;
	*EWindowMain::group_vertex_editor->size_y = *_b->gabarite->size_y * 2.0f + 10.0f;
}

void ExternalButtonAction::external_button_action_add_selected_region_to_autobuilding_group(EButton* _b, float _f)
{
	if
		(
			(!EWindowMain::selected_entities.empty())
			&
			(EWindowMain::group_grid_entity_list_link->selected_button != NULL)
			&
			(EWindowMain::button_group_autobuilding_group->selected_button != NULL)
			&
			(EWindowMain::button_group_autobuilding_base->selected_button != NULL)
			)
	{
		Entity::AutobuildingGroupElement* just_created_autobuilding_entity_element = new Entity::AutobuildingGroupElement();
		//Entity::AutobuildingRegionTexture* just_created_autobuilding_texture = new Entity::AutobuildingRegionTexture();

		just_created_autobuilding_entity_element->autobuilding_base
			=
			get_entity()->
			autobuilding_base_list.at(get_autobuilding_base_id());

		get_entity()
			->
			autobuilding_group_list.at(get_autobuilding_group_id())
			->
			autobuilding_group_element_list.push_back(just_created_autobuilding_entity_element);

		for (EButton* b : EWindowMain::button_group_autobuilding_group_element->button_list)
		{
			if (!b->is_active)
			{
				b->is_active = true;
				b->gabarite = just_created_autobuilding_entity_element->autobuilding_base->main_texture;

				break;
			}
		}

		EButton::update_data_id_for_buttons(EWindowMain::button_group_autobuilding_group_element);
	}
	else
	{
		if (EWindowMain::selected_entities.empty())
		{
			std::cout << "ERROR: selected entity list is NULL" << std::endl;
		}

		if (EWindowMain::group_grid_entity_list_link->selected_button == NULL)
		{
			std::cout << "ERROR: entity not selected" << std::endl;
		}

		if (EWindowMain::button_group_autobuilding_group->selected_button == NULL)
		{
			std::cout << "ERROR: group not selected" << std::endl;
		}

		if (EWindowMain::button_group_autobuilding_base->selected_button == NULL)
		{
			std::cout << "ERROR: texture region not selected" << std::endl;
		}
	}
}

void ExternalButtonAction::external_button_action_add_new_group_for_autobuilding(EButton* _b, float _f)
{
	if (valid_entity_select())
	{
		for (EButton* b : EWindowMain::button_group_autobuilding_group->button_list)
		{
			if (!b->is_active)
			{
				b->is_active = true;

				Entity* en = get_entity();

				Entity::AutobuildingGroup* jcg = new Entity::AutobuildingGroup();
				jcg->master_entity = en;

				en->autobuilding_group_list.push_back( jcg );


				break;
			}
		}
	}

	EButton::update_data_id_for_buttons(EWindowMain::button_group_autobuilding_group);
}

void ExternalButtonAction::external_button_action_select_autobuilding_group(EButton* _b, float _f)
{
	if ((valid_entity_select()) & (true))
	{
		for (int i = 0; i < EWindowMain::button_group_autobuilding_group_element->button_list.size(); i++)
			if (*EWindowMain::button_group_autobuilding_group_element->button_list.at(i)->can_be_selected)
			{
				if
				(
					(get_selected_autobuilding_group(get_entity()) != NULL)
					&&
					(i < get_selected_autobuilding_group(get_entity())->autobuilding_group_element_list.size())
				)
				{
					EWindowMain::button_group_autobuilding_group_element->button_list.at(i)->is_active = true;

					if
					(
						(get_selected_autobuilding_base(get_entity()) != NULL)
						&&
						(get_selected_autobuilding_base(get_entity())->main_texture != NULL)
						&&
						(get_selected_autobuilding_group_element(get_entity()) != NULL, "button action select autobuilding group [EBA]")
					)
					{
						EWindowMain::button_group_autobuilding_group_element->button_list.at(i)->gabarite
						=
						//EGraphicCore::gabarite_radial_button;
						get_selected_autobuilding_group(get_entity())->autobuilding_group_element_list.at(i)->autobuilding_base->main_texture;
					}
					else
					{
						EWindowMain::button_group_autobuilding_group_element->button_list.at(i)->gabarite = EGraphicCore::gabarite_ERROR;
					}

					//std::cout << "LOL TAM" << std::endl;
				}
				else
				{
					//std::cout << "HUI TAM" << std::endl;
					EWindowMain::button_group_autobuilding_group_element->button_list.at(i)->is_active = false;

					EWindowMain::button_group_autobuilding_group_element->button_list.at(i)->gabarite = EGraphicCore::gabarite_white_pixel;
				}
			}

		if (get_selected_autobuilding_group(get_entity()) != NULL)
		{
			for (Entity::AutobuildingGroupElement* a_element : get_selected_autobuilding_group(get_entity())->autobuilding_group_element_list)
			{
				*a_element->highlight_time = 0.5f;
			}
			//get_entity()->autobuilding_group_list;
		}

		if (get_selected_autobuilding_group(get_entity()) != NULL)
		{
			EWindowMain::link_button_sprite_push_direction->target_address_for_int = get_selected_autobuilding_group(get_entity())->selected_direction_of_push;
		}

		if
		(
			(EWindowMain::button_group_autobuilding_group->selected_button != NULL)
			&&
			(get_selected_autobuilding_group(get_entity()) != NULL)
		)
		{
			EWindowMain::button_group_autobuilding_group->selected_button->target_address_for_string = get_selected_autobuilding_group(get_entity())->name;
			EWindowMain::button_group_autobuilding_group->selected_button->text = *get_selected_autobuilding_group(get_entity())->name;
		}
	}
}

void ExternalButtonAction::external_button_action_select_autobuilding_group_element(EButton* _b, float _f)
{
	if (valid_entity_select())
	{
		if (get_selected_autobuilding_group_element(get_entity()) != NULL, "external_button_action_select_autobuilding_group_element")
		{
			*get_selected_autobuilding_group_element(get_entity())->highlight_time = 0.5f;
		}
	}
}

void ExternalButtonAction::external_button_action_remove_autobuilding_group_element(EButton* _b, float _f)
{
	if (valid_entity_select())
	{
		get_entity()->autobuilding_group_list.at(get_autobuilding_group_id())->autobuilding_group_element_list.erase
		(
			get_entity()
			->
			autobuilding_group_list.at(get_autobuilding_group_id())->autobuilding_group_element_list.begin()
			+
			_b->data_id
		);

		_b->is_active = false;

		EButton::update_data_id_for_buttons(EWindowMain::button_group_autobuilding_group_element);
	}
}

void ExternalButtonAction::external_button_action_close_master_button_super_group(EButton* _b, float _f)
{
	if (_b->master_super_group != NULL)
	{
		*_b->master_super_group->is_active = false;
	}
}

void ExternalButtonAction::external_button_action_set_button_value(EButton* _b, float _f)
{
	if ((_b->target_address_for_int != NULL) & (_b->text != "") & (_b->have_input_mode) & (_b->input_only_numbers))
	{
		*_b->target_address_for_int = std::stoi(_b->text);
	}

	if ((_b->target_address_for_bool != NULL) & (*_b->is_checkbox))
	{
		*_b->target_address_for_bool = *_b->is_checked;
	}

	if ((_b->target_address_for_int != NULL) & (_b->is_drop_list))
	{
		*_b->target_address_for_int = _b->selected_element;
	}
	if ((_b->target_address_for_string != NULL))
	{
		*_b->target_address_for_string = _b->text;
	}

	if ((_b->target_address_for_float != NULL))
	{
		if ((_b->is_slider) || (*_b->is_radial_button))
		{
			*_b->target_address_for_float = _b->slider_value;
		}
	}

}

void ExternalButtonAction::external_button_action_set_button_constant_value(EButton* _b, float _f)
{
	if ((_b->target_address_for_int != NULL))
	{
		*_b->target_address_for_int = *_b->target_value_for_int;
	}

	if ((_b->target_address_for_bool != NULL))
	{
		*_b->target_address_for_bool = *_b->target_value_for_bool;
	}

}

void ExternalButtonAction::external_button_action_drag_autobuilding_base(EButton* _b, float _f)
{
	if (*EButton::dragged_button->drag_is_positive)
	{
		Entity::AutobuildingBase* swap_base = get_entity()->autobuilding_base_list.at(EButton::dragged_button->data_id);

		get_entity()->autobuilding_base_list.at(EButton::dragged_button->data_id)
			=
			get_entity()->autobuilding_base_list.at(EButton::dragged_button->data_id + 1);

		get_entity()->autobuilding_base_list.at(EButton::dragged_button->data_id + 1) = swap_base;
	}
	else
	{
		Entity::AutobuildingBase* swap_base = get_entity()->autobuilding_base_list.at(EButton::dragged_button->data_id);

		get_entity()->autobuilding_base_list.at(EButton::dragged_button->data_id)
			=
			get_entity()->autobuilding_base_list.at(EButton::dragged_button->data_id - 1);

		get_entity()->autobuilding_base_list.at(EButton::dragged_button->data_id - 1) = swap_base;

		//std::cout << "elements " << std::to_string(EButton::dragged_button->data_id) << " and " << std::to_string(EButton::dragged_button->data_id -1) << " swapped" << std::endl;
	}
}

void ExternalButtonAction::external_button_action_drag_autobuilding_group_element(EButton* _b, float _f)
{
	if (*EButton::dragged_button->drag_is_positive)
	{
		Entity::AutobuildingGroupElement* swap_element = get_entity()->autobuilding_group_list.at(get_autobuilding_group_id())->autobuilding_group_element_list.at(EButton::dragged_button->data_id);

		get_entity()->autobuilding_group_list.at(get_autobuilding_group_id())->autobuilding_group_element_list.at(EButton::dragged_button->data_id)
			=
			get_entity()->autobuilding_group_list.at(get_autobuilding_group_id())->autobuilding_group_element_list.at(EButton::dragged_button->data_id + 1);

		get_entity()->autobuilding_group_list.at(get_autobuilding_group_id())->autobuilding_group_element_list.at(EButton::dragged_button->data_id + 1) = swap_element;
	}
	else
	{
		Entity::AutobuildingGroupElement* swap_element = get_entity()->autobuilding_group_list.at(get_autobuilding_group_id())->autobuilding_group_element_list.at(EButton::dragged_button->data_id);

		get_entity()->autobuilding_group_list.at(get_autobuilding_group_id())->autobuilding_group_element_list.at(EButton::dragged_button->data_id)
			=
			get_entity()->autobuilding_group_list.at(get_autobuilding_group_id())->autobuilding_group_element_list.at(EButton::dragged_button->data_id - 1);

		get_entity()->autobuilding_group_list.at(get_autobuilding_group_id())->autobuilding_group_element_list.at(EButton::dragged_button->data_id - 1) = swap_element;
		//std::cout << "elements " << std::to_string(EButton::dragged_button->data_id) << " and " << std::to_string(EButton::dragged_button->data_id - 1) << " swapped" << std::endl;
	}
}

void ExternalButtonAction::external_button_action_drag_autobuilding_group(EButton* _b, float _f)
{
	Entity::AutobuildingGroup* swap_element = get_entity()->autobuilding_group_list.at(EButton::dragged_button->data_id);
	int swap_direction = 1;
	if (!*EButton::dragged_button->drag_is_positive) { swap_direction = -1; }

	get_entity()->autobuilding_group_list.at(EButton::dragged_button->data_id)
		=
		get_entity()->autobuilding_group_list.at(EButton::dragged_button->data_id + swap_direction);

	get_entity()->autobuilding_group_list.at(EButton::dragged_button->data_id + swap_direction) = swap_element;
}

void ExternalButtonAction::external_button_action_save_map(EButton* _b, float _f)
{
	EWindowMain::save_map("test");
}

void ExternalButtonAction::external_button_action_load_map(EButton* _b, float _f)
{
	EWindowMain::load_map("test");
}

void ExternalButtonAction::external_button_action_change_normal_color_for_vertex(EButton* _b, float _f)
{
	if
	(
			(EWindowMain::link_to_button_vertex_editor->polygon_massive != NULL)
			&&
			(EWindowMain::link_to_button_vertex_editor->polygon_massive->shape_list.at(0) != NULL)
			&&
			(EWindowMain::link_to_button_vertex_editor->polygon_massive->shape_list.at(0)->selected_vertex != NULL)
	)
	{
		*EWindowMain::link_to_button_vertex_editor->polygon_massive->shape_list.at(0)->selected_vertex->float_vector.at(0)
		=
		*_b->two_dimension_gradient->value_x;

		*EWindowMain::link_to_button_vertex_editor->polygon_massive->shape_list.at(0)->selected_vertex->float_vector.at(1)
		=
		*_b->two_dimension_gradient->value_y;
	}
}

void ExternalButtonAction::external_button_action_change_sun_position(EButton* _b, float _f)
{
	if (_b->two_dimension_gradient != NULL)
	{
		EGraphicCore::sun_position_x = *_b->two_dimension_gradient->value_x;
		EGraphicCore::sun_position_y = *_b->two_dimension_gradient->value_y;
	}
}

Entity* ExternalButtonAction::get_entity()
{
	if
	(
		(EWindowMain::group_grid_entity_list_link->selected_button != NULL)
		&&
		(EWindowMain::group_grid_entity_list_link->selected_button->data_id >= 0)
		&&
		(EWindowMain::group_grid_entity_list_link->selected_button->data_id < EWindowMain::selected_entities.size())
	)
	{
		return EWindowMain::selected_entities.at(EWindowMain::group_grid_entity_list_link->selected_button->data_id);
	}
	else
	{
		return NULL;
	}
	
}

bool ExternalButtonAction::valid_entity_select()
{
	return ((!EWindowMain::selected_entities.empty()) & (EWindowMain::group_grid_entity_list_link->selected_button != NULL));
}

int ExternalButtonAction::get_autobuilding_base_id()
{
	if (EWindowMain::button_group_autobuilding_base->selected_button != NULL)
	{
		return EWindowMain::button_group_autobuilding_base->selected_button->data_id;
	}
	else
	{
		return -1;
	}
}

int ExternalButtonAction::get_autobuilding_group_element_id()
{
	if (EWindowMain::button_group_autobuilding_group_element->selected_button != NULL)
	{
		return EWindowMain::button_group_autobuilding_group_element->selected_button->data_id;
	}
	else
	{
		return -1;
	}
}

int ExternalButtonAction::get_autobuilding_group_id()
{
	if (EWindowMain::button_group_autobuilding_group->selected_button != NULL)
	{
		//std::cout << "selected group ID [" << std::to_string(EWindowMain::button_group_autobuilding_group->selected_button->data_id) << "]" << std::endl;
		return EWindowMain::button_group_autobuilding_group->selected_button->data_id;
	}
	else
	{
		return -1;
	}
}

Entity::AutobuildingGroup* ExternalButtonAction::get_selected_autobuilding_group(Entity* _e)
{
	//std::cout << "!@! " << std::to_string(get_autobuilding_group_id()) << std::endl;
	//std::cout << "#$# " << std::to_string(_e->autobuilding_group_list.size()) << std::endl;
	if ((_e != NULL) && (!_e->autobuilding_group_list.empty()) && (get_autobuilding_group_id() >= 0) && (get_autobuilding_group_id()< _e->autobuilding_group_list.size()))
	{
		
		//return NULL;
		return _e->autobuilding_group_list.at(get_autobuilding_group_id());
	}
	else
	{
		return NULL;
	}
}

Entity::AutobuildingGroupElement* ExternalButtonAction::get_selected_autobuilding_group_element(Entity* _e, std::string _text)
{
	//have entity, selected group, select element group
	if
		(
			(_e != NULL)
			&&
			(get_autobuilding_group_id() != -1)
			&&
			(get_autobuilding_group_element_id() != -1)
			&&
			(get_autobuilding_group_id() < _e->autobuilding_group_list.size())
			&&
			(get_autobuilding_group_element_id() < _e->autobuilding_group_list.at(get_autobuilding_group_id())->autobuilding_group_element_list.size())
		)
	{
		return _e->autobuilding_group_list.at(get_autobuilding_group_id())->
			autobuilding_group_element_list.at(get_autobuilding_group_element_id());
	}
	else
	{
		if (_text != "")
		{
			std::cout << "Source: " << _text << std::endl;
			if (_e == NULL) { std::cout << "ERROR: entity is null"; }
			else
			{
				if (get_autobuilding_group_id() < 0) { std::cout << "ERROR: selected group is [" << std::to_string(get_autobuilding_group_id()) << "]" << std::endl; }

				int AAA = get_autobuilding_group_id();
				int BBB = _e->autobuilding_group_list.size();

				if (AAA >= BBB)
				{


					std::cout
						<< "ERROR: selected group is ["
						<< std::to_string(AAA)
						<< "], but vector size is ["
						<< std::to_string(BBB)
						<< "]"
						<< std::endl;
				}


			}
		}

		return NULL;
	}
}

Entity::AutobuildingBase* ExternalButtonAction::get_selected_autobuilding_base(Entity* _e)
{
	if ((_e != NULL) && (get_autobuilding_base_id() >= 0) && (get_autobuilding_base_id() < _e->autobuilding_base_list.size()))
	{
		return _e->autobuilding_base_list.at(get_autobuilding_base_id());
	}
	else
	{
		if (_e == NULL) { std::cout << "ERROR: entity is null"; }
		else
		{
			if (get_autobuilding_base_id() < 0) { std::cout << "ERROR: selected base is [" << std::to_string(get_autobuilding_base_id()) << std::endl; }
			
			if (get_autobuilding_base_id() >= _e->autobuilding_base_list.size())
			{ 
				std::cout
				<< "ERROR: selected base is ["
				<< std::to_string(get_autobuilding_base_id())
				<< "], but vector size is ["
				<< std::to_string(_e->autobuilding_base_list.size())
				<< "]"
				<< std::endl; 
			}

		}
		
		return NULL;
	}
}