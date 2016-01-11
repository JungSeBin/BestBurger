#include "SelectBurgerScene.h"
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

    PrintSelectedBurger();

    return true;
}

void SelectBurgerScene::PrintSelectedBurger()
{
    auto SelectedBurgerMap = DBManager::getInstance().GetTableMap(TABLE_SELECTEDBURGER);
    auto x = 300.0f;
    auto y = 490.0f;
    std::wstring wstr;
    std::string str;

    for (auto& burger : SelectedBurgerMap)
    {
        wstr = std::wstring(burger.second);
        str = std::string(wstr.begin(), wstr.end());

        auto label = Label::createWithSystemFont(str, "fonts/MarkerFelt.ttf", 20);
        label->setAnchorPoint(Vec2(0.0f, 0.5f));
        label->setHorizontalAlignment(TextHAlignment::CENTER);
        label->setPosition(Vec2(x, y));
        label->setColor(Color3B::BLACK);
        this->addChild(label, 0);

        //set label coordinate(x,y)
        if (x == 300.0f)
        {
            x += 300.0f;
        }
        else
        {
            x = 300.0f;
            y -= 30.0f;
        }
    }
}
