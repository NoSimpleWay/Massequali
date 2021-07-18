#pragma once

#include "NSW_api/EGraphicCore.h"
#include "NSW_api/EWindow.h"
#include "ExternalEnums.h"

class Entity
{
public:
	float* position_x = new float(0.0f);
	float* position_y = new float(0.0f);
	float* position_z = new float(0.0f);

	float* speed_x = new float(0.0f);
	float* speed_y = new float(0.0f);
	float* speed_z = new float(0.0f);

	std::vector<EGraphicCore::ESprite*> sprite_list;

	int* previvous_cluster_x = new int(0);
	int* previvous_cluster_y = new int(0);

	//ECluster* previvous_cluster = NULL;

	Entity();
	~Entity();

	static void draw_entity(Entity* _e, Batcher* _b, float _d);
	
	static void draw_entity_autobuilging_helping(Entity* _e, Batcher* _b, float _d);

	EGraphicCore::sprite_array* entity_sprite_array;
	bool* is_selected = new bool(false);

	struct AutobuildingBase
	{
		EGabarite* main_texture;
		EGabarite* normal_gloss_map_texture = NULL;

		float* space_between_sprite_x = new float(0.0f);
		float* space_between_sprite_y = new float(0.0f);

		int* random_space_between_sprite_x = new int(0.0f);
		int* random_space_between_sprite_y = new int(0.0f);

		int* selected_sprite_fill_mode = new int(0.0f);

		int* random_sprite_count = new int(0.0f);

		std::vector<EButton::EGridRegion*> grid_region;

		AutobuildingBase();

		//bool* is_AO_embient_shadow = new bool(false);
		int* selected_sprite_draw_mode = new int(SpriteDrawMode::SPRITE_DRAW_MODE_NORMAL);

		
	};

	struct AutobuildingGroup;

	struct AutobuildingGroupElement
	{

		float* offset_x = new float(0.0f);
		float* offset_y = new float(0.0f);
		float* offset_z = new float(0.0f);

		float* size_x = new float(300.0f);
		float* size_y = new float(100.0f);

		AutobuildingBase* autobuilding_base;

		bool* catched_left_side = new bool(false);
		bool* catched_right_side = new bool(false);
		bool* catched_up_side = new bool(false);
		bool* catched_down_side = new bool(false);

		bool* catched_mid = new bool(false);
		bool* catched_z = new bool(false);

		float* highlight_time = new float(0.0f);

		AutobuildingGroup* master_group;
	};

	struct AutobuildingGroup
	{
		float* offset_x = new float(0.0f);
		float* offset_y = new float(0.0f);
		float* offset_z = new float(0.0f);

		float* size_x = new float(0.0f);
		float* size_y = new float(0.0f);

		float* bottom_offset	= new float(0.0f);
		float* up_offset		= new float(0.0f);

		int* selected_direction_of_push = new int(AutobuildingSpritePushDirection::AUTOBUILDING_SPRITE_PUSH_DIRECTION_ROOF_Y);


		std::vector<AutobuildingGroupElement*> autobuilding_group_element_list;

		std::vector<EGraphicCore::ESprite*> sprite_list;

		Entity* master_entity;
		bool* is_catched = new bool (false);
		std::string* name = new string("!");

		float* max_height = new float(0.0f);

		float*	pseudo_pos_x		= new float(0.0f);
		float*	pseudo_pos_x2		= new float(0.0f);
		float*	pseudo_size_x		= new float(0.0f);

		float*	pseudo_pos_y		= new float(0.0f);
		float*	pseudo_pos_y2		= new float(0.0f);
		float*	pseudo_size_y		= new float(0.0f);

		float*	pseudo_pos_z		= new float(0.0f);
		float*	pseudo_pos_z2		= new float(0.0f);
		float*	pseudo_size_z		= new float(0.0f);

		int*	seed				= new int(0);
	
	};

	std::vector<AutobuildingBase*> autobuilding_base_list;
	std::vector<AutobuildingGroup*> autobuilding_group_list;
	//EButton::EGridRegion* autobuilding

	int* selected_cluster_mode = new int(EntityClusterMode::ENTITY_CLUSTER_MODE_STATIC);

	static void draw_catched_element(Entity::AutobuildingGroupElement* _element, Entity* _e, Entity::AutobuildingGroup* _group, bool _always_show);
};

class ECluster
{
public:
	std::vector<Entity*> entity_list;

	static const int CLUSTER_SIZE_X = 250;
	static const int CLUSTER_SIZE_Y = 250;

	static const int CLUSTED_DIM_X = 40;
	static const int CLUSTED_DIM_Y = 40;
};

class ECamera
{
public:
	float* position_x = new float(500.0f);
	float* position_y = new float(800.0f);

	float* speed_x = new float(0.0f);
	float* speed_y = new float(0.0f);

	float* zoom = new float(1.0f);

	ECamera();
	~ECamera();
};