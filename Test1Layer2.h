#ifndef __TEST1LAYER2_H__
#define __TEST1LAYER2_H__

#include "cocos2d.h"

USING_NS_CC;

class Test1Layer2 : public cocos2d::CCLayer
{
	private:
		CCSize m_visibleSize;
		CCPoint m_origin;

	public:

		// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
		virtual bool init();

		CREATE_FUNC(Test1Layer2);
    
		// a selector callback
		void menuCloseCallback1(CCObject* pSender);
		void menuCloseCallback2();
};


#endif


