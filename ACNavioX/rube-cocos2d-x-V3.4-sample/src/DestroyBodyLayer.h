//  Author: Chris Campbell - www.iforce2d.net
//  -----------------------------------------
//
//  DestroyBodyLayer
//
//  Just to demonstrate removing bodies from the world. The only thing
//  different to the superclass is the TouchesBegan method.
//

#ifndef DESTROY_BODY_LAYER
#define DESTROY_BODY_LAYER

#include "RUBELayer.h"

class DestroyBodyLayer : public RUBELayer
{
public:    
    static cocos2d::Scene* scene();    
    CREATE_FUNC(DestroyBodyLayer);

    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
};

#endif /* DESTROY_BODY_LAYER */
