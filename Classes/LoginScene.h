#ifndef __LOGIN_SCENE_H__
#define __LOGIN_SCENE_H__

#include "cocos2d.h"

class InputBox;
class LoginScene : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void menuCallback(cocos2d::Ref* pSender);
    void menuCallback2(cocos2d::Ref* pSender);

    std::wstring FromUtf8(const std::string& utf8string);
    std::string ToUtf8(const std::wstring& widestring);

    CREATE_FUNC(LoginScene);

private:
    InputBox* _LoginBox;
};

#endif
