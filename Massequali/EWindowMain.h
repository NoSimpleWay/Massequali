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

};