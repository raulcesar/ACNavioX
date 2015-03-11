//
//  Navio.h
//  ACNavioX
//
//  Created by Raul Cesar Teixeira on 3/9/15.
//
//

#ifndef __ACNavioX__Navio__
#define __ACNavioX__Navio__

#include "cocos2d.h"
using namespace cocos2d;

class Navio : public Sprite{
public:
    Navio();
    ~Navio();
    
    static Navio* create();
    void initOptions();
    void addEvents();
    
    
    
};

#endif /* defined(__ACNavioX__Navio__) */
