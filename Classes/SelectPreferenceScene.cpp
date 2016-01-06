#include "SelectPreferenceScene.h"

USING_NS_CC;

Scene* SelectPreference::createScene()
{
    auto scene = Scene::create();

    auto layer = SelectPreference::create();

    scene->addChild(layer);

    return scene;
}

bool SelectPreference::init()
{
    if (!Layer::init())
    {
        return false;
    }
    char textBox[20];
    WideCharToMultiByte(CP_UTF8, 0, L"이름을 입력하세요", -1, textBox, 20, NULL, NULL);
    auto label = Label::createWithTTF(textBox, "NanumGothic.ttf", 24);

    this->addChild(label);

    return true;
}

void SelectPreference::editBoxEditingDidBegin(EditBox* editBox)
{

}

void SelectPreference::editBoxEditingDidEnd(EditBox* editBox)
{

}

void SelectPreference::editBoxTextChanged(EditBox* editBox, const std::string& text)
{

}

void SelectPreference::editBoxReturn(EditBox* editBox)
{

}

void SelectPreference::PrepareResources()
{
    _Name = EditBox::create(CCSizeMake(300, 50), Scale9Sprite::create("editBox_bg_normal.png"));
    _Name->setPosition(Vec2(500.0f,500.0f));
    _Name->setFontColor(ccRED);
    _Name->setPlaceHolder("Name");
    _Name->setPlaceholderFontColor(Color3B::WHITE);
    _Name->setReturnType(EditBox::KeyboardReturnType::DEFAULT);
    _Name->setInputMode(EditBox::InputMode::ANY);
    _Name->setTag(1);
    _Name->setDelegate(EditBox::setDelegate(_Name));
    this->addChild(_Name);
}
