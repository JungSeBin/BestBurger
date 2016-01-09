#pragma once
#ifndef __INGREDIENT_LAYER_H__
#define __INGREDIENT_LAYER_H__

#include "cocos2d.h"
#include <vector>

class IngredientLayer : public cocos2d::LayerColor
{
public:
    virtual bool init();

    CREATE_FUNC(IngredientLayer);

    void menuCallback(cocos2d::Object* sender);

    void PrintIngredients();

private:
    std::vector<int> _selectedIDVec;
};
#endif