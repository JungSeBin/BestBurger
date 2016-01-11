#include "LoginScene.h"
#include "SelectPreferenceScene.h"
#include "InputBox.h"
#include "DBManager.h"
#include <string>
#include "ConvertUTF.h"

#define MAX_NAME_LEN 15

USING_NS_CC;

Scene* LoginScene::createScene()
{
    auto scene = Scene::create();

    auto layer = LoginScene::create();

    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool LoginScene::init()
{
    if (!LayerColor::initWithColor(Color4B::WHITE))
    {
        return false;
    }
    auto winSize = Director::getInstance()->getWinSize();

    auto background = Sprite::create("background.png");
    background->setAnchorPoint(Vec2(0.5f, 0.5f));
    background->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    this->addChild(background);

    auto title = Sprite::create("title.png");
    title->setAnchorPoint(Vec2(0.5f, 0.5f));
    title->setPosition(Vec2(winSize.width / 2, 550.0f));
    this->addChild(title);

    auto loginBox = MenuItemImage::create(
        "loginField.png",
        "loginField.png",
        CC_CALLBACK_1(LoginScene::menuCallback, this));

    auto loginMenu1 = Menu::create(loginBox, NULL);
    loginMenu1->setAnchorPoint(Vec2(0.5f, 0.5f));
    loginMenu1->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    this->addChild(loginMenu1);                   

    auto loginButton = MenuItemImage::create(
        "startButton.png",
        "startButton_selected.png", 
        CC_CALLBACK_1(LoginScene::menuCallback2, this));

    auto loginMenu2 = Menu::create(loginButton, NULL);
    loginMenu2->setPosition(Vec2(150, -150));
    loginBox->addChild(loginMenu2);

    _LoginBox = InputBox::create("이름을 입력해주세요", "NanumGothic.ttf", MAX_NAME_LEN);
    _LoginBox->setAnchorPoint(Vec2(0.5f, 0.5f));
    _LoginBox->setPosition(Vec2(150.0f, 40.0f));
    _LoginBox->setColor(Color3B::BLACK);
    _LoginBox->setFontSize(30);
    loginBox->addChild(_LoginBox);

    return true;
}


void LoginScene::menuCallback(Ref* pSender)
{
    _LoginBox->clear();
    _LoginBox->beginInput();
}

void LoginScene::menuCallback2(cocos2d::Ref* pSender)
{
    std::string name = _LoginBox->getString();
    std::wstring wName = std::wstring(name.begin(), name.end());

    if (!IsEnglish(name))
    {    
        _LoginBox->clear();
        _LoginBox->beginInput();
        return;
    }

    DBManager::getInstance().InsertUserNameToDB(wName);

    DBManager::getInstance().GetDataFromDB();
    Director::getInstance()->replaceScene(SelectPreferenceScene::createScene());
}

bool LoginScene::IsEnglish(std::string name)
{
    if (name.size() <= 0)
    {
        return false;
    }
    for (auto& letter : name)
    {
        if (!(letter >= 'a' && letter <= 'z')
            && !(letter >= 'A' && letter <= 'Z'))
            return false;
    }
}