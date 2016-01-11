#ifndef __BURGERINFO_LAYER_H__
#define __BURGERINFO_LAYER_H__

#include "cocos2d.h"
#include <vector>;


class BurgerInfoLayer : public cocos2d::LayerColor
{
public:
    virtual bool init();

    void GetBurgerInfoFromDB(int id);
    void PrintBurgerInfo();

    void menuCallback1(cocos2d::Ref* sender);
    void menuCalllback2(cocos2d::Ref* sender);

    CREATE_FUNC(BurgerInfoLayer);

private:
    int                      _burgerID;
    std::string              _burgerName;
    std::vector<std::string> _IngredientVec;
    std::vector<std::string> _SauceVec;
    std::vector<std::string> _TasteVec;
    int                      _burgerPrice;
    int                      _burgerKcal;
};

#endif
