#include "MenuLayer.h"
#include "Test1Layer.h"
#include "AppMacros.h"

USING_NS_CC;


CCScene* MenuLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene * pScene = CCScene::create();
    
    // 'layer' is an autorelease object
    MenuLayer * pLayer = MenuLayer::create();

    // add layer as a child to scene
    pScene->addChild(pLayer);

    // return the scene
    return pScene;
}

// on "init" you need to initialize your instance
bool MenuLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
  
    m_visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    m_origin = CCDirector::sharedDirector()->getVisibleOrigin();
	m_center = CCPoint( m_origin.x + m_visibleSize.width / 2.f , m_origin.y + m_visibleSize.height / 2.f );
	m_speed = 0.f;
	m_touching = false;
	//m_menuDeceleration = 0.5f;
    
    CCMenuItemFont::setFontSize(24);
    
    CCMenuItem * pMenuScene1 = CCMenuItemFont::create("Scene 1", this, menu_selector(MenuLayer::menuLayer1Callback));
    CCMenuItem * pMenuElem1  = CCMenuItemFont::create("Elem 1",  this, menu_selector(MenuLayer::menuEmptyCallback ));
    CCMenuItem * pMenuElem2  = CCMenuItemFont::create("Elem 2",  this, menu_selector(MenuLayer::menuEmptyCallback ));
    CCMenuItem * pMenuElem3  = CCMenuItemFont::create("Elem 3",  this, menu_selector(MenuLayer::menuEmptyCallback ));
    CCMenuItem * pMenuElem4  = CCMenuItemFont::create("Elem 4",  this, menu_selector(MenuLayer::menuEmptyCallback ));
    CCMenuItem * pMenuElem5  = CCMenuItemFont::create("Elem 5",  this, menu_selector(MenuLayer::menuEmptyCallback ));
    CCMenuItem * pMenuElem6  = CCMenuItemFont::create("Elem 6",  this, menu_selector(MenuLayer::menuEmptyCallback ));
    CCMenuItem * pMenuElem7  = CCMenuItemFont::create("Elem 7",  this, menu_selector(MenuLayer::menuEmptyCallback ));
    CCMenuItem * pMenuElem8  = CCMenuItemFont::create("Elem 8",  this, menu_selector(MenuLayer::menuEmptyCallback ));
    CCMenuItem * pMenuExit   = CCMenuItemFont::create("Exit",    this, menu_selector(MenuLayer::menuExitCallback  ));
    
    m_pMenu = CCMenu::create(pMenuScene1, pMenuElem1, pMenuElem2, pMenuElem3, pMenuElem4, pMenuElem5, pMenuElem6, pMenuElem7, pMenuElem8, pMenuExit, NULL);

	float menuPadding = 10.f;
	m_pMenu->alignItemsVerticallyWithPadding(menuPadding);

	int nbElems = m_pMenu->getChildrenCount();
	float menuElemHeight = pMenuScene1->getContentSize().height;

	m_menuMaxY = nbElems * menuElemHeight + (nbElems-1) * menuPadding;

    this->addChild(m_pMenu, 1);

    setTouchEnabled(true);

	this->schedule(schedule_selector(MenuLayer::update));

	cc_timeval currentTime;
	CCTime::gettimeofdayCocos2d(&currentTime,NULL);
	m_previousTimeMs = (currentTime.tv_sec * 1000 + currentTime.tv_usec / 1000);
    
    return true;
}


void MenuLayer::menuLayer1Callback(CCObject* pSender)
{
	CCScene * pScene = Test1Layer::scene();
	
    CCScene* pTransScene = CCTransitionShrinkGrow::create(1.f, pScene);

    CCDirector::sharedDirector()->replaceScene(pTransScene);
}

void MenuLayer::menuEmptyCallback(CCObject* pSender)
{}

void MenuLayer::menuExitCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void MenuLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);

    m_beginTouch = touch->getLocation();

	m_touching = true;

	cc_timeval currentTime;
	CCTime::gettimeofdayCocos2d(&currentTime,NULL);
	m_beginTouchTimeMs = (currentTime.tv_sec * 1000 + currentTime.tv_usec / 1000);

	//CCLOG( "Touch started at %f , %f", m_beginTouch.x, m_beginTouch.y );
}

void MenuLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);

    CCPoint touchLocation = touch->getLocation();
    float nMoveY = touchLocation.y - m_beginTouch.y;
	//CCLOG( "Touch moved to %f , %f", touchLocation.x, touchLocation.y );

    CCPoint curPos  = m_pMenu->getPosition();
    CCPoint nextPos = ccp(curPos.x, curPos.y + nMoveY);
	/*CCLOG( "Menu position: %f , %f", curPos.x, curPos.y );*/

    if (nextPos.y < 0.0f)
    {
        //nextPos.y = 0.f;
		nextPos = ccp(curPos.x, curPos.y + nMoveY/3.f);
		m_speed = 40.f;
    }
	else if (nextPos.y > m_menuMaxY)
    {
        //nextPos.y = m_menuMaxY;
		nextPos = ccp(curPos.x, curPos.y + nMoveY/3.f);
		m_speed = -40.f;
    }
	else
	{
		cc_timeval currentTime;
		CCTime::gettimeofdayCocos2d(&currentTime,NULL);
		unsigned int DeltaTimeMs;
		unsigned long long CurrentTimeMs;
		CurrentTimeMs = (currentTime.tv_sec * 1000 + currentTime.tv_usec / 1000);
		DeltaTimeMs = CurrentTimeMs - m_beginTouchTimeMs;

		if (DeltaTimeMs)
		{
			m_speed = nMoveY / ( DeltaTimeMs / 1000.f );
			//CCLOG( "Speed %f", m_speed );
		}
		else
		{
			m_speed = 0;
		}
	}

	m_pMenu->setPosition(nextPos);
	m_beginTouch = touchLocation;

}

void MenuLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	m_touching = false;
	//CCLOG( "Touch ended at %f , %f", m_beginTouch.x, m_beginTouch.y );
}

void MenuLayer::update(float deltaTime)
{
	cc_timeval currentTime;
	CCTime::gettimeofdayCocos2d(&currentTime,NULL);
	unsigned int DeltaTimeMs;
	unsigned long long CurrentTime;
	CurrentTime = (currentTime.tv_sec * 1000 + currentTime.tv_usec / 1000);

	DeltaTimeMs = CurrentTime - m_previousTimeMs;
	m_previousTimeMs = CurrentTime;

	if (!m_touching)
	{
		float nMoveY = m_speed * 10.f * DeltaTimeMs / 1000.f;
		//CCLOG( "Speed %f", m_speed );

		CCPoint curPos  = m_pMenu->getPosition();
 		CCPoint nextPos = ccp(curPos.x, curPos.y + nMoveY);

		m_pMenu->setPosition(nextPos);

		if (nextPos.y < 0.0f)
		{
			//nextPos.y = 0.f;
			if (m_speed < 0) m_speed *= -1.f;
		}
		else if (nextPos.y > m_menuMaxY)
		{
			//nextPos.y = m_menuMaxY;
			if (m_speed > 0) m_speed *= -1.f;
		}
		else
		{
			m_speed = m_speed * 0.9f * ( 1.0f - DeltaTimeMs / 1000.f );
		}
		
		//CCLOG( "Speed %f - Pos %f", m_speed, nextPos.y );
	}
}
