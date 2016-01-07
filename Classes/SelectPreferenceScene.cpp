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

    return true;
}

//void SelectPreference::editBoxEditingDidBegin(EditBox* editBox)
//{
//
//}
//
//void SelectPreference::editBoxEditingDidEnd(EditBox* editBox)
//{
//
//}
//
//void SelectPreference::editBoxTextChanged(EditBox* editBox, const std::string& text)
//{
//
//}
//
//void SelectPreference::editBoxReturn(EditBox* editBox)
//{
//
//}
//
//void SelectPreference::PrepareResources()
//{
//    _Name = ui::EditBox::create(cocos2d::CCSizeMake(300, 50), "HelloWorld.png");
//    _Name->setPosition(Vec2(500.0f,500.0f));
//    _Name->setFontColor(ccRED);
//    _Name->setPlaceHolder("Name");
//    _Name->setPlaceholderFontColor(Color3B::WHITE);
//    _Name->setReturnType(EditBox::KeyboardReturnType::DEFAULT);
//    _Name->setInputMode(EditBox::InputMode::ANY);
//    _Name->setTag(1);
//    _Name->setDelegate(this);
//    this->addChild(_Name);
//}
