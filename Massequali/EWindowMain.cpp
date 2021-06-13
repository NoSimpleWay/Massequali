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


	EButton::button_group* just_created_button_group = new EButton::button_group();
	just_created_button_super_group->button_group_list.push_back(just_created_button_group);
	*just_created_button_group->can_be_stretched_x = false;
	*just_created_button_group->can_be_stretched_y = false;
	*just_created_button_group->size_x = 512.0f;
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
			but = new EButton(0.0f, 0.0f, 50.0f, 50.0f);
			but->master_window = this;
			just_created_button_group->button_list.push_back(but);

			but->description_text = "" + p.path().filename().u8string().substr(0, p.path().filename().u8string().length() - 4);
			but->gabarite = ETextureAtlas::put_texture_to_atlas(p.path().u8string(), EWindow::default_texture_atlas);
			but->have_icon = true;

			*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_X;
			

		}
	}

	but = new EButton(*just_created_button_group->size_x - 20.0f, 0.0f, 18.0f, *just_created_button_group->size_y);
	but->master_window = this;
	but->is_slider = true;
	but->slider_is_horizontal = false;
	just_created_button_group->button_list.push_back(but);
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_FREE;
	textures_selector_slider = but;
	
	
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

	just_created_button_group = new EButton::button_group();
	just_created_button_super_group->button_group_list.push_back(just_created_button_group);

	but = new EButton(0.0f, 0.0f, 512.0f, 20.0f);
	but->master_window = this;
	*but->selected_auto_align_mode = EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_NONE;
	just_created_button_group->button_list.push_back(but);
	but->have_input_mode = true;


}

EWindowMain::~EWindowMain()
{
}
