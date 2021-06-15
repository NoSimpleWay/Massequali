#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::reset_sprite_data(EGraphicCore::ESprite* _sprite)
{
	*_sprite->fragment_x = 1.0f;
	*_sprite->fragment_y = 1.0f;

	*_sprite->offset_x = 0.0f;
	*_sprite->offset_y = 0.0f;
	*_sprite->offset_z = 0.0f;

	_sprite->texture_gabarite = NULL;
}

ECamera::ECamera()
{
}

ECamera::~ECamera()
{
}
