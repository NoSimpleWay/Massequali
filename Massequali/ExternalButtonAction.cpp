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
	EButton* target_button = EWindowMain::grid_region_button_link;

	target_grid_region = EWindowMain::grid_region_button_link->grid_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT_UP_CORNER);
	*target_grid_region->position_x		= 0.0f;
	*target_grid_region->position_y		= target_button->button_size_y / target_button->icon_size_multiplier - target_value_up;
	*target_grid_region->size_x			= target_value_left;
	*target_grid_region->size_y			= target_value_up;

	target_grid_region = EWindowMain::grid_region_button_link->grid_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_UP);
	*target_grid_region->position_x		= target_value_left;
	*target_grid_region->position_y		= target_button->button_size_y / target_button->icon_size_multiplier - target_value_up;
	*target_grid_region->size_x			= target_button->button_size_x / target_button->icon_size_multiplier - target_value_left - target_value_right;
	*target_grid_region->size_y			= target_value_up;

	target_grid_region = EWindowMain::grid_region_button_link->grid_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT_UP_CORNER);
	*target_grid_region->position_x		= target_button->button_size_x / target_button->icon_size_multiplier - target_value_right;
	*target_grid_region->position_y		= target_button->button_size_y / target_button->icon_size_multiplier - target_value_up;
	*target_grid_region->size_x			= target_value_right;
	*target_grid_region->size_y			= target_value_up;



	target_grid_region = EWindowMain::grid_region_button_link->grid_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT);
	*target_grid_region->position_x = 0.0f;
	*target_grid_region->position_y = target_value_down;
	*target_grid_region->size_x = target_value_left;
	*target_grid_region->size_y = target_button->button_size_y / target_button->icon_size_multiplier - target_value_up - target_value_down;

	target_grid_region = EWindowMain::grid_region_button_link->grid_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_MID);
	*target_grid_region->position_x = target_value_left;
	*target_grid_region->position_y = target_value_down;
	*target_grid_region->size_x = target_button->button_size_x / target_button->icon_size_multiplier - target_value_left - target_value_right;
	*target_grid_region->size_y = target_button->button_size_y / target_button->icon_size_multiplier - target_value_up - target_value_down;

	target_grid_region = EWindowMain::grid_region_button_link->grid_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT);
	*target_grid_region->position_x = target_button->button_size_x / target_button->icon_size_multiplier - target_value_right;
	*target_grid_region->position_y = target_value_down;
	*target_grid_region->size_x = target_value_right;
	*target_grid_region->size_y = target_button->button_size_y / target_button->icon_size_multiplier - target_value_up - target_value_down;



	target_grid_region = EWindowMain::grid_region_button_link->grid_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_LEFT_DOWN_CORNER);
	*target_grid_region->position_x = 0.0f;
	*target_grid_region->position_y = 0.0f;
	*target_grid_region->size_x = target_value_left;
	*target_grid_region->size_y = target_value_down;
	
	target_grid_region = EWindowMain::grid_region_button_link->grid_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_DOWN);
	*target_grid_region->position_x = target_value_left;
	*target_grid_region->position_y = 0.0f;
	*target_grid_region->size_x = target_button->button_size_x / target_button->icon_size_multiplier - target_value_left - target_value_right;
	*target_grid_region->size_y = target_value_down;

	target_grid_region = EWindowMain::grid_region_button_link->grid_region_list.at(EWindowMain::GridRegionNameByOrder::GRID_REGION_NAME_BY_ORDER_RIGHT_DOWN_CORNER);
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
