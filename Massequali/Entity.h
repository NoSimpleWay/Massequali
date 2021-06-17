#pragma once

#include "NSW_api/EGraphicCore.h"

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

	static void reset_sprite_data(EGraphicCore::ESprite* _sprite);

	static void draw_entity(Entity* _e, Batcher* _b, float _d);

	EGraphicCore::sprite_array* entity_sprite_array;
	bool* is_selected = new bool(false);
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