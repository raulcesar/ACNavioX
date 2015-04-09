//
//  GameScene.cpp
//  ACNavioX
//
//  Created by Raul Cesar Teixeira on 3/9/15.
//
//
#define COCOS2D_DEBUG 1

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


void GameScene::initBox2dWorld() {
    b2Vec2 gravity;
    gravity.Set(0.0f, -9.0f);//No gravity
    bool doSleep = true;
    _world = new b2World(gravity);

    //For now, we will just create a world and a ball to see it work.
    // Create ball body and shape
    b2BodyDef ballBodyDef;
    ballBodyDef.type = b2_dynamicBody;
    ballBodyDef.position.Set(100 / PTM_RATIO, 300 / PTM_RATIO);
    ballBodyDef.userData = _ball;
    _body = _world->CreateBody(&ballBodyDef);

    b2CircleShape circle;
    circle.m_radius = 26.0 / PTM_RATIO;

    b2FixtureDef ballShapeDef;
    ballShapeDef.shape = &circle;
    ballShapeDef.density = 1.0f;
    ballShapeDef.friction = 0.2f;
    ballShapeDef.restitution = 0.8f;
    _body->CreateFixture(&ballShapeDef);
    //Call tick method
    //TODO: Review fixed time tick method (from platformer)
    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::tick), 0, CC_REPEAT_FOREVER, 0);
    // this->schedule(schedule_selector(GameScene::tick));


}

void GameScene::tick(float dt) {
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    _world->Step(dt, velocityIterations, positionIterations);
    for (b2Body *b = _world->GetBodyList(); b; b = b->GetNext()) {
        b2Vec2 position = b->GetPosition();
        float32 angle = b->GetAngle();


        CCLOG("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
        // printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
        if (b->GetUserData() != NULL) {
            Sprite *ballSprite = (Sprite*) b->GetUserData();
            auto spritePosition = Point((position.x * PTM_RATIO), (position.y * PTM_RATIO));

            ballSprite->setPosition(spritePosition);
            ballSprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
            // ballSprite.setrot
            // ballData.rotation = -1 * CC_RADIANS_TO_DEGREES(b->GetAngle());
        }
    }

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
    auto skyLayer = LayerGradient::create(Color4B(92, 104, 238, 255), Color4B(92, 104, 238, 10));
    skyLayer->setContentSize(visibleSize);
    skyLayer->setPosition(Vec2(0, 0));


    //Cria navio a partir do spritesheet.
    auto navioTemp = Sprite::createWithSpriteFrameName("navior2l0.png");
//    navioTemp->setScale(-1, 1);
    navioTemp->setPosition(Vec2(0, 0));
    navioTemp->setAnchorPoint(Vec2(0, 0));
    navioTemp->setFlippedX(true);


    this->addChild(skyLayer);
    this->addChild(navioTemp);


    //Cria nossa bola de teste physics
    _ball = Sprite::create("CloseNormal.png");
    _ball->setPosition(300, 300);
    this->addChild(_ball);
    



    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                         "CloseNormal.png",
                         "CloseSelected.png",
                         CC_CALLBACK_1(GameScene::menuCloseCallback, this));

    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2 ,
                                origin.y + closeItem->getContentSize().height / 2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...
    GameScene::initBox2dWorld();

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
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
