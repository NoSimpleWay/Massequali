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

void Entity::draw_entity(Entity* _e, Batcher* _b, float _d)
{
	if (_e->entity_sprite_array != NULL)
	{
		EGraphicCore::draw_sprite_regular(_e->entity_sprite_array, EGraphicCore::batch, *_e->position_x, *_e->position_y, *_e->position_z);
	}

	if (*_e->is_selected)
	{
		EGraphicCore::batch->setcolor(EColor::COLOR_GREEN);
		EGraphicCore::batch->draw_rama(*_e->position_x-10.0f, *_e->position_y-10.0f, 20.0f, 20.0f, 2.0f, EGraphicCore::gabarite_white_pixel);
	}
}

ECamera::ECamera()
{
}

ECamera::~ECamera()
{
}
