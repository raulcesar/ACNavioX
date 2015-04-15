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

typedef std::pair<b2Fixture*, b2Fixture*> fixturePair;

class b2dJson;

struct bodyUserData {
      std::string name;
      std::string material;

};

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, uint32_t transformUpdated);  // standard Cocos2d layer method
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    std::set<fixturePair> m_boyancyFixturePairs;
    virtual void afterLoadProcessing(b2dJson* json);            // override this in a subclass to do something else after loading the world (before discarding the JSON info)

    // virtual void BeginContact(b2Contact* contact);      // called by Box2D during the Step function when two fixtures begin touching
    // virtual void EndContact(b2Contact* contact);        // called by Box2D during the Step function when two fixtures finish touching

private:
	void initBox2dWorld();
    void initEventListeners();
    void debugDrawPhysics(b2World *_world);
    void tick(float dt);
	b2World *_world;
    b2Body * _body;
    b2Body * _wave;

    cocos2d::Sprite * _ball;
    cocos2d::DrawNode * _drawNode;
    virtual cocos2d::Vec2 initialWorldOffset();              // override this in subclasses to set the inital view position
    virtual float initialWorldScale();                          // override this in subclasses to set the initial view scale


};


class BoyancyContactListener : public b2ContactListener
{
public:
    virtual void BeginContact(b2Contact* contact);      // called by Box2D during the Step function when two fixtures begin touching
    virtual void EndContact(b2Contact* contact);        // called by Box2D during the Step function when two fixtures finish touching
    
    class GameScene* m_layer;
};


#endif  // __ACNavioX__GameScene__
