#include "Enemy.h"
#include "GameScene.h"
bool CEnemy::init()
{
	if (!Node::init())
	{
		return false;
	}
	m_nState = E_STATE_M_NONE;
	m_vDir.x = 0;
	m_vDir.y = -1;
	m_nDiedDurTime = 0;
	m_vVelocity.x = m_vVelocity.y = 0;
	m_pImage = Sprite::createWithSpriteFrameName("Enemy_1_01.png");
	this->createAnimations();
	this->addChild(m_pImage);
	this->scheduleUpdate();
	return true;
}

void CEnemy::update(float delta)
{
	if (m_nState == E_STATE_M_DIED)
	{
		if (m_nDiedDurTime == 0)
		{
			m_nDiedDurTime++;
			//m_pImage->runAction(JumpBy::create(0.8f, 0, -30, 3));
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
		/*if (m_vDir.y == -1)
		{
		fall(delta);
		}*/
		if (checkTouchY() == "none")
		{
			m_vDir.y = -1;
			fall(delta);
			/*m_vVelocity.y += -500 * delta * m_vDir.y;
			float fPositionY = this->getPositionY();
			fPositionY += m_vDir.y * delta * m_vVelocity.y;
			this->setPositionY(fPositionY);*/
		}
		/*else if (checkTouchY() != "none")
		{
			if (checkTouchY() == "trap")
			{
				changeState(E_STATE_M_DIED);
			}
			else
			{
				float fPositionY = this->getPositionY();
				Vec2 vGroundTile = CGameScene::getInstance()->getTileMap()->getTileByPos(Vec2(this->getPositionX(), fPositionY - m_pImage->getContentSize().height / 2));
				fPositionY = (CGameScene::getInstance()->getTileMap()->getPosByTile(vGroundTile)).y + 16;
				m_vDir.y = 0;
				m_vVelocity = 0;
				this->setPositionY(fPositionY);
			}
			
		}*/
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

void CEnemy::createAnimations()
{
	SpriteFrameCache* pCache = SpriteFrameCache::getInstance();
	Animation* aniWalk = Animation::create();
	char name[52] = {};
	for (int i = 1; i <= 2; ++i)
	{
		sprintf_s(name, "Enemy_1_%02d.png", i);
		aniWalk->addSpriteFrame(pCache->getSpriteFrameByName(name));
	}
	aniWalk->setDelayPerUnit(0.08);
	AnimationCache::getInstance()->addAnimation(aniWalk, "walk");

	
	m_pImage->runAction(RepeatForever::create(Animate::create(aniWalk)));
}

void CEnemy::changeState(int nState)
{
	if (nState == m_nState)
	{
		return;
	}
	m_nState = nState;
	m_pImage->stopAllActions();
	if (E_STATE_M_DIED == m_nState)
	{
		m_pImage->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy_1_die_01.png"));
	}
}

std::string CEnemy::gIdTostrType(int nGid)
{
	if (nGid == 1)
		{
			return "nBlock"; // normal block, without coin.
		}
		else if (nGid == 91)
		{
			return "csBlock"; // block with coins.
		}
		else if (nGid == 29 || nGid == 30 || nGid == 59 || nGid == 60)
		{
			return "pipe";
		}
		else if (nGid == 601)
		{

			return "cBlock"; // block with one coin.
		}
		else if (nGid == 31)
		{
			return "bBlock"; // blank block
		}
		else if (nGid == 121)
		{
			return "ground";
		}
		else if (nGid == 151)
		{
			return "step";
		}
		else if (nGid == 661)
		{
			return "coin";
		}
		else if (nGid == 875 || nGid == 874 || nGid == 876 || nGid == 845 || nGid==846)
		{
			return "trap";
		}
		else if (nGid == 0)
		{
			return  "none";
		}
}


std::string CEnemy::checkTouchX()
{
	Vec2 vTouchPoint;
	if (m_vDir.x == 1)
	{
		vTouchPoint = this->getTouchPoint(Vec2(1, 0));
	}
	else
	{
		vTouchPoint = this->getTouchPoint(Vec2(-1, 0));
	}
	CTileMap* pTileMap = CGameScene::getInstance()->getTileMap();
	Vec2 touchPoint = pTileMap->getTileByPos(vTouchPoint); 
	int nGid = pTileMap->checkTouchX(touchPoint);
	string strTouch = gIdTostrType(nGid);

	return strTouch;
}

std::string CEnemy::checkTouchY()
{
	Vec2 vTouchPoint;
	if (m_vDir.y == 1)
	{
		vTouchPoint = this->getTouchPoint(Vec2(0, 1));
	}
	else
	{
		vTouchPoint = this->getTouchPoint(Vec2(0, -1));
	}
	CTileMap* pTileMap = CGameScene::getInstance()->getTileMap();
	Vec2 touchPoint = pTileMap->getTileByPos(vTouchPoint);  
	int nGid = pTileMap->checkTouchY(touchPoint, m_vDir.y);
	string strTouch = gIdTostrType(nGid);

	return strTouch;
}

cocos2d::Vec2 CEnemy::getTouchPoint(const Vec2& dir)
{
	Vec2 pos = this->getPosition();
	Size playerSize = m_pImage->getContentSize();
	pos.x += dir.x * playerSize.width / 2;
	pos.y += dir.y * playerSize.height / 2;
	return pos;
}

void CEnemy::fall(float delta)
{
	m_vVelocity.y += -500 * delta * m_vDir.y;
	float fPositionY = this->getPositionY();
	fPositionY += m_vDir.y * delta * m_vVelocity.y;
	string strTouchTypeY = checkTouchY();
	if (fPositionY <= 32)
	{
		this->setPositionX(this->getPositionX() - 6);
		m_nState = E_STATE_M_DIED;
	}
	else
	{
		this->setPositionY(fPositionY);
	}
	
	//if (strTouchTypeY != "none")
	//{
	//	if (strTouchTypeY == "trap")
	//	{
	//		changeState(E_STATE_M_DIED);
	//	}
	//	else if (strTouchTypeY == "ground" )
	//	{
	//		Vec2 vGroundTile = CGameScene::getInstance()->getTileMap()->getTileByPos(Vec2(this->getPositionX(), fPositionY - m_pImage->getContentSize().height / 2));
	//		fPositionY = (CGameScene::getInstance()->getTileMap()->getPosByTile(vGroundTile)).y + 16;
	//		/*if (this->getPositionY() <= 40)
	//		{
	//			log("fposY: %.2f\nGroundTile: %.2f, %.2f", fPositionY, vGroundTile.x, vGroundTile.y);
	//		}*/
	//		m_vDir.y = 0;
	//		m_vVelocity = 0;
	//		this->setPositionY(fPositionY);
	//	}
	//}
	/*else if (fPositionY <= 35)
	{
		changeState(E_STATE_M_DIED);
	}*/
	/*else
	{
		this->setPositionY(fPositionY);
	}*/
}

void CEnemy::walk(float delta)
{
	m_vVelocity.x = 60;
	float fPositionX = this->getPositionX();
	fPositionX += m_vDir.x * delta * m_vVelocity.x;
	if (checkTouchX() != "none")
	{
		Vec2 vGroundTile = CGameScene::getInstance()->getTileMap()->getTileByPos(Vec2(fPositionX + 8 * m_vDir.x, this->getPositionY()));
		fPositionX = (CGameScene::getInstance()->getTileMap()->getPosByTile(vGroundTile)).x - m_vDir.x * 16;
		m_vDir.x *= -1;
		this->setPositionX(fPositionX);
	}
	else if (fPositionX <= 0)
	{
		this->setVisible(false);
		this->setPositionX(5);
	}
	else
	{
		this->setPositionX(fPositionX);
	}
}

void CEnemy::checkDistaceWithMario()
{
	m_pPlayer = CGameScene::getInstance()->getCPlayer();
	
	float fEnemyX =  m_vBirthPoint.x;
	float fPlayerX = m_pPlayer->getPositionX();
	if ((fEnemyX - fPlayerX) <= 180)
	{
		m_vDir.x = -1;
	}
}

void CEnemy::setBirthPoint(Vec2 m_vBirthPoint)
{
	this->m_vBirthPoint = m_vBirthPoint;
}

void CEnemy::updateDiedY(float delta)
{
	float fY = this->getPositionY();
	fY += -1 * delta * m_vVelocity.y;
	this->setPositionY(fY);
	if (fY <= 2)
	{
		this->setVisible(false);
	}
}

int CEnemy::getDiedDurTime()
{
	return m_nDiedDurTime;
}





