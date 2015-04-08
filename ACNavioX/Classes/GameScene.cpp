//
//  GameScene.cpp
//  ACNavioX
//
//  Created by Raul Cesar Teixeira on 3/9/15.
//
//

#include "GameScene.h"
USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto bgLayer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(bgLayer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    //Add navio.
    //Aqui na scena, vamos incluir:
    /*
       1 Background (vai ser refatorado num node
       2 Navio.
     
     */
    
    
    //Load spritesheet
    auto spritecache = SpriteFrameCache::getInstance();
    spritecache->addSpriteFramesWithFile("sprites.plist");
    
    
    //Cria background... sera um layer?
    auto skyLayer = LayerGradient::create(Color4B(92,104,238,255), Color4B(92,104,238,10));
    skyLayer->setContentSize(visibleSize);
    skyLayer->setPosition(Vec2(0,0));
    
    
    //Cria navio a partir do spritesheet.
    auto navioTemp = Sprite::createWithSpriteFrameName("navior2l0.png");
//    navioTemp->setScale(-1, 1);
    navioTemp->setPosition(Vec2(0, 0));
    navioTemp->setAnchorPoint(Vec2(0,0));
    navioTemp->setFlippedX(true);
    
    
    this->addChild(skyLayer);
    this->addChild(navioTemp);
    
    
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameScene::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
//    // add a label shows "Hello World"
//    // create and initialize a label
//    
//    auto label = Label::createWithTTF("Toca Navio do Augusto", "fonts/Marker Felt.ttf", 24);
//    
//    // position the label on the center of the screen
//    label->setPosition(Vec2(origin.x + visibleSize.width/2,
//                            origin.y + visibleSize.height - label->getContentSize().height));
//    
//    // add the label as a child to this layer
//    this->addChild(label, 1);
//    
//    // add "HelloWorld" splash screen"
//    auto sprite = Sprite::create("HelloWorld.png");
//    
//    // position the sprite on the center of the screen
//    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//    
//    // add the sprite as a child to this layer
//    this->addChild(sprite, 0);
    
    return true;
}


void GameScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
