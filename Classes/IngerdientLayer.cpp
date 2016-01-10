#include "IngerdientLayer.h"
#include "DBManager.h"
#include <stdio.h>
#include <string>

static const int unSelected = 0;
static const int selected = 1;

USING_NS_CC;

bool IngredientLayer::init()
{
    if (!LayerColor::initWithColor(Color4B::WHITE))
    {
        return false;
    }

    auto label = Label::createWithSystemFont("싫어하는 재료를 선택해주십시오.", "NanumGothic.ttf", 50);
    label->setAnchorPoint(Vec2::ZERO);
    label->setHorizontalAlignment(TextHAlignment::CENTER);
    label->setPosition(Vec2(0.0f, 580.0f));
    label->setColor(Color3B::BLACK);
    this->addChild(label, 0, "TableLabel");

    PrintIngredients();

    return true;
}

void IngredientLayer::PrintIngredients()
{
    auto IngredientMap = DBManager::getInstance().GetTableMap(TABLE_INGREDIENT);
    auto x = 300.0f;
    auto y = 490.0f;
    std::wstring wstr;
    std::string str;

    int id = 1;

    for (auto& ingredientName : IngredientMap)
    {
        wstr = std::wstring(ingredientName.second);
        str = std::string(wstr.begin(), wstr.end());

        auto label = Label::createWithSystemFont(str, "fonts/MarkerFelt.ttf", 20);
        label->setAnchorPoint(Vec2(0.0f,0.5f));
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
            CC_CALLBACK_1(IngredientLayer::menuCallback, this),
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

void IngredientLayer::menuCallback(cocos2d::Object* sender)
{
    auto item = (MenuItemToggle*)sender;
    auto id = item->getTag();
    auto index = item->getSelectedIndex();

    if (index == selected)
    {
        _selectedIDVec.push_back(item->getTag());
    }
    else if (index == unSelected)
    {
        auto selectedID = std::find(_selectedIDVec.begin(), _selectedIDVec.end(), id);
        if (selectedID != _selectedIDVec.end())
        {
            _selectedIDVec.erase(selectedID);
        }
    }
}

void IngredientLayer::InsertDataToDB()
{
    std::wstring wstr = L"INSERT INTO burgeringredient VALUES(";
    for (auto& ingredientID : _selectedIDVec)
    {
        wstr += std::to_wstring(DBManager::getInstance().GetUserID()) + L",";
        wstr += std::to_wstring(ingredientID) + L")";
        DBManager::getInstance().Excute((SQLWCHAR*)wstr.c_str());
    }
}
