#include "EWindow.h"
//#include "../../../EBA.h"


GLFWwindow* EWindow::main_window = NULL;

std::vector<EWindow*> EWindow::window_list;

ETextureAtlas* EWindow::default_texture_atlas;
ETextureAtlas* EWindow::shadow_FBO;
ETextureAtlas* EWindow::shadow_ground_FBO;
ETextureAtlas* EWindow::lightmap_FBO;
ETextureAtlas* EWindow::lightmap_FBO2;
ETextureAtlas* EWindow::base_lightmap;
ETextureAtlas* EWindow::base_blockmap;

ETextureAtlas* EWindow::screen_FBO;








unsigned int EWindow::transformLoc;

double EWindow::mouse_x = 0;
double EWindow::mouse_y = 0;

int EWindow::saved_pos_x = 0;
int EWindow::saved_pos_y = 0;

int EWindow::prev_mouse_x = 0;
int EWindow::prev_mouse_y = 0;

float EWindow::mouse_speed_x = 0.0f;
float EWindow::mouse_speed_y = 0.0f;

float EWindow::real_mouse_x;
float EWindow::real_mouse_y;

bool EWindow::LMB = false;
bool EWindow::RMB = false;

bool EWindow::button_pressed = false;
bool EWindow::button_main_group_pressed = false;

bool EWindow::button_right_pressed = false;
bool EWindow::button_backspace_released = true;


//bool EWindow::is_active = true;

float EWindow::delete_button_hold_time = 0.0f;

char EWindow::last_inputed_char = NULL;

int EWindow::time_process_rota_id = 0;

std::vector<EWindow::time_process_struct*> EWindow::tps_list;

bool EWindow::system_button_release = true;
double EWindow::scroll = 0;


std::chrono::time_point<std::chrono::high_resolution_clock> EWindow::start, EWindow::stop;

EWindowMain* EWindow::window_main;
//std::pair<float, std::string> EWindow::time_process;

int EButton::top_window_id = -1;
//void (*zzz)();

//void (*action_on_left_click)(EButton* _b, float _d);

bool EButton::any_input = false;
bool EButton::any_overlap = false;

std::vector <EWindow::massive_style*> EWindow::list_of_massive_style;


EButton::EButton()
{
	update_localisation();

}

void EButton::static_click()
{
	std::cout << "STATIC CLICK!!!" << std::endl;
}

void EButton::static_click2()
{
	std::cout << "STATIC CLICK2!!!" << std::endl;
}




void EButton::set_left_click_action(void(*function)(EButton*, float))
{
	//action_on_left_click = function;
}

EButton::EButton(float _x, float _y, float _sx, float _sy)
{
	//EBA::foo = &EButton::static_click;
	//EBA::foo = NULL;

	/*if (rand() % 100 < 50)
	{
		EBA::set_method(&static_click);
	}
	else
	{
		EBA::set_method(&static_click2);
	}*/

	button_x_offset = _x;
	button_y_offset = _y;

	button_base_x = _x;
	button_base_y = _y;

	button_size_x = _sx;
	button_size_y = _sy;

	button_min_size_x = _sx;
	button_min_size_y = _sy;

	update_localisation();

	//action_on_left_click = &EBA::action_add_new_sprite;


}




EButton::~EButton()
{

}

bool EButton::is_number(char _c)
{
	if
		(
			(_c == '-') ||
			(_c == '.') ||
			(_c == '0') ||
			(_c == '1') ||
			(_c == '2') ||
			(_c == '3') ||
			(_c == '4') ||
			(_c == '5') ||
			(_c == '6') ||
			(_c == '7') ||
			(_c == '8') ||
			(_c == '9')
			)
	{
		return true;
	}

	return false;
}

bool EButton::is_overlap()
{

	//ETexture::texture[0] = 0;
	//std::cout << "" << std::endl;

	//std::cout << Helper::x << " " << Helper::y << " " << std::endl;
	//std::cout << "PIZDOS=" << EMouse::mouse_x<< endl;
	if
		(
			(EWindow::mouse_x > master_position_x - bound_size_left)
			&&
			(EWindow::mouse_x < master_position_x + button_size_x + bound_size_right)
			&&
			(EWindow::mouse_y > master_position_y - bound_size_down)
			&&
			(EWindow::mouse_y < master_position_y + button_size_y + bound_size_up)
			&&
			(top_window_id == master_window->id)
			)
	{
		return true;
	}
	else
	{
		return false;
	}
	//return false;
}

bool EButton::is_click()
{
	if ((EWindow::LMB) && (!EWindow::button_pressed) && (is_overlap())) { return true; }

	return false;
}

bool EButton::is_outclick()
{
	if ((EWindow::LMB) && (!is_overlap()) && (!outclick_protection)) { return true; }

	return false;
}

bool EButton::is_right_click()
{
	if ((EWindow::RMB) && (!EWindow::button_right_pressed) && (is_overlap())) { EWindow::button_right_pressed = true; return true; }

	return false;
}

