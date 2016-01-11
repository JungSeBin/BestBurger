#ifndef __SELECTPREFERENCE_SCENE_H__
#define __SELECTPREFERENCE_SCENE_H__

#include "cocos2d.h"

class InputBox;
class SelectPreferenceScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void menuCallback(cocos2d::Object* pSender);
    void menuCallback2(cocos2d::Ref* sender);
    void menuCallback3(cocos2d::Ref* sender);
    void menuCallback4(cocos2d::Ref* sender);
    void menuCallback5(cocos2d::Ref* sender);

    void UpdateUserPreference();
    bool IsNumber(std::string num);


    CREATE_FUNC(SelectPreferenceScene);

private:
    InputBox* _PriceBox;
    InputBox* _KcalBox;
};

#endif