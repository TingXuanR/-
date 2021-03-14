#ifndef __Enemy_H__
#define __Enemy_H__

#include "cocos2d.h"
USING_NS_CC;

class CEnemy : public Node
{
public:
	virtual bool init();
	CREATE_FUNC(CEnemy);
	
	void move();
private:

};

#endif;

