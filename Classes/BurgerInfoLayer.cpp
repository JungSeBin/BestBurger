#include "BurgerInfoLayer.h"
#include "DBManager.h"

USING_NS_CC;

bool BurgerInfoLayer::init()
{
    if (!LayerColor::initWithColor(Color4B::WHITE))
    {
        return false;
    }

    return true;
}

void BurgerInfoLayer::GetBurgerInfoFromDB(int id)
{
    _burgerID = id;
    auto wcharName = DBManager::getInstance().GetBurgerName(id);
    std::wstring wstr = std::wstring(wcharName);
    _burgerName = std::string(wstr.begin(), wstr.end());
    _burgerPrice = DBManager::getInstance().GetBurgerPrice(id);
    _burgerKcal = DBManager::getInstance().GetBurgerKcal(id);
    _IngredientVec = DBManager::getInstance().GetBurgerInfo(id, TABLE_INGREDIENT);
    _SauceVec = DBManager::getInstance().GetBurgerInfo(id, TABLE_SAUCE);
    _TasteVec = DBManager::getInstance().GetBurgerInfo(id, TABLE_TASTE);
}

void BurgerInfoLayer::PrintBurgerInfo()
{
    this->removeAllChildren();

    auto backItem = MenuItemImage::create("backButton.png",
        "backButton_selected.png",
        CC_CALLBACK_1(BurgerInfoLayer::menuCallback1,this));
    backItem->setAnchorPoint(Vec2(0.5f, 0.5f));
    auto decideItem = MenuItemImage::create("decideButton.png",
        "decideButton_selected.png",
        CC_CALLBACK_1(BurgerInfoLayer::menuCalllback2,this));
    decideItem->setAnchorPoint(Vec2(0.5f, 0.5f));

    auto menu = Menu::create(decideItem, backItem, NULL);
    menu->alignItemsVerticallyWithPadding(50.0f);
    menu->setPosition(Vec2(850.0f, 200.0f));
    this->addChild(menu);

    auto title1 = Label::createWithSystemFont("ÀÌ¸§: ", "NanumGothic.ttf", 35);
    title1->setPosition(Vec2(400.0f, 600.0f));
    title1->setColor(Color3B::BLACK);
    this->addChild(title1);

    auto label = Label::create(_burgerName, "fonts/MarkerFelt.ttf", 35);
    label->setAnchorPoint(Vec2(0.0f, 0.5f));
    label->setColor(Color3B::BLACK);
    label->setPosition(Vec2(500.0f, 600.0f));

    this->addChild(label);

    auto posX = 220.0f;
    auto posY = 550.0f;

    auto title2 = Label::createWithSystemFont("Àç·á", "NanumGothic.ttf", 30);
    title2->setPosition(Vec2(posX, posY));
    title2->setColor(Color3B::BLACK);
    this->addChild(title2);
    for (auto& ingredient : _IngredientVec)
    {
        posY -= 70.f;
        auto label2 = Label::create(ingredient, "fonts/MarkerFelt.ttf", 25);
        label2->setColor(Color3B::BLACK);
        label2->setPosition(Vec2(posX, posY));

        this->addChild(label2);
    }

    posX += 250.0f;
    posY = 550.0f;
    auto title3 = Label::createWithSystemFont("¼Ò½º", "NanumGothic.ttf", 30);
    title3->setPosition(Vec2(posX, posY));
    title3->setColor(Color3B::BLACK);
    this->addChild(title3);
    for (auto& sauce : _SauceVec)
    {
        posY -= 70.f;
        auto label3 = Label::create(sauce, "fonts/MarkerFelt.ttf", 25);
        label3->setColor(Color3B::BLACK);
        label3->setPosition(Vec2(posX, posY));

        this->addChild(label3);
    }

    posX += 250.0f;
    posY = 550.0f;
    auto title4 = Label::createWithSystemFont("¸À", "NanumGothic.ttf", 30);
    title4->setPosition(Vec2(posX, posY));
    title4->setColor(Color3B::BLACK);
    this->addChild(title4);
    for (auto& taste : _TasteVec)
    {
        posY -= 70.f;
        auto label4 = Label::create(taste, "fonts/MarkerFelt.ttf", 25);
        label4->setColor(Color3B::BLACK);
        label4->setPosition(Vec2(posX, posY));

        this->addChild(label4);
    }

    auto title5 = Label::createWithSystemFont("°¡°İ: ", "NanumGothic.ttf", 30);
    title5->setPosition(Vec2(200.0f, 50.0f));
    title5->setColor(Color3B::BLACK);
    this->addChild(title5);

    auto label5 = Label::create(std::to_string(_burgerPrice), "fonts/MarkerFelt.ttf", 25);
    label5->setPosition(Vec2(280.0f, 50.0f));
    label5->setColor(Color3B::BLACK);
    this->addChild(label5);

    auto title6 = Label::createWithSystemFont("Ä®·Î¸®: ", "NanumGothic.ttf", 30);
    title6->setPosition(Vec2(450.0f, 50.0f));
    title6->setColor(Color3B::BLACK);
    this->addChild(title6);

    auto label6 = Label::create(std::to_string(_burgerKcal) + " Kcal", "fonts/MarkerFelt.ttf", 25);
    label6->setPosition(Vec2(550.0f, 50.0f));
    label6->setColor(Color3B::BLACK);
    this->addChild(label6);
}

void BurgerInfoLayer::menuCallback1(cocos2d::Ref* sender)
{
    this->setZOrder(-1);
}

void BurgerInfoLayer::menuCalllback2(cocos2d::Ref* sender)
{
    this->removeAllChildren();
    
    DBManager::getInstance().DecideBurgerToDB(_burgerID);
    Director::getInstance()->end();
}
