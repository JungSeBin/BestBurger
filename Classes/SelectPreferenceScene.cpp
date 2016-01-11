#pragma once
#include "SelectPreferenceScene.h"
#include "SelectBurgerScene.h"
#include "IngerdientLayer.h"
#include "SauceLayer.h"
#include "TasteLayer.h"
#include "InputBox.h"
#include "DBManager.h"

USING_NS_CC;

Scene* SelectPreferenceScene::createScene()
{
    auto scene = Scene::create();

    auto layer = SelectPreferenceScene::create();

    scene->addChild(layer);

    return scene;
}

bool SelectPreferenceScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto winSize = Director::getInstance()->getWinSize();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // layer생성
    auto ingredientLayer = IngredientLayer::create();
    this->addChild(ingredientLayer, 100, "ingredientLayer");

    auto sauceLayer = SauceLayer::create();
    this->addChild(sauceLayer, 0, "sauceLayer");

    auto tasteLayer = TasteLayer::create();
    this->addChild(tasteLayer, 0, "tasteLayer");

    //layer를 선택할 button생성
    auto item1 = MenuItemImage::create("ingredient_unselected.png", "ingredient_unselected.png");
    auto item2 = MenuItemImage::create("ingredient_selected.png", "ingredient_selected.png");
    auto itemToggle1 = MenuItemToggle::createWithCallback(
        CC_CALLBACK_1(SelectPreferenceScene::menuCallback, this),
        item1, item2, NULL);
    itemToggle1->setSelectedIndex(1);
    itemToggle1->setName("ingredientButton");

    auto item3 = MenuItemImage::create("sauce_unselected.png", "sauce_unselected.png");
    auto item4 = MenuItemImage::create("sauce_selected.png", "sauce_selected.png");
    auto itemToggle2 = MenuItemToggle::createWithCallback(
        CC_CALLBACK_1(SelectPreferenceScene::menuCallback, this),
        item3, item4, NULL);
    itemToggle2->setName("sauceButton");

    auto item5 = MenuItemImage::create("taste_unselected.png", "taste_unselected.png");
    auto item6 = MenuItemImage::create("taste_selected.png", "taste_selected.png");
    auto itemToggle3 = MenuItemToggle::createWithCallback(
        CC_CALLBACK_1(SelectPreferenceScene::menuCallback, this),
        item5, item6, NULL);
    itemToggle3->setName("tasteButton");

    auto menu = Menu::create(itemToggle1, itemToggle2, itemToggle3, NULL);
    menu->alignItemsHorizontallyWithPadding(50.0f);
    menu->setPosition(Vec2(200.0f, 590.0f));
    this->addChild(menu, 1000, "menu");

    //정보를 받을 box생성
    auto priceBox = MenuItemImage::create(
        "loginField.png",
        "loginField.png",
        CC_CALLBACK_1(SelectPreferenceScene::menuCallback3, this));

    auto priceMenu1 = Menu::create(priceBox, NULL);
    priceMenu1->setAnchorPoint(Vec2(0.5f, 0.5f));
    priceMenu1->setPosition(Vec2(800.0f, visibleSize.height / 2));
    this->addChild(priceMenu1, 1000);

    _PriceBox = InputBox::create("최대 허용 가격입력", "NanumGothic.ttf", 9);
    _PriceBox->setAnchorPoint(Vec2(0.5f, 0.5f));
    _PriceBox->setPosition(Vec2(150.0f, 40.0f));
    _PriceBox->setColor(Color3B::BLACK);
    _PriceBox->setFontSize(20);
    priceBox->addChild(_PriceBox);

    auto kcalBox = MenuItemImage::create(
        "loginField.png",
        "loginField.png",
        CC_CALLBACK_1(SelectPreferenceScene::menuCallback4, this));

    auto kcalMenu1 = Menu::create(kcalBox, NULL);
    kcalMenu1->setAnchorPoint(Vec2(0.5f, 0.5f));
    kcalMenu1->setPosition(Vec2(800.0f, visibleSize.height / 4));
    this->addChild(kcalMenu1, 1000);

    _KcalBox = InputBox::create("최대 허용 Kcal입력", "NanumGothic.ttf", 9);
    _KcalBox->setAnchorPoint(Vec2(0.5f, 0.5f));
    _KcalBox->setPosition(Vec2(150.0f, 40.0f));                               
    _KcalBox->setColor(Color3B::BLACK);
    _KcalBox->setFontSize(20);
    kcalBox->addChild(_KcalBox);

    //선택완료 버튼
    auto selectButton = MenuItemImage::create(
        "selectButton.png",
        "selectButton_selected.png",
        CC_CALLBACK_1(SelectPreferenceScene::menuCallback2, this));

    auto selectMenu = Menu::create(selectButton, NULL);
    selectMenu->setAnchorPoint(Vec2(0.5f, 0.5f));
    selectMenu->setPosition(Vec2(800.0f, 550.0f));
    this->addChild(selectMenu, 1000);
    return true;
}

