#include "SauceLayer.h"
#include "DBManager.h"

USING_NS_CC;

static const int unSelected = 0;
static const int selected = 1;

bool SauceLayer::init()
{
    if (!LayerColor::initWithColor(Color4B::WHITE))
    {
        return false;
    }

    auto label = Label::createWithSystemFont("싫어하는 소스를 선택해주십시오.", "NanumGothic.ttf", 50);
    label->setAnchorPoint(Vec2::ZERO);
    label->setHorizontalAlignment(TextHAlignment::CENTER);
    label->setPosition(Vec2(0.0f, 580.0f));
    this->addChild(label, 0, "TableLabel");

    PrintSauces();

    return true;
}

void SauceLayer::PrintSauces()
{
    auto IngredientMap = DBManager::getInstance().GetTableMap(TABLE_SAUCE);
    auto x = 300.0f;
    auto y = 490.0f;
    std::wstring wstr;
    std::string str;

    int id = 1;

    for (auto& sauceName : IngredientMap)
    {
        wstr = std::wstring(sauceName.second);
        str = std::string(wstr.begin(), wstr.end());

        auto label = Label::createWithSystemFont(str, "fonts/MarkerFelt.ttf", 20);
        label->setAnchorPoint(Vec2(0.0f, 0.5f));
        label->setHorizontalAlignment(TextHAlignment::CENTER);
        label->setPosition(Vec2(x, y));
        label->setColor(Color3B::BLACK);
        this->addChild(label, 0);

        auto selectItem1 = MenuItemImage::create(
            "frame_unselected.png",
            "frame_unselected.png");

        auto selectItem2 = MenuItemImage::create(
            "frame_selected.png",
            "frame_selected.png");

        auto toggle = MenuItemToggle::createWithCallback(
            CC_CALLBACK_1(SauceLayer::menuCallback, this),
            selectItem1, selectItem2, NULL);
        toggle->setPosition(Vec2(x - 40.0f, y));
        toggle->setAnchorPoint(Vec2(0.5f, 0.5f));
        toggle->setTag(id++);

        auto menu = Menu::create(toggle, NULL);
        menu->setPosition(Vec2::ZERO);
        this->addChild(menu, 1);

        //set label coordinate(x,y)
        if (x == 300.0f)
        {
            x += 300.0f;
        }
        else
        {
            x = 300.0f;
            y -= 70.0f;
        }
    }
}

void SauceLayer::menuCallback(cocos2d::Object* sender)
{
    auto item = (MenuItemToggle*)sender;
    auto id = item->getTag();
    auto index = item->getSelectedIndex();

    if (index == selected)
    {
        _SelectedIDVec.push_back(item->getTag());
    }
    else if (index == unSelected)
    {
        auto selectedID = std::find(_SelectedIDVec.begin(), _SelectedIDVec.end(), id);
        if (selectedID != _SelectedIDVec.end())
        {
            _SelectedIDVec.erase(selectedID);
        }
    }
}
