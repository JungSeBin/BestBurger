#include "TasteLayer.h"
#include "DBManager.h"

USING_NS_CC;

static const int unSelected = 0;
static const int selected = 1;

bool TasteLayer::init()
{
    if (!LayerColor::initWithColor(Color4B::WHITE))
    {
        return false;
    }

    auto label = Label::createWithSystemFont("싫어하는 맛을 선택해주십시오.", "NanumGothic.ttf", 50);
    label->setAnchorPoint(Vec2::ZERO);
    label->setHorizontalAlignment(TextHAlignment::CENTER);
    label->setPosition(Vec2(0.0f, 580.0f));
    this->addChild(label, 0, "TableLabel");

    PrintTastes();

    return true;
}

void TasteLayer::PrintTastes()
{
    auto tasteMap = DBManager::getInstance().GetTableMap(TABLE_TASTE);
    auto x = 300.0f;
    auto y = 490.0f;
    std::wstring wstr;
    std::string str;

    int id = 1;

    for (auto& sauceName : tasteMap)
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
            CC_CALLBACK_1(TasteLayer::menuCallback, this),
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

void TasteLayer::menuCallback(cocos2d::Object* sender)
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

void TasteLayer::InsertDataToDB()
{
    int userID = DBManager::getInstance().GetUserID();
    std::wstring wstr;
    for (auto& tasteID : _SelectedIDVec)
    {
        wstr = L"INSERT INTO disliketaste VALUES(";
        wstr += std::to_wstring(userID) + L",";
        wstr += std::to_wstring(tasteID) + L")";
        DBManager::getInstance().Excute((SQLWCHAR*)wstr.c_str());
    }
}
