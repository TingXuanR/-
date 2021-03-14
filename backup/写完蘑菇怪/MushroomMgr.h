#ifndef __MushroomMgr_H__
#define __MushroomMgr_H__

#include "cocos2d.h"
#include "Mushroom.h"
USING_NS_CC;

class CMushroomMgr : public Node
{
public:
 	virtual bool init();
	virtual void update();
	CREATE_FUNC(CMushroomMgr);
	
private:
	vector<CMushroom*> m_vMushrooms;
};

#endif; 