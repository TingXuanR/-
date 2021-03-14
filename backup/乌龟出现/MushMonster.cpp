#include "MushMonster.h"

bool CMushMonster::init()
{
	this->initData();
	m_pImage = Sprite::createWithSpriteFrameName("tortoise_01.png");
	scheduleUpdate();
	return true;
}

void CMushMonster::changeState()
{
	SpriteFrameCache* pCache = SpriteFrameCache::getInstance();
	Animation* aniMushRoomWalk = Animation::create();
	char name[52] = {};
	for (int i = 1; i <= 2; ++i)
	{
		sprintf_s(name, "mushroom_1_%02d.png", i);
		aniMushRoomWalk->addSpriteFrame(pCache->getSpriteFrameByName(name));
	}
	aniMushRoomWalk->setDelayPerUnit(0.08);
	AnimationCache::getInstance()->addAnimation(aniMushRoomWalk, "Mushroomwalk");

}

void CMushMonster::initData()
{
	m_nState = E_STATE_M_NONE;
	m_vDir.x = 0;
	m_vDir.y = -1;
	m_nDiedDurTime = 0;
	m_vVelocity.x = m_vVelocity.y = 0;
}

void CMushMonster::update(float delta)
{
	if (m_nState == E_STATE_M_DIED)
	{
		if (m_nDiedDurTime == 0)
		{
			m_nDiedDurTime++;
			m_vVelocity.x = 0;
			m_vVelocity.y = 30;
		}
		else
		{
			updateDiedY(delta);
		}
	}
	else
	{
		if (checkTouchY() == "none")
		{
			m_vDir.y = -1;
			fall(delta);
		}
		if (m_vDir.x == 1 || m_vDir.x == -1)
		{
			walk(delta);
		}
		if (m_vDir.x == 0)
		{
			checkDistaceWithMario();
		}
	}
}
