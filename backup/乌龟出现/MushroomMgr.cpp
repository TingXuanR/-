#include "EnemyMgr.h"


bool CEnemyMgr::init()
{
	if (!Node::init())
	{
		return false;
	}

	this->scheduleUpdate();
	return true;
}

void CEnemyMgr::update()
{
	
}
