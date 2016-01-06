#ifndef __SELECTPREFERENCE_SCENE_H__
#define __SELECTPREFERENCE_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;

class SelectPreference : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void menuCloseCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(SelectPreference);

    virtual void editBoxEditingDidBegin(EditBox* editBox);
    virtual void editBoxEditingDidEnd(EditBox* editBox);
    virtual void editBoxTextChanged(EditBox* editBox, const std::string& text);
    virtual void editBoxReturn(EditBox* editBox);

private:
    void PrepareResources();// �� ���������� ����� ���ҽ� �ε�
    void StartLayout();     // ��ü ���̾ƿ� ����
    void PrepareEditBox();  // �̸�, �������, ��й�ȣ �Է� �ؽ�Ʈ�ڽ� ����

    SpriteBatchNode* batchNode;

    EditBox* _Name;        // �̸��� �Է��� �ؽ�Ʈ�ڽ�
    EditBox* Birth;       // ��������� �Է��� �ؽ�Ʈ�ڽ�
    EditBox* Pwd;         // ��й�ȣ�� �Է��� �ؽ�Ʈ�ڽ�
};

#endif