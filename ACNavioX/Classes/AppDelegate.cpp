#include "AppDelegate.h"
#include "GameScene.h"
#include "BasicRUBELayer.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {

    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if (!glview) {
        //Para linux...
#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("Toca Navio", Rect(0, 0, 1200, 900), 1);
#else
        glview = GLViewImpl::create("Toca Navio");
#endif
        director->setOpenGLView(glview);
    }


    director->setContentScaleFactor(2);

    auto fileUtils = CCFileUtils::getInstance();
    auto screenSize = glview->getFrameSize();

    std::vector<std::string> resDirOrders;

    //Check resolution
    if (screenSize.width > 2024) {
        //retina ipad
        resDirOrders.push_back("hd");
        resDirOrders.push_back("Resources");
        glview->setDesignResolutionSize(2048, 1536, ResolutionPolicy::NO_BORDER);
    }

    fileUtils->setSearchPaths(resDirOrders);









    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = GameScene::createScene();
    // auto scene = BasicRUBELayer::scene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
