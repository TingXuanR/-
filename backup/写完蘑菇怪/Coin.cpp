#include "Coin.h"

//CCoin* CCoin::m_pInstance = nullptr;
//CCoin* CCoin::getInstance()
//{
//	if (!m_pInstance)
//	{
//		m_pInstance = new CCoin();
//	}
//	return m_pInstance;
//}

bool CCoin::init()
{
	if (!Node::init())
	{
		return false;
	}
	m_bIsExist = false;
	Sprite* pCoin = Sprite::createWithSpriteFrameName("coin_ani_01.png");
	this->addChild(pCoin);
	Animate* m_aniCoin = Animate::create(AnimationCache::getInstance()->getAnimation("coin"));
	pCoin->runAction(RepeatForever::create(m_aniCoin));

	return true;
}