void SelectPreferenceScene::menuCallback(cocos2d::Object* pSender)
{
    MenuItemToggle* selectedItem = (MenuItemToggle*)pSender;
    MenuItemToggle* anotherItem1;
    MenuItemToggle* anotherItem2;

    auto menu = this->getChildByName("menu");
    auto buttonName = selectedItem->getName();

    if (buttonName == "ingredientButton")
    {
        anotherItem1 = (MenuItemToggle*)menu->getChildByName("sauceButton");
        anotherItem2 = (MenuItemToggle*)menu->getChildByName("tasteButton");
        this->getChildByName("ingredientLayer")->setZOrder(100);
        this->getChildByName("sauceLayer")->setZOrder(0);
        this->getChildByName("tasteLayer")->setZOrder(0);
    }
    else if (buttonName == "sauceButton")
    {
        anotherItem1 = (MenuItemToggle*)menu->getChildByName("ingredientButton");
        anotherItem2 = (MenuItemToggle*)menu->getChildByName("tasteButton");
        this->getChildByName("ingredientLayer")->setZOrder(0);
        this->getChildByName("sauceLayer")->setZOrder(100);
        this->getChildByName("tasteLayer")->setZOrder(0);
    }
    else
    {
        anotherItem1 = (MenuItemToggle*)menu->getChildByName("ingredientButton");
        anotherItem2 = (MenuItemToggle*)menu->getChildByName("sauceButton");
        this->getChildByName("ingredientLayer")->setZOrder(0);
        this->getChildByName("sauceLayer")->setZOrder(0);
        this->getChildByName("tasteLayer")->setZOrder(100);
    }

    //선택된 item은 선택된 이미지로 출력, 나머지는 unselected
    selectedItem->setSelectedIndex(1);
    anotherItem1->setSelectedIndex(0);
    anotherItem2->setSelectedIndex(0);
}

void SelectPreferenceScene::menuCallback2(cocos2d::Ref* sender)
{
    IngredientLayer* ingredientLayer = (IngredientLayer*)this->getChildByName("ingredientLayer");
    SauceLayer* sauceLayer = (SauceLayer*)this->getChildByName("sauceLayer");
    TasteLayer* tasteLayer = (TasteLayer*)this->getChildByName("tasteLayer");
   
    UpdateUserPreference();
    ingredientLayer->InsertDataToDB();
    sauceLayer->InsertDataToDB();
    tasteLayer->InsertDataToDB();

    DBManager::getInstance().SelectBurgerByUserInfo();
    Director::getInstance()->replaceScene(SelectBurgerScene::createScene());
}

void SelectPreferenceScene::UpdateUserPreference()
{
    std::string maxPrice = _PriceBox->getString();
    if (!IsNumber(maxPrice))
    {
        return;
    }
    std::string maxKcal = _KcalBox->getString();
    if (!IsNumber(maxKcal))
    {
        return;
    }
    std::wstring wPrice = std::wstring(maxPrice.begin(), maxPrice.end());
    std::wstring wKcal = std::wstring(maxKcal.begin(), maxKcal.end());
    int id = DBManager::getInstance().GetUserID();

    std::wstring query = L"UPDATE user_preference SET ";
    query += L"maxPrice = " + wPrice + L",";
    query += L"maxKcal = " + wKcal;
    query += L" WHERE user_id = " + std::to_wstring(id);

    DBManager::getInstance().Excute((SQLWCHAR*)query.c_str());
}

void SelectPreferenceScene::menuCallback3(cocos2d::Ref* sender)
{
    _PriceBox->clear();
    _PriceBox->beginInput();
}

void SelectPreferenceScene::menuCallback4(cocos2d::Ref* sender)
{
    _KcalBox->clear();
    _KcalBox->beginInput();
}

bool SelectPreferenceScene::IsNumber(std::string num)
{
    if (num.size() <= 0)
    {
        return false;
    }
    for (auto& letter : num)
    {
        if (letter < '0' || letter > '9')
        {
            return false;
        }
    }
}