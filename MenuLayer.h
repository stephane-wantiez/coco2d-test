#ifndef __MENULAYER_H__
#define __MENULAYER_H__

#include "cocos2d.h"
//#include "cocoa/CCGeometry.h"

USING_NS_CC;

class MenuLayer : public CCLayer
{
	private:
		CCSize m_visibleSize;
		CCPoint m_origin;
		CCPoint m_center;
		CCPoint m_beginTouch;
		CCMenu * m_pMenu;
		float m_menuMaxY;
		float m_speed;
		unsigned long long m_beginTouchTimeMs;
		unsigned long long m_previousTimeMs;
		bool m_touching;
		//float m_menuDeceleration;

	public:
		// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
		virtual bool init();  

		// there's no 'id' in cpp, so we recommend returning the class instance pointer
		static CCScene* scene();

		CREATE_FUNC(MenuLayer);
    
		void menuLayer1Callback(CCObject* pSender);
		void  menuEmptyCallback(CCObject* pSender);
		void   menuExitCallback(CCObject* pSender);

		void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
		void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
		void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

		void update(float deltaTime);

};


#endif
