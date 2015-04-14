//
//  PhysicsDebugNode.h
//  ACNavioX
//
//  Created by Raul Cesar Teixeira on 14/04/2015
//
//

#ifndef __ACNavioX__PhysicsDebugNode__
#define __ACNavioX__PhysicsDebugNode__

#define PTM_RATIO 32.0

#include "cocos2d.h"
#include "Box2D/Box2D.h"


class PhysicsDebugNode : public cocos2d::Node
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    // static cocos2d::DrawNode* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, uint32_t transformUpdated);  // standard Cocos2d layer method
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

private:
	void initBox2dWorld();
    // void debugDrawPhysics(b2World *_world);
    void tick(float dt);
	b2World *_world;
    b2Body * _body;
    cocos2d::Sprite * _ball;
    cocos2d::DrawNode * _drawNode;
    virtual cocos2d::Point initialWorldOffset();              // override this in subclasses to set the inital view position
    virtual float initialWorldScale();                          // override this in subclasses to set the initial view scale

};


#endif  // __ACNavioX__GameScene__
