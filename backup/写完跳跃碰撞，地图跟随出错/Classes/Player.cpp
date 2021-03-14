#include "Player.h"
#include "GameScene.h"
bool CPlayer::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	// 初始化
	m_fAccel = -1000;
	m_vDir.x = 0;
	m_vDir.y = 0;
	/*m_vVelocity.x = 0;
	m_vVelocity.y = 0;*/
	m_nMaxJumpHeight = 70;
	m_fStartJumpPoint = 0;
	m_fMaxVel = 180;
	m_fMaxX = 0;
	m_nState = E_STATE_IDLE;
	m_bResetFollow = false;
	m_pImage = Sprite::createWithSpriteFrameName("small_1_walk_01.png");
	this->createAnimations();
	this->addChild(m_pImage);
	this->addKeyboardEvent();
	this->scheduleUpdate();

	return true;
}

float CPlayer::calVelocity(float fInitVel, float fAcl, float fTime)
{
	float Vel = fInitVel + fAcl*fTime;
	return Vel > m_fMaxVel ? m_fMaxVel : Vel;
}

void CPlayer::walk(float delta)
{
	m_pImage->setFlippedX(false);
	this->changeState(E_STATE_WALK);
	m_vVelocity.x = 100;
	/*float fPositionX = this->getPositionX();
	fPositionX += m_vDir.x * delta * m_vVelocity.x;
	this->setPositionX(fPositionX);
	if (checkTouchY() == "none")
	{
		m_vDir.y = -1;
	}
	if (m_vDir.y == 1)
	{
		jump(delta);
	}
	else if (m_vDir.x == -1)
	{
		changeState(E_STATE_WALK);
		m_pImage->setFlippedX(true);
	}*/
	if (checkTouchY() == "none")
	{
		m_vDir.y = -1;
	}
	if (m_vDir.y == 1)
	{
		//jump(delta);
		m_vVelocity.y = 270;
	}
	else if (m_vDir.x == -1)
	{
		changeState(E_STATE_WALK);
		m_pImage->setFlippedX(true);
	}
}

void CPlayer::stand(float delta)
{
	changeState(E_STATE_IDLE);
	m_vVelocity.x = m_vVelocity.y = 0;
	if (checkTouchY() == "none")
	{
		m_vDir.y = -1;
	}
	/*if (m_vDir.x == 1)
	{
		m_pImage->setFlippedX(false);
		this->changeState(E_STATE_WALK);
	}
	else if (m_vDir.x == -1)
	{
		changeState(E_STATE_WALK);
		m_pImage->setFlippedX(true);
	}
	else if (m_vDir.y == 1)
	{
		this->changeState(E_STATE_JUMP);
	}*/
}

void CPlayer::jump(float delta)
{
	changeState(E_STATE_JUMP);
	m_vVelocity.y = 270;
	m_vVelocity.y += m_fAccel*delta;
	/*float fPositionY = this->getPositionY();
	fPositionY = fPositionY + m_vDir.y*m_vVelocity.y*delta;

	if (fPositionY >= m_fStartJumpPoint + m_nMaxJumpHeight)
	{
		fPositionY = m_fStartJumpPoint + m_nMaxJumpHeight;
		m_vDir.y = -1;
	}
	else if (m_vVelocity.y <= 0)
	{
		m_vVelocity.y = 0;
		m_vDir.y = -1;
	}
	else if (checkTouchY() != "none")
	{
		m_vVelocity.y = 0;
		m_vDir.y = -1;
	}
   	this->setPositionY(fPositionY);*/

	if (m_vDir.x == 1)
	{
		m_vVelocity.x = 100;
		m_pImage->setFlippedX(false);
		this->changeState(E_STATE_WALK);
	}
	else if (m_vDir.x == -1)
	{
		m_vVelocity.x = 100;
		m_pImage->setFlippedX(true);
		this->changeState(E_STATE_WALK);
	}
}

