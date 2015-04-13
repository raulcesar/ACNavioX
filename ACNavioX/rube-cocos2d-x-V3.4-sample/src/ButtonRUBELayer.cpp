//
//  ButtonRUBELayer.m
//  mtb
//
//  Created by chris on 10/04/13.
//
//

#include "ButtonRUBELayer.h"
#include "rubestuff/b2dJson.h"
#include "rubestuff/b2dJsonImage.h"
#include "SimpleAudioEngine.h"

using namespace std;
using namespace cocos2d;
using namespace CocosDenshion;

ButtonRUBELayer::ButtonRUBELayer()
{
    m_buttonTouch = NULL;
    m_touchedButton = NULL;
}

string ButtonRUBELayer::getFilename()
{
    return m_filename;
}

Point ButtonRUBELayer::initialWorldOffset()
{
    Size s = Director::getInstance()->getWinSize();
    float w = s.width;
    if ( w < s.height )
        w = s.height;
    return Vec2( w * 0.5, 0 );
}

float ButtonRUBELayer::initialWorldScale()
{
    Size s = Director::getInstance()->getWinSize();
    float h = s.height;
    if ( h > s.width )
        h = s.width;
    return h / 6.4; 
}

int getAllImagesOnBody( std::vector<b2dJsonImage*>& images, b2Body* b, std::vector<b2dJsonImage*>& result )
{
    for (int i = 0; i < images.size(); i++)
        if ( images[i]->body == b )
            result.push_back(images[i]);
    return result.size();
}

SEL_CallFunc ButtonRUBELayer::getSelectorByName(string name)
{
    map<string, SEL_CallFunc>::iterator it = m_selectorMap.find(name);
    if ( it == m_selectorMap.end() )
        return NULL;
    return it->second;
}

void ButtonRUBELayer::registerSelector(std::string name, cocos2d::SEL_CallFunc selector)
{
    m_selectorMap[name] = selector;
}

void ButtonRUBELayer::setupButtonActions(b2dJson* json)
{
    std::vector<b2dJsonImage*> allImages;
    json->getAllImages(allImages);

    for (b2Body* b = m_world->GetBodyList(); b; b = b->GetNext()) {
        for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext()) {
            
            _buttonInfo bi;
            bi.fixture = f;
            bi.selectorName = json->getCustomString(f, "selectorButton", "");
            bi.sceneName = json->getCustomString(f, "sceneButton", "");
            bi.selector = NULL;
            //bi.sceneClassType = NULL;
            bi.imageFile_normal = "";
            bi.imageFile_hover = "";
            bi.highlighted = false;
            bi.sprite = NULL;
            
            //look for all images on this body
            vector<b2dJsonImage*> imagesOnBody;
            if ( getAllImagesOnBody(allImages, b, imagesOnBody) > 0 ) {
                b2dJsonImage* baseImage = imagesOnBody[0];
                bi.sprite = getAnySpriteOnBody(b);
                if ( imagesOnBody.size() > 1 && f->GetType() == b2Shape::e_polygon ) {
                    b2PolygonShape* poly = (b2PolygonShape*)f->GetShape();
                    float bestDist = FLT_MAX;
                    for (int i = 0; i < imagesOnBody.size(); i++) {
                        float dist = (imagesOnBody[i]->center - poly->m_centroid).Length();
                        if ( dist < bestDist ) {
                            bestDist = dist;
                            baseImage = imagesOnBody[i];
                            bi.sprite = getSpriteWithImageName(imagesOnBody[i]->name);
                        }
                    }
                }
                string baseImageName = baseImage->name;
                b2dJsonImage* hoverImage = json->getImageByName(baseImageName + "_hover");
                bi.imageFile_normal = baseImage->file;
                memcpy(bi.colorTint_normal, baseImage->colorTint, 4 * sizeof(int));
                if ( hoverImage ) {
                    bi.imageFile_hover = hoverImage->file;
                    memcpy(bi.colorTint_hover, hoverImage->colorTint, 4 * sizeof(int));
                }
            }
            
            if ( !bi.selectorName.empty() ) {
                bi.selector = getSelectorByName( bi.selectorName );
                if ( !bi.selector )
                    CCLOG("Failed to find selector for %s", bi.selectorName.c_str());
            }
            
            if ( bi.selector || !bi.imageFile_hover.empty() )
                m_buttons.push_back(bi);
        }
    }
}

