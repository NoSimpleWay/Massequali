#include "NSW_api/EWindow.h"
#include "Entity.h"

class EWindowMain : public EWindow
{
public:
	EWindowMain();
	~EWindowMain();

	ECluster* cluster_list[100][100];

	EButton::button_super_group* super_group_texture_collection_link;
	EButton::button_group* group_texture_collection_link;

	EButton* textures_selector_slider;
	virtual void draw(float _d);
	virtual void update(float _d);

	void reset_render();

	std::vector<Entity*> entity_list;

	ECamera* main_camera = new ECamera();
};