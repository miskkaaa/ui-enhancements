#include "Geode/cocos/sprite_nodes/CCSpriteBatchNode.h"

#include <Geode/Geode.hpp>
#include <Geode/binding/ListButtonBar.hpp>
#include <Geode/binding/BoomScrollLayer.hpp>
#include <Geode/binding/ExtendedLayer.hpp>
#include <Geode/modify/GJShopLayer.hpp>

#include <alphalaneous.alphas-ui-pack/include/API.hpp>

// TODO: fix https://cdn.discordapp.com/attachments/1496901371444728009/1532784275018092635/image.png

using namespace geode::prelude;
using namespace alpha::prelude;

class $modify(MyShopLayer, GJShopLayer) {
    bool init(ShopType shopType) {
        if (!GJShopLayer::init(shopType))
            return false;

        auto listButtonBar = this->getChildByType<ListButtonBar>(0);
        if (!listButtonBar)
            return true;

        auto boomScrollLayer = listButtonBar->getChildByType<BoomScrollLayer>(0);
        auto menu = listButtonBar->getChildByType<CCMenu>(0);
        auto dots = listButtonBar->getChildByType<CCSpriteBatchNode>(0);

        if (!boomScrollLayer)
            return true;

        auto extendedLayer = boomScrollLayer->getChildByType<ExtendedLayer>(0);
        if (!extendedLayer)
            return true;

        if (menu) {
            menu->setVisible(false);
            menu->setEnabled(false);
        }

        if (dots) {
            dots->setVisible(false);
        }

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

        float x = 0.f;
        float maxHeight = 0.f;
        int count = 0;

        CCArrayExt<CCNode*> childrenExt(extendedLayer->getChildren());
        std::vector<CCNode*> pages(childrenExt.begin(), childrenExt.end());

        for (auto page : pages) {
            if (!page) continue;

            Ref<CCNode> pageRef = page;

            page->removeFromParent();

            page->setAnchorPoint({0.f, 0.f});
            page->setPosition({x, 0.f});

            content->addChild(page);

            x += page->getContentWidth();
            maxHeight = std::max(maxHeight, page->getContentHeight());

            count++;
        }

        content->setContentSize({x, maxHeight});
        scroll->setInnerContentSize({x, maxHeight});

        boomScrollLayer->setVisible(false);
        boomScrollLayer->setTouchEnabled(false);

        listButtonBar->addChild(scroll);

        return true;
    }
};