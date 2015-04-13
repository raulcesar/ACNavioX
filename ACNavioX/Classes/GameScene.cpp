//
//  GameScene.cpp
//  ACNavioX
//
//  Created by Raul Cesar Teixeira on 3/9/15.
//
//
#define COCOS2D_DEBUG 1

#include "GameScene.h"
#include "rubestuff/b2dJson.h"
#include "Box2DDebugDraw.h"
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
    gravity.Set(0.0f, 0.0f);//No gravity
//    bool doSleep = true;
    // _world = new b2World(gravity);

    
    //Seting the anchor point... this will be a diferent layer later...
    setAnchorPoint( Vec2(0,0) );
    
    // set the starting scale and offset values from the subclass
    setPosition( initialWorldOffset() );
    setScale( initialWorldScale() );
    
    // load the world from RUBE .json file (this will also call afterLoadProcessing)
    

    std::string filename = "Navio.json";


    CCLOG("filname: %s", filename.c_str());

    // Find out the absolute path for the file
    std::string fullpath = CCFileUtils::getInstance()->fullPathForFilename(filename.c_str());

    // This will print out the actual location on disk that the file is read from.
    // When using the simulator, exporting your RUBE scene to this folder means
    // you can edit the scene and reload it without needing to restart the app.
    CCLOG("Full path is: %s", fullpath.c_str());

    // Create the world from the contents of the RUBE .json file. If something
    // goes wrong, m_world will remain NULL and errMsg will contain some info
    // about what happened.
    b2dJson json;
    std::string errMsg;
    std::string jsonContent = CCFileUtils::getInstance()->getStringFromFile(fullpath.c_str());
    _world = json.readFromString(jsonContent, errMsg);
    _world->SetGravity(gravity);

    if ( _world ) {
        CCLOG("Loaded JSON ok");

        // Set up a debug draw so we can see what's going on in the physics engine.
        // The scale for rendering will be handled by the layer scale, which will affect
        // the entire layer, so we keep the PTM ratio here to 1 (ie. one physics unit
        // will be one pixel)
        //TODO: This is all fucked up. We need to destory.
        _drawNode = DrawNode::create();


        this->addChild(_drawNode);



        Box2DDebugDraw* m_debugDraw;            // used to draw debug data
        m_debugDraw = new Box2DDebugDraw(_drawNode, 1);

        // set the debug draw to show fixtures, and let the world know about it
        m_debugDraw->SetFlags( b2Draw::e_shapeBit | b2Draw::e_jointBit );
        _world->SetDebugDraw(m_debugDraw);

        // This body is needed if we want to use a mouse joint to drag things around.
        // b2BodyDef bd;
        // m_mouseJointGroundBody = _world->CreateBody( &bd );

        // afterLoadProcessing(&json);
    }
    else {
        CCLOG("%s", errMsg.c_str());
    }
    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::tick), 0, CC_REPEAT_FOREVER, 0);
}



// void GameScene::initBox2dWorldOLD() {
// // m_debugDraw = new GLESDebugDraw( PTM_RATIO );
// // world->SetDebugDraw(m_debugDraw);

// // world->SetAllowSleeping(false);

// // uint32 flags = 0;
// // flags += b2Draw::e_shapeBit;
// // //        flags += b2Draw::e_jointBit;
// // //        flags += b2Draw::e_aabbBit;
// // //        flags += b2Draw::e_pairBit;
// // //        flags += b2Draw::e_centerOfMassBit;
// // m_debugDraw->SetFlags(flags);
//     _drawNode = DrawNode::create();


//     this->addChild(_drawNode);


//     b2Vec2 gravity;
//     gravity.Set(0.0f, -9.0f);//No gravity
//     bool doSleep = true;
//     _world = new b2World(gravity);

//     //For now, we will just create a world and a ball to see it work.
//     // Create ball body and shape
//     b2BodyDef ballBodyDef;
//     ballBodyDef.type = b2_dynamicBody;
//     ballBodyDef.position.Set(100 / PTM_RATIO, 300 / PTM_RATIO);
//     ballBodyDef.userData = _ball;
//     _body = _world->CreateBody(&ballBodyDef);

//     b2CircleShape circle;
//     circle.m_radius = 26.0 / PTM_RATIO;

//     b2FixtureDef ballShapeDef;
//     ballShapeDef.shape = &circle;
//     ballShapeDef.density = 1.0f;
//     ballShapeDef.friction = 0.2f;
//     ballShapeDef.restitution = 0.8f;
//     _body->CreateFixture(&ballShapeDef);
//Call tick method
//TODO: Review fixed time tick method (from platformer)
// this->schedule(CC_SCHEDULE_SELECTOR(GameScene::tick), 0, CC_REPEAT_FOREVER, 0);
// this->schedule(schedule_selector(GameScene::tick));
// }

