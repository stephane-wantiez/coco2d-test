#ifndef __TEST1LAYER_H__
#define __TEST1LAYER_H__

#include "cocos2d.h"
//#include "cocoa/CCGeometry.h"

USING_NS_CC;

class Test1Layer : public cocos2d::CCLayer
{
	private:
		static const CCPoint HAPPY_SPRITE_SPEED_PPSEC;
		CCSize m_visibleSize;
		CCPoint m_origin;
		CCSprite* mHappySprite;
		float m_maxX , m_maxY;

	public:

		// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
		virtual bool init();  

		// there's no 'id' in cpp, so we recommend returning the class instance pointer
		static CCScene* scene();

		CREATE_FUNC(Test1Layer);
    
		// a selector callback
		void menuCloseCallback(CCObject* pSender);
    
		// a selector callback
		void menuOpenLayer2Callback(CCObject* pSender);

		void update(float deltaTime);
};


#endif