void ButtonRUBELayer::afterLoadProcessing(b2dJson* json)
{
    RUBELayer::afterLoadProcessing(json);
    
    setupButtonActions(json);
    
    SimpleAudioEngine::getInstance()->preloadEffect("sounds/button.wav");
}

void ButtonRUBELayer::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, bool transformUpdated)
{
    //no debug draw
}

_buttonInfo* ButtonRUBELayer::getButtonInfo(b2Fixture* fixture)
{
    for (int i = 0; i < m_buttons.size(); i++) {
        _buttonInfo& bi = m_buttons[i];
        if (fixture == bi.fixture)
            return &bi;
    }
    return NULL;
}

void ButtonRUBELayer::setButtonHighlighted(_buttonInfo* bi, bool tf)
{
    if ( ! allowButtonPresses() )
        return;
    if ( !bi )
        return;
    
    bool needsTextureChange = bi->highlighted != tf;
    bi->highlighted = tf;

    if ( !needsTextureChange )
        return;
    if ( !bi->sprite )
        return;
    
    if ( tf && !bi->imageFile_hover.empty() ) {
        bi->sprite->setTexture( Sprite::create(bi->imageFile_hover.c_str())->getTexture() );
        bi->sprite->setColor( Color3B(bi->colorTint_hover[0], bi->colorTint_hover[1], bi->colorTint_hover[2]) );
        bi->sprite->setOpacity(bi->colorTint_hover[3]);
    }
    else if ( !tf && !bi->imageFile_normal.empty() ) {
        bi->sprite->setTexture( Sprite::create(bi->imageFile_normal.c_str())->getTexture() );
        bi->sprite->setColor( Color3B(bi->colorTint_normal[0], bi->colorTint_normal[1], bi->colorTint_normal[2]) );
        bi->sprite->setOpacity(bi->colorTint_normal[3]);
    }
}

void ButtonRUBELayer::doButtonTouch(Touch* touch)
{
    b2Fixture* f = getTouchedFixture(touch);
    _buttonInfo* bi = getButtonInfo(f);
    if ( bi && bi == m_touchedButton && allowButtonPresses() ) {
        //CCLOG("Detected touch on button fixture %08X", bi->fixture);
        if ( bi->selector ) {
            SimpleAudioEngine::getInstance()->playEffect("sounds/button.wav");
            (this->*(bi->selector))();
        }
    }
}

void ButtonRUBELayer::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event)
{
    RUBELayer::onTouchesBegan(touches, event);
    
    Touch *touch = touches[0];

    if ( ! m_touchedButton ) {
        m_buttonTouch = touch;
        b2Fixture* f = getTouchedFixture(touch);
        m_touchedButton = getButtonInfo(f);
        if ( m_touchedButton )
            setButtonHighlighted(m_touchedButton, true);
        
        if ( actOnTouchDown() )
            doButtonTouch(touch);
    }
}

void ButtonRUBELayer::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event)
{
    RUBELayer::onTouchesMoved(touches, event);
    
    Touch *touch = touches[0];
    
    if ( touch == m_buttonTouch ) {
        if ( m_touchedButton ) {
            b2Fixture* f = getTouchedFixture(touch);
            _buttonInfo* bi = getButtonInfo(f);
            
            setButtonHighlighted(m_touchedButton, (bi == m_touchedButton));
        }
    }
}

void ButtonRUBELayer::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event)
{
    RUBELayer::onTouchesEnded(touches, event);
    
    for (int i = 0; i < touches.size(); i++) {
        Touch* touch = touches[i];
        if ( touch == m_buttonTouch ) {
            if ( m_touchedButton )
                setButtonHighlighted(m_touchedButton, false);
            
            if ( ! actOnTouchDown() )
                doButtonTouch(touch);
            
            m_buttonTouch = NULL;
            m_touchedButton = NULL;
        }
    }
}

bool ButtonRUBELayer::allowPinchZoom()
{
    return false;
}

bool ButtonRUBELayer::allowButtonPresses()
{
    return true;
}

bool ButtonRUBELayer::actOnTouchDown()
{
    return false;
}














