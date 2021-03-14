#ifndef __EnemyMgr_H__
#define __EnemyMgr_H__

#include "cocos2d.h"
#include "Enemy.h"
USING_NS_CC;

class CEnemyMgr : public Node
{
public:
 	virtual bool init();
	virtual void update();
	CREATE_FUNC(CEnemyMgr);
	
private:
	vector<CEnemy*> m_vEnemys;
};

#endif; 