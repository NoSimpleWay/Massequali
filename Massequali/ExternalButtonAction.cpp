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
	*target_grid_region->position_x		= 0.0f;
	*target_grid_region->position_y		= target_button->button_size_y / target_button->icon_size_multiplier - target_value_up;
	*target_grid_region->size_x			= target_value_left;
	*target_grid_region->size_y			= target_value_up;

	target_grid_region = EWindowMain::grid_region_edit_button_link->grid_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_UP);
	*target_grid_region->position_x		= target_value_left;
	*target_grid_region->position_y		= target_button->button_size_y / target_button->icon_size_multiplier - target_value_up;
	*target_grid_region->size_x			= target_button->button_size_x / target_button->icon_size_multiplier - target_value_left - target_value_right;
	*target_grid_region->size_y			= target_value_up;

	target_grid_region = EWindowMain::grid_region_edit_button_link->grid_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT_UP_CORNER);
	*target_grid_region->position_x		= target_button->button_size_x / target_button->icon_size_multiplier - target_value_right;
	*target_grid_region->position_y		= target_button->button_size_y / target_button->icon_size_multiplier - target_value_up;
	*target_grid_region->size_x			= target_value_right;
	*target_grid_region->size_y			= target_value_up;



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

void ExternalButtonAction::external_button_action_import_data_from_entity_to_autobuilding_interface(EButton* _b, float _f)
{
	Entity* en = NULL;

	if (valid_entity_select())
	{
		en = get_entity();
		EWindowMain::import_data_from_entity_to_autobuilding_interface(en);

		for (int i = 0; i < EWindowMain::group_grid_all_autobuilding_regions_link->button_list.size(); i++)
		if (*EWindowMain::group_grid_all_autobuilding_regions_link->button_list.at(i)->can_be_selected)
		{
			if (i < en->autobuilding_region_list.size())
			{
				EWindowMain::group_grid_all_autobuilding_regions_link->button_list.at(i)->is_active = true;
				EWindowMain::group_grid_all_autobuilding_regions_link->button_list.at(i)->gabarite = en->autobuilding_region_list.at(i)->main_texture;
				//EWindowMain::group_grid_all_autobuilding_regions_link->button_list.at(i)->icon_color->set_color(EColor::COLOR_WHITE);
				//EWindowMain::group_grid_all_autobuilding_regions_link->button_list.at(i)->text_color->set_color(EColor::COLOR_BLACK);
			}
			else
			{
				EWindowMain::group_grid_all_autobuilding_regions_link->button_list.at(i)->is_active = false;
				//EWindowMain::group_grid_all_autobuilding_regions_link->button_list.at(i)->icon_color->set_color(EColor::COLOR_RED);
				//EWindowMain::group_grid_all_autobuilding_regions_link->button_list.at(i)->text_color->set_color(EColor::COLOR_RED);
			}
		}

		for (int i = 0; i < EWindowMain::group_grid_autobuilding_group_texture_container->button_list.size(); i++)
		if (*EWindowMain::group_grid_autobuilding_group_texture_container->button_list.at(i)->can_be_selected)
		{
			if
			(
				(EWindowMain::group_grid_autobuilding_group_selector->selected_button != NULL)
				&&
				(!en->autobuilding_region_group_list.empty())
				&&
				(!en->autobuilding_region_group_list.at(get_autobuilding_element_region_id())->AB_entity_region_element_list.empty())
				&&
				(i < en->autobuilding_region_group_list.at(get_autobuilding_element_region_id())->AB_entity_region_element_list.size())
			)
			{
				EWindowMain::group_grid_autobuilding_group_texture_container->button_list.at(i)->is_active = true;
				EWindowMain::group_grid_autobuilding_group_texture_container->button_list.at(i)->gabarite = en->autobuilding_region_list.at(i)->main_texture;
				//EWindowMain::group_grid_all_autobuilding_regions_link->button_list.at(i)->icon_color->set_color(EColor::COLOR_WHITE);
				//EWindowMain::group_grid_all_autobuilding_regions_link->button_list.at(i)->text_color->set_color(EColor::COLOR_BLACK);
			}
			else
			{
				EWindowMain::group_grid_autobuilding_group_texture_container->button_list.at(i)->is_active = false;
				//EWindowMain::group_grid_all_autobuilding_regions_link->button_list.at(i)->icon_color->set_color(EColor::COLOR_RED);
				//EWindowMain::group_grid_all_autobuilding_regions_link->button_list.at(i)->text_color->set_color(EColor::COLOR_RED);
			}
		}

		for (int i = 0; i < EWindowMain::group_grid_autobuilding_group_selector->button_list.size(); i++)
		if (*EWindowMain::group_grid_autobuilding_group_selector->button_list.at(i)->can_be_selected)
		{
			if
			(
				(i < en->autobuilding_region_group_list.size())
			)
			{
				EWindowMain::group_grid_autobuilding_group_selector->button_list.at(i)->is_active = true;
				//EWindowMain::group_grid_autobuilding_group_selector->button_list.at(i)->gabarite = en->autobuilding_region_list.at(i)->main_texture;
				//EWindowMain::group_grid_all_autobuilding_regions_link->button_list.at(i)->icon_color->set_color(EColor::COLOR_WHITE);
				//EWindowMain::group_grid_all_autobuilding_regions_link->button_list.at(i)->text_color->set_color(EColor::COLOR_BLACK);
			}
			else
			{
				EWindowMain::group_grid_autobuilding_group_selector->button_list.at(i)->is_active = false;
				//EWindowMain::group_grid_all_autobuilding_regions_link->button_list.at(i)->icon_color->set_color(EColor::COLOR_RED);
				//EWindowMain::group_grid_all_autobuilding_regions_link->button_list.at(i)->text_color->set_color(EColor::COLOR_RED);
			}
		}

		if (EWindowMain::group_grid_autobuilding_group_selector->selected_button != NULL)
		{
			external_button_action_select_autobuilding_group(EWindowMain::group_grid_autobuilding_group_selector->selected_button, 0.0f);
		}
	}
}

