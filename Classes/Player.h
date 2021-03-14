#ifndef __Player_H__
#define __Player_H__


#include "cocos2d.h"
//#include <iostream>
USING_NS_CC;
using namespace std;
enum
{
	E_STATE_NONE,
	E_STATE_IDLE,
	E_STATE_WALK,
	E_STATE_JUMP,
	E_STATE_FALL,
	E_STATE_DIED,
	E_STATE_BIGWALK
};

class CPlayer : public Node//Sprite
{
public:
	virtual bool init();
	CREATE_FUNC(CPlayer);
	void changeState(int nState);
	int getDiedTime();
	bool isBig();
	void turnBig();
	void turnSmall();
	Vec2 getPlayerSize();
	CC_SYNTHESIZE_READONLY(Sprite*, m_pImage, Image);
	CC_SYNTHESIZE_READONLY(Vec2, m_vDir, Dir);
	CC_SYNTHESIZE(int, m_nInvincibleTime, InvincibleTime);
	CC_SYNTHESIZE(bool, m_bIsOpenTimer, OpenTimer);
private:
	virtual void update(float delta);
	string checkTouchY();
	string checkTouchX();
	Vec2 getTouchPoint(const Vec2& dir); //(L/R, U/D)
	void initData();
	void createAnimations();
	void addKeyboardEvent();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* pEvent);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* pEvent);
	float calVelocity(float fInitVel, float fAcl, float fTime);
	void walk(float delta);
	void stand(float delta);
	void jump(float delta);
	void fall(float delta);
	void updatePosition(float delta);
	void checkTouchType(string strType, Vec2 vTouchPos);
	string gIdTostrType(int nGid);

	
private:
	float m_fAccel;
	Sprite* m_pPlayer;
	int m_nState;
	Animate* m_aniWalk;
	//Vec2 m_vDir;
	Vec2 m_vVelocity;
	float m_fMaxVel;
	float m_fStartJumpPoint;
	int m_nMaxJumpHeight;
	Vec2 m_vColliPointsY[3]; // 123,456,789
	Vec2 m_vColliPointsX[3];
	bool m_bResetFollow;
	float m_fMaxX;
	int m_nCoinCount;
	bool m_bIsBig;
	bool m_bOldState; // false对应small，true对应big
	int m_nDiedTime;
	/*int m_nMaxVecX;
	int m_nMaxVecY;*/
};

#endif