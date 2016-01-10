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
    loginMenu2->setPosition(Vec2(415, 35));
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

    if (name[0] == '\0' || name[0] == ' ')
    {
        _LoginBox->clear();
        _LoginBox->beginInput();
        return;
    }

    DBManager::getInstance().InsertUserNameToDB(wName);

    DBManager::getInstance().GetDataFromDB();
    Director::getInstance()->replaceScene(SelectPreferenceScene::createScene());
}
std::wstring LoginScene::FromUtf8(const std::string& utf8string)
{
    size_t widesize = utf8string.length();
    if (sizeof(wchar_t) == 2)
    {
        std::wstring resultstring;
        resultstring.resize(widesize + 1, L'\0');
        const UTF16* sourcestart = reinterpret_cast<const UTF16*>(utf8string.c_str());
        const UTF16* sourceend = sourcestart + widesize;
        UTF32* targetstart = reinterpret_cast<UTF32*>(&resultstring[0]);
        UTF32* targetend = targetstart + widesize;
        ConversionResult res = ConvertUTF16toUTF32
            (&sourcestart, sourceend, &targetstart, targetend, strictConversion);
        if (res != conversionOK)
        {
            throw std::exception("La falla!");
        }
        *targetstart = 0;
        return resultstring;
    }
    else if (sizeof(wchar_t) == 4)
    {
        std::wstring resultstring;
        resultstring.resize(widesize + 1, L'\0');
        const UTF8* sourcestart = reinterpret_cast<const UTF8*>(utf8string.c_str());
        const UTF8* sourceend = sourcestart + widesize;
        UTF32* targetstart = reinterpret_cast<UTF32*>(&resultstring[0]);
        UTF32* targetend = targetstart + widesize;
        ConversionResult res = ConvertUTF8toUTF32
            (&sourcestart, sourceend, &targetstart, targetend, strictConversion);
        if (res != conversionOK)
        {
            throw std::exception("La falla!");
        }
        *targetstart = 0;
        return resultstring;
    }
    else
    {
        throw std::exception("La falla!");
    }
    return L"";
}
std::string LoginScene::ToUtf8(const std::wstring& widestring)
{
    size_t widesize = widestring.length();

    if (sizeof(wchar_t) == 2)
    {
        size_t utf8size = 3 * widesize + 1;
        std::string resultstring;
        resultstring.resize(utf8size, '\0');
        const UTF16* sourcestart =
            reinterpret_cast<const UTF16*>(widestring.c_str());
        const UTF16* sourceend = sourcestart + widesize;
        UTF8* targetstart = reinterpret_cast<UTF8*>(&resultstring[0]);
        UTF8* targetend = targetstart + utf8size;
        ConversionResult res = ConvertUTF16toUTF8
            (&sourcestart, sourceend, &targetstart, targetend, strictConversion);
        if (res != conversionOK)
        {
            throw std::exception("La falla!");
        }
        *targetstart = 0;
        return resultstring;
    }
    else if (sizeof(wchar_t) == 4)
    {
        size_t utf8size = 4 * widesize + 1;
        std::string resultstring;
        resultstring.resize(utf8size, '\0');
        const UTF32* sourcestart =
            reinterpret_cast<const UTF32*>(widestring.c_str());
        const UTF32* sourceend = sourcestart + widesize;
        UTF8* targetstart = reinterpret_cast<UTF8*>(&resultstring[0]);
        UTF8* targetend = targetstart + utf8size;
        ConversionResult res = ConvertUTF32toUTF8
            (&sourcestart, sourceend, &targetstart, targetend, strictConversion);
        if (res != conversionOK)
        {
            throw std::exception("La falla!");
        }
        *targetstart = 0;
        return resultstring;
    }
    else
    {
        throw std::exception("La falla!");
    }
    return "";
}