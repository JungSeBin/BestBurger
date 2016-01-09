#include "SauceLayer.h"
#include "DBManager.h"

USING_NS_CC;

bool SauceLayer::init()
{
    if (!LayerColor::initWithColor(Color4B::BLACK))
    {
        return false;
    }

    auto label = Label::createWithSystemFont("싫어하는 소스를 선택해주십시오.", "NanumGothic.ttf", 50);
    label->setAnchorPoint(Vec2::ZERO);
    label->setHorizontalAlignment(TextHAlignment::CENTER);
    label->setPosition(Vec2(0.0f, 580.0f));
    this->addChild(label, 0, "TableLabel");

    return true;
}

void SauceLayer::PrintSauces()
{
    auto SauceMap = DBManager::getInstance().GetTableMap(TABLE_SAUCE);
    auto x = 300.0f;
    auto y = 490.0f;
    std::wstring wstr;
    std::string str;
    for (auto& sauceName : SauceMap)
    {
        wstr = std::wstring(sauceName.second);
        str = std::string(wstr.begin(), wstr.end());

        auto label = Label::createWithSystemFont(str, "fonts/MarkerFelt.ttf", 20);
        label->setAnchorPoint(Vec2(0.5f, 0.5f));
        label->setHorizontalAlignment(TextHAlignment::CENTER);
        label->setPosition(Vec2(x, y));
        this->addChild(label, 0);

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
