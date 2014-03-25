#include "HelloWorldScene.h"

#include "test/engine/TestKeyUpDown.h"
#include "keypad_dispatcher/CCKeypadDispatcher.h"

#include "aircraft/heroAircraft.h"
#include "input/InputManager.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    // CCLayerColor* layer = CCLayerColor::create();
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);

    test();
    
    return true;
}

void HelloWorld::test()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    // CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();


    // CCSprite* testSprite = CCSprite::create("png/hero.png");
    // testSprite->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
    // addChild(testSprite);

    // ----------------------
    // test key up down event
    // ----------------------
    //TestKeyUpDown* keyHandler = new TestKeyUpDown();
    //CCDirector::sharedDirector()->getKeypadDispatcher()->addDelegate(keyHandler);


    // init input manager
    InputManager* input = InputManager::sharedInstance();
    CCDirector::sharedDirector()->getKeypadDispatcher()->addDelegate(input);

    // hero
    HeroAircraft* hero = HeroAircraft::create();
    addChild(hero->graphics);
    hero->graphics->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
	CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(hero, 0, false);
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
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