void CPlayer::fall(float delta)
{
	changeState(E_STATE_FALL);
	m_vVelocity.y = calVelocity(m_vVelocity.y, m_vDir.y*m_fAccel, delta);

	//float fPositionY = this->getPositionY();
	//
	//fPositionY = fPositionY + m_vDir.y*m_vVelocity.y*delta;
	//this->setPositionY(fPositionY);
	//if (checkTouchY() != "none")
	//{
	//	changeState(E_STATE_IDLE);
	//	Vec2 vGroundTile = CGameScene::getInstance()->getTileMap()->getTileByPos(Vec2(this->getPositionX(), fPositionY-16));
	//	//ground上顶点减去自身高度。
	//	fPositionY = (CGameScene::getInstance()->getTileMap()->getPosByTile(vGroundTile)).y + m_pImage->getContentSize().height / 2;
	//	m_vDir.y = 0;
	//	m_vDir.x = 0;
	//	this->setPositionY(fPositionY);
	//	m_fStartJumpPoint = fPositionY;
	//}
}



void CPlayer::update(float delta)
{

	if (m_vDir.y == 1)
	{
		jump(delta);
	}
	else if (m_vDir.y == -1)
	{
		fall(delta);
	}
	else if (m_vDir.x == -1 || m_vDir.x == 1)
	{
		walk(delta);
	}
	else if (m_vDir.x == 0 && m_vDir.y == 0)
	{
		stand(delta);
	}
	updatePosition(delta);
	/*if (m_nState == E_STATE_WALK)
	{
		walk(delta);
	}
	if (m_nState == E_STATE_JUMP)
	{
		jump(delta);
	}
	if (m_nState == E_STATE_FALL)
	{
		fall(delta);
	}
	if (m_nState == E_STATE_IDLE)
	{
		stand(delta);
	}*/
}


Vec2 CPlayer::getTouchPoint(const Vec2& dir)
{
	Vec2 pos = this->getPosition();
	Size playerSize = m_pImage->getContentSize();
	pos.x += dir.x * playerSize.width / 2;
	pos.y += dir.y * playerSize.height / 2;
	return pos;
}

string CPlayer::checkTouchX()
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
	Vec2 touchPoint = pTileMap->getTileByPos(vTouchPoint);  // 第一根水管最左边格子坐标(28, 11)
	string strTouch = pTileMap->checkTouchX(touchPoint);
	return strTouch;
}

string CPlayer::checkTouchY()
{
	string strTouchType = "";
	
	Vec2 touchPoint;
	if (m_vDir.y == 1)
	{
		touchPoint = this->getTouchPoint(Vec2(0, 1));
	}
	else
	{
		touchPoint = this->getTouchPoint(Vec2(0, -1));
	}
	m_vColliPointsY[1] = touchPoint;
	m_vColliPointsY[0] = Vec2(touchPoint.x - m_pImage->getContentSize().width / 2 + 3, touchPoint.y); // Left-up/down
	m_vColliPointsY[2] = Vec2(touchPoint.x + m_pImage->getContentSize().width / 2 - 3, touchPoint.y); // Right-up/down
	for (int i = 0; i < 3; ++i)
	{
		Vec2 touchTile = CGameScene::getInstance()->getTileMap()->getTileByPos(m_vColliPointsY[i]);
		strTouchType = CGameScene::getInstance()->getTileMap()->checkTouchY(touchTile);
		if (strTouchType != "none")
		{
			break;
		}
	}
	
	return strTouchType;
}



void CPlayer::createAnimations()
{
	SpriteFrameCache* pCache = SpriteFrameCache::getInstance();

	//小玛丽走路动画
	Animation* aniWalk_S = Animation::create();
	char name[52] = {};
	for (int i = 1; i <= 10; ++i)
	{
		sprintf_s(name, "small_1_walk_%02d.png", i);
		aniWalk_S->addSpriteFrame(pCache->getSpriteFrameByName(name));
	}
	aniWalk_S->setDelayPerUnit(0.05);
	AnimationCache::getInstance()->addAnimation(aniWalk_S, "walk_s");

	// 大玛丽走路动画
	Animation* aniWalk_B = Animation::create();
	for (int i = 1; i <= 10; ++i)
	{
		sprintf_s(name, "big_1_walk_%02d.png", i);
		aniWalk_B->addSpriteFrame(pCache->getSpriteFrameByName(name));
	}
	aniWalk_B->setDelayPerUnit(0.05);
	AnimationCache::getInstance()->addAnimation(aniWalk_B, "walk_b");

	m_aniWalk = Animate::create(AnimationCache::getInstance()->getAnimation("walk_s"));
}

