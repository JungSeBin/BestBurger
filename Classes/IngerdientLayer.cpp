#include "IngerdientLayer.h"
#include "DBManager.h"

USING_NS_CC;

bool IngredientLayer::init()
{
    if (!LayerColor::initWithColor(Color4B::BLACK))
    {
        return false;
    }

    auto label = Label::createWithSystemFont("�Ⱦ��ϴ� ��Ḧ �������ֽʽÿ�.", "NanumGothic.ttf", 50);
    label->setAnchorPoint(Vec2::ZERO);
    label->setHorizontalAlignment(TextHAlignment::CENTER);
    label->setPosition(Vec2(0.0f, 580.0f));
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
    for (auto& ingredientName : IngredientMap)
    {
        wstr = std::wstring(ingredientName.second);
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
