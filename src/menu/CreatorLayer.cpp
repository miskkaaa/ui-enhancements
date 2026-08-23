#include <Geode/Geode.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include <CreatorLayer.hpp>

#include "../thing.hpp"

using namespace geode::prelude;

class $modify(CreatorLayer) {
    bool init() {
        if (!CreatorLayer::init()) return false;

        if (thing::IsOptionEnabled("ILoveMapPacks")) {
            UICreatorLayer::DoTheFunni(this);
        }

        return true;
    }

    void onWeeklyLevel(CCObject* sender) {
        if (thing::IsOptionEnabled("ILoveMapPacks")) {
            onMapPacks(sender);
        } else {
            CreatorLayer::onWeeklyLevel(sender);
        }
    }
};

void UICreatorLayer::DoTheFunni(CreatorLayer* something) {
    if (!something) return;
    auto menu   = something->getChildByID("creator-buttons-menu");
    // auto bi     = this->getChildByID("cvolton.betterinfo/center-right-menu");
    auto br     = something->getChildByID("bottom-right-menu");
    auto trmenu = something->getChildByID("top-right-menu");
    auto weekly = menu->getChildByID("weekly-button");
    if (!menu)      return;
    if (!weekly)    return;
    // if (!bi)        return true;
    if (!br)        return;
    if (!trmenu)    return;

    // bi->setVisible(false);
    br->setVisible(false);
    trmenu->setVisible(false);

    for (auto child : menu->getChildrenExt()) {
        if (child->getID() != "weekly-button") {
            child->setVisible(false);            
        }
    }

    for (auto child : weekly->getChildrenExt()) {
        auto sprite  = typeinfo_cast<CCSprite*>(child);
        if (sprite) {
            auto frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("GJ_mapPacksBtn_001.png");

            if (frame) {
                sprite->setDisplayFrame(frame);
            }

            break;
        }
    }
}