void CPlayer::changeState(int nState)
{
	if (nState == m_nState)
	{
		return;
	}
	m_nState = nState;
	m_pImage->stopAllActions();
	if (E_STATE_JUMP == m_nState || E_STATE_FALL == m_nState)
	{
		m_pImage->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("small_1_walk_11.png"));
	}
	else if (E_STATE_WALK == m_nState)
	{
		m_aniWalk = Animate::create(AnimationCache::getInstance()->getAnimation("walk_s"));
		m_pImage->runAction(RepeatForever::create(m_aniWalk));
	}
	else if (E_STATE_IDLE == m_nState)
	{
		m_pImage->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("small_1_walk_04.png"));
	}
}

void CPlayer::addKeyboardEvent()
{
	EventListenerKeyboard* pListener = EventListenerKeyboard::create();
	pListener->onKeyPressed = CC_CALLBACK_2(CPlayer::onKeyPressed, this);
	pListener->onKeyReleased = CC_CALLBACK_2(CPlayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(pListener, this);
}

void CPlayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* pEvent)
{
	if (EventKeyboard::KeyCode::KEY_A == keyCode || EventKeyboard::KeyCode::KEY_D == keyCode)
	{
		m_vDir.x = 0;
		m_vVelocity.x = 0;
	}

	if (EventKeyboard::KeyCode::KEY_SPACE == keyCode)
	{
		if (m_vDir.y == 1)
		{
			m_vDir.y = -1;
		}
	}
	
}

void CPlayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* pEvent)
{
	if (EventKeyboard::KeyCode::KEY_A == keyCode)
	{
		if (m_bResetFollow)
		{
			CTileMap* pTileMap = CGameScene::getInstance()->getTileMap();
			pTileMap->follow(this);
			m_bResetFollow = false;
		}
		m_vDir.x = -1;
	}
	else if (EventKeyboard::KeyCode::KEY_D == keyCode)
	{
		m_vDir.x = 1; 
	}
	else if (EventKeyboard::KeyCode::KEY_SPACE == keyCode)
	{
		if (m_vDir.y >= 0)
		{
			m_vDir.y = 1;
		}
	}
}

void CPlayer::updatePosition(float delta)
{
	float fPositionX = this->getPositionX();
	float fPositionY = this->getPositionY();
	
	fPositionX += m_vDir.x * delta * m_vVelocity.x;
	// this->setPositionX(fPositionX);

	if (false||checkTouchX() != "none")
	{
		Vec2 vGroundTile = CGameScene::getInstance()->getTileMap()->getTileByPos(Vec2(fPositionX + 8*m_vDir.x, this->getPositionY()));
		//取障碍物边缘左上顶点x坐标，减去格子的一半宽度和任务的一半宽度作为positionX。
		fPositionX = (CGameScene::getInstance()->getTileMap()->getPosByTile(vGroundTile)).x - m_vDir.x * 16;
		m_vDir.x = 0;
		this->setPositionX(fPositionX);
	}
	if (fPositionX > m_fMaxX)
	{
		m_fMaxX = fPositionX;
		m_bResetFollow = true;
	}

	fPositionY = fPositionY + m_vDir.y*m_vVelocity.y*delta;
	if (fPositionY >= m_fStartJumpPoint + m_nMaxJumpHeight)
	{
		fPositionY = m_fStartJumpPoint + m_nMaxJumpHeight;
		m_vDir.y = -1;
	}
	else if (m_vVelocity.y < 0)
	{
		m_vVelocity.y = 0;
		m_vDir.y = -1;
	}
	else if (m_vDir.y == 1 && checkTouchY() != "none")
	{
		m_vVelocity.y = 0;
		m_vDir.y = -1;
	}
	else if (m_vDir.y == -1 && checkTouchY() != "none")
	{
		changeState(E_STATE_IDLE);
		Vec2 vGroundTile = CGameScene::getInstance()->getTileMap()->getTileByPos(Vec2(this->getPositionX(), fPositionY - m_pImage->getContentSize().height / 2));
		//ground上顶点减去自身高度。
		fPositionY = (CGameScene::getInstance()->getTileMap()->getPosByTile(vGroundTile)).y + m_pImage->getContentSize().height / 2;
		m_vDir.y = 0;
		m_vDir.x = 0;
		this->setPositionY(fPositionY);
		m_fStartJumpPoint = fPositionY;
	}
	this->setPositionX(fPositionX);
	this->setPositionY(fPositionY);
}




