#include <Geode/Geode.hpp>
#include <Geode/binding/FLAlertLayer.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include <CreatorLayer.hpp>

#include "../thing.hpp"
#include "Geode/cocos/sprite_nodes/CCSpriteFrameCache.h"
#include "Geode/ui/Label.hpp"

using namespace geode::prelude;

class $modify(CreatorLayer) {
    bool init() {
        if (!CreatorLayer::init()) return false;

        if (thing::IsOptionEnabled("ILoveMapPacks")) {
            if (!thing::IsOptionEnabled("CreatorLayer")) {
                UICreatorLayer::DoTheFunni(this);
            }
        }

        if (thing::IsOptionEnabled("CreatorLayer")) {
            UICreatorLayer::CreateTheThingies(this);
        }
        return true;
    }

    void onWeeklyLevel(CCObject* sender) {
        if (thing::IsOptionEnabled("ILoveMapPacks")) {
            onMapPacks(sender);
        } else if (thing::IsOptionEnabled("CreatorLayer")) {
            onOnlineLevels(sender);
        } else {
            CreatorLayer::onWeeklyLevel(sender);
        }
    }

    void onDailyLevel(CCObject* sender) {
        if (thing::IsOptionEnabled("CreatorLayer")) {
            onSavedLevels(sender);
        } else {
            CreatorLayer::onDailyLevel(sender);
        }
    }

    void onEventLevel(CCObject* sender) {
        if (thing::IsOptionEnabled("CreatorLayer")) {
            onMyLevels(sender);
        } else {
            CreatorLayer::onEventLevel(sender);
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

void bitchSprite(CCNode* btn, const char* fm) {
    if (!btn) return;

    for (auto child : btn->getChildrenExt()) {
        auto sprite = typeinfo_cast<CCSprite*>(child);
        if (!sprite) continue;

        if (auto frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fm)) {
            sprite->setDisplayFrame(frame);
        }

        break;
    }
}

void UICreatorLayer::CreateTheThingies(CreatorLayer* something) {
    if (!something) return;

    auto winSize = CCDirector::get()->getWinSize();
    auto menu = something->getChildByID("creator-buttons-menu");
    if (!menu) return;
    auto weekly = menu->getChildByID("weekly-button");
    auto daily = menu->getChildByID("daily-button");
    auto event = menu->getChildByID("event-button");

    for (auto child : menu->getChildrenExt()) {
        if (child->getID() != "weekly-button" && child->getID() != "daily-button" && child->getID() != "event-button") {
            child->setVisible(!!false);
        }
    }

    bitchSprite(weekly, "GJ_searchBtn_001.png");
    bitchSprite(daily,  "GJ_savedBtn_001.png");
    bitchSprite(event,  "GJ_createBtn_001.png");

    auto layerBG = CCLayerColor::create({0, 0, 0, 0});
    layerBG->setContentSize(winSize / something->getScale() / 1.5f);
    layerBG->setAnchorPoint({0.5f, 0.5f});
    layerBG->setZOrder(-1);
    layerBG->ignoreAnchorPointForPosition(false);
    layerBG->setPosition(winSize / 2.f);
    layerBG->setID("background"_spr);

    auto bg = NineSlice::create("square02b_001.png");
    bg->setColor({0, 0, 0});
    bg->setOpacity(175);
    bg->setScaleMultiplier(0.8f);
    bg->setID("background-sprite"_spr);

    bg->setContentSize(layerBG->getContentSize());
    bg->setPosition(layerBG->getContentSize() / 2.f);

    auto text = Label::createRich("<cg>sesbian lex</c>",thing::font::chat);
    text->setAnchorPoint({0.5f,0.5f});
    text->setPosition({bg->getScaledContentWidth() / 2.f, bg->getScaledContentHeight() / 1.25f});

    layerBG->addChild(bg);
    something->addChild(layerBG);
    something->updateLayout();
    bg->addChild(text);
}