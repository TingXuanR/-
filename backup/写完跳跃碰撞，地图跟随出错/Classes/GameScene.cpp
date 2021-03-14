#include "GameScene.h"

CGameScene* CGameScene::m_pInstance = nullptr;
CGameScene* CGameScene::getInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = CGameScene::create();
	}
	return m_pInstance;
}

bool CGameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	this->loadRes();

	m_pTileMap = CTileMap::create();
	this->addChild(m_pTileMap);
	
	m_pPlayer = CPlayer::create();
	this->addChild(m_pPlayer);
	m_pPlayer->setPosition(m_pTileMap->getBirthPoint());
	
	m_pTileMap->follow(m_pPlayer);
	return true;
}

void CGameScene::loadRes()
{
	SpriteFrameCache* pCache = SpriteFrameCache::getInstance();
	pCache->addSpriteFramesWithFile("Image/plist/AllPics.plist");
}
