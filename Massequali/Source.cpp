#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION

#include <ctime>

#include "NSW_api/EWindow.h"

//#include "EWindowMain.h"

#include "NSW_api/EGraphicCore.h"
//#include "ETextureAtlas.h"

#include "NSW_api/Enums.h"
#include "NSW_api/EFont.h"

#include <windows.h>
#include "EWindowMain.h"
#include "ExternalEnums.h"

static unsigned int transformLoc;

float delta_time;
float saved_time_for_delta;

void recalculate_correction();
void processInput(GLFWwindow* window);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void recalculate_correction();
void processInput(GLFWwindow* window);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void mouse_position_callback(GLFWwindow* window, double _x, double _y);
void char_input_callback(GLFWwindow* window, unsigned int _char);
//void load_texture(char const* _path, int _id);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


int main()
{
	//EDataWatcher::data_watcher_struct* just_created_float_struct = new EDataWatcher::data_watcher_struct;

	srand(time(NULL));

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 2);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

// glfw window creation
// --------------------
	
	
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	glfwWindowHint(GLFW_DECORATED, NULL);

	//EWindow::main_window = glfwCreateWindow(EGraphicCore::SCR_WIDTH, EGraphicCore::SCR_HEIGHT, "Window name", glfwGetPrimaryMonitor(), NULL); 
	EWindow::main_window = glfwCreateWindow(EGraphicCore::SCR_WIDTH, EGraphicCore::SCR_HEIGHT, "Window name", NULL, NULL);


	

	if (EWindow::main_window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(EWindow::main_window);

	glfwSetFramebufferSizeCallback(EWindow::main_window, framebuffer_size_callback);
	glfwSetScrollCallback(EWindow::main_window, scroll_callback);
	glfwSetMouseButtonCallback(EWindow::main_window, mouse_button_callback);
	glfwSetCursorPosCallback(EWindow::main_window, mouse_position_callback);
	glfwSetCharCallback(EWindow::main_window, char_input_callback);

	glfwSetInputMode(EWindow::main_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	//glfwSetMousePos(0, 0);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	GLint max_tex_size;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_tex_size);

	logger_param("max_texture_size:", max_tex_size);

	EGraphicCore::ourShader = new Shader("data/#default.vs", "data/#default.fs");
	EGraphicCore::AO_shader = new Shader("data/#AO_shadow.vs", "data/#AO_shadow.fs");
	EGraphicCore::PBR_shader = new Shader("data/PBR.vs", "data/PBR.fs");
	EGraphicCore::simple_blur = new Shader("data/simple_blur.vs", "data/simple_blur.fs");
	/*EGraphicCore::shadowmap = new Shader("data/shadowmap.vs", "data/shadowmap.fs");
	EGraphicCore::shader_terrain = new Shader("data/terrain.vs", "data/terrain.fs");
	EGraphicCore::lightmap_blur = new Shader("data/lightmap_blur.vs", "data/lightmap_blur.fs");
	EGraphicCore::lightmap_spread = new Shader("data/lightmap_spread.vs", "data/lightmap_spread.fs");*/

	EGraphicCore::ourShader->use();
	

	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glViewport(0, 0, EGraphicCore::SCR_WIDTH, EGraphicCore::SCR_HEIGHT);
	recalculate_correction();

	//
	//batcher initiation
	EGraphicCore::batch = new Batcher();
	EGraphicCore::batch_shadowmap = new Batcher();
	EGraphicCore::batch_terrain = new Batcher();

	EGraphicCore::batch_PBR = new Batcher();

	for (int i = 0; i < 1000; i++)
	{
		EGraphicCore::batch->fill_indices();
		
		//EGraphicCore::batch_shadowmap->fill_indices();
		//EGraphicCore::batch_terrain->fill_indices();
	}

	std::cout << "indices count for {default}:" << std::to_string(EGraphicCore::batch->indices_id) << std::endl;

	for (int i = 0; i < 1000; i++)
	{
		EGraphicCore::batch_PBR->fill_indices();
	}

	std::cout << "indices count for {PBR}:" << std::to_string(EGraphicCore::batch_PBR->indices_id) << std::endl;

	EGraphicCore::batch->init();
	EGraphicCore::batch_PBR->init_PBR();
	//EGraphicCore::batch_shadowmap->init_shadowmap();
	//EGraphicCore::batch_terrain->init_terrain();
	//
	//

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	glBlendEquation(GL_FUNC_ADD);
	//--------------------------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------------------------

	//cout << (int)01.35f << endl;
	glViewport(0, 0, EGraphicCore::SCR_WIDTH, EGraphicCore::SCR_HEIGHT);

	EWindow::default_texture_atlas = new ETextureAtlas(4096, 4096);

	EWindow::supermap_FBO = new ETextureAtlas(512, 512);
	//EWindow::supermap_FBO = new ETextureAtlas(512, 512);
	//EWindow::AO_shadow_FBO = new ETextureAtlas(1920, 1080, GL_RGBA16, GL_UNSIGNED_SHORT);
	EWindow::AO_shadow_FBO = new ETextureAtlas(2048.0f / 16.0f, 1024.0f / 16.0f, GL_RGBA16, GL_UNSIGNED_SHORT);

	for (int i = 0; i < skydome_texture_levels; i++)
	{
		EWindow::skydome_light_FBO[i]			= new ETextureAtlas(int(2048.0f / pow(2.0f, i)), int(1024.0f / pow(2.0f, i)), GL_RGBA16, GL_UNSIGNED_SHORT);
		EWindow::skydome_light_FBO_buffer[i]	= new ETextureAtlas(int(2048.0f / pow(2.0f, i)), int(1024.0f / pow(2.0f, i)), GL_RGBA16, GL_UNSIGNED_SHORT);
	}
	/*
	EWindow::shadow_FBO = new ETextureAtlas(1920, 1580);
	EWindow::screen_FBO = new ETextureAtlas(1920, 1080);

	EWindow::shadow_ground_FBO = new ETextureAtlas(1920, 1080);
	EWindow::lightmap_FBO = new ETextureAtlas(300, 300);
	EWindow::lightmap_FBO2 = new ETextureAtlas(300, 300);
	EWindow::base_lightmap = new ETextureAtlas(300, 300);
	EWindow::base_blockmap = new ETextureAtlas(300, 300);*/

	EGraphicCore::load_texture("data/textures/white_pixel.png", 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, EGraphicCore::texture[0]);

	EGraphicCore::ourShader->setInt("texture1", EGraphicCore::texture[0]);

	EWindowMain* wg = new EWindowMain();
	//EWindow::window_game = wg;
	EWindow::window_list.push_back(wg);
	EWindow::window_main = wg;
	wg->have_bg = true;
	wg->screen_space = true;
	wg->screen_space_texture = ETextureAtlas::put_texture_to_atlas("data/textures/massive_bg_blue.png", EWindow::default_texture_atlas);
	//wg->
	wg->id = 0;
	wg->always_fullscreen = true;

	//wg->init();

	//loading font

	for (EWindow* w : EWindow::window_list)
	{
		w->default_resize_event();
	}

	std::cout << "game window created" << std::endl;

	EGraphicCore::gabarite_white_pixel = ETextureAtlas::put_texture_to_atlas("data/textures/white_pixel.png", EWindow::default_texture_atlas);

	/**EGraphicCore::gabarite_white_pixel->x += 1.0f / 4096.0f / 2.0f;
	*EGraphicCore::gabarite_white_pixel->y += 1.0f / 4096.0f / 2.0f;

	*EGraphicCore::gabarite_white_pixel->x2 -= 1.0f / 4096.0f / 2.0f;
	*EGraphicCore::gabarite_white_pixel->y2 -= 1.0f / 4096.0f / 2.0f;*/

	//EGraphicCore::gabarite_full_atlas = //ETextureAtlas::put_texture_to_atlas("data/textures/white_pixel.png", EWindow::default_texture_atlas);
	EGabarite* gab = new EGabarite("full atlas");
	*gab->x = 0.0f;
	*gab->y = 0.0f;
	*gab->x2 = 1.0f;
	*gab->y2 = 1.0f;
	*gab->uv_size_x = 1.0f;
	*gab->uv_size_y = 1.0f;
	*gab->size_x = 4096.0f;
	*gab->size_y = 4096.0f;
	EGraphicCore::gabarite_list.push_back(gab);
	EGraphicCore::gabarite_full_atlas = gab;

	*EGraphicCore::gabarite_white_pixel->y2 -= 1.0f / 4096.0f / 2.0f;

	EGraphicCore::gabarite_ERROR = ETextureAtlas::put_texture_to_atlas("data/textures/ERROR.png", EWindow::default_texture_atlas);
	EGraphicCore::gabarite_radial_button = ETextureAtlas::put_texture_to_atlas("data/textures/radial_button.png", EWindow::default_texture_atlas);
	EGraphicCore::gabarite_radial_button_dot = ETextureAtlas::put_texture_to_atlas("data/textures/radial_button_dot.png", EWindow::default_texture_atlas);
	
	EGraphicCore::gabarite_sun							= ETextureAtlas::put_texture_to_atlas("data/textures/sun2.png", EWindow::default_texture_atlas);
	EGraphicCore::gabarite_sky							= ETextureAtlas::put_texture_to_atlas("data/textures/sky3.png", EWindow::default_texture_atlas);
	EGraphicCore::gabarite_panorama						= ETextureAtlas::put_texture_to_atlas("data/textures/panorama[4].png", EWindow::default_texture_atlas);
	EGraphicCore::gabarite_button_texture_AO_shadow		= ETextureAtlas::put_texture_to_atlas("data/textures/button_texture_AO_shadow.png", EWindow::default_texture_atlas);

	EGraphicCore::gabarite_small_wood_button_bg = ETextureAtlas::put_texture_to_atlas("data/textures/button_bg.png", EWindow::default_texture_atlas);

	//EGraphicCore::gabarite_wood_button_bg = ETextureAtlas::put_texture_to_atlas("data/textures/wood_bg.png", EWindow::default_texture_atlas);
	//EGraphicCore::gabarite_supermap_placeholder = ETextureAtlas::put_texture_to_atlas("data/textures/supermap_placeholder.png", EWindow::default_texture_atlas);

	EFont* new_font = NULL;
	EGabarite* font_gabarite = ETextureAtlas::put_texture_to_atlas("data/font/franklin_0.png", EWindow::default_texture_atlas);

	new_font = new EFont("franklin", font_gabarite, false);
	EFont::active_font = new_font;
	EFont::font_list.push_back(new_font);

	font_gabarite = ETextureAtlas::put_texture_to_atlas("data/font/dot_0.png", EWindow::default_texture_atlas);
	new_font = new EFont("dot", font_gabarite, false);
	//EFont::active_font = new_font;
	EFont::font_list.push_back(new_font);

	//EGabarite* zzz = ETextureAtlas::put_texture_to_atlas("data/font/franklin_0.png", EWindow::shadow_FBO);

	EWindow::massive_style* jc_massive_style = new EWindow::massive_style;
	jc_massive_style->background = ETextureAtlas::put_texture_to_atlas("data/textures/massive_bg_blue_blured.png", EWindow::default_texture_atlas);
	EWindow::list_of_massive_style.push_back(jc_massive_style);


	std::vector <float> fff(1000);
	float start_id;

	glfwSwapInterval(1);

	//setVerticalSyncEnabled(true);

	#if defined (_WIN32) || defined (_WIN64)
			// Turn on vertical screen sync under Windows.
			// (I.e. it uses the WGL_EXT_swap_control extension)
		typedef BOOL(WINAPI* PFNWGLSWAPINTERVALEXTPROC)(int interval);
		PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = NULL;
		wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
		if (wglSwapIntervalEXT)
			wglSwapIntervalEXT(1);
	#endif

	while (!glfwWindowShouldClose(EWindow::main_window))
	{
		

		EWindow::stop = std::chrono::high_resolution_clock::now();
		EWindow::start = std::chrono::high_resolution_clock::now();

		start_id = 0;
		EWindow::add_time_process("@_Begin_@");

		
		
		//key_pressed_array[GLFW_KEY_W] = true;

		

		glfwPollEvents();

		if ((glfwGetKey(EWindow::main_window, GLFW_KEY_W) == GLFW_PRESS))				{ EWindow::key_pressed_array[GLFW_KEY_W] = true; }
		if ((glfwGetKey(EWindow::main_window, GLFW_KEY_W) == GLFW_RELEASE))				{ EWindow::key_pressed_array[GLFW_KEY_W] = false; }

		if ((glfwGetKey(EWindow::main_window, GLFW_KEY_A) == GLFW_PRESS))				{ EWindow::key_pressed_array[GLFW_KEY_A] = true; }
		if ((glfwGetKey(EWindow::main_window, GLFW_KEY_A) == GLFW_RELEASE))				{ EWindow::key_pressed_array[GLFW_KEY_A] = false; }

		if ((glfwGetKey(EWindow::main_window, GLFW_KEY_S) == GLFW_PRESS))				{ EWindow::key_pressed_array[GLFW_KEY_S] = true; }
		if ((glfwGetKey(EWindow::main_window, GLFW_KEY_S) == GLFW_RELEASE))				{ EWindow::key_pressed_array[GLFW_KEY_S] = false; }

		if ((glfwGetKey(EWindow::main_window, GLFW_KEY_D) == GLFW_PRESS))				{ EWindow::key_pressed_array[GLFW_KEY_D] = true; }
		if ((glfwGetKey(EWindow::main_window, GLFW_KEY_D) == GLFW_RELEASE))				{ EWindow::key_pressed_array[GLFW_KEY_D] = false; }

		if ((glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS))		{ EWindow::key_pressed_array[GLFW_KEY_LEFT_SHIFT] = true; }
		if ((glfwGetKey(EWindow::main_window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE))	{ EWindow::key_pressed_array[GLFW_KEY_LEFT_SHIFT] = false; }

		if ((glfwGetKey(EWindow::main_window, GLFW_KEY_GRAVE_ACCENT) == GLFW_PRESS))	{ EWindow::key_pressed_array[GLFW_KEY_GRAVE_ACCENT] = true; }
		if ((glfwGetKey(EWindow::main_window, GLFW_KEY_GRAVE_ACCENT) == GLFW_RELEASE))	{ EWindow::key_pressed_array[GLFW_KEY_GRAVE_ACCENT] = false; }
		
		clock_t time = clock();
		delta_time = (time - saved_time_for_delta) / 1000.0;
		saved_time_for_delta = time;

		delta_time /= 1.0f;//

		//std::cout << "delta:" << std::to_string(delta_time) << std::endl;



		
		/*if (!EWindow::key_pressed_array[GLFW_KEY_GRAVE_ACCENT])
		{
			
			glfwSwapInterval(0);
		}
		else
		{
			glfwSwapInterval(1);
		}*/

		

		if (delta_time > 0.5f) { delta_time = 0.5f; }

		POINT cursorPos;
		GetCursorPos(&cursorPos);

		EWindow::mouse_speed_x = cursorPos.x - EWindow::prev_mouse_x;
		EWindow::mouse_speed_y = -(cursorPos.y - EWindow::prev_mouse_y);

		EWindow::real_mouse_x = cursorPos.x;
		EWindow::real_mouse_y = cursorPos.y;

		EWindow::prev_mouse_x = cursorPos.x;
		EWindow::prev_mouse_y = cursorPos.y;

		//очищаем графический буфер и подготавливаем трансформацию
		//glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glClearColor(0.4f, 0.5f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//сброс батчера
		EGraphicCore::batch->reset();

		EButton::top_window_id = -1;

		if (!EWindow::LMB) { EWindow::button_pressed = false; }
		if (!EWindow::RMB) { EWindow::button_right_pressed = false; }

		if (!EWindow::button_backspace_released)
		{
			EWindow::delete_button_hold_time += delta_time;
		}

		if
			(
				(glfwGetKey(EWindow::main_window, GLFW_KEY_BACKSPACE) == GLFW_RELEASE)
				&&
				(glfwGetKey(EWindow::main_window, GLFW_KEY_DELETE) == GLFW_RELEASE)
				)
		{
			EWindow::button_backspace_released = true;

			EWindow::delete_button_hold_time = 0;
		}

		if
			(
				(glfwGetKey(EWindow::main_window, GLFW_KEY_E) == GLFW_RELEASE)
				&&
				(glfwGetKey(EWindow::main_window, GLFW_KEY_V) == GLFW_RELEASE)
				&&
				(glfwGetKey(EWindow::main_window, GLFW_KEY_DELETE) == GLFW_RELEASE)
				&&
				(glfwGetKey(EWindow::main_window, GLFW_KEY_F1) == GLFW_RELEASE)
				&&
				(glfwGetKey(EWindow::main_window, GLFW_KEY_COMMA) == GLFW_RELEASE)
				&&
				(glfwGetKey(EWindow::main_window, GLFW_KEY_PERIOD) == GLFW_RELEASE)
			)
		{
			EWindow::button_main_group_pressed = false;
		}

		EButton::top_window_id = -1;
		for (int i = 0; i < EWindow::window_list.size(); i++)
		{
			if (
				(EWindow::is_overlap(EWindow::window_list.at(i)))
				&&
				(EWindow::window_list.at(i)->is_active)
				)
			{
				EButton::top_window_id = i;
			}
		}

		//update windows
		EWindow::top_overlaped_group = NULL;

		if
		(
			(EWindow::operable_button != NULL)
			&&
			(
				(!EWindow::operable_button->is_active)
				||
				(
					(EWindow::operable_button->master_super_group != NULL)
					&&
					(!*EWindow::operable_button->master_super_group->is_active)
				)
			)
		)
		{
			EWindow::operable_button = NULL;
		}

		EButton::any_input = false;
		EButton::any_overlap = false;
		for (EWindow* w : EWindow::window_list)
		for (EButton::button_super_group* _sg:w->button_group_list)
		if
		(
			(*_sg->is_active)
			&
			(EWindow::is_group_overlapped_by_mouse(_sg))
		)
		{
			EWindow::top_overlaped_group = _sg;

			
		}

		for (EWindow* w : EWindow::window_list)
		if ((EWindow::top_overlaped_group != NULL) & (EWindow::LMB))
		{
			send_this_button_group_to_top(w, EWindow::top_overlaped_group);
		}

		
		EWindow::add_time_process("__window pre process");
		for (EWindow* w : EWindow::window_list)
			if (w->is_active) { w->default_update(delta_time); }

		EWindow::add_time_process("__window default update ");

		for (EWindow* w : EWindow::window_list)
		{
			
			if (w->is_active) { w->update(delta_time); }
			
		}
			EWindow::add_time_process("__window update ");

		for (EWindow* w : EWindow::window_list)
			if (w->is_active)
			{
				w->default_draw(delta_time);
				EWindow::add_time_process("__default draw ");
				w->draw(delta_time);
				EWindow::add_time_process("__draw");
				w->default_draw_interface(delta_time);
				EWindow::add_time_process("__default draw interface");
				w->draw_interface(delta_time);
				EWindow::add_time_process("draw interface");
			}

		if ((EButton::dragged_button != NULL) & (!EWindow::LMB))
		{
			EButton::dragged_button = NULL;
		}

		EGraphicCore::batch->reinit();
		EGraphicCore::batch->draw_call();
		EWindow::add_time_process("__DRAW CALL ");
		/*EGraphicCore::batch->reset();
			EGraphicCore::batch->setcolor(EColor::COLOR_WHITE);
			EGraphicCore::batch->draw_gabarite(0.0f, 0.0f, EGraphicCore::gabarite_full_atlas);
		EGraphicCore::batch->reinit();
		EGraphicCore::batch->draw_call();*/

		//glFlush();
		
		//gl_flush();
		glfwSwapBuffers(EWindow::main_window);
		EWindow::add_time_process("swap buffer");
		processInput(EWindow::main_window);

		EWindow::last_inputed_char = NULL;

		EWindow::scroll = 0;
		//sleep(0.1);

		if (delta_time < 1.0f / 70.0f)
		{
			//Sleep((DWORD)((1.0f / 70.0f - delta_time) * 1000.0f));
		}

		EWindow::add_time_process("@_End_@");
		
	}

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{//
	//width = round(width / 2.0f) * 2;
	//height = round(height / 2.0f) * 2;
	//glScissor(0, 0, 500, 500);
	glfwSetWindowSize(EWindow::main_window, width, height);

	glViewport(0, 0, width, height);
	glfwGetWindowSize(window, &EGraphicCore::SCR_WIDTH, &EGraphicCore::SCR_HEIGHT);

	std::cout << "Resize event width:" << EGraphicCore::SCR_WIDTH << " height: " << EGraphicCore::SCR_HEIGHT << std::endl;

	recalculate_correction();
}

void recalculate_correction()
{
	if ((EGraphicCore::SCR_WIDTH > 100) && (EGraphicCore::SCR_HEIGHT > 100))
	{
		EGraphicCore::correction_x = 1.0f / EGraphicCore::SCR_WIDTH * 2.0f;
		EGraphicCore::correction_y = 1.0f / EGraphicCore::SCR_HEIGHT * 2.0f;

		//std::cout << "helper correction_x: " << correction_x << " correction_y: " << correction_y << std::endl;
	}

	for (EWindow* w : EWindow::window_list)
	{
		w->default_resize_event();
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	std::cout << "scroll: " << std::to_string(yoffset) << std::endl;
	EWindow::scroll = yoffset;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	//if () 00:13:53 27.11.2019
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		EWindow::LMB = true;
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		EWindow::LMB = false;
	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		EWindow::RMB = true;
	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
	{
		EWindow::RMB = false;
	}
}

void mouse_position_callback(GLFWwindow* window, double _x, double _y)
{
	EWindow::mouse_x = _x;
	EWindow::mouse_y = EGraphicCore::SCR_HEIGHT - _y;
}

void char_input_callback(GLFWwindow* window, unsigned int _char)
{
	int inputed_c = (int)_char;

	if (inputed_c == 1025) { inputed_c = 168; }
	else
		if (inputed_c == 1105) { inputed_c = 184; }
		else
			if (inputed_c > 255) { inputed_c -= 848; }

	//cout << "input character: " << inputed_c << "|" << (int)_char << "[  " << (char)inputed_c << " ]" << " (" << _char << ")" << endl;

	EWindow::last_inputed_char = (char)inputed_c;

	//EWindow::last_inputed_char = _char;
}

void processInput(GLFWwindow* window)
{
	/*
	if ((glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS))
	{
		for (Entity* e : EWindow::window_game->entity_list)
		{
			*e->position_x = (rand() % 1000) + 55.0f;
			*e->position_y = (rand() % 1000) + 55.0f;
		}
	}*/

	/*
	if ((glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS))
	{
		for (int i = 0; i < PATH_MATRIX_ARRAY_SIZE; i++)
		for (int j = 0; j < PATH_MATRIX_ARRAY_SIZE; j++)
			{
				if (rand() % 5 == 0)
				{
					EWindow::window_game->unwalk_matrix[j][i][0] = true;
					EWindow::window_game->unwalk_matrix[j][i][1] = true;
				}
				else
				{
					EWindow::window_game->unwalk_matrix[j][i][0] = false;
					EWindow::window_game->unwalk_matrix[j][i][1] = false;
				}

				EWindow::window_game->path_matrix[j][i][0] = 99;
				EWindow::window_game->path_matrix[j][i][1] = 99;

				EWindow::window_game->blocked_by_entity[j][i][0] = false;
				EWindow::window_game->blocked_by_entity[j][i][1] = false;
			}
	}*/
}