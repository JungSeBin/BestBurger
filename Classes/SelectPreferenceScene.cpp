#pragma once
#include "SelectPreferenceScene.h"
#include "IngerdientLayer.h"
#include "SauceLayer.h"
#include "TasteLayer.h"

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

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // layer생성
    auto ingredientLayer = IngredientLayer::create();
    this->addChild(ingredientLayer, 100, "ingredientLayer");

    auto sauceLayer = SauceLayer::create();
    this->addChild(sauceLayer, 1, "sauceLayer");

    auto tasteLayer = TasteLayer::create();
    this->addChild(tasteLayer, 1, "tasteLayer");

    //layer를 선택할 button생성
    auto item1 = MenuItemImage::create("ingredient_unselected.png", "ingredient_unselected.png");
    auto item2 = MenuItemImage::create("ingredient_selected.png", "ingredient_selected.png");
    auto itemToggle1 = MenuItemToggle::createWithCallback(
        CC_CALLBACK_1(SelectPreferenceScene::menuCallback, this),
        item1, item2, NULL);
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

    return true;
}

void SelectPreferenceScene::menuCallback(cocos2d::Object* pSender)
{
    MenuItemToggle* selectedItem = (MenuItemToggle*)pSender;
    MenuItemToggle* anotherItem1;
    MenuItemToggle* anotherItem2;

    auto menu = this->getChildByName("menu");
    auto buttonName = selectedItem->getName();

    IngredientLayer* ingredientLayer = (IngredientLayer*)this->getChildByName("ingredientLayer");

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

        ingredientLayer->InsertDataToDB();
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

void SelectPreferenceScene::menuCallback2()
{

}