void GameScene::debugDrawPhysics(b2World *_world) {
    const Color4F fillColor(1.0f, 0.0f, 0.0f, 0.3f);
    const Color4F outlineColor(1.0f, 0.0f, 0.0f, 1.0f);

    _drawNode->clear();
    for (b2Body *b = _world->GetBodyList(); b; b = b->GetNext()) {
        //Por hora, vamos assumir que so temos circulos....
        for (b2Fixture *f = b->GetFixtureList(); f; f = f->GetNext()) {
            b2Shape *s = f->GetShape();


            b2CircleShape *circle = (b2CircleShape*) s;

            float radiuspx = circle->m_radius * PTM_RATIO;

            b2Vec2 position = b->GetPosition();
            auto spritePosition = Point((position.x * PTM_RATIO), (position.y * PTM_RATIO));


            static const int CIRCLE_SEG_NUM = 12;
            Vec2 seg[CIRCLE_SEG_NUM] = {};
            Vec2 center((position.x * PTM_RATIO), (position.y * PTM_RATIO));
            CCLOG("Radius: %4.2f Center: %4.2f, %4.2f \n", radiuspx, center.x, center.y);

            for (int i = 0; i < CIRCLE_SEG_NUM; ++i)
            {
                float angle = (float)i * M_PI / (float)CIRCLE_SEG_NUM * 2.0f;
                Vec2 d(radiuspx * cosf(angle), radiuspx * sinf(angle));
                seg[i] = center + d;
            }

            _drawNode->drawPolygon(seg, CIRCLE_SEG_NUM, fillColor, 1, outlineColor);


        }


        //get radius
        //get center
        // CCLOG("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);



    }

}
// Override this in subclasses to set the inital view position
Point GameScene::initialWorldOffset()
{
    // This function should return the location in pixels to place
    // the (0,0) point of the physics world. The screen position
    // will be relative to the bottom left corner of the screen.
    
    //place (0,0) of physics world at center of bottom edge of screen
    Size s = Director::getInstance()->getWinSize();
    return Vec2( s.width/2, 100 );
}


// Override this in subclasses to set the inital view scale
float GameScene::initialWorldScale()
{
    // This method should return the number of pixels for one physics unit.
    // When creating the scene in RUBE I can see that the jointTypes scene
    // is about 8 units high, so I want the height of the view to be about
    // 10 units, which for iPhone in landscape (480x320) we would return 32.
    // But for an iPad in landscape (1024x768) we would return 76.8, so to
    // handle the general case, we can make the return value depend on the
    // current screen height.
    
    Size s = Director::getInstance()->getWinSize();
    return s.height / 50; //screen will be 10 physics units high
}

void GameScene::tick(float dt) {
    int32 velocityIterations = 6;
    int32 positionIterations = 2;


    //TODO: Fix the steping.


    _world->Step(dt, velocityIterations, positionIterations);
//    this->debugDrawPhysics(_world);

    // for (b2Body *b = _world->GetBodyList(); b; b = b->GetNext()) {



    //     b2Vec2 position = b->GetPosition();
    //     float32 angle = b->GetAngle();


    //     CCLOG("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
    //     // printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
    //     if (b->GetUserData() != NULL) {
    //         Sprite *ballSprite = (Sprite*) b->GetUserData();
    //         auto spritePosition = Point((position.x * PTM_RATIO), (position.y * PTM_RATIO));

    //         ballSprite->setPosition(spritePosition);
    //         ballSprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
    //         // ballSprite.setrot
    //         // ballData.rotation = -1 * CC_RADIANS_TO_DEGREES(b->GetAngle());
    //     }
    // }

    // debugDraw();
}

void GameScene::draw(Renderer *renderer, const Mat4 &transform, uint32_t transformUpdated)
{
    if ( !_world )
        return;
    
    // debug draw display will be on top of anything else
    Layer::draw(renderer, transform, transformUpdated);
    CCLOG("Should be drawing shit at this satege!!!");

    _drawNode->clear();
    _world->DrawDebugData();
    
    // Draw mouse joint line
//    if ( m_mouseJoint ) {
//        b2Vec2 p1 = m_mouseJoint->GetAnchorB();
//        b2Vec2 p2 = m_mouseJoint->GetTarget();
//        
//        b2Color c;
//        c.Set(0.0f, 1.0f, 0.0f);
//        m_debugDraw->DrawPoint(p1, 4.0f, c);
//        m_debugDraw->DrawPoint(p2, 4.0f, c);
//        
//        c.Set(0.8f, 0.8f, 0.8f);
//        m_debugDraw->DrawSegment(p1, p2, c);
//    }
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
//    auto navioTemp = Sprite::createWithSpriteFrameName("navior2l0.png");
////    navioTemp->setScale(-1, 1);
//    navioTemp->setPosition(Vec2(0, 0));
//    navioTemp->setAnchorPoint(Vec2(0, 0));
//    navioTemp->setFlippedX(true);
//
//
//    
//    
//    this->addChild(skyLayer);
//    this->addChild(navioTemp);
//
//
//    //Cria nossa bola de teste physics
//    _ball = Sprite::create("CloseNormal.png");
//    _ball->setPosition(300, 300);
//    this->addChild(_ball);




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
    
    
    
    this->initBox2dWorld();

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
