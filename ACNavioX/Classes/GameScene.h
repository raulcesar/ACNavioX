//
//  GameScene.h
//  ACNavioX
//
//  Created by Raul Cesar Teixeira on 3/9/15.
//
//

#ifndef __ACNavioX__GameScene__
#define __ACNavioX__GameScene__

#define PTM_RATIO 32.0

#include "cocos2d.h"
#include "Box2D/Box2D.h"


class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

private:
	void initBox2dWorld();
    void tick(float dt);
	b2World *_world;
    b2Body * _body;
    cocos2d::Sprite * _ball;
};


#endif  // __ACNavioX__GameScene__
