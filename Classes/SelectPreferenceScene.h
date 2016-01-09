#ifndef __SELECTPREFERENCE_SCENE_H__
#define __SELECTPREFERENCE_SCENE_H__

//#include "Common.h"
#include "cocos2d.h"

class SelectPreferenceScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void menuCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(SelectPreferenceScene);

    //virtual void editBoxEditingDidBegin(EditBox* editBox);
    //virtual void editBoxEditingDidEnd(EditBox* editBox);
    //virtual void editBoxTextChanged(EditBox* editBox, const std::string& text);
    //virtual void editBoxReturn(EditBox* editBox);

private:
    //void PrepareResources();// 본 페이지에서 사용할 리소스 로드
    //void StartLayout();     // 전체 레이아웃 구성
    //void PrepareEditBox();  // 이름, 생년월일, 비밀번호 입력 텍스트박스 생성

    //EditBox* _Name;        // 이름을 입력할 텍스트박스
    //EditBox* Birth;       // 생년월일을 입력할 텍스트박스
    //EditBox* Pwd;         // 비밀번호를 입력할 텍스트박스
};

#endif