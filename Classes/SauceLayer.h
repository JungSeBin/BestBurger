#pragma once
#ifndef __SAUCE_LAYER_H__
#define __SAUCE_LAYER_H__

#include "cocos2d.h"
#include <vector>
class SauceLayer : public cocos2d::LayerColor
{
public:
    virtual bool init();

    CREATE_FUNC(SauceLayer);

    void PrintSauces();
    void menuCallback(cocos2d::Object* sender);
    void InsertDataToDB();
private:
    std::vector<int> _SelectedIDVec;
};
#endif