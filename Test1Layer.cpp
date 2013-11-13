#include "Test1Layer.h"
#include "Test1Layer2.h"
#include "MenuLayer.h"
#include "AppMacros.h"

USING_NS_CC;


const CCPoint Test1Layer::HAPPY_SPRITE_SPEED_PPSEC = CCPoint( 20.f, 10.f );


CCScene* Test1Layer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    Test1Layer *layer = Test1Layer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Test1Layer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    m_visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    m_origin = CCDirector::sharedDirector()->getVisibleOrigin();

	m_maxX = m_visibleSize.width  + m_origin.x;
	m_maxY = m_visibleSize.height + m_origin.y;

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(Test1Layer::menuCloseCallback));

	

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pOpenLayer2Item = CCMenuItemImage::create(
                                        "btn-play-normal.png",
                                        "btn-play-selected.png",
                                        this,
                                        menu_selector(Test1Layer::menuOpenLayer2Callback));
    
	pCloseItem->setPosition(ccp(m_origin.x + m_visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                m_origin.y + pCloseItem->getContentSize().height/2));
    
	pOpenLayer2Item->setScale(2.f);
	pOpenLayer2Item->setPosition(ccp(m_origin.x + m_visibleSize.width/2.f ,
                                     m_origin.y + m_visibleSize.height/2.f));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, pOpenLayer2Item, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Test 1", "Arial", TITLE_FONT_SIZE);
	pLabel->setColor(ccYELLOW);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(m_origin.x + m_visibleSize.width/2,
                            m_origin.y + m_visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "Test1Layer" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(m_visibleSize.width/2 + m_origin.x, m_visibleSize.height/2 + m_origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);


	
    /*mHappySprite = CCSprite::create("Pea.png");
	mHappySprite->setScale(10.f);
    mHappySprite->setPosition(ccp(m_visibleSize.width/2 + m_origin.x, m_visibleSize.height/2 + m_origin.y));
    this->addChild(mHappySprite, 1);


    CCActionInterval * happySpriteScaleAction1 = CCScaleTo::create( 2.f, 20.f , 20.f  );
    CCActionInterval * happySpriteScaleAction2 = CCScaleTo::create( 2.f, 5.f, 5.f );
	CCActionInterval * happySpriteScaleActionsSequence = CCSequence::create(happySpriteScaleAction1, happySpriteScaleAction2, NULL);
	CCActionInterval * happySpriteScaleActionsSequenceRepeat = CCRepeatForever::create(happySpriteScaleActionsSequence);
    mHappySprite->runAction(happySpriteScaleActionsSequenceRepeat);*/


	this->schedule(schedule_selector(Test1Layer::update));
    
    return true;
}

void Test1Layer::update(float deltaTime)
{
	/*CCPoint happySpritePos = mHappySprite->getPosition();

	happySpritePos.x += HAPPY_SPRITE_SPEED_PPSEC.x * deltaTime;
	happySpritePos.y += HAPPY_SPRITE_SPEED_PPSEC.y * deltaTime;

	happySpritePos.x = happySpritePos.x > m_maxX ? happySpritePos.x - m_maxX : happySpritePos.x ;
	happySpritePos.y = happySpritePos.y > m_maxY ? happySpritePos.y - m_maxY : happySpritePos.y ;

	mHappySprite->setPosition(happySpritePos);*/
}


void Test1Layer::menuCloseCallback(CCObject* pSender)
{
	CCScene * pScene = MenuLayer::scene();
	
    CCScene* pTransScene = CCTransitionSlideInT::create(1.f, pScene);

    CCDirector::sharedDirector()->replaceScene(pTransScene);
}
    
void Test1Layer::menuOpenLayer2Callback(CCObject* pSender)
{
	Test1Layer2 * pLayer2 = Test1Layer2::create();
	pLayer2->setScale(0);
	CCDirector::sharedDirector()->getRunningScene()->addChild(pLayer2,1);

	CCActionInterval * pScaleAction = CCScaleTo::create( 1.f, 1.f, 1.f );
	pLayer2->runAction(pScaleAction);
}
