#include "SelectBurgerScene.h"
#include "BurgerInfoLayer.h"
#include "DBManager.h"

USING_NS_CC;

Scene* SelectBurgerScene::createScene()
{
    auto scene = Scene::create();

    auto layer = SelectBurgerScene::create();

    scene->addChild(layer);

    return scene;
}

bool SelectBurgerScene::init()
{
    if (!LayerColor::initWithColor(Color4B::WHITE))
    {
        return false;
    }

    auto winSize = Director::getInstance()->getWinSize();

    auto background = Sprite::create("background.png");
    background->setAnchorPoint(Vec2(0.5f, 0.5f));
    background->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    background->setOpacity(50.0f);
    this->addChild(background, 0);

    PrintSelectedBurger();


    auto layer = BurgerInfoLayer::create();
    this->addChild(layer, 0, "burgerInfoLayer");

    auto label = Label::createWithSystemFont("추천 버거", "NanumGothic.ttf", 60);
    label->setPosition(Vec2(500.0f, 550.0f));
    label->setColor(Color3B::BLACK);
    this->addChild(label);

    auto label2 = Label::createWithSystemFont("버거를 선택해 주십시오.", "NanumGothic.ttf", 60);
    label2->setPosition(Vec2(500.0f, 80.0f));
    label2->setColor(Color3B::BLACK);
    this->addChild(label2);

    return true;
}

void SelectBurgerScene::PrintSelectedBurger()
{
    auto SelectedBurgerMap = DBManager::getInstance().GetTableMap(TABLE_SELECTEDBURGER);
    auto x = 350.0f;
    auto y = 450.0f;
    std::wstring wstr;
    std::string str;

    for (auto& burger : SelectedBurgerMap)
    {
        wstr = std::wstring(burger.second);
        str = std::string(wstr.begin(), wstr.end());

        auto label = Label::createWithSystemFont(str, "fonts/MarkerFelt.ttf", 20);
        label->setColor(Color3B::BLACK);
        auto item = MenuItemLabel::create(label, CC_CALLBACK_1(SelectBurgerScene::menuCallback, this));
        item->setTag(burger.first);
        auto menu = Menu::create(item, NULL);
        menu->setAnchorPoint(Vec2(0.0f, 0.5f));
        menu->setPosition(Vec2(x, y));
        this->addChild(menu, 1);

        //set label coordinate(x,y)
        if (x == 350.0f)
        {
            x += 300.0f;
        }
        else
        {
            x = 350.0f;
            y -= 50.0f;
        }
    }
}

void SelectBurgerScene::menuCallback(cocos2d::Object* sender)
{
    auto item = (MenuItemLabel*)sender;
    auto id = item->getTag();

    auto layer = (BurgerInfoLayer*)this->getChildByName("burgerInfoLayer");

    layer->setZOrder(100);
    layer->GetBurgerInfoFromDB(id);
    layer->PrintBurgerInfo();
}
