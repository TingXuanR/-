#include "MushroomMgr.h"


bool CMushroomMgr::init()
{
	if (!Node::init())
	{
		return false;
	}

	this->scheduleUpdate();
	return true;
}

void CMushroomMgr::update()
{
	
}
