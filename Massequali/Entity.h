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

};

class ECluster
{
public:
	std::vector<Entity*> entity_list;

	static const int CLUSTER_SIZE_X = 200;
	static const int CLUSTER_SIZE_Y = 200;
	
};