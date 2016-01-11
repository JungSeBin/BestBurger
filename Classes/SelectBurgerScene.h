#ifndef __SELECTBURGER_SCENE_H__
#define __SELECTBURGER_SCENE_H__

#include "cocos2d.h"

class InputBox;
class SelectBurgerScene : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void PrintSelectedBurger();

    CREATE_FUNC(SelectBurgerScene);
};

#endif