void ExternalButtonAction::external_button_action_add_new_autobuilding_region(EButton* _b, float _f)
{
	for (EButton* b : EWindowMain::group_grid_all_autobuilding_regions_link->button_list)
	{
		if (!b->is_active)
		{
			b->is_active = true;
			//b->gabarite = ETextureAtlas::put_texture_to_atlas("data/textures/hrusch_wall_main_002_v1.png", EWindow::default_texture_atlas);
			b->gabarite = EWindowMain::group_texture_collection_link->button_list.at(rand() % EWindowMain::group_texture_collection_link->button_list.size())->gabarite;
			Entity* en = NULL;

			if (valid_entity_select())
			{
				en = get_entity();

				Entity::AutobuildingRegionTexture* just_created_autobuilding_region = new Entity::AutobuildingRegionTexture();
				en->autobuilding_region_list.push_back(just_created_autobuilding_region);
				just_created_autobuilding_region->main_texture = b->gabarite;
			}
			b->update(0.1f);
			b->update_additional(0.1f);
			break;
		}
	}

	EButton::update_data_id_for_buttons(EWindowMain::group_grid_all_autobuilding_regions_link);
}

void ExternalButtonAction::external_button_action_remove_autobuilding_region(EButton* _b, float _f)
{
	if (valid_entity_select())
	{

		//search destroyed texture region on autobuilding regions
		int id = 0;
		for (Entity::AutobiuldingRegionGroup* a_group : get_entity()->autobuilding_region_group_list)
		for (Entity::AutobuildingRegionEntityElement* a_element : a_group->AB_entity_region_element_list)
		{
			if (a_element->autobuilding_texture_region == get_entity()->autobuilding_region_list.at(_b->data_id))
			{
				a_group->AB_entity_region_element_list.erase(a_group->AB_entity_region_element_list.begin() + id);

				EWindowMain::group_grid_autobuilding_group_texture_container->button_list.at(id)->is_active = false;


			}

			id++;
		}



		get_entity()
		->
		autobuilding_region_list.erase
								(
									get_entity()
									->
									autobuilding_region_list.begin()
									+
									_b->data_id
								);

		_b->is_active = false;

		

		EButton::update_data_id_for_buttons(EWindowMain::group_grid_all_autobuilding_regions_link);
		EButton::update_data_id_for_buttons(EWindowMain::group_grid_autobuilding_group_texture_container);
	}
}

void ExternalButtonAction::external_button_action_select_texture_region_button(EButton* _b, float _f)
{
	if (valid_entity_select())
	{
		EWindowMain::grid_region_edit_button_link->gabarite
		=
			get_entity()->autobuilding_region_list.at(_b->data_id)->main_texture;

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
			get_entity()->autobuilding_region_list.at(_b->data_id)->texture_region_list;



	}
}

void ExternalButtonAction::external_button_action_open_select_texture_window_for_autobuilding_region(EButton* _b, float _f)
{
	*EWindowMain::super_group_texture_collection_link->is_active = true;

	for (EButton* b : EWindowMain::group_texture_collection_link->button_list)
	if (*b->can_be_selected)
	{
		b->action_on_left_click.clear();
		b->action_on_left_click.push_back(&external_button_action_select_texture_for_autobuilding_region);
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
		autobuilding_region_list.at(get_autobuilding_texture_region_id())->
		main_texture
		=
		_b->gabarite;

		EWindowMain::group_grid_all_autobuilding_regions_link->selected_button->gabarite = _b->gabarite;

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
		

		if (EWindowMain::group_grid_autobuilding_group_selector->selected_button != NULL)
		{
			external_button_action_select_autobuilding_group(EWindowMain::group_grid_autobuilding_group_selector->selected_button, 0.0f);
		}
	}
}

