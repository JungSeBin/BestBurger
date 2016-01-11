#pragma once
#ifndef __TASTE_LAYER_H__
#define __TASTE_LAYER_H__

#include "cocos2d.h"
class TasteLayer : public cocos2d::LayerColor
{
public:
    virtual bool init();

    CREATE_FUNC(TasteLayer);

    void PrintTastes();
    void menuCallback(cocos2d::Object* sender);
    void InsertDataToDB();

private:
    std::vector<int> _SelectedIDVec;
};
#endif