#pragma once
#ifndef __INGREDIENT_LAYER_H__
#define __INGREDIENT_LAYER_H__

//#include "Common.h"
#include "cocos2d.h"
class IngredientLayer : public cocos2d::LayerColor
{
public:
    virtual bool init();

    CREATE_FUNC(IngredientLayer);

    void PrintIngredients();
};
#endif