void ExternalButtonAction::external_button_action_add_selected_region_to_autobuilding_group(EButton* _b, float _f)
{
	if
	(
		(!EWindowMain::selected_entities.empty())
		&
		(EWindowMain::group_grid_entity_list_link->selected_button != NULL)
		&
		(EWindowMain::group_grid_autobuilding_group_selector->selected_button != NULL)
		&
		(EWindowMain::group_grid_all_autobuilding_regions_link->selected_button != NULL)
	)
	{
		Entity::AutobuildingRegionEntityElement* just_created_autobuilding_entity_element = new Entity::AutobuildingRegionEntityElement();
		//Entity::AutobuildingRegionTexture* just_created_autobuilding_texture = new Entity::AutobuildingRegionTexture();


		just_created_autobuilding_entity_element->autobuilding_texture_region
		=
			get_entity()->
		autobuilding_region_list.at(get_autobuilding_texture_region_id());


		get_entity()
		->
		autobuilding_region_group_list.at(get_autobuilding_element_region_id())
		->
		AB_entity_region_element_list.push_back(just_created_autobuilding_entity_element);

		for (EButton* b : EWindowMain::group_grid_autobuilding_group_texture_container->button_list)
		{
			if (!b->is_active)
			{
				b->is_active = true;
				b->gabarite = just_created_autobuilding_entity_element->autobuilding_texture_region->main_texture;

				break;
			}
		}

		EButton::update_data_id_for_buttons(EWindowMain::group_grid_autobuilding_group_texture_container);
	}
	else
	{
		if (EWindowMain::selected_entities.empty())
		{ std::cout << "ERROR: selected entity list is NULL" << std::endl; }

		if (EWindowMain::group_grid_entity_list_link->selected_button == NULL)
		{ std::cout << "ERROR: entity not selected" << std::endl; }

		if (EWindowMain::group_grid_autobuilding_group_selector->selected_button == NULL)
		{ std::cout << "ERROR: group not selected" << std::endl; }

		if (EWindowMain::group_grid_all_autobuilding_regions_link->selected_button == NULL)
		{ std::cout << "ERROR: texture region not selected" << std::endl; }
	}
}

void ExternalButtonAction::external_button_action_add_new_group_for_autobuilding(EButton* _b, float _f)
{
	if (valid_entity_select())
	{
		for (EButton* b : EWindowMain::group_grid_autobuilding_group_selector->button_list)
		{
			if (!b->is_active)
			{
				b->is_active = true;

				Entity* en = get_entity();

				en->autobuilding_region_group_list.push_back(new Entity::AutobiuldingRegionGroup());

				break;
			}
		}
	}

	EButton::update_data_id_for_buttons(EWindowMain::group_grid_autobuilding_group_selector);
}

void ExternalButtonAction::external_button_action_select_autobuilding_group(EButton* _b, float _f)
{
	if (valid_entity_select())
	{
		for (int i = 0; i < EWindowMain::group_grid_autobuilding_group_texture_container->button_list.size(); i++)
		if (*EWindowMain::group_grid_autobuilding_group_texture_container->button_list.at(i)->can_be_selected)
		{
			if (i < get_entity()->autobuilding_region_group_list.at(_b->data_id)->AB_entity_region_element_list.size())
			{
				EWindowMain::group_grid_autobuilding_group_texture_container->button_list.at(i)->is_active = true;

				EWindowMain::group_grid_autobuilding_group_texture_container->button_list.at(i)->gabarite
				=
				get_entity()->
				autobuilding_region_group_list.at(_b->data_id)->
				AB_entity_region_element_list.at(i)->autobuilding_texture_region->main_texture;
			}
			else
			{
				EWindowMain::group_grid_autobuilding_group_texture_container->button_list.at(i)->is_active = false;
			}
		}
	}
}

void ExternalButtonAction::external_button_action_remove_autobuilding_group_element(EButton* _b, float _f)
{
	if (valid_entity_select())
	{
		get_entity()->autobuilding_region_group_list.at(get_autobuilding_element_region_id())->AB_entity_region_element_list.erase
			(
				get_entity()
				->
				autobuilding_region_group_list.at(get_autobuilding_element_region_id())->AB_entity_region_element_list.begin()
				+
				_b->data_id
			);

		_b->is_active = false;

		EButton::update_data_id_for_buttons(EWindowMain::group_grid_autobuilding_group_texture_container);
	}
}

Entity* ExternalButtonAction::get_entity()
{
	return EWindowMain::selected_entities.at(EWindowMain::group_grid_entity_list_link->selected_button->data_id);
}

bool ExternalButtonAction::valid_entity_select()
{

	return ((!EWindowMain::selected_entities.empty()) & (EWindowMain::group_grid_entity_list_link->selected_button != NULL));
}

int ExternalButtonAction::get_autobuilding_texture_region_id()
{
	return EWindowMain::group_grid_all_autobuilding_regions_link->selected_button->data_id;
}

int ExternalButtonAction::get_autobuilding_element_region_id()
{
	return EWindowMain::group_grid_autobuilding_group_selector->selected_button->data_id;
}
