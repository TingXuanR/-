#include "Tortoies.h"

bool CTortoies::init()
{
	if (!CEnemy::init())
	{
		return false;
	}
	m_pImage = Sprite::createWithSpriteFrameName("tortoise_01.png");
	scheduleUpdate();
	return true;
}

void CTortoies::changeState()
{
	SpriteFrameCache* pCache = SpriteFrameCache::getInstance();
	Animation* aniMushRoomWalk = Animation::create();
	char name[52] = {};
	Animation* aniTortoiseWalk = Animation::create();
	for (int i = 1; i <= 2; ++i)
	{
		sprintf_s(name, "tortoise_%02d.png", i);
		aniTortoiseWalk->addSpriteFrame(pCache->getSpriteFrameByName(name));
	}
	aniTortoiseWalk->setDelayPerUnit(0.08);
	AnimationCache::getInstance()->addAnimation(aniTortoiseWalk, "Tortoieswalk");

	m_pImage->runAction(RepeatForever::create(Animate::create(aniTortoiseWalk)));
}
