// #include "Geode/cocos/sprite_nodes/CCSpriteBatchNode.h"

// please dont mind clangd automatically including shit

#include <Geode/Geode.hpp>

/*

im too lazy to make this work

#include <Geode/binding/ListButtonBar.hpp>
#include <Geode/binding/BoomScrollLayer.hpp>
#include <Geode/binding/ExtendedLayer.hpp>
#include <Geode/modify/GJGarageLayer.hpp>

#include <alphalaneous.alphas-ui-pack/include/API.hpp>

using namespace geode::prelude;
using namespace alpha::prelude;

class $modify(MyGarageLayer, GJGarageLayer) {
    bool init() {
        if (!GJGarageLayer::init())
            return false;

        auto listButtonBar = this->getChildByType<ListButtonBar>(0);
        if (!listButtonBar)
            return true;

        auto boomScrollLayer = listButtonBar->getChildByType<BoomScrollLayer>(0);

        auto prevMenu = this->getChildByID("prev-page-menu");
        auto nextMenu = this->getChildByID("next-page-menu");
        auto navDotMenu = this->getChildByID("navdot-menu");

        if (prevMenu) {
            prevMenu->setVisible(false);
        }

        if (nextMenu) {
            nextMenu->setVisible(false);
        }   

        if (navDotMenu) {
            navDotMenu->setVisible(false);
        }

        if (!boomScrollLayer)
            return true;

        auto extendedLayer = boomScrollLayer->getChildByType<ExtendedLayer>(0);
        if (!extendedLayer)
            return true;

        CCSize viewportSize = boomScrollLayer->getContentSize();
        if (viewportSize.width <= 0.f || viewportSize.height <= 0.f) {
            viewportSize = CCDirector::sharedDirector()->getWinSize();
        }

        auto scroll = AdvancedScrollLayer::create(viewportSize);
        scroll->setAnchorPoint({0.f, 0.f});
        scroll->setPosition(boomScrollLayer->getPosition());

        scroll->setHorizontalScroll(true);
        scroll->setVerticalScroll(false);
        scroll->setDraggingEnabled(true);
        scroll->setTouchPriority(-500);

        auto content = scroll->getContentLayer();

        CCArrayExt<CCNode*> childrenExt(extendedLayer->getChildren());
        std::vector<CCNode*> pages(childrenExt.begin(), childrenExt.end());

        for (auto page : pages) {
            if (!page)
                continue;

            page->removeFromParent();
            content->addChild(page);
        }

        // content->updateLayout();

        scroll->setInnerContentSize(content->getContentSize());

        boomScrollLayer->setVisible(false);
        boomScrollLayer->setTouchEnabled(false);

        listButtonBar->addChild(scroll);

        return true;
    }
};

*/