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

    auto ingredientLayer = IngredientLayer::create();
    this->addChild(ingredientLayer, 100, "ingredientLayer");

    auto sauceLayer = SauceLayer::create();
    this->addChild(sauceLayer, 1, "sauceLayer");

    auto tasteLayer = TasteLayer::create();
    this->addChild(tasteLayer, 1, "tasteLayer");

    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(SelectPreferenceScene::menuCallback, this));

    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
        origin.y + closeItem->getContentSize().height / 2));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1000);

    return true;
}

void SelectPreferenceScene::menuCallback(cocos2d::Ref* pSender)
{
    this->getChildByName("sauceLayer")->setZOrder(100);
    this->getChildByName("ingredientLayer")->setZOrder(1);
}
