//  Author: Chris Campbell - www.iforce2d.net
//  -----------------------------------------
//
//  only for this demo project, you can remove this in your own app
//

#ifndef EXAMPLES_MENU_LAYER
#define EXAMPLES_MENU_LAYER

#include "cocos2d.h"

class ExamplesMenuLayer : public cocos2d::Layer {
public:
    static cocos2d::Scene* scene();
    virtual bool init();
    CREATE_FUNC(ExamplesMenuLayer);
    
    void loadBasic();
    void loadImages();
    void loadDestroy();
    void loadPinball();
    void loadPlanetCute();
    void loadSimpleMenu();
    void loadUIControls();
};

#endif /* EXAMPLES_MENU_LAYER */
