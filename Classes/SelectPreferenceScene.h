#ifndef __SELECTPREFERENCE_SCENE_H__
#define __SELECTPREFERENCE_SCENE_H__

#include "cocos2d.h"

class SelectPreferenceScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void menuCallback(cocos2d::Object* pSender);

    CREATE_FUNC(SelectPreferenceScene);
};

#endif