void EButton::update(float _d)
{

	if (*is_consumable)
	{
		if
		(
			(
				(is_slider)
				||
				(*is_radial_button)
			)
			&
			(target_address_for_float != NULL)
		)
		{
			slider_value = *target_address_for_float;
		}

		if ((*is_checkbox) & (target_address_for_bool != NULL))
		{
			*is_checked = *target_address_for_bool;
		}

		if ((*is_checkbox) & (target_address_for_short != NULL))
		{
			*is_checked = bool(*target_address_for_short);
		}

		if ((is_drop_list) &(target_address_for_int != NULL))
		{
			selected_element = *target_address_for_int;
		}

		if ((have_text) & (target_address_for_string != NULL))
		{
			text = *target_address_for_string;
		}
	}

	if ((is_overlap()) & (have_input_mode) & (input_only_numbers) & (text != "") & (EWindow::scroll != 0))
	{
		text = EString::float_to_string(EMath::to_float(text) + EWindow::scroll);
		input_finish_event();

		if (action_on_input_finish != NULL) { action_on_input_finish(this, _d); }
	}

	if
		(
			(can_receive_paste)
			&&
			(is_overlap())
			&&
			(glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
			&&
			(glfwGetKey(EWindow::main_window, GLFW_KEY_V) == GLFW_PRESS)
			)
	{
		if (!OpenClipboard(nullptr))
		{
		}

		// Get handle of clipboard object for ANSI text
		HANDLE hData = GetClipboardData(CF_TEXT);
		if (hData == nullptr)
		{
		}

		// Lock the handle to get the actual text pointer
		char* pszText = static_cast<char*>(GlobalLock(hData));
		if (pszText == nullptr)
		{
		}

		// Save text in a string class instance
		std::string clipboard_text(pszText);
		text = clipboard_text;

		// Release the lock
		GlobalUnlock(hData);

		// Release the clipboard
		CloseClipboard();

		if (is_input_mode_active)
		{
			input_event();

			if (action_on_input != NULL)
			{
				action_on_input(this, _d);
			}
		}

		//if (master_block != NULL) { StaticData::window_filter_block->unsave_change = true; }
		//if (master_separator != NULL) { StaticData::window_filter_block->unsave_change = true; }
	}

	if
		(
			(is_overlap())
			&&
			(glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
			&&
			(glfwGetKey(EWindow::main_window, GLFW_KEY_C) == GLFW_PRESS)
			)
	{
		const char* output = text.c_str();
		const size_t len = strlen(output) + 1;
		HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
		memcpy(GlobalLock(hMem), output, len);
		GlobalUnlock(hMem);
		OpenClipboard(0);
		EmptyClipboard();
		SetClipboardData(CF_TEXT, hMem);
		CloseClipboard();
	}
	//std::cout << "clipboard [" << (text) << "]" << std::endl;

	if (is_outclick())
	{
		//if (text == "") { text = "0"; }

		if ((input_only_numbers) && (text == ""))
		{
			text = "0";
		}

		if ((is_expanded) && (is_drop_list))
		{
			is_expanded = false;
		}

		if (is_input_mode_active)
		{
			is_input_mode_active = false;
			input_finish_event();

			if (action_on_input_finish != NULL) { action_on_input_finish(this, _d); }
		}
	}

	if (!EWindow::LMB)
	{
		outclick_protection = false;
	}

	//cout << main_window << endl;




	if ((master_position == Enums::PositionMaster::WINDOW) && (master_window != NULL))
	{
		if (position_mode_x == Enums::PositionMode::LEFT) { master_position_x = master_window->offset_x + button_x_offset; }
		if (position_mode_x == Enums::PositionMode::MID) { master_position_x = master_window->offset_x + (master_window->window_size_x - button_size_x) / 2.0f + button_x_offset; }
		if (position_mode_x == Enums::PositionMode::RIGHT) { master_position_x = master_window->offset_x + master_window->window_size_x + button_x_offset - button_size_x; }

		if (position_mode_y == Enums::PositionMode::DOWN) { master_position_y = master_window->offset_y + button_y_offset; }
		if (position_mode_y == Enums::PositionMode::MID) { master_position_y = master_window->offset_y + (master_window->window_size_y - button_size_y) / 2.0f + button_y_offset; }
		if (position_mode_y == Enums::PositionMode::UP) { master_position_y = master_window->offset_y + master_window->window_size_y + button_y_offset - button_size_y; }
	}

	if ((master_position == Enums::PositionMaster::BUTTON) && (master_button != NULL))
	{
		if (position_mode_x == Enums::PositionMode::SUPER_LEFT) { master_position_x = master_button->master_position_x + button_x_offset - master_button->button_size_x; }
		if (position_mode_x == Enums::PositionMode::LEFT) { master_position_x = master_button->master_position_x + button_x_offset; }
		if (position_mode_x == Enums::PositionMode::MID) { master_position_x = master_button->master_position_x + (master_button->button_size_x - button_size_x) / 2.0f + button_x_offset; }
		if (position_mode_x == Enums::PositionMode::RIGHT) { master_position_x = master_button->master_position_x + master_button->button_size_x + button_x_offset - button_size_x; }
		if (position_mode_x == Enums::PositionMode::SUPER_RIGHT) { master_position_x = master_button->master_position_x + master_button->button_size_x + button_x_offset; }

		if (position_mode_y == Enums::PositionMode::UP) { master_position_y = master_button->master_position_y + button_y_offset + master_button->button_size_y; }
		if (position_mode_y == Enums::PositionMode::MID) { master_position_y = master_button->master_position_y + (master_button->button_size_y - button_size_y) / 2.0f + button_y_offset; }
		if (position_mode_y == Enums::PositionMode::DOWN) { master_position_y = master_button->master_position_y + button_y_offset - button_size_y; }
	}

	if (master_position == Enums::PositionMaster::SCREEN)
	{
		if (position_mode_x == Enums::PositionMode::LEFT) { master_position_x = button_x_offset; }
		if (position_mode_y == Enums::PositionMode::DOWN) { master_position_y = button_y_offset; }
	}

	if (is_right_click())
	{
		right_click_event();


		if (can_be_removed)
		{
			std::cout << "TRY REMOVE" << std::endl;
			*need_remove = true;

			//if (master_block != NULL) { StaticData::window_filter_block->unsave_change = true; }
		}

		if (action_on_right_click != NULL)
		{
			action_on_right_click(this, _d);
		}
	}

	if ((is_overlap()) & (is_drop_list) & (is_expanded))
	{
		selected_element = (int)((master_position_y - EWindow::mouse_y) / 22.0f);

		if (action_on_drop_list_select_element != NULL)
		{
			action_on_drop_list_select_element(this, _d);
		}
	}

	if (is_click())
	{

		if (*is_double_click)
		{*double_click_started = true;}





		
		//(*action_on_left_click)();
		//if (master_block != NULL) { StaticData::window_filter_block->unsave_change = true; }

		if (simple_action_open_window != NULL)
		{
			simple_action_open_window->is_active = true;
		}

		if (!is_holdable) { EWindow::button_pressed = true; }
		std::cout << "Button pressed" << std::endl;

		if (is_drop_list)
		{
			if (is_expanded)
			{
				

				if (selected_element < 0) { selected_element = 0; }
				if (selected_element > drop_elements) { selected_element = drop_elements; }

				text = drop_text.at(selected_element);
				drop_list_select_event();
			}

			is_expanded = !is_expanded;


		}

		std::cout << "try active input mode" << std::endl;
		if ((have_input_mode) && (!is_input_mode_active))
		{
			//any_input = true;
			if (input_auto_clear_text) { text = ""; }
			is_input_mode_active = true;
		}



		if ((is_slider)|| (*is_radial_button)) { slider_activate = true; }


		click_event();

		if (*is_checkbox) {*is_checked = !*is_checked;}

		if ((!action_on_left_click.empty()) & (*click_timer <= 0.0f))
		{
			for (BUTTON_ACTION ba : action_on_left_click)
			{
				ba(this, _d);
			}
		}

		if (*click_timer > 0.0f)
		{
			if (action_on_left_double_click != NULL)
			{
				action_on_left_double_click(this, _d);
			}

			*click_timer = -1.0f;
		}

		
		
	}

	if (!EWindow::LMB)
	{
		slider_activate = false;
	}

	if (((is_slider) || (*is_radial_button)) && (slider_activate) && (slider_is_horizontal))
	{
		//slider_value = (EWindow::mouse_x - master_position_x) / button_size_x;
		//slider_value = EMath::clamp_value_float(slider_value, 0.0f, 1.0f) * slider_value_multiplier;
		//slider_value += , 0.0f, 1.0f;
		float shift_value = 1.0f / button_size_x;
		if
		(
			(glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			||
			(glfwGetKey(EWindow::main_window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
		)
		{
			shift_value *= 0.1f;
		}

		slider_value = EMath::clamp_value_float(slider_value + EWindow::mouse_speed_x * shift_value * slider_value_multiplier * *maximum_value, 0.0f, *maximum_value);

		slider_drag_event();

		if (action_on_slider_drag != NULL)
		{
			action_on_slider_drag(this, _d);
		}
		//if (master_block != NULL) { StaticData::window_filter_block->unsave_change = true; }
	}

	if (((is_slider) || (*is_radial_button)) && (slider_activate) && (!slider_is_horizontal))
	{
		slider_value = 1.0f - (EWindow::mouse_y - master_position_y) / button_size_y;
		slider_value = EMath::clamp_value_float(slider_value, 0.0f, *maximum_value);

		slider_drag_event();

		if (action_on_slider_drag != NULL)
		{
			action_on_slider_drag(this, _d);
		}
		//if (master_block != NULL) { StaticData::window_filter_block->unsave_change = true; }
	}

	if (is_input_mode_active)
	{
		//std::cout << last_inputed_char << std::endl;
		if
			(
				(EWindow::last_inputed_char != NULL)
				&&
				(
					(!input_only_numbers)
					||
					(is_number(EWindow::last_inputed_char))
					)
				&&
				(
					(EFont::active_font->get_width(EFont::active_font, text + EWindow::last_inputed_char) < button_size_x)
					||
					(dynamic_input_width)
					)
				)
		{
			text += EWindow::last_inputed_char;
			EWindow::last_inputed_char = NULL;

			//if (master_block != NULL) { StaticData::window_filter_block->unsave_change = true; }
			input_event();

			if (action_on_input != NULL)
			{
				action_on_input(this, _d);
			}
		}


		//is_button_pressed

		if ((EWindow::delete_button_hold_time > 0.5f) && (is_input_mode_active))
		{
			text = "";

			input_event();

			if (action_on_input != NULL)
			{
				action_on_input(this, _d);
			}
		}

		if
			(
				(
					(glfwGetKey(EWindow::main_window, GLFW_KEY_BACKSPACE) == GLFW_PRESS)
					||
					(glfwGetKey(EWindow::main_window, GLFW_KEY_DELETE) == GLFW_PRESS)
					)
				&&
				(EWindow::button_backspace_released)
				)
		{
			EWindow::button_backspace_released = false;

			if (text.length() > 1)
			{

				text = text.substr(0, text.length() - 1.0f);
				input_event();
			}
			else
			{
				text = "";
				input_event();
				//if (master_block != NULL) { StaticData::window_filter_block->unsave_change = true; }
			}

			if (action_on_input != NULL)
			{
				action_on_input(this, _d);
			}

			//input_event();


		}



		if
			(
				(glfwGetKey(EWindow::main_window, GLFW_KEY_ENTER) == GLFW_PRESS)
				||
				(glfwGetKey(EWindow::main_window, GLFW_KEY_KP_ENTER) == GLFW_PRESS)
				)
		{
			//any_input = false;
			is_input_mode_active = false;

			if ((input_only_numbers) && (text == ""))
			{
				text = "0";
			}

			input_finish_event();
			if (action_on_input_finish != NULL) { action_on_input_finish(this, _d); }
		}


	}

	flash_cooldown -= _d;
	if (flash_cooldown < 0)
	{
		flash_cooldown += 0.25f;

		flash_line_active = !flash_line_active;
	}

	if ((*double_click_started) & (!EWindow::LMB))
	{
		*double_click_started = false;
		*click_timer = 0.2f;
	}

	if (*click_timer >= 0.0f)
	{
		*click_timer -= _d;
	}
	update_additional(_d);

	if
	(
		(is_input_mode_active)
		||
		(slider_activate)
		||
		(is_expanded)
	)
	{
		//text = "+";
		EButton::any_input = true;
	}
	else
	{
		//text = "-";
	}

	if (is_overlap())
	{
		any_overlap = true;
	}
}

void EButton::update_additional(float _d)
{
}

void EButton::default_draw(Batcher* _batch, float _d)
{
	//std::cout << "!" << std::endl;
	EFont::active_font->scale = 1.0f;
	if (is_overlap())
	{
		_batch->setcolor_255(0, 200, 0, 100);
	}
	else
	{
		_batch->setcolor_255(20, 30, 45, 17);
	}

	if (is_input_mode_active)
	{
		_batch->setcolor_255(220, 255, 200, 100);
	}




	//std::cout << "red color is:" << _batch->batch_color_r;




	if ((have_bg)&(EGraphicCore::gabarite_small_wood_button_bg != NULL))
	{
		_batch->setcolor(bg_color);
		_batch->draw_gabarite(master_position_x, master_position_y, button_size_x, button_size_y, EGraphicCore::gabarite_small_wood_button_bg);
	}

	float temp_w = 0;




	if ((have_icon) & (gabarite != NULL))
	{
		if (icon_adaptation)
		{
			//float mul_x = 1;
			//float mul_y = 1;
			float mul = 1;

			float mul_method_vertical = 0.0f;
			float mul_method_horizontal = 0.0f;

			if ((*gabarite->size_x > button_size_x) || (*gabarite->size_y > button_size_y))
			{
				mul_method_vertical = button_size_x / *gabarite->size_x;
				mul_method_horizontal = button_size_y / *gabarite->size_y;

				if (mul_method_vertical < mul_method_horizontal)
				{
					mul = mul_method_vertical;
					mul = mul_method_vertical;
				}
				else
				{
					mul = mul_method_horizontal;
					mul = mul_method_horizontal;
				}
			}

			_batch->setcolor(icon_color);
			_batch->draw_gabarite(master_position_x + (button_size_x - *gabarite->size_x * mul) / 2.0f, master_position_y, *gabarite->size_x * mul, *gabarite->size_y * mul, gabarite);
		}
		else
		{
			_batch->setcolor(EColor::COLOR_WHITE);
			_batch->draw_gabarite(master_position_x, master_position_y, button_size_x, button_size_y, gabarite);
		}
	}

	EFont* target_font = EFont::active_font;



	if (have_text)
	{


		//if (EFont::get_width(EFont::active_font, text) + 5.0f > button_size_x)
		//{
		if (dynamic_input_width)
		{
			button_size_x = EFont::get_width(EFont::active_font, text) + 10.0f;
		}
		//}

		if (button_size_x < button_min_size_x)
		{
			button_size_x = button_min_size_x;
		}

		if (force_font != NULL) { target_font = force_font; }

		float added_x = 0;

		if (text_align_x == Enums::PositionMode::MID) { added_x = round(button_size_x / 2.0f); }
		target_font->align_x = text_align_x;

		if (text != "")
		{
			_batch->setcolor(text_color);
			target_font->draw(_batch, text, master_position_x + 3.0f + added_x, master_position_y + round((button_size_y - 20.0f) / 2.0f + 4.0f));
		}

		if ((text == "") && (input_hint != ""))
		{
			_batch->setcolor(0.2f, 0.2f, 0.2f, 0.8f);
			target_font->draw(_batch, input_hint, master_position_x + 3.0f + added_x, master_position_y + round((button_size_y - 20.0f) / 2.0f + 4.0f));
		}

		if (is_input_mode_active)
		{
			if (flash_line_active)
			{
				_batch->setcolor(EColor::COLOR_BLACK);
				_batch->draw_gabarite(master_position_x + 3.0f + EFont::get_width(target_font, text) + added_x, master_position_y + (button_size_y - 20.0f) / 2.0f + 4.0f, 3.0f, 17, EGraphicCore::gabarite_white_pixel);
			}
		}
	}

	if (*side_text != "")
	{
		target_font->draw_with_background(*side_text, _batch, master_position_x - 8.0f - EFont::get_width(target_font, *side_text), master_position_y + round((button_size_y - 20.0f) / 2.0f + 0.0f), EColor::COLOR_LIGHT_GRAY, EColor::COLOR_DARK_GRAY);
	}

	if (have_rama)
	{
		_batch->setcolor(rama_color);
		_batch->draw_rama(master_position_x, master_position_y, button_size_x, button_size_y, rama_thikness, EGraphicCore::gabarite_small_wood_button_bg);
	}

	if (is_slider)
	{
		if (slider_is_horizontal)
		{
			_batch->setcolor(EColor::COLOR_WHITE);
			_batch->draw_gabarite(master_position_x + (button_size_x - 3.0f) * slider_value / *maximum_value - 1, master_position_y - 1, 5, button_size_y + 2, EGraphicCore::gabarite_white_pixel);

			_batch->setcolor(EColor::COLOR_BLACK);
			_batch->draw_gabarite(master_position_x + (button_size_x - 3.0f) * slider_value / *maximum_value, master_position_y, 3, button_size_y, EGraphicCore::gabarite_white_pixel);
		}
		else
		{
			_batch->setcolor(EColor::COLOR_WHITE);
			_batch->draw_gabarite(master_position_x - 1, master_position_y - 31.0f + button_size_y - (button_size_y - 32.0f) * slider_value / *maximum_value, button_size_x + 2, 32.0f, EGraphicCore::gabarite_white_pixel);

			_batch->setcolor(EColor::COLOR_BLACK);
			_batch->draw_gabarite(master_position_x, master_position_y - 30.0f + button_size_y - (button_size_y - 32.0f) * slider_value / *maximum_value, button_size_x, 32.0f, EGraphicCore::gabarite_white_pixel);
		}


	}

	additional_draw(_batch, _d);

	if (is_overlap())
	{
		_batch->setcolor_alpha(EColor::COLOR_GREEN, 0.25f);
		_batch->draw_gabarite(master_position_x - 3.0f, master_position_y - 3.0f, button_size_x + 6.0f, button_size_y + 6.0f, EGraphicCore::gabarite_white_pixel);
	}

	if (*is_radial_button)
	{
		float tsx = EFont::get_width(EFont::font_list.at(EFont::FONT_ENUM::FE_DOT), EString::float_to_string(round(slider_value * 100.0f) / 100.0f));
		//float tx
		float tsy = *EGraphicCore::gabarite_radial_button->size_y + 3.0f;

		float tx = (*EGraphicCore::gabarite_radial_button->size_x - tsx) / 2.0f;

		_batch->setcolor(bg_color);
		_batch->draw_gabarite(master_position_x, master_position_y, EGraphicCore::gabarite_radial_button);
		
		_batch->setcolor_lum(EColor::COLOR_WHITE, 0.12f);
		_batch->draw_gabarite(master_position_x + tx, master_position_y + tsy, tsx, 20.0f,  EGraphicCore::gabarite_white_pixel);

		_batch->setcolor(text_color);
		EFont::font_list.at(EFont::FONT_ENUM::FE_DOT)->draw(_batch, EString::float_to_string (round(slider_value  * 100.0f)/100.0f) + "", master_position_x + tx, master_position_y + tsy);

		_batch->setcolor(EColor::COLOR_WHITE);
		_batch->draw_gabarite(master_position_x + cos(3.14f * (1.0f - slider_value / *maximum_value)) * 13.0f + 13.0f, master_position_y + sin(3.14f * (1.0f - slider_value / *maximum_value)) * 13.0f + 13.0f, EGraphicCore::gabarite_radial_button_dot);
	}

	if (*is_checkbox)
	{
		if (*is_checked)
		{
			_batch->setcolor(EColor::COLOR_GREEN);
			_batch->draw_rama(master_position_x + button_size_x + 2.0f - button_size_y, master_position_y + 2.0f, button_size_y - 4.0f, button_size_y - 4.0f, 2.0f, EGraphicCore::gabarite_white_pixel);

			_batch->setcolor(EColor::COLOR_DARK_GREEN);
			_batch->draw_gabarite(master_position_x + button_size_x + 4.0f - button_size_y, master_position_y + 4.0f, button_size_y - 8.0f, button_size_y -8.0f, EGraphicCore::gabarite_white_pixel);

			rama_color->set_color(EColor::COLOR_WHITE);
			bg_color->set_color(EColor::COLOR_LIME);
			text_color->set_color(EColor::COLOR_BLACK);
		}
		else
		{
			_batch->setcolor(EColor::COLOR_RED);
			_batch->draw_rama(master_position_x + button_size_x + 2.0f - button_size_y, master_position_y + 2.0f, button_size_y - 4.0f, button_size_y - 4.0f, 2.0f, EGraphicCore::gabarite_white_pixel);

			_batch->setcolor(EColor::COLOR_BLACK);
			_batch->draw_gabarite(master_position_x + button_size_x + 4.0f - button_size_y, master_position_y + 4.0f, button_size_y - 8.0f, button_size_y - 8.0f, EGraphicCore::gabarite_white_pixel);

			rama_color->set_color(EColor::COLOR_RED);
			bg_color->set_color(EColor::COLOR_RED);
			text_color->set_color(EColor::COLOR_WHITE);
		}

	}
}

void EButton::additional_draw(Batcher* _batch, float _d)
{
	//std::cout << "Default" << std::endl;
}

void EButton::text_pass(Batcher* _batch)
{
	catched_element = (int)((master_position_y - EWindow::mouse_y) / 22.0f);
	if (is_expanded)
	{
		bound_size_down = drop_elements * 22;

		for (int i = 0; i < drop_elements; i++)
		{
			if (catched_element == i)
			{
				_batch->setcolor(0.05f, 0.10f, 0.06f, 1.0f);
			}
			else
			{
				if (have_list_color)
				{
					_batch->setcolor(drop_list_color.at(i));
				}
				else
				{
					_batch->setcolor(0.8f, 0.9f, 1.0f, 1.0f);
				}
			}

			_batch->draw_gabarite(master_position_x, master_position_y - i * 22 - 20, button_size_x, 20, EGraphicCore::gabarite_white_pixel);

			_batch->setcolor(0.0f, 0.1f, 0.2f, 0.9f);
			_batch->draw_rama(master_position_x, master_position_y - i * 22 - 20, button_size_x, 20, rama_thikness, EGraphicCore::gabarite_white_pixel);

			if (catched_element == i)
			{
				_batch->setcolor(0.95f, 0.90f, 0.94f, 1.0f);
			}
			else
			{
				_batch->setcolor(EColor::COLOR_BLACK);
			}
			EFont::active_font->set_align_once(Enums::PositionMode::MID);
			EFont::active_font->draw(_batch, drop_text.at(i), master_position_x + button_size_x / 2.0f, master_position_y - i * 22 - 20 + 3);
		}
	}
	else
	{
		bound_size_down = 0;
	}

	/*if (prev_description_text != description_text)
	{


		//std::cout << "description changed from <" << prev_description_text << "> to [" << description_text << ">" << std::endl;

		//prev_description_text = description_text;
	}*/

	if ((have_description) && (is_overlap()) && (description_text != ""))
		//if (is_overlap() && (have_description))
	{

		EFont* target_font = EFont::active_font;

		float th = EFont::get_height(target_font, description_text) + 5.0f;

		if (force_font != NULL)
		{
			target_font = force_font;
		}

		float x_description = EWindow::mouse_x + 20.0f;
		if (x_description + EFont::get_width(target_font, description_text) + 5 > EGraphicCore::SCR_WIDTH)
		{
			x_description += EGraphicCore::SCR_WIDTH - (x_description + EFont::get_width(target_font, description_text) + 5.0f);
		}

		target_font->align_x = Enums::PositionMode::LEFT;

		_batch->setcolor(EColor::COLOR_WHITE);
		_batch->draw_gabarite(x_description, EWindow::mouse_y - 20.0f - th, EFont::get_width(target_font, description_text) + 8, th, EGraphicCore::gabarite_white_pixel);

		_batch->setcolor(EColor::COLOR_BLACK);
		target_font->draw(_batch, description_text, x_description + 5.0f, EWindow::mouse_y - 34.0f);

		_batch->draw_rama(x_description, EWindow::mouse_y - 20.0f - th, EFont::get_width(target_font, description_text) + 8, th, 2, EGraphicCore::gabarite_white_pixel);
	}

	if ((is_slider) && (slider_activate))
	{
		EFont* target_font = EFont::active_font;
		float th = EFont::get_height(target_font, std::to_string(slider_value * slider_value_multiplier)) + 5.0f;

		_batch->setcolor(EColor::COLOR_WHITE);
		_batch->draw_gabarite(EWindow::mouse_x + 10.0f, EWindow::mouse_y - 20.0f - th, EFont::get_width(target_font, std::to_string(slider_value * slider_value_multiplier)) + 8, th, EGraphicCore::gabarite_white_pixel);

		_batch->setcolor(EColor::COLOR_BLACK);
		target_font->draw(_batch, std::to_string(slider_value * slider_value_multiplier / *maximum_value), EWindow::mouse_x + 15.0f, EWindow::mouse_y - 34.0f);
	}
}



void EButton::click_event()
{
	std::cout << "STANDART click event" << std::endl;
}

void EButton::right_click_event()
{
}

void EButton::input_event()
{
}

void EButton::input_finish_event()
{

}

void EButton::drop_list_select_event()
{
}

void EButton::slider_drag_event()
{

}


void EButton::update_localisation()
{

	/* the ampersand is actually optional */

	//std::cout << "DEFAULT LOCAL" << std::endl;
}

EButton* EButton::clone_button(EButton* _b, float _x, float _y, float _sx, float _sy)
{
	EButton* but = new EButton(*_b);

	but->button_base_x = _x;
	but->button_x_offset = _x;

	but->button_base_y = _y;
	but->button_y_offset = _y;

	return but;
}

void EWindow::default_update(float _d)
{
	for (int i = 0; i < button_list.size(); i++)
	{
		if (*button_list.at(i)->need_remove)
		{
			button_list.erase(button_list.begin() + i);
		}
	}

	for (EButton* b : button_list)
	{
		if (b->is_active)
		{
			b->update(_d);
		}
	}

	for (EButton* b : default_button_list)
	{
		if (b->is_active) {b->update(_d);}
	}

	/*for (EButton::button_array_collection* z : button_array_collection_list)
	{
		z->update_button_position();
	}*/

	float add_offset_x = 0.0f;
	std::vector<float> maximum_button_size_x;
	maximum_button_size_x.clear();
	int array_id = 0;

	float maximum_size_of_horizontal = 0.0f;
	float maximum_size_of_vertical = 0.0f;
	float maximum_size_of_array = 0.0f;

	float h_base_offset_x = 0.0f;


	float button_added_position_x = 0.0f;
	float button_added_position_y = 0.0f;

	float maximum_button_gabarite_x = 0.0f;
	float maximum_button_gabarite_y = 0.0f;

	float maximum_group_size_x = 0.0f;
	float maximum_group_size_y = 0.0f;

	float base_x = 0.0f;
	float base_y = 0.0f;

	float previvous_button_size_x = 0.0f;
	float previvous_button_size_y = 0.0f;

	float previvous_button_position_x = 0.0f;
	float previvous_button_position_y = 0.0f;

	float previvous_group_size_x = 0.0f;
	float previvous_group_size_y = 0.0f;

	float group_total_offset_x = 0.0f;
	float group_total_offset_y = 0.0f;

	//update buttons on button group and update button group
	for (EButton::button_super_group* bsg : button_group_list)
	if (*bsg->is_active)
	{

		//*bsg->position_x += _d * 20.0f;


			for (EButton::button_group* bg : bsg->button_group_list)
			{

				button_added_position_x = 0.0f;
				button_added_position_y = 0.0f;

				maximum_button_gabarite_x = 0.0f;
				maximum_button_gabarite_y = 0.0f;

				base_x = 0.0f;
				base_y = 0.0f;

				previvous_button_position_x = *bsg->position_x + *bg->position_x + 5.0f;
				previvous_button_position_y = *bsg->position_y + *bg->position_y + 5.0f;

				previvous_button_size_x = 0.0f;
				previvous_button_size_y = 0.0f;

				group_total_offset_x = *bsg->position_x + *bg->position_x;
				group_total_offset_y = *bsg->position_y + *bg->position_y;

				if (*bg->size_x < previvous_group_size_x) { *bg->size_x = previvous_group_size_x; }
				if (*bg->position_y < previvous_group_size_y) { *bg->position_y = previvous_group_size_y + 5.0f; }

				for (EButton* b : bg->button_list)
				if (b->is_active)
				{
					//position relative screen
					if (*b->selected_auto_align_mode == EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_FREE)
					{
						b->button_x_offset = b->button_base_x + *bsg->position_x + *bg->position_x;
						b->button_y_offset = b->button_base_y + *bsg->position_y + *bg->position_y;
					}
					else
					{
						b->button_x_offset = *bsg->position_x + *bg->position_x + 5.0f + base_x;
						b->button_y_offset = *bsg->position_y + *bg->position_y + 5.0f + base_y;
					}


					if
					(
						((!*bg->can_be_stretched_x) & (previvous_button_position_x + previvous_button_size_x + b->button_size_x + 5.0f >= *bg->size_x + group_total_offset_x))
						||
						(*b->selected_auto_align_mode == EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_RESET_X_AND_ADD_Y)
					)
					{
						b->button_y_offset += maximum_button_gabarite_y + 5.0f;

						base_y += maximum_button_gabarite_y + 5.0f;
						maximum_button_gabarite_y = b->button_size_y;


					}

					if
					(
						((*bg->can_be_stretched_x) || (previvous_button_position_x + previvous_button_size_x + b->button_size_x + 5.0f < *bg->size_x + group_total_offset_x))
						&
						(*b->selected_auto_align_mode == EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_X)
					)
					{
						b->button_x_offset = previvous_button_position_x + previvous_button_size_x + 5.0f;


						if (b->button_size_x > maximum_button_gabarite_x) { maximum_button_gabarite_x = b->button_size_x; }
						if (b->button_size_y > maximum_button_gabarite_y) { maximum_button_gabarite_y = b->button_size_y; }

						
					}

					if (*b->selected_auto_align_mode == EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_ADD_Y)
					{
						b->button_y_offset += button_added_position_y;

						button_added_position_x += b->button_size_x + 5.0f;
						button_added_position_y += b->button_size_y + 5.0f;

						if (b->button_size_x > maximum_button_gabarite_x) { maximum_button_gabarite_x = b->button_size_x; }

					}

					if (*b->selected_auto_align_mode == EButton::ButtonAutoAlign::BUTTON_AUTO_ALIGN_RESET_Y_AND_ADD_X)
					{
						b->button_x_offset += maximum_button_gabarite_x + 5.0f;
						maximum_button_gabarite_x = b->button_size_x;

						button_added_position_x = b->button_size_x + 5.0f;
						button_added_position_y += b->button_size_y + 5.0f;

					}

					if ((*bg->can_be_stretched_x) & (b->button_x_offset + b->button_size_x - *bg->position_x - *bsg->position_x + 5.0f > * bg->size_x)) { *bg->size_x = b->button_x_offset + b->button_size_x - *bg->position_x - *bsg->position_x + 5.0f; }
					if (b->button_y_offset + b->button_size_y - *bg->position_y - *bsg->position_y + 5.0f > * bg->size_y) { *bg->size_y = b->button_y_offset + b->button_size_y - *bg->position_y - *bsg->position_y + 5.0f; }

					

					previvous_button_position_x = b->button_x_offset;
					previvous_button_position_y = b->button_y_offset;

					previvous_button_size_x = b->button_size_x;
					previvous_button_size_y = b->button_size_y;

					if (*bg->size_x > previvous_group_size_x) { previvous_group_size_x = *bg->size_x; }
					if (*bg->size_y > previvous_group_size_y) { previvous_group_size_y = *bg->size_y; }

					if (*bg->position_x + *bg->size_x > * bsg->size_x) { *bsg->size_x = *bg->position_x + *bg->size_x + 5.0f; }
					if (*bg->position_y + *bg->size_y > * bsg->size_y) { *bsg->size_y = *bg->position_y + *bg->size_y + 5.0f; }

					//b->text = EString::float_to_string(*b->selected_auto_align_mode);

					b->update(_d);
					b->update_additional(_d);

				}


			}
		}


}

/*EWindow::button_array_collection_massive()
{

}*/

void EWindow::update(float _d)
{
}

void EWindow::default_draw(float _d)
{
	if (have_bg)
	{
		if (!screen_space)
		{
			EGraphicCore::batch->setcolor_alpha(EColor::COLOR_WHITE, 0.8f);
			EGraphicCore::batch->draw_gabarite(offset_x, offset_y, window_size_x, window_size_y, EGraphicCore::gabarite_white_pixel);
		}
		else
		if (screen_space_texture != NULL)
		{
			EGraphicCore::batch->setcolor_alpha(EColor::COLOR_WHITE, 1.0f);
			EGraphicCore::batch->draw_with_custom_uv
			(
				offset_x,
				offset_y,

				window_size_x,
				window_size_y,

				*screen_space_texture->x + offset_x / EWindow::default_texture_atlas->size_x,
				*screen_space_texture->y + offset_y / EWindow::default_texture_atlas->size_y,

				*screen_space_texture->x + (offset_x + window_size_x) / EWindow::default_texture_atlas->size_x,
				*screen_space_texture->y + (offset_y + window_size_y) / EWindow::default_texture_atlas->size_y
			);
		}
	}



	
	


}

void EWindow::draw(float _d)
{
}

void EWindow::default_resize_event()
{
	if (always_fullscreen)
	{
		window_size_x = EGraphicCore::SCR_WIDTH;
		window_size_y = EGraphicCore::SCR_HEIGHT;

		offset_x = 0;
		offset_y = 0;
	}
	else
	{
		if (align_x == Enums::PositionMode::LEFT) { offset_x = position_x; }
		if (align_x == Enums::PositionMode::MID) { offset_x = (EGraphicCore::SCR_WIDTH - window_size_x) / 2.0f + position_x; }
		if (align_x == Enums::PositionMode::RIGHT) { offset_x = (EGraphicCore::SCR_WIDTH - window_size_x) + position_x; }		
		
		if (align_y == Enums::PositionMode::DOWN) { offset_y = position_y; }
		if (align_y == Enums::PositionMode::MID) { offset_y = (EGraphicCore::SCR_HEIGHT - window_size_y) / 2.0f + position_y; }
		if (align_y == Enums::PositionMode::UP) { offset_y = (EGraphicCore::SCR_HEIGHT - window_size_y) + position_y; }
	}
}

void EWindow::default_draw_interface(float _d)
{

	EGraphicCore::batch->reinit();
	EGraphicCore::batch->draw_call();

	EGraphicCore::ourShader->use();
	EGraphicCore::matrix_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

	EGraphicCore::matrix_transform = glm::translate(EGraphicCore::matrix_transform, glm::vec3(-1.0f, -1.0f, 0.0f));
	EGraphicCore::matrix_transform = glm::scale(EGraphicCore::matrix_transform, glm::vec3(EGraphicCore::correction_x, EGraphicCore::correction_y, 1));

	transformLoc = glGetUniformLocation(EGraphicCore::ourShader->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(EGraphicCore::matrix_transform));

	//����� �������
	EGraphicCore::batch->reset();

	


	for (EButton* b : button_list)
	{
		if (b->is_active)
		{
			b->default_draw(EGraphicCore::batch, _d);
			b->additional_draw(EGraphicCore::batch, _d);
		}
	}
	
	for (EButton* b : button_list)
	{
		if (b->is_active)
		{
			b->text_pass(EGraphicCore::batch);
		}
	}

	for (EButton* b : default_button_list)
	{
		if (b->is_active)
		{
			b->default_draw(EGraphicCore::batch, _d);
			b->additional_draw(EGraphicCore::batch, _d);
		}
	}

	for (EButton* b : default_button_list)
	{
		if (b->is_active)
		{
			b->text_pass(EGraphicCore::batch);
		}
	}

	/*
	for (button_array_collection_massive* massive : button_array_collection_massive_list)
	if (*massive->is_active)
	{
		for (button_array_horizontal_collection* horizontal : massive->button_array_horizontal_collection_list)
		{


			for (button_array_vertical_collection* vertical : horizontal->button_array_vertical_collection_list)
				if (*horizontal->selected_tab == *vertical->tab_id)
					for (button_array* array : vertical->button_array_list)
						

		}


	}*/


	//float previvous_button_size_x = 0.0f;
	//float previvous_button_size_y = 0.0f;


	//draw buttons on button group and update button group

	for (EButton::button_super_group* bsg : button_group_list)
	if (*bsg->is_active)
	{
		EGraphicCore::batch->setcolor_alpha(EColor::COLOR_BLACK, 0.5f);
		EGraphicCore::batch->draw_gabarite(*bsg->position_x, *bsg->position_y, *bsg->size_x, *bsg->size_y, EGraphicCore::gabarite_white_pixel);

		for (EButton::button_group* bg : bsg->button_group_list)
		{
			EGraphicCore::batch->setcolor_alpha(EColor::COLOR_GRAY, 0.9f);
			EGraphicCore::batch->draw_gabarite(*bsg->position_x + *bg->position_x, *bsg->position_y + *bg->position_y, *bg->size_x, *bg->size_y, EGraphicCore::gabarite_white_pixel);

			for (EButton* but : bg->button_list)
			{
				but->default_draw(EGraphicCore::batch, _d);
				but->additional_draw(EGraphicCore::batch, _d);
				but->text_pass(EGraphicCore::batch);

			}
		}
	}

	//draw graphic for button group
}

void EWindow::draw_interface(float _d)
{

}

void EWindow::add_time_process(std::string _name)
{
	//std::vector <float> tvec = new std::vector<float>(60, 0.0f);

	int id = -1;
	int tid = 0;
	for (time_process_struct* tps : tps_list)
	{
		if (tps->time_process_name == _name) { id = tid; break; }

		tid++;
	}

	stop = std::chrono::high_resolution_clock::now();
	

	if (id != -1)
	{
		tps_list.at(id)->time_process_name = _name;
		tps_list.at(id)->time_process_value.at(time_process_rota_id) = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() / 1000.0f;
	}
	else
	{
		time_process_struct* new_tps = new time_process_struct;

		tps_list.push_back(new_tps);

		for (int i = 0; i < 30; i++)
		{new_tps->time_process_value.push_back(std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() / 1000.0f);}

		new_tps->time_process_name = _name;
	}

	start = std::chrono::high_resolution_clock::now();

}

void EWindow::push_cursor(float _x, float _y)
{
	SetCursorPos(real_mouse_x + _x, real_mouse_y + _y);

	mouse_x += _x;
	mouse_y += _y;

	real_mouse_x += _x;
	real_mouse_y += _y;
}

EWindow::EWindow()
{
	default_resize_event();

	EButton* but = new EButton(0.0f, 0.0f, 20.0f, 20.0f);
	but->master_window = this;
	but->position_mode_x = Enums::PositionMode::RIGHT;
	but->position_mode_y = Enums::PositionMode::UP;
	but->text = "X";
	//but->action_on_left_click = &EBA::action_close_window;
	
	default_button_list.push_back(but);
}

EWindow::~EWindow()
{
}

bool EWindow::is_overlap(EWindow* _w)
{

	if
	(
		(mouse_x >= _w->offset_x)
		&&
		(mouse_x <= _w->offset_x + _w->window_size_x)
		&&
		(mouse_y >= _w->offset_y)
		&&
		(mouse_y <= _w->offset_y + _w->window_size_y)
	)
	{
		return true;
	}

	return false;
}

EButton::button_group* EWindow::get_button_group_by_name(EWindow* _w, std::string _super_group_name, std::string _group_name)
{
	return nullptr;
}


EWindow::button_array_collection_massive::button_array_collection_massive(EWindow* _w)
{
	button_close = new EButton(0.0f, 0.0f, 20.0f, 20.0f);

	button_close->text_color->set_color(EColor::COLOR_WHITE);
	button_close->bg_color->set_color(EColor::COLOR_RED);

	button_close->text = "X";

	button_close->master_window = _w;

	//button_close->action_on_left_click = &EBA::action_set_constant_bool_to_address;
	button_close->target_address_for_bool = is_active;
	*button_close->target_value_for_bool = false;

	service_button.push_back(button_close);
}
