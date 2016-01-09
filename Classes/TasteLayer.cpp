#include "TasteLayer.h"
#include "DBManager.h"

USING_NS_CC;

bool TasteLayer::init()
{
    if (!LayerColor::initWithColor(Color4B::BLACK))
    {
        return false;
    }

    auto label = Label::createWithSystemFont("�Ⱦ��ϴ� ���� �������ֽʽÿ�.", "NanumGothic.ttf", 50);
    label->setAnchorPoint(Vec2::ZERO);
    label->setHorizontalAlignment(TextHAlignment::CENTER);
    label->setPosition(Vec2(0.0f, 580.0f));
    this->addChild(label, 0, "TableLabel");

    return true;
}

void TasteLayer::PrintTastes()
{
    auto TasteMap = DBManager::getInstance().GetTableMap(TABLE_TASTE);
    auto x = 300.0f;
    auto y = 490.0f;
    std::wstring wstr;
    std::string str;
    for (auto& tasteName : TasteMap)
    {
        wstr = std::wstring(tasteName.second);
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
