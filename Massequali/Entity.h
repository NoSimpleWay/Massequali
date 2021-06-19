#pragma once

#include "NSW_api/EGraphicCore.h"
#include "NSW_api/EWindow.h"


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

	EGraphicCore::sprite_array* entity_sprite_array;
	bool* is_selected = new bool(false);

	struct AutobuildingBase
	{
		EGabarite* main_texture;


		float* space_between_sprite_x = new float(0.0f);
		float* space_between_sprite_y = new float(0.0f);

		std::vector<EButton::EGridRegion*> grid_region;

		AutobuildingBase();
	};

	struct AutobuildingGroupElement
	{
		float* offset_x = new float(0.0f);
		float* offset_y = new float(0.0f);

		float* size_x = new float(300.0f);
		float* size_y = new float(100.0f);

		AutobuildingBase* autobuilding_base;

		bool* catched_left_side = new bool(false);
		bool* catched_right_side = new bool(false);
		bool* catched_up_side = new bool(false);
		bool* catched_down_side = new bool(false);

		bool* catched_mid = new bool(false);

	};

	struct AutobiuldingGroup
	{
		float* offset_x = new float(0.0f);
		float* offset_y = new float(0.0f);

		float* size_x = new float(0.0f);
		float* size_y = new float(0.0f);

		std::vector<AutobuildingGroupElement*> autobuilding_group_element_list;
	};

	std::vector<AutobuildingBase*> autobuilding_base_list;
	std::vector<AutobiuldingGroup*> autobuilding_group_list;
	//EButton::EGridRegion* autobuilding
};

class ECluster
{
public:
	std::vector<Entity*> entity_list;

	static const int CLUSTER_SIZE_X = 200;
	static const int CLUSTER_SIZE_Y = 200;
	
};

class ECamera
{
public:
	float* position_x	=	new float(0.0f);
	float* position_y	=	new float(0.0f);

	float* speed_x		=	new float(0.0f);
	float* speed_y		=	new float(0.0f);

	float* zoom			= new float(1.0f);

		ECamera();
		~ECamera();

		
};