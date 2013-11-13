#include "Test1Layer2.h"
#include "AppMacros.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool Test1Layer2::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    m_visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    m_origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 3. add your codes below...
	

    CCSprite* pBackground = CCSprite::create("background1.jpg");

	pBackground->setScale(2.f);

    // position the sprite on the center of the screen
    pBackground->setPosition(ccp(m_visibleSize.width/2 + m_origin.x, m_visibleSize.height/2 + m_origin.y));

    // add the sprite as a child to this layer
    this->addChild(pBackground, 0);


    
    CCLabelTTF* pLabel = CCLabelTTF::create("Test 1 Layer 2", "Arial", TITLE_FONT_SIZE);
	pLabel->setColor(ccMAGENTA);
    
    // position the label on the center of the screen
	/*pLabel->setPosition(ccp(pBackground->getPositionX(),
                            pBackground->getPositionY() + pBackground->getContentSize().height/2.f - pLabel->getContentSize().height));*/
	pLabel->setPosition(ccp(m_visibleSize.width/2 + m_origin.x, m_visibleSize.height/2 + m_origin.y + pBackground->getContentSize().height - 10));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);


    
    CCSpriteFrameCache * pSpriteCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    pSpriteCache->addSpriteFramesWithFile("images/test.plist");

    CCArray* pSpriteFrames = CCArray::createWithCapacity(20);
	char str[25];
    for(int i = 1; i < 15; ++i) 
    {
        sprintf(str, "grossini_dance_%02d.png",i);
        CCSpriteFrame * frame = pSpriteCache->spriteFrameByName(str);
        pSpriteFrames->addObject(frame);
    }

	CCSprite * pSprite = CCSprite::createWithSpriteFrameName("grossini_dance_01.png");
    pSprite->setPosition(ccp(m_visibleSize.width/2 + m_origin.x, m_visibleSize.height/2 + m_origin.y - 50));
	pSprite->setScale(2.f);

	CCAnimation * pSpriteAnimation = CCAnimation::createWithSpriteFrames(pSpriteFrames, 0.3f);
    pSprite->runAction(CCRepeatForever::create( CCAnimate::create(pSpriteAnimation) ) );
	
    this->addChild(pSprite, 2);

	

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(Test1Layer2::menuCloseCallback1));
    
	pCloseItem->setPosition(pBackground->getPosition());

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);


	//this->schedule(schedule_selector(Test1Layer::update));
    
    return true;
}


void Test1Layer2::menuCloseCallback1(CCObject* pSender)
{
	CCActionInterval * pScaleAction = CCScaleTo::create( 1.f, 0.f, 0.f );
	CCAction * pCloseAction = CCCallFunc::create(this,callfunc_selector(Test1Layer2::menuCloseCallback2));
	CCActionInterval * pFadeActionSequence = CCSequence::create(pScaleAction, pCloseAction, NULL);
	this->runAction(pFadeActionSequence);
}


void Test1Layer2::menuCloseCallback2()
{
	CCDirector::sharedDirector()->getRunningScene()->removeChild(this);
}
