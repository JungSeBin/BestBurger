#pragma once
#ifndef __SAUCE_LAYER_H__
#define __SAUCE_LAYER_H__

#include "cocos2d.h"
class SauceLayer : public cocos2d::LayerColor
{
public:
    virtual bool init();

    CREATE_FUNC(SauceLayer);

    void PrintSauces();
};
#endif